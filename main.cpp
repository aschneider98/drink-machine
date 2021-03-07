#include <LiquidCrystal.h>
#include <NewPing.h>

const int rs = 0, en = 1, d4 = 5, d5 = 4, d6 = 3, d7 = 2; //LCD screen pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //Defines LCD object with pins
const long sec = 20000;

#define pump1 A0 //Pump 1 is on Pin A0
#define pump2 A1 //Pump 2 is on Pin A1
#define pump3 A2 //Pump 3 is on Pin A2
#define pump4 A3 //Pump 4 is on Pin A3
#define pump5 A4 //Pump 5 is on Pin A4
#define pump6 A5 //Pump 6 is on Pin A5

#define maxDist 200
#define trigPin 6 //Ultrasonic sensor trigger pin is on Pin 6
#define echoPin 7 //Ultrasonic sensor trigger pin is on Pin 7
NewPing sonar(trigPin, echoPin, maxDist);

#define CLK 9 //Clockwise pin
#define DT 8  //Counterclockwise pin
#define SW 10  //Button pin

int counter = 1;
int old = 0;
int currentStateCLK;
int lastStateCLK;
unsigned long lastButtonPress = 0;
int drinkNum = 0;
bool button = false;
String drink[] = {"Vodka Tonic", "Screwdriver", "Lemondriver", "Whiskey Sour", "Whiskey Tonic",
 "Mimosa", "Lemonade Bubbly", "Champagne", "Straight Vodka", "Whiskey Neat"};

void setup() {
  pinMode(A0,OUTPUT); //Pin A0 is an output for Pump 1
  pinMode(A1,OUTPUT); //Pin A1 is an output for Pump 2
  pinMode(A2,OUTPUT); //Pin A2 is an output for Pump 3
  pinMode(A3,OUTPUT); //Pin A3 is an output for Pump 4
  pinMode(A4,OUTPUT); //Pin A4 is an output for Pump 5
  pinMode(A5,OUTPUT); //Pin A5 is an output for Pump 6

  pinMode(trigPin,OUTPUT); //Ultrasonic sensor trigger pin is output
  pinMode(echoPin,INPUT); //Ultrasonic sensor echo pin is an input
  pinMode(CLK,INPUT);
  pinMode(DT,INPUT);
  pinMode(SW, INPUT_PULLUP);

  // Read the initial state of CLK
  lastStateCLK = digitalRead(CLK);
}

void loop() {
  lcdSetup();
  lcd.print("Place empty cup");
  while(!isCupEmpty()){
    isCupEmpty();
  }
  delay(2000);
  lcdSelect();
  delay(2000);
  lcdSetup();
  switch(drinkNum){
    case 1: //Vodka Tonic 
      lcd.print("Mixing");
      lcd.setCursor(0,1);
      lcd.print("Vodka Tonic");
      digitalWrite(pump1,HIGH); //1 part vodka
      delay(sec);
      digitalWrite(pump1,LOW);
      digitalWrite(pump6,HIGH); //3 parts tonic
      delay(3*sec);
      digitalWrite(pump6,LOW);
      digitalWrite(pump5,HIGH); //0.25 part lemonade
      delay(0.25*sec);
      digitalWrite(pump5,LOW);
      lcdSetup();
      lcd.print("Take your drink");
      break;

     case 2: //Screwdriver
      lcd.print("Mixing");
      lcd.setCursor(0,1);
      lcd.print("Screwdriver");
      digitalWrite(pump1,HIGH); //1 part vodka
      delay(2*sec);
      digitalWrite(pump1,LOW);
      digitalWrite(pump4,HIGH); //2 parts OJ
      delay(4*sec);
      digitalWrite(pump4,LOW);
      lcdSetup();
      lcd.print("Take your drink"); 
      break;

     case 3: //Lemondriver
      lcd.print("Mixing");
      lcd.setCursor(0,1);
      lcd.print("Lemondriver");
      digitalWrite(pump1,HIGH); //1 part vodka
      digitalWrite(pump5,HIGH); //4 parts lemonade
      delay(2*sec);
      digitalWrite(pump1,LOW);
      delay(6*sec);
      digitalWrite(pump5,LOW);
      lcdSetup();
      lcd.print("Take your drink"); 
      break;

     case 4: //Whiskey Sour
      lcd.print("Mixing");
      lcd.setCursor(0,1);
      lcd.print("Whiskey Sour");
      digitalWrite(pump2,HIGH); //2 parts whiskey
      delay(2*sec);
      digitalWrite(pump2,LOW);
      digitalWrite(pump4,HIGH); //2 parts OJ
      delay(2*sec);
      digitalWrite(pump4,LOW);
      digitalWrite(pump5,HIGH); //1.5 parts lemonade
      delay(1.5*sec);
      digitalWrite(pump5,LOW);
      lcdSetup();
      lcd.print("Take your drink"); 
      break;

     case 5: //Whiskey Tonic
      lcd.print("Mixing");
      lcd.setCursor(0,1);
      lcd.print("Whiskey Tonic");
      digitalWrite(pump2,HIGH); //1 part whiskey
      delay(2*sec);
      digitalWrite(pump2,LOW);
      digitalWrite(pump6,HIGH); //2 parts OJ
      delay(4*sec);
      digitalWrite(pump6,LOW);
      lcdSetup();
      lcd.print("Take your drink"); 
     break;

     case 6: //Mimosa
      lcd.print("Mixing");
      lcd.setCursor(0,1);
      lcd.print("Mimosa");
      digitalWrite(pump3,HIGH); //1 part champagne
      digitalWrite(pump4,HIGH); //1 part OJ
      delay(5*sec);
      digitalWrite(pump3,LOW);
      digitalWrite(pump4,LOW);
      lcdSetup();
      lcd.print("Take your drink"); 
     break;

     case 7: //Champagne and Lemonade
      lcd.print("Mixing Champagne");
      lcd.setCursor(0,1);
      lcd.print("and Lemonade");
      digitalWrite(pump3,HIGH); //1 part champagne
      digitalWrite(pump4,HIGH); //1 part lemonade
      delay(5*sec);
      digitalWrite(pump3,LOW);
      digitalWrite(pump4,LOW);
      lcdSetup();
      lcd.print("Take your drink"); 
     break;

     case 8: //Champagne
      lcd.print("Pouring");
      lcd.setCursor(0,1);
      lcd.print("Champagne");
      digitalWrite(pump3,HIGH); //champagne
      delay(5*sec);
      digitalWrite(pump3,LOW);
      lcdSetup();
      lcd.print("Take your drink"); 
     break;

     case 9: //Straight Vodka
      lcd.print("Pouring");
      lcd.setCursor(0,1);
      lcd.print("Straight Vodka");
      digitalWrite(pump1,HIGH); //vodka
      delay(5*sec); //Wait one second
      digitalWrite(pump1,LOW);
      lcdSetup();
      lcd.print("Take your drink"); 
     break;

     case 10: //Whiskey Neat
      lcd.print("Pouring");
      lcd.setCursor(0,1);
      lcd.print("Whiskey Neat");
      digitalWrite(pump2,HIGH); //whiskey
      delay(sec);
      digitalWrite(pump2,LOW);
      lcdSetup();
      lcd.print("Take your drink"); 
     break;
  }
  
  while(!isRemoved()){
    isRemoved();
  }
}

void lcdSelect(){
    lcdSetup();
    lcd.print("Select drink: ");
  while(button == false){
    lcd.setCursor(14,0);
    drinkNum = displayDrink();
    if(drinkNum != old){
      lcd.setCursor(13,0);
      lcd.print("   ");
      lcd.setCursor(0,1);
      lcd.print("                ");
      old = drinkNum;
    }
    lcd.print(drinkNum);
    lcd.setCursor(0,1);
    lcd.print(drink[drinkNum-1]);
    selectDrink();
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("You selected: ");
  lcd.setCursor(0,1);
  lcd.print(drink[drinkNum-1]);
  button = false;
}

void lcdSetup(){
  lcd.clear();
  lcd.begin(16, 2); //Starts the LCD screen
  lcd.setCursor(0,0); //Sets LCD screen cursor to first row
}

int displayDrink() {
  // Read the current state of CLK
  currentStateCLK = digitalRead(CLK);

  // If last and current state of CLK are different, then pulse occurred
  // React to only 1 state change to avoid double count
  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){

    // If the DT state is different than the CLK state then
    // the encoder is rotating CCW so decrement
    if (digitalRead(DT) != currentStateCLK) {
      if(counter == 1){
        counter = 10;
      } else {
      counter --;
      }
    } else {
      if(counter == 10){
        counter = 1;
      } else {
      // Encoder is rotating CW so increment
      counter ++;
      }
    }
  }

  // Remember last CLK state
  lastStateCLK = currentStateCLK;

  // Put in a slight delay to help debounce the reading
  delay(1);
  return(counter);
}

bool selectDrink(){// Read the button state
  int btnState = digitalRead(SW);

  //If we detect LOW signal, button is pressed
  if (btnState == LOW) {
    //if 50ms have passed since last LOW pulse, it means that the
    //button has been pressed, released and pressed again
    if (millis() - lastButtonPress > 50) {
    counter = 1;
    button = true;
  }

    // Remember last button press event
    lastButtonPress = millis();
  }
}

bool isCupEmpty(){
  bool cupEmpty;
  int distance;
  unsigned int uS = sonar.ping(); //Send ping, get pin time in microsconds (uS)
  distance = uS/US_ROUNDTRIP_CM; //Calculates the distance in centimeters
  if(distance < 11 && distance > 8){
    cupEmpty = true;
  }
  else{
    cupEmpty = false;
  }
  return cupEmpty;
}

bool isRemoved(){
  int distance;
  unsigned int uS = sonar.ping(); //Send ping, get pin time in microsconds (uS)
  distance = uS/US_ROUNDTRIP_CM; //Calculates the distance in centimeters
  if(distance < 8){
    return false;
  }
  else{
    return true;
  }
}
