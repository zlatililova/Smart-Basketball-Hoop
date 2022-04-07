    
#include <Servo.h>

const int trigPinBase = 6; // Trigger Pin of Ultrasonic Sensor
const int echoPinBase = 7; // Echo Pin of Ultrasonic Sensor
const int BaseServoPin = 8;
const int SensorServoPin = 9;
const int trigPinHoop = 11;
const int echoPinHoop = 12;
const int ledPin = 4;

Servo ServoBase;
Servo ServoSensor;

void setup() {
  Serial.begin(9600);
  ServoBase.attach(BaseServoPin);
  ServoSensor.attach(SensorServoPin);
  pinMode(trigPinBase, OUTPUT);
  pinMode(echoPinBase, INPUT);
  pinMode(trigPinHoop, OUTPUT);
  pinMode(echoPinHoop, INPUT);
  pinMode(ledPin, OUTPUT);
      
}

int position = 0;

void loop() {
  digitalWrite(ledPin, LOW);
 ServoBase.write(90);
  position = ServoSen_rotation();
  //delay(7000);
  Serial.println("HERE!\n");
  //delay(1000);
  while(ring_signal() != 0)
  {
    Serial.println("Stays in position");
    Serial.println(ring_signal());
    Serial.println("\n");
    
    
      delay(100);
    
  }
  Serial.println("Scored!");
  digitalWrite(ledPin, HIGH);
  delay(5000);
  
  
}

int ServoSen_rotation(){
  long cm;
  int i = 0;
  for(i =0; i < 180; i+=10){
        ServoSensor.write(i);
           delay(1200);
          cm = Base_signal();
           
          if(cm <45){
            ServoBase.write(i);
              return i;
          } 
           delay(500);
  }
  
}

long Base_signal(){
  long cm, duration;
  
          digitalWrite(trigPinBase, LOW);
           delayMicroseconds(2);
           digitalWrite(trigPinBase, HIGH);
           delayMicroseconds(10);
           digitalWrite(trigPinBase, LOW);
          duration = pulseIn(echoPinBase, HIGH);
           cm = microsecondsToCentimeters(duration);
          Serial.print("Base signal ");
          Serial.print(cm);
          Serial.print("\n");

    return cm;
}

long ring_signal(){
  long cm, duration;
  
          digitalWrite(trigPinHoop, LOW);
           delayMicroseconds(2);
           digitalWrite(trigPinHoop, HIGH);
           delayMicroseconds(10);
           digitalWrite(trigPinHoop, LOW);
          duration = pulseIn(echoPinHoop, HIGH,500);
           cm = microsecondsToCentimeters(duration);
 
  if(cm < 5){
    Serial.println(duration);
    Serial.println("Ring signsl scored");
    Serial.println(cm);
      return 0;
  }
  else{
      return 1;
  }
}
long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
