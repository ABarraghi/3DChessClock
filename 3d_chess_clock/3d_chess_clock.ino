/** 3D Chess Clock program
* By Arman Barraghi 
* Includes all the logic to control the Arduino-NANO powered chess clock
* Designed for the Juniata College course PC:209 Electronics
**/
#include <LiquidCrystal.h>

class Timer {
  public:
  
    Timer(int mins, int seconds);
  
    int getMins();

    void setMins(int mins);

    int getSeconds();

    void setSeconds(int seconds);

    long getRemainingTime();

    String toString();

  private:
  	int mins, seconds;
  	long remainingTime;

};

//Defining prototyped Timer methods
Timer::Timer(int mins, int seconds){
  this->mins = mins;
  this->seconds = seconds;
  remainingTime = static_cast<long>((mins*60) + seconds);
}

int Timer::getMins(){
  return mins;
}

void Timer::setMins(int mins){
  this->mins = mins;
  remainingTime = static_cast<long>((mins*60) + seconds);
}

int Timer::getSeconds(){
  return seconds;
}

void Timer::setSeconds(int seconds){
  this->seconds = seconds;
  remainingTime = static_cast<long>((mins*60) + seconds);
}

long Timer::getRemainingTime(){
  return remainingTime;
}

String Timer::toString(){
 String minString = " ";
 String secString = " ";
  
 if(mins < 10) minString = "0" + String(mins);
 else minString = String(mins);
  
 if(seconds < 10) secString = "0" + String(seconds);
 else secString = String(seconds);
   
 return minString + ":" + secString;  
}

class Player {

  public:

  Player(bool hasTurn, Timer timer);

  bool getTurn();

  void setTurn(bool hasTurn);

  Timer getTimer();

  void setTimer(Timer timer);
  
  bool hasTime();


  private:
   bool hasTurn;
   Timer timer;  

};

//Defining prototyped Player methods
Player::Player(bool hasTurn, Timer timer):timer(15,0){
  this->hasTurn = hasTurn;
  this->timer = timer;
}

bool Player::getTurn(){
 return hasTurn; 
}

void Player::setTurn(bool hasTurn){
  this->hasTurn = hasTurn; 
}

Timer Player::getTimer(){
  return timer;
}

void Player::setTimer(Timer timer){
  this->timer = timer;
}

bool Player::hasTime(){
  return timer.getRemainingTime() > 0;
}

//Setting up LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);


int buttonState;
int programState = 0;
long buttonMillis = 0;
const long intervalButton = 1000;  

//Setting up time controls
Timer timer(15,0); 
Player blackPlayer(false,timer);
Player whitePlayer(false,timer);
bool gameStarted = false;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);    
  lcd.noDisplay();
  
  //Pushbutton inputs
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();
  int whiteButtonState = digitalRead(A0);
  int blackButtonState = digitalRead(A1);
  
  //Flag to check if both players still have time
  bool playerTimeRemaining = blackPlayer.hasTime() && whitePlayer.hasTime();

  if (whiteButtonState == HIGH && programState == 0) {
    buttonMillis = currentMillis;
    programState = 1;
  }
  else if (programState == 1 && whiteButtonState == LOW) {
        programState = 0; //reset
  }

  if(currentMillis - buttonMillis > intervalButton && programState == 1) {
    programState = 3; //Turn chess clock "on"
  }
  
  //Logic of the "on state"
  if(programState==3) { 
    lcd.display();
    lcd.setCursor(0,0);
    lcd.print("Black | White");
    lcd.setCursor(0,1);
    lcd.print(blackPlayer.getTimer().toString() + " | " + whitePlayer.getTimer().toString());
    
    //Swap turns to black
    if((whiteButtonState == HIGH && gameStarted) && playerTimeRemaining){
    	blackPlayer.setTurn(true);
    	whitePlayer.setTurn(false);
  	}
    
    //Swap turns to white
  	if(blackButtonState==HIGH && playerTimeRemaining){
   		blackPlayer.setTurn(false);
    	whitePlayer.setTurn(true);
      	gameStarted = true;
  	}
    
    //Turn "off" chess clock, only when a player's time is out
    if(blackButtonState==HIGH && !playerTimeRemaining){ //Turn chess clock off
      lcd.noDisplay();
      programState = 0;
      blackPlayer.setTimer(timer);
      whitePlayer.setTimer(timer);
      blackPlayer.setTurn(false);
      whitePlayer.setTurn(false);
      gameStarted = false;
    }

  }
 
  //Countdown mechanisms for both players
   if(whitePlayer.getTurn() && whitePlayer.getTimer().getRemainingTime() > 0){ 
    Timer whiteTimer = whitePlayer.getTimer();
    if(whiteTimer.getSeconds() == 0){
      whiteTimer.setSeconds(59);
      whiteTimer.setMins(whiteTimer.getMins()-1);      
    }
    else whiteTimer.setSeconds(whiteTimer.getSeconds()-1);
    whitePlayer.setTimer(whiteTimer);
    delay(1000);
  }
  
    if(blackPlayer.getTurn() && blackPlayer.getTimer().getRemainingTime() > 0){ 
    Timer blackTimer = blackPlayer.getTimer();
    if(blackTimer.getSeconds() == 0){
      blackTimer.setSeconds(59);
      blackTimer.setMins(blackTimer.getMins()-1);      
    }
    else blackTimer.setSeconds(blackTimer.getSeconds()-1);
    blackPlayer.setTimer(blackTimer);
    delay(1000);
  }

}