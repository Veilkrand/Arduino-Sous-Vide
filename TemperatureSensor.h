#ifndef TemperatureSensor_h
#define TemperatureSensor_h


#include <OneWire.h>
#include <DallasTemperature.h>


#include "Arduino.h"


class TemperatureSensor{
  
  public:
        
        TemperatureSensor(uint8_t pin);
        
        float getTemp();
 
  
  private:
  
  // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
  OneWire oneWire;
  // Pass our oneWire reference to Dallas Temperature. 
  DallasTemperature sensors;  
 
};

#endif
