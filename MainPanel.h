#ifndef MainPanel_h
#define MainPanel_h

#include "Arduino.h"

#include "PanelGUI.h"

#include "Settings.h"



class MainPanel: public PanelGUI
{
  
  public:
        
        MainPanel(String headText,String subheadText,UTFT *myGLCD,UTouch *myTouch,UTFT_Buttons *myButtons,SettingsType *settings,CallbackFunction eventCallbackFunction);
        /*
        void setHeadText(String headText);
        void setSubheadText(String subheadText);	
*/        
        void show();

  
  
  private:
  
  SettingsType *_settings;

  
  String getFloatString(float value);
  String formatTemperature(float temperature);
  
  void updateTemperatureLabel();
  void updateTimeLabel();
  void updatePresetLabel(String presetString);
  
  int butHourPlusTime;
  int butHourMinusTime;
  int butMinusTemp;
  int butPlusTemp;
  int butStart;
  int butTop0;
  int butTop1;
  
  
  
  /*
    UTFT *_myGLCD;
    UTouch *_myTouch;
    
    String _headText;
    String _subheadText;    
    */
    
};

#endif
