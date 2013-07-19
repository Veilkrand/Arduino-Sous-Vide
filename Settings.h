#ifndef Settings_h
#define Settings_h

#include "Arduino.h"

//Settings type
  typedef struct
  {
    float temperature;
    int time;
    boolean fahrenheit;
    boolean preheating;
  }  SettingsType;


#endif
