/*******************************************************************
 * This is a program for pokehaji!
 * Written by Ayaka Ikezawa and Kasumi Yajima.
 * 
 * Adafruit_SoftServoライブラリをgithubからダウンロードしてね！
 * https://github.com/adafruit/Adafruit_SoftServo
 *
 *******************************************************************/

#include <Adafruit_SoftServo.h> 

#define SERVO1PIN 0   // サーボの信号線を0番ピンに！

Adafruit_SoftServo myServo1;

void setup() {
  //割り込みでサーボに信号を送るための準備
  OCR0A = 0xAF;            
  TIMSK |= _BV(OCIE0A);    

  //サーボの初期化
  myServo1.attach(SERVO1PIN);  
  myServo1.write(90);           
  delay(15);                    
}

void loop()  {
  int servoPos; 
  int turnVal = random(130, 180);//ランダムで振る角度を決める

  for(int servoPos = 90 ; servoPos <= turnVal; servoPos +=2) { 
    myServo1.write(servoPos);      
    delay(random(1,5));                            
  } 

  for(int servoPos = turnVal; servoPos >= 90; servoPos -=2) { 
    myServo1.write(servoPos);          
    delay(random(1,5));                            
  } 
  
  delay(random(100,500));//タイミングもランダムにして動物っぽく！
  delay(150);                      
}

//割り込み処理用
volatile uint8_t counter = 0;
SIGNAL(TIMER0_COMPA_vect) {
  // 2ミリsecごとに呼ぶ
  counter += 2;
  // 20ミリsecごとにサーボをリフレッシュ
  if (counter >= 20) {
    counter = 0;
    myServo1.refresh();
  }
}

