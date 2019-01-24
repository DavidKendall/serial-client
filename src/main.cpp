#include <mbed.h>
#include <stdbool.h>
#include <assert.h>
#include "counter.h"

UARTSerial client(D1, D0, 115200);
Serial pc(USBTX, USBRX, 115200);

char command[] = {'\xA5', '\x50'};
char clientBuffer[128];

int main() {
  ssize_t nBytes;
  int nReceived;
  uint32_t nIter = 0;
  uint64_t total = 0;
  uint32_t t;
  uint32_t min = (1ULL << 32) - 1;
  uint32_t mean = 0;
  uint32_t max = 0;

  counterInit();
  pc.printf("Serial Client\n");

  while (true) {
    while (! client.FileHandle::readable()) {
      while (! client.FileHandle::writable()) {
      }
      nBytes = client.write(command, sizeof(command));
      assert(nBytes == sizeof(command));
    }
    
    counterStart();
    nReceived = 0;
    while (nReceived < 20) {
      nBytes = client.read(&clientBuffer[nReceived], 20 - nReceived);
      nReceived += nBytes;
    }
    t = counterStop();
    
    nIter += 1;
    assert(nIter <= (1ULL << 32) - 1);
    total += t;
    mean = total / nIter;
    if (t < min) {
      min = t;
    }
    if (t > max) {
      max = t;
    }
    pc.printf("%s %ld %ld % ld %ld\n", clientBuffer, t, min, mean, max);
    wait_ms(2);
  }
}

