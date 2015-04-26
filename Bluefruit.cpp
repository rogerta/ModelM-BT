
#define __PROG_TYPES_COMPAT__ 1
#include "Bluefruit.h"

#define numberof(a) (sizeof(a)/sizeof((a)[0]))

void Bluefruit::sendKeyboardReport(const PS2KeyboardManager::Report& report) {
  write(0xFD);
  write(report.modifiers);
  write((uint8_t)0);
  write(report.keycodes, numberof(report.keycodes));
}

