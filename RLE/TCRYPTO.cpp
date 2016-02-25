#include "TCRYPTO.h"

TCRYPTO::TCRYPTO() {

}

void TCRYPTO::Init() {

}

void TCRYPTO::Encrypt(unsigned char *data, unsigned int len, unsigned char *Key) {
  int temp = 0;

  for (unsigned int i = 0; i < len; i++) {
    int temp2 = data[i] & 0xff;
    data[i] = (temp2 ^ (Key[i & 15] & 0xff) ^ temp);
    temp = data[i];
  };

  int old = Key[8] & 0xff;
  old |= (Key[9] << 0x08) & 0xff00;
  old |= (Key[10] << 0x10) & 0xff0000;
  old |= (Key[11] << 0x18) & 0xff000000;

  old += len;

  Key[8] = old & 0xff;
  Key[9] = (old >> 0x08) & 0xff;
  Key[10] = (old >> 0x10) & 0xff;
  Key[11] = (old >> 0x18) & 0xff;
}

void TCRYPTO::Decrypt(unsigned char *data, unsigned int len, unsigned char *Key) {

  int temp = 0;

  for (unsigned int i = 0; i < len; ++i) {
    int temp2 = data[i] & 0xff;
    data[i] = (temp2 ^ (Key[i & 15] & 0xff) ^ temp);
    temp = temp2;
  };



  int old = Key[8] & 0xff;
  old |= (Key[9] << 0x08) & 0xff00;
  old |= (Key[10] << 0x10) & 0xff0000;
  old |= (Key[11] << 0x18) & 0xff000000;

  old += len;

  Key[8] = old & 0xff;
  Key[9] = (old >> 0x08) & 0xff;
  Key[10] = (old >> 0x10) & 0xff;
  Key[11] = (old >> 0x18) & 0xff;
}
