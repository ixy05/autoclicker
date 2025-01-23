// This cycles between different clicking speeds at a button press
#include <USBHIDMouse.h>
USBHIDMouse Mouse;

int state = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 10;
#define LED_BRIGHTNESS 64 // Adjust 0-255 for desired brightness
int lastButtonState = HIGH;

void setup() {
  Mouse.begin();
  pinMode(0, INPUT_PULLUP);
  pinMode(15, OUTPUT);
  Serial.begin(9600);
}

void checkButton() {
  int currentState = digitalRead(0);
  if (currentState != lastButtonState && (millis() - lastDebounceTime) > debounceDelay) {
    lastDebounceTime = millis();
    if (currentState == LOW) {
      state = (state + 1) % 4;
      Serial.print("State changed to: ");
      Serial.println(state);
    }
  }
  lastButtonState = currentState;
}

void nonBlockingDelay(unsigned long ms) {
  unsigned long start = millis();
  while ((millis() - start) < ms) {
    checkButton();
  }
}

void loop() {
  checkButton();
  switch (state) {
    case 0:
      analogWrite(15, 0); // Off
      break;
    case 1:
      analogWrite(15, LED_BRIGHTNESS);
      Mouse.press(MOUSE_RIGHT);
      nonBlockingDelay(100);
      Mouse.release(MOUSE_RIGHT);
      analogWrite(15, 0);
      nonBlockingDelay(900);
      break;
    case 2:
      analogWrite(15, LED_BRIGHTNESS);
      Mouse.press(MOUSE_RIGHT);
      nonBlockingDelay(100);
      Mouse.release(MOUSE_RIGHT);
      analogWrite(15, 0);
      nonBlockingDelay(400);
      break;
    case 3:
      analogWrite(15, LED_BRIGHTNESS);
      Mouse.press(MOUSE_RIGHT);
      nonBlockingDelay(100);
      Mouse.release(MOUSE_RIGHT);
      analogWrite(15, 0);
      nonBlockingDelay(200);
      break;
  }
}
