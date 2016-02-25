#pragma once

#include <iostream>

class TCRYPTO
{
public:
  TCRYPTO();

private:
  void Init();
  void Encrypt(unsigned char *data, unsigned int len, unsigned char *Key);
  void Decrypt(unsigned char *data, unsigned int len, unsigned char *Key);

public:
  template<typename T>
  void ReverseBytes(T* a, size_t len);

  template<typename T, size_t size = sizeof(T) * 8 / 2>
  T&& LOWORD(T val);

  template<typename T, size_t size = sizeof(T) * 8 / 2>
  T&& HIWORD(T val);

  template<typename T, size_t size = sizeof(T) * 8 / 2>
  void SwapBites(T& a);
};

template<typename T, size_t size>
T&& TCRYPTO::LOWORD(T val) {
  return std::move((val <<= size) >>= size);
}

template<typename T, size_t size>
T&& TCRYPTO::HIWORD(T val) {
  return std::move(val >>= size);
}

template<typename T, size_t size>
void TCRYPTO::SwapBites(T& a) {
  a = (a >> size) + (a << size);
}

template<typename T>
void TCRYPTO::ReverseBytes(T* a, size_t len) {
  std::reverse(a, a + len);
}
