/*
  Analog input, analog output, serial output
 
 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.
 
 The circuit:
 * potentiometer connected to analog pin 0.
   Center pin of the potentiometer goes to the analog pin.
   side pins of the potentiometer go to +5V and ground
 * LED connected from digital pin 9 to ground
 
 created 29 Dec. 2008
 modified 9 Apr 2012
 by Tom Igoe
 
 This example code is in the public domain.
 
 */
 
// import the library (must be located in the
// Arduino/libraries directory)
#include <CapacitiveSensor.h>
#include <Time.h>

// create an instance of the library
// pin 4 sends electrical energy
// pin 2 senses senses a change
CapacitiveSensor cs_4_2 = CapacitiveSensor(4,2);
CapacitiveSensor cs_4_8 = CapacitiveSensor(4,8);

int threshold = 300;

boolean switch1 = false;
boolean switch2 = false;
boolean start_timer_switch2 = false;

int r = 255;
int g = 0;
int b = 0;

unsigned long time_switch2;
unsigned long time;

boolean fadeto = false;

// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin1 = A0;  // Analog input pin that the potentiometer is attached to
const int analogInPin2 = A1;  // Analog input pin that the potentiometer is attached to
const int analogInPin3 = A2;  // Analog input pin that the potentiometer is attached to
const int analogInPin4 = A3;  // Analog input pin that the potentiometer is attached to
const int led1OutPin = 6; // Analog output pin that the LED is attached to
const int led2OutPin = 9;
const int led3OutPin = 10;
const int led4OutPin = 11;
const int ledgeschirr = 13;

const int vibration = 12;

const int REDPin = 3;
const int GREENPin = 5;
//const int BLUEPin = 6;

int sensor1Value = 0;        // value read from the pot
int output1Value = 0;        // value output to the PWM (analog out)
int sensor2Value = 0;        // value read from the pot
int output2Value = 0;        // value output to the PWM (analog out)
int sensor3Value = 0;        // value read from the pot
int output3Value = 0;        // value output to the PWM (analog out)
int sensor4Value = 0;        // value read from the pot
int output4Value = 0;        // value output to the PWM (analog out)

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
  
  pinMode(REDPin, OUTPUT);
  pinMode(GREENPin, OUTPUT);
  //pinMode(BLUEPin, OUTPUT);
  
  pinMode(led1OutPin, OUTPUT);
  pinMode(led2OutPin, OUTPUT);
  pinMode(led3OutPin, OUTPUT);
  pinMode(led4OutPin, OUTPUT);
  
  
  
  pinMode(vibration, OUTPUT);
  pinMode(ledgeschirr, OUTPUT);
}

void loop() {
  
  //Backofen
  long sensorValue_1 = cs_4_2.capacitiveSensor(30);
  
  if(sensorValue_1 > threshold) {
    // turn the LED on
    //digitalWrite(ledPin, HIGH);
    switch1 = !switch1;
    delay(400);
  }
  
   if( switch1 == true ) { 
    
    ofen();
    //digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(REDPin, LOW);
    digitalWrite(GREENPin, LOW);
    //digitalWrite(BLUEPin, LOW);
  }  

  delay(10);
  
  //GeschirrSpüler
  long sensorValue_2 = cs_4_8.capacitiveSensor(30);
  
  if(sensorValue_2 > threshold * 2) {
    // turn the LED on
      
      start_timer_switch2 = true;
      
      time_switch2 = millis();
     
      delay(400);
      
  }
  
  
   time = (millis() - time_switch2);
     
     if( time < 3000 && start_timer_switch2 == true) { 
       Serial.print(time);
        switch2 = true;
      } else {
        switch2 = false;
        start_timer_switch2 = false;
      }
  
  if( switch2 == true ) { 
    
    Serial.print(time_switch2);
    //Serial.print(millis());
    
    digitalWrite(vibration, HIGH);
    
    digitalWrite(ledgeschirr, HIGH);
    
    
    //digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(vibration, LOW);
    //digitalWrite(BLUEPin, LOW);
    digitalWrite(ledgeschirr, LOW);
  } 
  
  // read the analog in value:
  sensor1Value = analogRead(analogInPin1);
  sensor2Value = analogRead(analogInPin2);
  sensor3Value = analogRead(analogInPin3);
  sensor4Value = analogRead(analogInPin4);
  // map it to the range of the analog out:
  output1Value = map(sensor1Value, 0, 1023, 0, 255);
  output2Value = map(sensor2Value, 0, 1023, 0, 255);
  output3Value = map(sensor3Value, 0, 1023, 0, 255);
  output4Value = map(sensor4Value, 0, 1023, 0, 255);
  // change the analog out value:
  analogWrite(led1OutPin, output1Value);
  analogWrite(led2OutPin, output2Value);
  analogWrite(led3OutPin, output3Value);
  analogWrite(led4OutPin, output4Value);

  // print the results to the serial monitor:
  Serial.print("sensor = " );                       
  Serial.print(sensor1Value);      
  Serial.print("\t output = ");      
  Serial.println(output1Value);   

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(2);                     
}

void ofen() {


analogWrite(REDPin, r);
analogWrite(GREENPin, g);
//analogWrite(BLUEPin, b);

 Serial.println(g);
              
              if ( g <= 0 ) {
               fadeto = true;
              } 
              
              if ( g > 160 ) {
               fadeto = false;
              } 
              
  if ( fadeto == true ) {
    g++;
  } else {
    g--;
  }            

//digitalWrite(GREENPin, HIGH);

}


