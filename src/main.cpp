#include <mbed.h>
#include <stdbool.h>
#include <assert.h>

UARTSerial client(D1, D0, 115200);
Serial pc(USBTX, USBRX, 115200);

char command[] = {'\xA5', '\x50'};
char clientBuffer[128];
int nReceived;

int main() {
  uint32_t i;
  ssize_t nBytes;

  pc.printf("Serial Client\n");

  while (true) {
    while (! client.FileHandle::readable()) {
      while (! client.FileHandle::writable()) {
      }
      nBytes = client.write(command, sizeof(command));
      assert(nBytes == sizeof(command));
    }

    nReceived = 0;
    while (nReceived < 20) {
      nBytes = client.read(&clientBuffer[nReceived], 20 - nReceived);
      nReceived += nBytes;
    }
    
    clientBuffer[20] = '\n';
    pc.printf("%s", clientBuffer);
    wait_ms(2);
  }
}

