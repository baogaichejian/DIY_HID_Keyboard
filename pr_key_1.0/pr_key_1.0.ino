//---------------------------------------------------------------
//抖音：爆改车间主任
//开发板Arduino Leonardo
//pr方向快捷键和裁剪功能
//共享代码请勿商用
//---------------------------------------------------------------

#include "HID-Project.h"    //该HID库文件下载地址 https://github.com/NicoHood/HID
#define  CLK 2
#define  DT 3
#define  BUTTON 4
#define PIN_5V  A2
#define PIN_GND  A3
bool aState;
bool aLastState;
bool lastButtonState = 0;

void setup() {
  Consumer.begin();

  pinMode(DT, INPUT);
  pinMode(CLK, INPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  aLastState = digitalRead(DT);
}
long lastClickTime = 0;

void loop() {

  if (millis() - lastClickTime > 1000) {

    aState = digitalRead(DT);

    if (aState != aLastState) {

      if (digitalRead(CLK) != aState) {
        Keyboard.write(KEY_LEFT_ARROW);
        delay(8);
      } else {
        Keyboard.write(KEY_RIGHT_ARROW);
        delay(8);
      }

      Keyboard.releaseAll();
      aLastState = aState;
    }


    if (digitalRead(BUTTON) == LOW) {

      if (lastButtonState == HIGH) {
        //Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_GUI);
        Keyboard.press('k');
        delay(100);
        Keyboard.releaseAll();
        lastClickTime = millis();
      }

      lastButtonState = LOW;
    } else {

      lastButtonState = HIGH;
    }
  }

}
