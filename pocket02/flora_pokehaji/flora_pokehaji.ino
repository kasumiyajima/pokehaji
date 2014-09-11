#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
Adafruit_GPS GPS(&Serial1);

uint32_t timer = millis();

void setup()  
{
  // PIN Setting
  for(int i=0; i < 10; i++){
    pinMode(i, OUTPUT);
  }
  
  // GPS Initialize
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  
  delay(1000);
  
  // ??
  Serial1.println(PMTK_Q_RELEASE);
}

void loop()
{
  char c = GPS.read();
  
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA())) return;
  }
  
  // Timer
  if (timer > millis())
    timer = millis();
  
  
  // Main
  if (millis() - timer > 2000) { 
    timer = millis();
    
    // GPS is Correct?
    // GPS Fix -> 1
    // GPS UnFix -> 0
    Serial.print("Fix: ");
    Serial.println((int)GPS.fix);
    
    if(GPS.fix){
      // Get altitude
      int alt = GPS.altitude;
      
      // Takaosan height is 599.
      // 10 LED point
      int a = 600 / 10;
      
      // LED
      if(alt > 0 || alt < a){ // 1
        digitalWrite(0, HIGH);
        led_off(0);
      } else if (alt >= a || alt < a*2 ) { // 2
        digitalWrite(1, HIGH);
        led_off(1);
      } else if (alt >= a*2 || alt < a*3 ) { // 3
        digitalWrite(2, HIGH);
        led_off(2);
      } else if (alt >= a*3 || alt < a*4 ) { // 4
        digitalWrite(3, HIGH);
        led_off(3);
      } else if (alt >= a*4 || alt < a*5 ) { // 5
        digitalWrite(4, HIGH);
        led_off(4);
      } else if (alt >= a*5 || alt < a*6 ) { // 6
        digitalWrite(5, HIGH);
        led_off(5);
      } else if (alt >= a*6 || alt < a*7 ) { // 7
        digitalWrite(6, HIGH);
        led_off(6);
      } else if (alt >= a*7 || alt < a*8 ) { // 8
        digitalWrite(7, HIGH);
        led_off(7);
      } else if (alt >= a*8 || alt < a*9 ) { // 9
        digitalWrite(8, HIGH);
        led_off(8);
      } else if(alt > a*9 ) { // 10
        digitalWrite(9, HIGH);
        led_off(9);
      } else {
        led_off(1000);
      }
    }
  }
}

// Turn off LEDs except one
void led_off(int n){
  for(int i=0; i<10; i++){
    if(i != n){
      digitalWrite(i, LOW);
    }
  }
}
