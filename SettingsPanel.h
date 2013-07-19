#ifndef SettingsPanel_h
#define SettingsPanel_h

#include "Arduino.h"

#include "PanelGUI.h"

#include "Settings.h"



class SettingsPanel: public PanelGUI
{
  
  public:
        
        SettingsPanel(String headText,String subheadText,UTFT *myGLCD,UTouch *myTouch,UTFT_Buttons *myButtons,SettingsType *settings,CallbackFunction eventCallbackFunction);
        /*
        void setHeadText(String headText);
        void setSubheadText(String subheadText);	
*/        
        void show();

  
  
  private:
  
  SettingsType *_settings;

  int buttonsLine[];
  
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
