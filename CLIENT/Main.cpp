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
  char * LS = true ? "89.108.87.58" : "92.222.249.228";
  TSOCKCLIENT x(2106, LS, SOCK_STREAM, IPPROTO_TCP, nullptr);
  x.Connect();
  //Init -> from server
  //������ ��� ������� ��������� 0x785a : (��� ������� 785a �� ���������� 11 ����, ��� c621 � 170)
  //00
  //XX XX XX XX	// ID ������
  //XX XX XX XX	// ������ ��������� 0x785a
  std::cout << x.Recv(2) << std::endl;
  std::cout << "packet size: " << *(short*)x.GetBuff() << std::endl;
  std::cout << x.Recv(*(short*)x.GetBuff());
  std::cout << "read packet bytes: " << x.GetBuffSize() << std::endl;
  std::cout << "read packet bytes: " << x.GetRecvSize() << std::endl;
  std::cout << "read packet bytes: " << *(short*)x.GetBuff() << std::endl;
  //RequestGGAuth -> to server
  //07
  //XX XX XX XX		// ID ������
  //XX XX XX XX		// ����������
  //XX XX XX XX		// ����������
  //XX XX XX XX		// ����������
  //XX XX XX XX		// ����������
  /*x.SetCurrPos(0);
  x.SetBuffer(0x07, 1);
  x.Send(x.GetBuff(), 21);*/
  //GGAuth
  //0B - success
  //XX XX XX XX
  //x.Recv();
  USHORT sh = *(unsigned short*)x.GetBuff();
  std::cout << "server GGAuth status: " << sh << std::endl;
  std::cin.get();
  return 0;
}
