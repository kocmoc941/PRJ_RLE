//#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "TSOCKET.h"
#include <stdexcept>
#include <sstream>
#include <windows.h>
#include <assert.h>
#include <WS2tcpip.h>
#include <iostream>

TSOCKCLIENT::TSOCKCLIENT(int port, char *addr, int type, int proto, char* uri) try :_port(port), _type(type), _proto(proto), _addr(addr), _uri(uri) {
  assert(!(WSAStartup(MAKEWORD(2, 2), &WSADATA()) == SOCKET_ERROR));
  server = socket(AF_INET, type, proto);

  IN_ADDR ia;
  if (_uri) {
    PADDRINFOA res = nullptr;
    addrinfo hint{};
    if (!getaddrinfo(_uri, nullptr, &hint/*nullptr*/, &res)) {
      //HOSTENT *hst = gethostbyname(_uri);
      //ia.s_addr = ((IN_ADDR*)hst->h_addr_list[0])->s_addr;
      ia.s_addr = ((sockaddr_in*)res->ai_addr)->sin_addr.s_addr;
      char hostname[NI_MAXHOST]{};
      if (!getnameinfo(res->ai_addr, res->ai_addrlen, hostname, NI_MAXHOST, nullptr, 0, 0))
        std::cout << hostname << std::endl;
      freeaddrinfo(res);
    }
  }
  ULONG add = 0;
  if (inet_pton(AF_INET, addr, &add)) {
    servsa.sin_addr.s_addr = _uri ? ia.s_addr : add;
  }
  //servsa.sin_addr.s_addr = _uri ? ia.s_addr : inet_addr(addr);
  servsa.sin_family = AF_INET;
  servsa.sin_port = htons(port);
}

catch (std::runtime_error&e) {
  std::stringstream str("GetLastError: ");
  str << GetLastError() << std::endl;
  str << e.what();
}

TSOCKCLIENT::~TSOCKCLIENT() {
  assert(!(shutdown(server, SD_BOTH) == SOCKET_ERROR));
  assert(!(closesocket(server) == SOCKET_ERROR));
  assert(!(WSACleanup() == SOCKET_ERROR));
}

unsigned long TSOCKCLIENT::checksum(unsigned char *packet, int count)
{
  long chksum = 0L;
  for (int i = 0; i < count; i += 4) chksum ^= *((unsigned long *)&packet[i]);
  return chksum;
}

void TSOCKCLIENT::Connect() {
  //assert(!(bind(server, (sockaddr*)&servsa, sizeof(servsa)) == SOCKET_ERROR));
  /*assert*/if (connect(server, (sockaddr*)&servsa, sizeof(servsa)) == SOCKET_ERROR) {
    std::cout << GetLastError();
  }
}

int TSOCKCLIENT::Send(char *buff, size_t size) {
  return sendto(server, buff, size, 0, (sockaddr*)&servsa, sizeof(servsa));
}

int TSOCKCLIENT::Recv() {
  _recvlen = 0;
  memset(_buff, 0, sizeof(_buff));
  return _recvlen = recvfrom(server, _buff, (unsigned short)~0, 0, (sockaddr*)&servsa, (int*)sizeof(servsa));
}

const char* TSOCKCLIENT::GetBuff() {
  return _buff;
}

int TSOCKCLIENT::GetBuffSize() {
  return _recvlen;
}
