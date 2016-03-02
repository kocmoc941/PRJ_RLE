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
  int Send(const char *buff, size_t size);
  int Send();
  int Recv();
  const char* GetBuff();
  int GetBuffSize();
  int GetRecvSize();
  template<typename V, typename ...T>
  void SetBuffer(V&& value, T&&... arg);
  template<typename V>
  void SetBuffer(V&& value);
  template<typename V>
  void SetBufferMass(V* value, size_t size);
  void ResetBuffer();

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
  HOSTENT *hst = nullptr;
  char _buff[(unsigned short)~0]{};
  size_t _currbuffsize = 0;
  int _recvlen = 0;
};

template<typename V>
void TSOCKCLIENT::SetBuffer(V&& value) {
  _buff[_currbuffsize++] = *(char*)&value;
}

template<typename V, typename ...T>
void TSOCKCLIENT::SetBuffer(V&& value, T&&... arg) {
  _buff[_currbuffsize++] = *(char*)&value;
  SetBuffer(arg...);
}

template<typename V>
void TSOCKCLIENT::SetBufferMass(V* value, size_t size) {
  for (size_t i = 0; i < size; ++i)
    _buff[i] = value[i];
  _currbuffsize = size;
}
