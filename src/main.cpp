#include <Arduino.h>

//simModePin high: input value on sinSource pin
//simModePin low: random generated value between min and max defined below
#define simModePin     2 
#define simSource      A0


//high: transmitance
//low: absorbance
#define measureUnitPin 3

#define transmitance " %T"
#define absorbance " Abs"

void setup() {
  //initialize inputs
  pinMode(simModePin, INPUT_PULLUP);
  pinMode(simSource, INPUT);
  pinMode(measureUnitPin, INPUT_PULLUP);

  //digitalWrite(simModePin, LOW);
  //digitalWrite(measureUnitPin, LOW);

  //initialize serial
  Serial.begin(9600, SERIAL_7N1);
  
  //okay, lets start
  Serial.println("spectro femto 600 SIMULATOR");
}

void loop() {
  //choose mode 
  bool autoGenerate = digitalRead(simModePin);
  bool unitPinState = !digitalRead(measureUnitPin);

  String reading = "";

  String unit = unitPinState ? transmitance : absorbance;

  //generate data
  float rawValue = 
        autoGenerate ? 
        random((92000), (101000))/1000:
        map(analogRead(simSource), 0, 1024, 10, 200000)/1000;

  float read = 
        unitPinState ?
        rawValue : //transmitance value
        (2-log10(rawValue)); //transmitance
  
  
  //debug values
  //reading = 
  //        "raw value: " + 
  //        String(rawValue)+ 
  //        " reading: " + 
  //        (unitPinState ? String(read, 2) : String(read, 3)) + 
  //        unit;
  
 
  reading =
          "  " + 
          (unitPinState ? String(read, 2) : String(read, 3)) + 
          unit;

  //print reading
  Serial.println(reading);
  
  //delay
  delay(500);
}