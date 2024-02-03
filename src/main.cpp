#include <Arduino.h>

// Pins
int blueLED = 26; 
int greenLED = 14; 
int redLED = 27; 
int pinButton1 = 25;
int pinButton2 = 33;
int pinButton3 = 32;

//Read button
int button1_read ; // increase intensity
int button2_read ; // decrease intensity
int button3_read ;
int button3_old ; // Toggle switch


//Command for pwm
int freq = 5000 ;
int resolution = 8 ;
int ledChannel = 0 ;

//define the duty-cycle 
int dutyCycle = 127 ;

int state = 0 ; // LED Off in the begin

void setup() {

  //Setup Serial
  Serial.begin(921600);
  Serial.println("Initializing SetUp");

  //Setup Red and green LED
  pinMode(greenLED,OUTPUT);
  pinMode(redLED,OUTPUT);
  
  //Setup PWM Led (Blue LED)
  ledcSetup(ledChannel,freq,resolution);
  ledcAttachPin(blueLED,ledChannel);

  //Setup Button PIN
  pinMode(pinButton1,INPUT);
  pinMode(pinButton2,INPUT);
  pinMode(pinButton3,INPUT);

  ledcWrite(ledChannel,255);
  delay(200);
  digitalWrite(greenLED,HIGH);
  delay(200);
  digitalWrite(redLED,HIGH);
  delay(1000);

  ledcWrite(ledChannel,0);
  delay(200);
  digitalWrite(greenLED,LOW);
  delay(200);
  digitalWrite(redLED,LOW);
  delay(1000);

}

void loop() {

  delay(15);
  button3_read = !digitalRead(pinButton3) ;
  button1_read = !digitalRead(pinButton1) ; // 1 if pressed
  button2_read = !digitalRead(pinButton2) ;

  Serial.print("Button 1 read : "); Serial.print(button1_read);
  Serial.print(" / Button 2 read : "); Serial.print(button2_read);
  Serial.print(" / Button 3 read : "); Serial.println(button3_read);

  
  if(button3_read == 1 && button3_old == 0){ //Enter the if statement if we have 1 and 0
    state = !state ;
  }

  button3_old = button3_read;

  if(state){

    Serial.println("Blue LED OFF ! ");
    ledcWrite(ledChannel,0);
    digitalWrite(redLED,HIGH);
    digitalWrite(greenLED,LOW);

  }
  else{
    
    Serial.println("Blue LED ON ! ");
    digitalWrite(redLED,LOW);
    digitalWrite(greenLED,HIGH);
    ledcWrite(ledChannel,dutyCycle); 

    if(button1_read && dutyCycle <255){
      dutyCycle++;
    }

    if(button2_read && dutyCycle > 1){
      dutyCycle-- ; 
    }

    Serial.print(" Duty Cycle : "); Serial.println(dutyCycle) ; 
  }
}

