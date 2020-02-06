//---------------------------------------------------------------
//抖音：爆改车间主任
//开发板Arduino Leonardo
//电脑音调节、短按播放暂停、长按下一曲
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
        Consumer.write(MEDIA_VOLUME_DOWN); 
        delay(8);
      } else {
        Consumer.write(MEDIA_VOLUME_UP);
        delay(8);
      }

      Keyboard.releaseAll();
      aLastState = aState;
    }


    if (digitalRead(BUTTON) == LOW) {

      if (lastButtonState == HIGH) {
        
        Consumer.write(MEDIA_PLAY_PAUSE);

         lastClickTime = millis();
      }
       delay(200);
      if(digitalRead(BUTTON)==LOW){
        Consumer.write(MEDIA_NEXT);
        while(!digitalRead(BUTTON));
      }

      lastButtonState = LOW;
    } else {

      lastButtonState = HIGH;
    }
  }

}
