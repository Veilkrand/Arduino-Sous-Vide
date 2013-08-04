#ifndef CookingPanel_h
#define CookingPanel_h

#include "Arduino.h"

#include "PanelGUI.h"

#include "Settings.h"

#include "TemperatureSensor.h"

#include "GraphPanel.h"


//pins
#define PIN_TEMPPROBE A0 //Dallas DS18B20
#define PIN_POWERTAIL A7 //PowerSwitch Tail II

class CookingPanel: public PanelGUI
{
  
  public:
        
        CookingPanel(String headText,String subheadText,UTFT *myGLCD,UTouch *myTouch,UTFT_Buttons *myButtons,SettingsType *settings,CallbackFunction eventCallbackFunction);
        /*
        void setHeadText(String headText);
        void setSubheadText(String subheadText);	
*/        
        void show();
        
        
//        String presetString;
        
          void updateTemperature();

  
  
  private:
  
  SettingsType *_settings;
  
  String getFloatString(float value);
  String formatTemperature(float temperature);



  
  TemperatureSensor mySensor;
  GraphPanel myGraph;
  
  float tempC;
  void drawGraphLine();
  int _graphIndex;
  
  /*
  void updateTemperatureLabel();
  void updateTimeLabel();

  void updatePresetLabel(String presetString);
  void updatePresetLabel();  
  void resetPreset();
  */
  
  int butTop;
  
  /*
  int butHourPlusTime;
  int butHourMinusTime;
  int butMinusTemp;
  int butPlusTemp;
  int butStart;
  int butTop0;
  int butTop1;
  */
  
  
  /*
    UTFT *_myGLCD;
    UTouch *_myTouch;
    
    String _headText;
    String _subheadText;    
    */
    
};

#endif
