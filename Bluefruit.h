#ifndef ADAFRUIT_BLUEFRUIT_H_
#define ADAFRUIT_BLUEFRUIT_H_

#include <Arduino.h>
#include <AltSoftSerial.h>
#include <ps2_keyboard_manager.h>

class Bluefruit : public AltSoftSerial {
 public:
  void sendKeyboardReport(const PS2KeyboardManager::Report& report);
};

#endif  // ADAFRUIT_BLUEFRUIT_H_

