#pragma once
#include <WinSock2.h>
class TSOCKET {
public:
  TSOCKET() = delete;
  ~TSOCKET();
  TSOCKET(int port, char *addr, int type, int proto, char* uri = nullptr);
  unsigned long checksum(unsigned char *packet, int count);

  int ListenAsServer() = delete;
  void ConnectAsClient();
  int Send(char *buff, size_t size);
  int Recv();
  const char* GetBuff();
  int GetBuffSize();

private:
    int _port, _type, _proto;
    char *_addr, *_uri;
    SOCKET client, server;
    SOCKADDR_IN servsa;
    IN_ADDR servia;
    HOSTENT *hst;
    char _buff[1024*10]{};
    int _recvlen;
};
