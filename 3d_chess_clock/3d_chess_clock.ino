/** 3D Chess Clock program
* By Arman Barraghi 
* Includes all the logic to control the Arduino-NANO powered chess clock
* Designed for the Juniata College course PC:209 Electronics
**/

#include <LiquidCrystal.h>


//Setting up LED
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

//Setting up Buttons for the clock
const int whiteButtonPin = 7;
const int blackButtonPin = 8;

int buttonState;
int programState = 0;
long buttonMillis = 0;
const long intervalButton = 5000;  

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  pinMode(whiteButtonPin, INPUT);      
  digitalWrite(whiteButtonPin, HIGH);
  lcd.noDisplay();
}

void loop() {
  // put your main code here, to run repeatedly:

  unsigned long currentMillis = millis();
  buttonState = digitalRead(whiteButtonPin);

  if (buttonState == LOW && programState == 0) {
    buttonMillis = currentMillis;
    programState = 1;
  }
  else if (programState == 1 && buttonState == HIGH) {
        programState = 0; //reset
  }

  if(currentMillis - buttonMillis > intervalButton && programState == 1) {
    lcd.display();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Hello");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("World!");
    delay(1000);
  }

}
