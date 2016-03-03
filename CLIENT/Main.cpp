#define _CRT_SECURE_NO_WARNINGS
#include "TSOCKCLIENT.h"
#include <algorithm>
#include <iostream>

bool decrypt(char* dest, const char* source, uintptr_t len) {
  if (dest == nullptr || source == nullptr || len < 2)
    return false;

  for (size_t i = 0, k = -1; i < len; ++i) {
    if (source[i] < 0) {
      size_t repeat = -1 * source[i];
      for (size_t j = 0; j < repeat; ++j) {
        dest[++k] = source[++i];
      }
    }
    else {
      size_t repeat = source[i++];
      for (size_t j = 0; j < repeat; ++j) {
        dest[++k] = source[i];
      }
    }
  }
  return true;
}

bool encrypt(char* dest, const char* source, uintptr_t len) {

  if (dest == nullptr || source == nullptr || len < 2)
    return false;

  enum EHASH {
    REPEAT,
    ONE,
    BYTE = ONE
  };

  char **hash = new(std::nothrow) char*[len];
  if (hash == nullptr)
    return false;

  for (size_t i = 0; i < len; ++i) {
    hash[i] = new char[2];
  }

  // make hash from abcddd to 1a1b1c3d
  char chf = 0;
  unsigned char some = 1;
  size_t hashLen = 0;
  for (size_t i = 0; i < len; ++i) {
    if (!i) {
      chf = source[i];
    }
    else {
      if (chf == source[i] && some < 128)
        ++some;
      else
      {
        hash[hashLen][EHASH::REPEAT] = some;
        hash[hashLen][EHASH::BYTE] = chf;
        chf = source[i];
        ++hashLen;
        some = 1;
      }
      if (i == len - 1) {
        if (chf != source[i - 1])
          hash[hashLen][EHASH::REPEAT] = EHASH::ONE;
        else
          hash[hashLen][EHASH::REPEAT] = some;
        hash[hashLen][EHASH::BYTE] = chf;
      }
    }
  }

#ifdef _DEBUGs
  for (size_t i = 0, j = 0; i < (hashLen + 1) * 2; i += 2, ++j)
    dest[i] = hash[j][EHASH::REPEAT],
    dest[i + 1] = hash[j][EHASH::BYTE];
#else
  // pack hash, make hash from -1a-1b-1c3d to -3abc3d
  size_t nOnes = 0;
  for (size_t i = 0, j = 0, k = 0; i < hashLen + 1; ++i) {
    if (hash[i][EHASH::REPEAT] == EHASH::ONE && nOnes <= 128) {
      ++nOnes;
    }
    else {
      if (nOnes) {
        dest[k++] = (unsigned char)nOnes * -1;
        for (size_t ii = nOnes; ii > 0; --ii) {
          dest[k++] = hash[i - ii][EHASH::BYTE];
        }
      }
      if (hash[i][EHASH::REPEAT] > EHASH::ONE)
      {
        dest[k++] = (unsigned char)hash[i][EHASH::REPEAT];
        dest[k++] = hash[i][EHASH::BYTE];
      }
      nOnes = 0;
    }
    if (i == hashLen) {
      if (nOnes) {
        dest[k++] = (unsigned char)nOnes * -1;
        for (size_t ii = nOnes - 1; ii > 0; --ii) {
          dest[k++] = hash[i - ii][EHASH::BYTE];
        }
        dest[k] = hash[i][EHASH::BYTE];
      }
      else if (hash[i][EHASH::REPEAT] == EHASH::ONE) {
        dest[k++] = -1 * hash[i][EHASH::REPEAT];
        dest[k] = hash[i][EHASH::BYTE];
      }
    }
  }
#endif

  delete[]hash;
  return true;
}

int main(int argc, char **argv) {
  using namespace std;
  // lineageclassic.ru
  // GS: 89.108.86.149 7777
  // LS: 89.108.87.58 2106
  // l2classic.club
  // 
  // LS: 92.222.249.228 2106
  TSOCKCLIENT x(2106, "92.222.249.228", SOCK_STREAM, IPPROTO_TCP, nullptr);
  x.Connect();
  //Init -> from server
  //Формат для ревизии протокола 0x785a : (для ревизии 785a он составляет 11 байт, для c621 – 170)
  //00
  //XX XX XX XX	// ID сессии
  //XX XX XX XX	// Версия протокола 0x785a
  std::cout << x.Recv() << std::endl;
  //std::cout << x.GetBuff() << std::endl;
  //RequestGGAuth -> to server
  //07
  //XX XX XX XX		// ID сессии
  //XX XX XX XX		// неизвестно
  //XX XX XX XX		// неизвестно
  //XX XX XX XX		// неизвестно
  //XX XX XX XX		// неизвестно
  /*x.SetCurrPos(0);
  x.SetBuffer(0x07, 1);
  x.Send(x.GetBuff(), 21);*/
  //GGAuth
  //0B - success
  //XX XX XX XX
  //x.Recv();
  std::cout << "server GGAuth status: " << std::hex << *(unsigned short*)x.GetBuff() << std::endl;

#ifdef _NBLOCKED
#define SIO_RCVALL 0x98000001 //promiscuous
  unsigned long fl = 1;
  ioctlsocket(x.GetServerSocket(), FIONBIO, &fl);
  std::cout << "socket change to non-block\n";
  while (x.Recv() == WSAEWOULDBLOCK);
#endif
  fd_set read;
  FD_ZERO(&read);
  FD_SET(x.GetServerSocket(), &read);
  timeval sec{ 1 };
  if (select(x.GetServerSocket() + 1, &read, nullptr, nullptr, &sec) > 0)
    if (x.Recv()>0) {
      std::cout << *(unsigned short*)x.GetBuff() << std::endl;
      std::cout << x.GetBuffSize() << std::endl;
    }
  std::cin.get();
  return 0;
  char buff[1024]{ "\x1\x0\x2\x2" };
  //for (size_t i = 0; i < 257; ++i)
  //buff[i] = 'a';
  char en[1024]{};
  memset(buff, 0, 1024);
  strcpy(en, "\xF9[p,moju\3g\xFCnhdb\2s\xFDvgf");
  decrypt(buff, en, strlen(en));
  std::cout << en << std::endl;
  std::cout << en << std::endl;
  encrypt(en, buff, strlen(buff));
  std::cout << buff << std::endl;
  std::cout << en << std::endl;
  std::cin.get();
  return 0;
}
