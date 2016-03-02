#pragma once
#pragma once
#include <WinSock2.h>
class TSOCKCLIENT {
public:
  TSOCKCLIENT() = delete;
  ~TSOCKCLIENT();
  TSOCKCLIENT(int port, char *addr, int type, int proto, char* uri = nullptr);
  unsigned long checksum(unsigned char *packet, int count);

  void Connect();
  int Send(char *buff, size_t size);
  int Recv();
  const char* GetBuff();
  int GetBuffSize();

  //#ifdef __DEBUG
  SOCKET GetServerSocket() {
    return server;
  }
  //#endif

private:
  int _port, _type, _proto;
  char *_addr, *_uri;
  SOCKET client, server;
  SOCKADDR_IN servsa;
  IN_ADDR servia;
  HOSTENT *hst;
  char _buff[(unsigned short)~0]{};
  int _recvlen;
};
