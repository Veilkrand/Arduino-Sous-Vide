#include "TemperatureSensor.h"

/* Notice the Initialiser List in the constructor...*/
TemperatureSensor::TemperatureSensor(uint8_t pin) : oneWire(pin), sensors(&oneWire)
{
 
  // Start up the library
  sensors.begin();

}

float TemperatureSensor::getTemp(){
  
  sensors.requestTemperatures(); // Send the command to get temperatures
  return sensors.getTempCByIndex(0);
  
}
