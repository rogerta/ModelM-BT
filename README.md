ModelM-BT
---------
ModelM-BT is an [Arduino sketch](http://www.arduino.cc/en/Tutorial/Sketch) used to bluetooth-enable an old [IBM Model M keyboard](http://en.wikipedia.org/wiki/Model_M_keyboard).  It is based on an original idea described at [Adafruit's website](https://learn.adafruit.com/convert-your-model-m-keyboard-to-bluetooth-with-bluefruit-ez-key-hid).

The original project's code is based on a hacked and incomplete version of [TMK Keyboard Firmware](http://github.com/tmk/tmk_keyboard) and it's **huge**!  So I decided to write my own code with the following properties:

1. small footprint
2. easy to understand, very well componentized
3. fully unit tested, have confidence it works
4. interrupt driven solution rather than [bit banging](http://en.wikipedia.org/wiki/Bit_banging)
 
To this end, I first implemented a fully generic and reusable library for interfacing with PS2 devices called [PS2Utils](https://github.com/rogerta/PS2Utils).

I wrote [Bluefruit](https://github.com/rogerta/ModelM-BT/blob/master/Bluefruit.h), a simple class to interface with Adafruit's [Bluefruit EZ-Key module](https://learn.adafruit.com/introducing-bluefruit-ez-key-diy-bluetooth-hid-keyboard/overview).  I put PS2Utils and Bluefruit together into a complete [sketch](https://github.com/rogerta/ModelM-BT/blob/master/ModelM.ino) to fully enable my keyboard.

Pictures of the keyboard at various stages of development can be found on my [Google+ stream](https://plus.google.com/u/0/+RogerTawa/posts/6iFpTALQ4o6).

BOM
---
The following hardware components were used to build this project:

1. A old Model-M keyboard (thanks [Stef](https://plus.google.com/u/0/+StefanoLandi/posts)!)
2. [OSEPP nano](http://osepp.com/products/arduino-compatible-boards/osepp-nano-arduino-compatible/), Arduino Nano compatible
3. Adafruit [Bluefruit EZ-Key](https://www.adafruit.com/product/1535)
4. Adafruit [PowerBoost 500c](https://www.adafruit.com/product/1944)
5. Adafruit [Lithium ion polymer battery](https://www.adafruit.com/product/328)
6. Wires, buttons, resistors

If I were to do this again, I'd make the following changes:

1. Use an [Arduino Pro Mini](http://www.arduino.cc/en/Main/ArduinoBoardProMini) board, to make the modified keyboard as power efficient as possible.  While the OSEPP is great for prototyping, it has too many unneeded components like voltage regulators, USB circuitry, and extra LEDs for a production device.
2. Use a 3.3V Arduino rather than a 5V part.  Not only would this use less power, it would obviate the need for the resistors to connect the Arduino to the Bluefruit.

Schematic
---------
![Schematic](https://plus.google.com/u/0/photos/+RogerTawa/albums/6134379641493379793/6141875861268645266?pid=6141875861268645266&oid=110747475977701798390)

Special Features
----------------
Because Model M keyboard were built long before the Windows key was added to keyboards, this sketch remaps the Caps Lock key as a Windows key.  To get a real Caps Lock, press ALT+CapsLock.

Hold ALT+KeypadMinus down for five seconds to pair the keyboard with a computer.  The pairing will be remembered until the keyboard is re-paired.  Tested with Windows 7, MacOS 10.10.3, Ubuntu 14.04, and Android Lollipop.

Building
--------
To use this sketch, first [install the PS2Utils library into the IDE](https://github.com/rogerta/PS2Utils/blob/master/README.md).  Then clone this repository as follows:
```
$ git clone git@github.com:rogerta/ModelM-BT.git
```
Open the ModelM.ino sketch and upload it to your Arduino.

> Written with [StackEdit](https://stackedit.io/).

