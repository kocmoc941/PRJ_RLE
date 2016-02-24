#pragma once

#include <iostream>

class TCRYPTO
{
public:
  TCRYPTO();

private:
  void Init();
  void Encrypt();
  void Decrypt();
  template<typename T>
  T&& TCRYPTO::getSizeOf(T type);

public:
  template<typename T>
  T&& LOWORD(T val);

  template<typename T>
  T&& HIWORD(T val);
};

template<typename T>
T&& TCRYPTO::getSizeOf(T type) {
  #define isSomeType(a,b) typeid(a) == typeid(b)
  T size = 0;
  if (isSomeType(T, unsigned short) ||
    isSomeType(T, unsigned short) || isSomeType(T, short) ||
    isSomeType(T, unsigned int) || isSomeType(T, int) ||
    isSomeType(T, unsigned long) || isSomeType(T, long) ||
    isSomeType(T, unsigned long long) || isSomeType(T, long long))
    size = (sizeof(T) * 8) / 2;
  else
    return -1;
  return std::move(size);
}

template<typename T>
T&& TCRYPTO::LOWORD(T val) {
  size_t size = getSizeOf(val);
  return std::move(val << size >> size);
}

template<typename T>
T&& TCRYPTO::HIWORD(T val) {
  T size = getSizeOf(val);
  return std::move(val >> size << size);
}
