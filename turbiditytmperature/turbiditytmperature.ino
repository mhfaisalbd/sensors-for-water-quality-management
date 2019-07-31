#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is conntec to the Arduino digital pin 4
#define ONE_WIRE_BUS 4

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature tmpsensor(&oneWire);

void setup(void)
{
  // Start serial communication for debugging purposes
  Serial.begin(9600);
  // Start up the library
  tmpsensor.begin();
}

String quality(float volt){
  String q = "Filtered,No tred";
  if(volt >= 4.0){
    q = "Filtered,No tred";
  }
  else if(volt >= 3.25){
    q = "very Slightly tred";
  }
  else if(volt >= 3.0){
    q = "avarage tred";
  }
  else if(volt >= 2.5){
    q = "heavy tred";
  }
  else if(volt >= 2.5){
    q = "extrimely tred";
  }
  else if(volt < 2.5){
    q = "tred is greater than water";
  }
  return q;
}



void loop(void){ 
  int trsensor = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = trsensor * (5.0 / 1023.0);
  // print out the value you read:
  Serial.print(quality(voltage));
  Serial.print(" | Voltage Returned: ");
  Serial.println(voltage);
  delay(1000);
  
  // Call tmpsensor.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  tmpsensor.requestTemperatures(); 
  
  Serial.print("Celsius temperature: ");
  // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  Serial.print(tmpsensor.getTempCByIndex(0)); 
  Serial.print(" - Fahrenheit temperature: ");
  Serial.println(tmpsensor.getTempFByIndex(0));
  delay(1000);
}


