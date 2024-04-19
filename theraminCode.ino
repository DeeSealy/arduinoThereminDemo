#include <LiquidCrystal.h>

//ranges for sensors (cm)
float minDistance = 10;
float maxDistance = 40;

//pins !!NEEDS ADJUSTMENT!!

//Sensor
const int keyTrigPin = 9;
const int keyEchoPin = 8;

//speaker
const int speakerPin = 13;

//In-Progress Settings

//pitch
float currPitch = 65.41;
float currPitchMin = 65.41;
float currPitchMax = 2093.00;

//LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//led pins
int redPin = 10;
int greenPin = 7;

//note references
float C2 = 65.41;
float C3 = 130.81;
float C4 = 261.63;
float C5 = 523.25;
float C6 = 1046.50;
float C7 = 2093.00;

void RedLed(){
  analogWrite(greenPin, 0);
  analogWrite(redPin, 255);
}

void GreenLed(){
  analogWrite(redPin, 0);
  analogWrite(greenPin, 255);
}

void CurrentNote(){

  lcd.clear();

  Serial.println(currPitch);

  if (currPitch == C2) {

    lcd.setCursor(0,0);
    lcd.print(String(currPitch) + " Hz");
    lcd.setCursor(0,1);
    lcd.print("Current Note: C2");
    GreenLed();
  }
  else if (currPitch > C2 && currPitch < C3){
    lcd.setCursor(0,0);
    lcd.print(String(currPitch) + " Hz");
    lcd.setCursor(0,1);
    lcd.print("Between C2 and C3");
    RedLed();
  }
  else if (currPitch == C3) {
    lcd.setCursor(0,0);
    lcd.print(String(currPitch) + " Hz");
    lcd.setCursor(0,1);
    lcd.print("Current Note: C3");
    GreenLed();
  }
  else if (currPitch > C3 && currPitch < C4){
    lcd.setCursor(0,0);
    lcd.print(String(currPitch) + " Hz");
    lcd.setCursor(0,1);
    lcd.print("Between C3 and C4");
    RedLed();
  }
  else if (currPitch == C4){
    lcd.setCursor(0,0);
    lcd.print(String(currPitch) + " Hz");
    lcd.setCursor(0,1);
    lcd.print("Current Note: C4");
    GreenLed();
  }
  else if (currPitch > C4 && currPitch < C5){
    lcd.setCursor(0,0);
    lcd.print(String(currPitch) + " Hz");
    lcd.setCursor(0,1);
    lcd.print("Between C4 and C5");
    RedLed();
  }
  else if (currPitch == C5){
    lcd.setCursor(0,0);
    lcd.print(String(currPitch) + " Hz");
    lcd.setCursor(0,1);
    lcd.print("Current Note: C5");
    GreenLed();
  }
  else if (currPitch > C5 && currPitch < C6){
    lcd.setCursor(0,0);
    lcd.print(String(currPitch) + " Hz");
    lcd.setCursor(0,1);
    lcd.print("Between C5 and C6");
    RedLed();
  }
  else if (currPitch == C6){
    lcd.setCursor(0,0);
    lcd.print(String(currPitch) + " Hz");
    lcd.setCursor(0,1);
    lcd.print("Current Note: C6");
    GreenLed();
  }
  else if (currPitch > C6 && currPitch < C7){
    lcd.setCursor(0,0);
    lcd.print(String(currPitch) + " Hz");
    lcd.setCursor(0,1);
    lcd.print("Between C6 and C7");
    RedLed();
  }
  else if (currPitch == C7){
    lcd.setCursor(0,0);
    lcd.print(String(currPitch) + " Hz");
    lcd.setCursor(0,1);
    lcd.print("Current Note: C7");
    GreenLed();
  }
  
}

//pitch
void Sensor(){

  //Ping. If within range, adjust pitch

  //clear trigger pin
  digitalWrite(keyTrigPin, LOW);
  delayMicroseconds(2);

  //ping for 10? ms to send pulse
  digitalWrite(keyTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(keyTrigPin, LOW);

  //get the duration to find distance
  long duration = pulseIn(keyEchoPin, HIGH);

  //calculate distance 
  long distance = duration / 29 / 2;

  //if the distance is within our range, we need to adjust the pitch within our key range
  if (distance > minDistance && distance < maxDistance){

    //calculate the pitch via linear interpolation
    //forumla for linear interpolation: y = y1 + (x-x1)(y2-y1) / (x2-x1)
    //y is the Hz we need
    //x is current distance
    //x1 is min distance
    //x2 is max distance
    //y1 is min Hz (depends on current key)
    //y2 is max Hz (depends on current key)

    float y = currPitchMin + (distance - minDistance) * (currPitchMax - currPitchMin) / (maxDistance - minDistance);

    currPitch = y;

    if (currPitch < currPitchMin) currPitch = currPitchMin;
    if (currPitch > currPitchMax) currPitch = currPitchMax;
  }
  else {
    currPitch = currPitchMin;
    return;
  }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //set up the sensor
  pinMode(keyTrigPin, OUTPUT);
  pinMode(keyEchoPin, INPUT);

  //set up the speaker
  pinMode(speakerPin, OUTPUT);

  //led
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  //lcd
  lcd.begin(16,2);

}

void loop() {
  // put your main code here, to run repeatedly:

  //otherwise, we basically need it to keep playing in the note range and pinging the hands over the sensors
  Sensor();

  //play the note based on current volume and pitch
  tone(speakerPin, (unsigned int)currPitch);

  //show note info on LCD
  CurrentNote();

}
