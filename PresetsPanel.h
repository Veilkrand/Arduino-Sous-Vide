#ifndef PresetsPanel_h
#define PresetsPanel_h

#include "Arduino.h"

#include "PanelGUI.h"

#include "Settings.h"

#include "MainPanel.h"


class PresetsPanel: 
public PanelGUI
{

public:

  PresetsPanel(String headText,String subheadText,UTFT *myGLCD,UTouch *myTouch,UTFT_Buttons *myButtons,SettingsType *settings,CallbackFunction eventCallbackFunction,MainPanel *mainPanel);

  void show();



private:
  

  SettingsType *_settings;

  MainPanel *_mainPanel;

  int buttonsLine[5];
  int butTop;

  String getFloatString(float value);
  String formatTemperature(float temperature);

  void updateTemperatureLabel();
  void updateTimeLabel();
  void updatePresetLabel(String presetString);  



};

#endif

