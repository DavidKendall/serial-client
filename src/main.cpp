#include <mbed.h>
#include <stdbool.h>
#include <assert.h>

RawSerial client(D1, D0, 115200);
Serial pc(USBTX, USBRX, 115200);

char clientBuffer[128];

int main() {
  uint32_t i;
  int c;

  pc.printf("Serial Client\n");

  while (true) {
    c = client.putc('\xA5');
    assert(c == '\xA5');
    c = client.putc('\x50');
    assert(c == '\x50');

    for (i=0; i<20; i++) {
      clientBuffer[i] = client.getc();
    }
    
    clientBuffer[20] = '\n';
    pc.printf("%s", clientBuffer);
    wait_ms(2);
  }
}

