#include "TSOCKET.h"
#include <stdexcept>
#include <sstream>
#include <windows.h>
#include <assert.h>
#include <WS2tcpip.h>

TSOCKET::TSOCKET(int port, char *addr, int type, int proto, char* uri) try:_port(port), _type(type), _proto(proto), _addr(addr), _uri(uri) {
  assert( !(WSAStartup(MAKEWORD(2, 2), &WSADATA()) == SOCKET_ERROR) );
  server = socket(AF_INET, type, proto);
  char add[1024];
  
  IN_ADDR ia;
  if (_uri) {
    HOSTENT *hst = gethostbyname(_uri);
    ia = ((sockaddr_in*)hst->h_addr_list[0])->sin_addr;
  }

  servsa.sin_addr.s_addr = inet_pton(AF_INET, addr, add);
  servsa.sin_addr.s_addr = _uri ? ia.s_addr : inet_addr(addr);
  servsa.sin_family = AF_INET;
  servsa.sin_port = htons(port);
}

catch (std::runtime_error&e) {
  std::stringstream str("GetLastError: ");
  str << GetLastError() << std::endl;
  str << e.what();
}

TSOCKET::~TSOCKET() {
  assert( !(WSACleanup() == SOCKET_ERROR) );
}

unsigned long TSOCKET::checksum(unsigned char *packet, int count)
{
  long chksum = 0L;
  for (int i = 0; i < count; i += 4) chksum ^= *((unsigned long *)&packet[i]);
  return chksum;
}

void TSOCKET::ConnectAsClient() {
  //assert(!(bind(server, (sockaddr*)&servsa, sizeof(servsa)) == SOCKET_ERROR));
  assert(!(connect(server, (sockaddr*)&servsa, sizeof(servsa)) == SOCKET_ERROR));
}

int TSOCKET::Send(char *buff, size_t size) {
  return sendto(server, buff, size, 0, (sockaddr*)&servsa, sizeof(servsa));
}

int TSOCKET::Recv() {
  _recvlen = 0;
  return _recvlen = recvfrom(server, _buff, sizeof(_buff), 0, (sockaddr*)&servsa, (int*)sizeof(servsa));
}

const char* TSOCKET::GetBuff() {
  return _buff;
}

int TSOCKET::GetBuffSize() {
  return _recvlen;
}
