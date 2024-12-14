/*
  Programmer/Designer: Varsan Jeyakkumar
  Project Partner: Ayushi Anuprova
  Project Title: Ultrasonic Control for Ruth Goldberg
  Project Purpose: To rotate a servo motor to release a marble upon the detection of a marble by the ultrasonic range finder
*/

// Variable Declaration for Ultrasonic Pins
#define ultrasonicEchopin  27
#define ultrasonicTriggerpin 14

// Variable Declaration for Calculation Variables
float Xtime = 0;
float distance = 0;

// Variable Declaration for Servos
#include <ESP32Servo.h>
Servo servoM;
const int servoMpin = 15;
int Position = 180;


void setup() {
  pinMode(ultrasonicTriggerpin, OUTPUT);
  pinMode(ultrasonicEchopin, INPUT);
  pinMode(servoMpin, OUTPUT);
  servoM.attach(servoMpin);
  Serial.begin(9600); //allows output
  servoM.write(180);
}

void loop() {
  //Startup
  digitalWrite(ultrasonicTriggerpin, LOW);
  delayMicroseconds(2);
  digitalWrite(ultrasonicTriggerpin, HIGH);
  delayMicroseconds(5);
  digitalWrite(ultrasonicTriggerpin, LOW);
  
  //Calculations
  Xtime = pulseIn(ultrasonicEchopin, HIGH); 
  Serial.print("Time is ");
  Serial.println(Xtime);
  distance = Xtime/29/2;
  Serial.print("Distance is ");
  Serial.println(distance);

  //Conditionals
  if (distance < 10)
  {
    for (int i = 0; i<= 15; i++)
    {
      servoM.write(Position);
      Position -= 6;
      Serial.println("Detected!}");
      delay(4000);
    }
  servoM.write(180);  
  }
}
