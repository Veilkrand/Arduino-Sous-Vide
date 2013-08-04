/*
July 2013
Alberto Naranjo Galet
alberto[dot]galet[at]gmail[dot]com


ARDUINO SOUS-VIDE SMART APPLIANCE
=================================


HARDWARE
- Arduino Mega
- Sainsmart TFT/Touch shield
- Sainsmart TFT/Touch display

- PIN:A0 -> Waterproof DS18B20 Digital temperature sensor http://www.adafruit.com/products/381
- PIN:A7 -> TailGateII http://www.adafruit.com/products/268

- Reference from: http://learn.adafruit.com/sous-vide-powered-by-arduino-the-sous-viduino/the-whole-enchilada


EXTERNAL CLASSES
- TFT/Touch/Buttons classes from http://www.henningkarlsen.com/electronics
- DallasTemperature.h + OneWire.h for controlling the DS18B20 Digital temperature sensor
- PID_v1.h PID Controller

CLASS HIERARCHY
- Main file
  - PanelGUI
    -- CookingPanel
       - GraphPanel
       - TemperatureSensor
    -- MainPanel
    -- PresetsPanel
    -- SettingsPanel
    -- Settings.h


CLASS DOCS

* Main file
Initialize display, touch and button class. Initialize Panel classes and receive callback from them to switch panel. It loses the flow control to panels.


*/


#include <avr/EEPROM.h>
#include <UTFT.h>
#include <UTouch.h>
#include <UTFT_Buttons.h>
// web: http://www.henningkarlsen.com/electronics

//Settings struct
#include "Settings.h"

#include <Time.h>
#include <TimeAlarms.h>


//Implementation of Panel Classes
#include "MainPanel.h"
#include "SettingsPanel.h"
#include "PresetsPanel.h"
#include "CookingPanel.h"

#include <OneWire.h>
#include <DallasTemperature.h>

// Declare which fonts we will be using
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t Dingbats1_XL[];

// Set up UTFT...
// Set the pins to the correct ones for your development board
// -----------------------------------------------------------
// Standard Arduino 2009/Uno/Leonardo shield   : <display model>,19,18,17,16
// Standard Arduino Mega/Due shield            : <display model>,38,39,40,41
// CTE TFT LCD/SD Shield for Arduino Due       : <display model>,25,26,27,28
// Standard chipKit Uno32/uC32                 : <display model>,34,35,36,37
// Standard chipKit Max32                      : <display model>,82,83,84,85
// AquaLEDSource All in One Super Screw Shield : <display model>,82,83,84,85
//
// Remember to change the model parameter to suit your display module!
UTFT myGLCD(ITDB32S,38,39,40,41);

// Set up UTouch...
// Set the pins to the correct ones for your development board
// -----------------------------------------------------------
// Standard Arduino 2009/Uno/Leonardo shield   : 15,10,14,9,8
// Standard Arduino Mega/Due shield            : 6,5,4,3,2
// CTE TFT LCD/SD Shield for Arduino Due       : 6,5,4,3,2
// Standard chipKit Uno32/uC32                 : 20,21,22,23,24
// Standard chipKit Max32                      : 62,63,64,65,66
// AquaLEDSource All in One Super Screw Shield : 62,63,64,65,66
UTouch myTouch(6,5,4,3,2);

// Finally we set up UTFT_Buttons :)
UTFT_Buttons  myButtons(&myGLCD, &myTouch);
  
  
  //Panels ids for callback function/delegate
  #define mainPanel 0
  #define presetPanel 1
  #define cookingPanel 2  
  #define configPanel 3
  
  
  SettingsType settings;
  
  
  MainPanel panelMain("Cook Settings","Preset: None ",&myGLCD, &myTouch,&myButtons,&settings,switchPanelCallback);
  SettingsPanel panelSettings("Configuration"," ",&myGLCD, &myTouch,&myButtons,&settings,switchPanelCallback);
  PresetsPanel panelPresets("Presets","Select a cooking preset",&myGLCD, &myTouch,&myButtons,&settings,switchPanelCallback,&panelMain);
  CookingPanel panelCooking("Cooking 0:0:0","",&myGLCD, &myTouch,&myButtons,&settings,switchPanelCallback);
  

void setup()
{
  
  //Serial.begin(9600);
   
  myGLCD.InitLCD();
  
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  //myGLCD.setFont(BigFont);

  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);
  
  myButtons.setTextFont(BigFont);
  myButtons.setSymbolFont(Dingbats1_XL);
  
  /*
  //Write factory settings. Only first time!!!
  SettingsType settings={temperature,time,fahrenheit,preheating};
  eeprom_write_block((void*)&settings, (void*)0, sizeof(SettingsType));
*/

  //Load Settings
  eeprom_read_block((void*)&settings, (void*)0, sizeof(SettingsType));
  
  
  //Serial.print(settings.temperature);
  
  panelMain.show();


  
}

void switchPanelCallback(int toPanel){
  
  Serial.print(toPanel);
  
  switch(toPanel){
   
    case mainPanel:
    saveSettings();
    panelMain.show();
    break;
    case presetPanel:
    panelPresets.show();
    break;
    case cookingPanel:
    panelCooking.show();
    break;
    case configPanel:
    panelSettings.show();
    break;
    
  }
  
}



void loop(){
      
//Doesn't run while in the loop inside panel objects



}

void saveSettings(){

    eeprom_write_block((void*)&settings, (void*)0, sizeof(SettingsType));
    
}




