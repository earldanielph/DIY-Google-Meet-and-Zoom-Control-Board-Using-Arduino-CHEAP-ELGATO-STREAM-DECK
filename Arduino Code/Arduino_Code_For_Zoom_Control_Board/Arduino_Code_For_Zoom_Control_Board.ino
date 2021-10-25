// Arduino Code For Zoom Control Board
// Evtech | @earldanielph

#include "HID-Project.h"

#define ZOOMBTNS

// Define Arduino pin numbers for buttons and LEDs
#define led 13

#ifdef ZOOMBTNS
#define BTN1 8
#define BTN2 9
#define BTN3 10
#define BTN4 A0
#define BTN5 A1
#define BTN6 A2
#define BTN7 A3
#define NUMBUTTONS 7
int buttons[NUMBUTTONS] = {BTN1, BTN2, BTN3, BTN4, BTN5, BTN6, BTN7};
unsigned long btntime[NUMBUTTONS];
boolean btnpress[NUMBUTTONS];
#endif

char line[80];
unsigned long t;
int n;

void setup() {

#ifdef ZOOMBTNS
  for (int i = 0; i < NUMBUTTONS; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
    btntime[i] = 0;
    btnpress[i] = false;
  }
#endif
}

void loop() {

#ifdef ZOOMBTNS
  for (int i = 0; i < NUMBUTTONS; i++) {
    if (!digitalRead(buttons[i])) {
      // Button pressed (negative logic)
      if (btntime[i] == 0) {
        // Button has just been pressed
        btntime[i] = millis();
      }
      else {
        // Button is still pressed
        if (millis() - btntime[i] > 20 && !btnpress[i]) {
          // This is not just a glitch          
          btnpress[i] = true;
          // Now do your stuff!
          digitalWrite(led, HIGH);
          switch (i) {
#if 1
          case 0: // Alt-F2: Gallery view
            BootKeyboard.press(KEY_LEFT_ALT);
            BootKeyboard.write(KEY_F2);
            BootKeyboard.release(KEY_LEFT_ALT);
            break;
          case 1: // Alt-F1: Speaker view
            BootKeyboard.press(KEY_LEFT_ALT);
            BootKeyboard.write(KEY_F1);
            BootKeyboard.release(KEY_LEFT_ALT);
            break;
          case 2: // Alt-M: Mute all
            BootKeyboard.press(KEY_LEFT_ALT);
            BootKeyboard.write(KEY_M);
            BootKeyboard.release(KEY_LEFT_ALT);
            break;
          case 3: // Alt-A: Mute self
            BootKeyboard.press(KEY_LEFT_ALT);
            BootKeyboard.write(KEY_A);
            BootKeyboard.release(KEY_LEFT_ALT);
            break;
          case 4: // Alt-F: Full screen
            BootKeyboard.press(KEY_LEFT_ALT);
            BootKeyboard.write(KEY_F);
            BootKeyboard.release(KEY_LEFT_ALT);
            break;
          case 5: // Alt-S: Share screen
            BootKeyboard.press(KEY_LEFT_ALT);
            BootKeyboard.write(KEY_S);
            BootKeyboard.release(KEY_LEFT_ALT);
            break;
          case 6: // Alt-S: Toggle video
            BootKeyboard.press(KEY_LEFT_ALT);
            BootKeyboard.write(KEY_V);
            BootKeyboard.release(KEY_LEFT_ALT);
            break;
#else
          case 0:
            BootKeyboard.write(KEY_0);
            break;
          case 1:
            BootKeyboard.write(KEY_1);
            break;
          case 2:
            BootKeyboard.write(KEY_2);
            break;
          case 3:
            BootKeyboard.write(KEY_3);
            break;
          case 4:
            BootKeyboard.write(KEY_4);
            break;
          case 5:
            BootKeyboard.write(KEY_5);
            break;
          case 6:
            BootKeyboard.write(KEY_6);
            break;
#endif
          }  
        }
      }
    }
    else {
      // Button not pressed
      if (btntime[i] != 0) {
        // Looks like it's just been released
        digitalWrite(led, LOW);
        btntime[i] = 0;
        btnpress[i] = false;
      }
    }
  }
#endif

}
