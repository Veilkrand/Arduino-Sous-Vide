#ifndef GraphPanel_h
#define GraphPanel_h

#include "Arduino.h"
#include <UTFT.h>
#include "Settings.h"

class GraphPanel
{
  
  public:
        
        GraphPanel(UTFT *myGLCD,SettingsType *settings);
        /*
        void setHeadText(String headText);
        void setSubheadText(String subheadText);	
*/        
        void drawFrame(int minValue);
        
        void drawValue(float tempValue);
        void setHeight(int height);  
  
  private:
  
  SettingsType *_settings;
  UTFT *_myGLCD;
  
  int _height;
  
  int _graphIndex;
  
  int _sizeX;
  int _sizeY;
  
  int   _maxValue;
  int _minValue;
  
  int _oldyValue;
  int _yValue;
  
  String formatTemperature(float temperature);
  String getFloatString(float value);
  /*
  void updateTemperatureLabel();
  void updateTimeLabel();

  void updatePresetLabel(String presetString);
  void updatePresetLabel();  
  void resetPreset();
  */
  
    
};

#endif
