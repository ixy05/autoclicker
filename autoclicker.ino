#include <USBHIDMouse.h>
USBHIDMouse Mouse;

void setup() {
Mouse.begin();
}

void loop() {
  Mouse.press(MOUSE_RIGHT);
  delay(100);
  Mouse.release(MOUSE_RIGHT);
  delay(900);
}
