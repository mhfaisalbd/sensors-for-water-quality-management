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

float quality(float volt){
  volt = 5.0 - volt;
  volt = ((1995*(volt-4.8))/68)+100;
  return volt;
}



void loop(void){ 
  int trsensor = analogRead(A0);
  int phsensor = analogRead(A1);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = trsensor * (5.0 / 1023.0);
  // print out the value you read:
   Serial.print("Turbidity (in NTU): ");
  Serial.println(quality(voltage));
  Serial.print("Voltage Return: ");
  Serial.println(voltage);
  delay(2000);

  float ph = phsensor * (5.0 / 1023.0);
  Serial.print("PH Return: ");
  Serial.println(ph);
  ph = ph*2.8;
  Serial.print("PH: ");
  Serial.println(ph);
  delay(2000);
  // Call tmpsensor.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  tmpsensor.requestTemperatures(); 
  
  Serial.print("Celsius temperature: ");
  // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  Serial.println(tmpsensor.getTempCByIndex(0)); 
  Serial.print("Fahrenheit temperature: ");
  Serial.println(tmpsensor.getTempFByIndex(0));
  delay(2000);
}
