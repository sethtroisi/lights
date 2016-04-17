#include <cstdlib>
#include <iostream>

#include <wiringPi.h>

using namespace std;

#define DEFAULT_LED_PORT 26
#define BLINK_DELAY_MS 2500

void setup(int port) {
  // Give program higher priority to affect more real timeness.
  piHiPri(4);

  if (wiringPiSetup () == -1) {
    cout << "wiringPiSetup failed" << endl;
    exit;
  }

  pinMode (port, OUTPUT);
}

int main(void) {
  // TODO take port / delay from args

  int port = DEFAULT_LED_PORT;
  setup(port);


  cout << "Blinking light on port " << port << " every " << BLINK_DELAY_MS << " ms" << endl;

  while (true) {
      cout << "on" << endl;
    digitalWrite (port, 1);
    delay(BLINK_DELAY_MS);

    cout << "off" << endl;
    digitalWrite (port, 0);
    delay(BLINK_DELAY_MS);
  }

  return 0;
}
