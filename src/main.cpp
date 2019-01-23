#include <mbed.h>
#include <stdbool.h>
#include <assert.h>

Serial client(D1, D0, 115200);
Serial pc(USBTX, USBRX, 115200);

char clientBuffer[128];

int main() {
  uint32_t i;

  pc.printf("Serial Client\n");

  while (true) {
    if (client.putc('\xA5') == '\xA5') {
      if (client.putc('\x50') == '\x50') {
      }
      for (i=0; i<20; i++) {
        clientBuffer[i] = client.getc();
      }
      clientBuffer[20] = '\n';
      pc.printf("%s", clientBuffer);
    }
    wait_ms(2);
  }
}

