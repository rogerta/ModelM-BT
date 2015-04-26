
#define __PROG_TYPES_COMPAT__ 1
#include "Bluefruit.h"

#define numberof(a) (sizeof(a)/sizeof((a)[0]))

namespace {

PROGMEM static const prog_char mouseHeader[3] = {0xFD, 0x00, 0x03};

}  // namespace


void Bluefruit::sendKeyboardReport(const PS2KeyboardManager::Report& report) {
  write(0xFD);
  write(report.modifiers);
  write((uint8_t)0);
  write(report.keycodes, numberof(report.keycodes));
}

