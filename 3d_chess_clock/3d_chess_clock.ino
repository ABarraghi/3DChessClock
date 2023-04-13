/** 3D Chess Clock program
* By Arman Barraghi 
* Includes all the logic to control the Arduino-NANO powered chess clock
* Designed for the Juniata College course PC:209 Electronics
**/

#include <LiquidCrystal.h>


//Setting up LED
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Hello");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("World!");

}
