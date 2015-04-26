#ifndef ADAFRUIT_BLUEFRUIT_H_
#define ADAFRUIT_BLUEFRUIT_H_

#include <Arduino.h>
#include <AltSoftSerial.h>
#include <ps2_keyboard_manager.h>

class Bluefruit : public AltSoftSerial {
 public:
  enum Button {
    B_LEFT = 1 << 0,
    B_RIGHT = 1 << 1,
    B_MIDDLE = 1 << 2,
    B_BACK = 1 << 3,
    B_FORWARD = 1 << 4,
  };

  void sendKeyboardReport(const PS2KeyboardManager::Report& report);
};

#endif  // ADAFRUIT_BLUEFRUIT_H_

