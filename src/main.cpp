#include <mbed.h>
#include <stdbool.h>
#include <assert.h>
#include "counter.h"

RawSerial client(D1, D0, 115200);
Serial pc(USBTX, USBRX, 115200);

char clientBuffer[128];

int main() {
  int c;
  uint32_t i;
  uint32_t nIter = 0;
  uint64_t total = 0;
  uint32_t t;
  uint32_t min = (1ULL << 32) - 1;
  uint32_t mean = 0;
  uint32_t max = 0;

  counterInit();
  pc.printf("Serial Client\n");

  while (true) {
    while (! client.readable()) {
      while (! client.writeable()) {
      }
      c = client.putc('\xA5');
      assert(c == '\xA5');
      while (! client.writeable()) {
      }
      c = client.putc('\x50');
      assert(c == '\x50');
    }
    counterStart();
    for (i=0; i<20; i++) {
      clientBuffer[i] = client.getc();
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

