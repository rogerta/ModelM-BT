// Implementation of the "device side" of a bluetooth keyboard, using an
// IBM Model M keyboard as the hardware keyboard.

// NOTE: even though SoftwareSerial is not used directly in this file,
// it must be included here, otherwise the IDE will not add a -I
// command line arg for the AltSoftSerial library during compilation.
// The result will be that AltSoftSerial.h will not be found.

#include <AltSoftSerial.h>
#include <ps2_debug.h>
#include <ps2_keyboard.h>
#include <ps2_keyboard_manager.h>
#include <ps2_protocol.h>

#include "Bluefruit.h"

// I/O pins used with the PS2 keyboard.
const static int kClockPin = 2;
const static int kDataPin = 3;

// I/O pins used with the bluefruit module.  Note that the bluefruit does not
// send data back to the arduino, so the RX pin is never used.
const static int kBTRXPin = 8;
const static int kBTTXPin = 9;

// I/O pin to put the bluefruit into pairing mode.  Set pin to HIGH to start
// pairing.
const static int kBTPBPin = 6;

// Class to map keys the way I like them.
class RogertaKeyboardManager : public PS2KeyboardManager {
 public:
  RogertaKeyboardManager() {}

 private:
  virtual PS2Keyboard::Key transformKey(PS2Keyboard::Key key);
};

PS2Keyboard::Key RogertaKeyboardManager::transformKey(PS2Keyboard::Key key) {
  // CapsLock becomes the windows key.
  // ALT+CapsLock is a regular capslock.
  if (key.code() == PS2Keyboard::KC_CAPS_LOCK && !isAltPressed())
    key.set(PS2Keyboard::KC_LGUI, key.type());

  return key;
}

// Global objects to handle PS2 keyboard.
static PS2P_GLOBAL(protocol);
static PS2Keyboard keyboard;
static RogertaKeyboardManager manager;
static PS2Debug debug;
static bool isPairing = false;

// Global object to handle Bluefruit module.
static Bluefruit bluefruit;

void setup() {
  // Intiailize the bluefruit pairing pin.
  pinMode(kBTPBPin, OUTPUT);
  digitalWrite(kBTPBPin, LOW);

  // Initialize communication with the bluefruit module.
  bluefruit.begin(9600);

  // Initialize PS2 protocol handler for the keyboard.  Pin 2 is the clock
  // input and pin 3 is the data input.
  if (!protocol.begin(kClockPin, kDataPin, &debug)) {
    Serial.println(F("*** Unable to begin PS2 protocol"));
    return;
  }

  // Initialize PS2 keyboard.
  if (!keyboard.begin(&protocol, &debug)) {
    Serial.println(F("*** Unable to begin PS2 keyboard"));
    return;
  }

  // Initialize PS2 keyboard manager.
  if (!manager.begin(&keyboard, 0, &debug)) {
    Serial.println(F("*** Unable to begin PS2 keyboard manager"));
    return;
  }

  debug.begin(&manager);
}

void loop() {
  //debug.dump();

  // Allow the keyboard manager to check the current state of the keyboard.
  // If the state has changed, available() returns the number of available
  // reports.
  int count = manager.available();
  while (count > 0) {
    PS2KeyboardManager::Report report = manager.read();
    bluefruit.sendKeyboardReport(report);
    //debug.dumpReport(report);

    // While ALT+keypad-minus is held down, set the bluefruit in pair mode.
    bool doPairing = report.isAltPressed() &&
        report.isKeyPressed(PS2Keyboard::KC_KP_SUB);
    if (isPairing != doPairing) {
      isPairing = doPairing;
      digitalWrite(kBTPBPin, doPairing);
      //Serial.print(F("+++ Pairing "));
      //Serial.println(doPairing ? F("on") : F("off"));
    }

    --count;
  }

  // The bluefruit module does not send us data, so no need to check
  // if anything is available.
}
