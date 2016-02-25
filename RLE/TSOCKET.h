#pragma once
#include <WinSock2.h>
class TSOCKET {
public:
  TSOCKET() = delete;
  ~TSOCKET();
  TSOCKET(int port, char *addr, int type, int proto);
  unsigned long checksum(unsigned char *packet, int count);

  int ListenAsServer() = delete;
  void ConnectAsClient();
  int Send(char *buff, size_t size);
  int Recv();
  const char* GetBuff();
  int GetBuffSize();

private:
    int _port, _type, _proto;
    char *_addr;
    SOCKET client, server;
    SOCKADDR_IN servsa;
    IN_ADDR servia;
    HOSTENT *hst;
    char _buff[1024]{};
    int _recvlen;
};
