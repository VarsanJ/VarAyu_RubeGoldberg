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
  // Establishes input/output mode for each connected pin
  pinMode(ultrasonicTriggerpin, OUTPUT);
  pinMode(ultrasonicEchopin, INPUT);
  pinMode(servoMpin, OUTPUT);

  // Connects servo motor and establishes serial for display
  servoM.attach(servoMpin);
  Serial.begin(9600); 

  // Sets initial angle position for the servo
  servoM.write(180);
}

void loop() {
  //Startup, including establishing each pins state and delays help ensure code runs smoothly
  digitalWrite(ultrasonicTriggerpin, LOW);
  delayMicroseconds(2);
  digitalWrite(ultrasonicTriggerpin, HIGH);
  delayMicroseconds(5);
  digitalWrite(ultrasonicTriggerpin, LOW);
  
  // Obtains the time, and uses the time and physics formula to determine distance from the sensor. Displays this information to serial for testing purposes
  Xtime = pulseIn(ultrasonicEchopin, HIGH); 
  Serial.print("Time is ");
  Serial.println(Xtime);
  distance = Xtime/29/2;
  Serial.print("Distance is ");
  Serial.println(distance);

  // Primary functionality of the code, to run once object (the car) falls in front of the sensor
  if (distance < 10) // Physically designed on the build itself
  {
    for (int i = 0; i<= 15; i++)
    {
      servoM.write(Position);
      Position -= 6; // Modifies the positon in a for loop for a nice delayed rotation until the servo motor arm hits another ball
      Serial.println("Detected!}");
      delay(4000);
    }
  servoM.write(180); // At end restores position to initial location 
  }
}
