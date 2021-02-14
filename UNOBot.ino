// Including LCD Display and IR Remote Libraries

#include <LiquidCrystal.h>
#include <IRremote.h>


// LCD Pins

const int D4 = 6;
const int D5 = 7;
const int D6 = 10;
const int D7 = 11;

const int EN = A0;
const int RS = A1;

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);


// Motor Pins

const int motorPin1 = 4;
const int motorPin2 = 5;
const int motorPin3 = 2;
const int motorPin4 = 3;


// IR and Ultrasonic Sensor Pins

const int IRsensor = 8;

IRrecv IRinput(IRsensor);
decode_results result;

const int USsensor = 9;


// Power LED

const int powerLED = 13;


// Motor Movement Methods

void forward() {
  
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);  }

void reverse() {
  
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);   }
 
void rotateClockwise() {
  
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);   }
 
void rotateCounterClockwise() {
  
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);  }

void stop() {
  
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);   }
  
  
// Ultrasonic Distance Method

long distance() {
  
  pinMode(USsensor, OUTPUT);
  digitalWrite(USsensor, LOW);
  delayMicroseconds(2);
  digitalWrite(USsensor, HIGH);
  delayMicroseconds(5);
  digitalWrite(USsensor, LOW);
  
  pinMode(USsensor, INPUT);
  
  long duration = pulseIn(USsensor, HIGH);
  
  return duration / 46;   }



void setup() {
  
  Serial.begin(9600);
  IRinput.enableIRIn();
  
  pinMode(powerLED, OUTPUT);
  digitalWrite(powerLED, HIGH);
  
  pinMode(IRsensor, INPUT);
  
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  delay(700);
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("UNOBot 1.0");  }

void loop() {
 
  IRinput.decode(&result);
  
   IRinput.resume();
  
   Serial.println(result.value);
  
 switch(result.value) {
 
 case 16582903: 
 
  if (distance() >= 15) { forward(); } 
  
  if (distance() < 15) { 
    
    // REQUIRES MODIFICATION
    stop(); 
    delay(100); 
    reverse(); 
    delay(200); 
    rotateClockwise(); 
    delay(300); 
    forward(); }
    
  break;
 
 case 16615543: forward(); break; 
 case 16601263: forward(); break; 
 case 16589023: rotateCounterClockwise(); break;
 case 16605343: rotateClockwise(); break;
 case 16584943: reverse(); break;
 case 16621663: stop(); break; 
  
  default: 

  if (distance() >= 15) { forward(); } 
  
  if (distance() < 15) { 
  
    // REQUIRES MODIFICATION
    stop(); 
    delay(100); 
    reverse(); 
    delay(200); 
    rotateClockwise(); 
    delay(300); 
    forward(); }
    
  break; }
  
  delay(300);   }
