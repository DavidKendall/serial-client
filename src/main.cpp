#include <mbed.h>
#include <stdbool.h>
#include <assert.h>

RawSerial client(D1, D0, 115200);
Serial pc(USBTX, USBRX, 115200);

uint8_t clientBuffer[128];
volatile bool messageReceived;

void serialCbHandler(int events);

int main() {
  bool messagePending;
  event_callback_t serialCb = serialCbHandler;
  int c;
  int result;

  pc.printf("Serial Client\n");

  while (true) {
    messagePending = false;
    messageReceived = false;
    while (! messageReceived) {
      while (! client.writeable()) {
      }
      c = client.putc('\xA5');
      assert(c == '\xA5');
      while (! client.writeable()) {
      }
      c = client.putc('\x50');
      assert(c == '\x50');
      if (! messagePending) {
        //result = client.read(&clientBuffer[0], 20, serialCb, SERIAL_EVENT_RX_COMPLETE, '\xFF');
        result = client.read(&clientBuffer[0], 20, serialCb);
        assert(result >= 0);
        messagePending = true;
      }
      wait_ms(3);
    }

    pc.printf("%s\n", clientBuffer);
    wait_ms(2);
  }
}

void serialCbHandler(int events) {
  messageReceived = true;
}
