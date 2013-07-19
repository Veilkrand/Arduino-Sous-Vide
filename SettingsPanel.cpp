#include "Arduino.h"
#include "SettingsPanel.h"

SettingsPanel::SettingsPanel(String headText,String subheadText,UTFT *myGLCD,UTouch *myTouch,UTFT_Buttons *myButtons,SettingsType *settings,CallbackFunction eventCallbackFunction):PanelGUI(headText,subheadText,myGLCD,myTouch,myButtons,eventCallbackFunction)
{
  

  _settings=settings;
  
  //float temperature=_settings->temperature;
  //Serial.print(temperature);

}

void SettingsPanel::show(){
  /*
  _myGLCD->clrScr();
  _myButtons->deleteAllButtons();  
  setHeadText(_headText);
  setSubheadText(_subheadText);
 */
 
   
  _sizeX=_myGLCD->getDisplayXSize();
  _sizeY=_myGLCD->getDisplayYSize();
 
   clearScreen();
   
   isActive=true;
   
   
   
  _myGLCD->setFont(SmallFont);
  _myGLCD->print("Sous-Vide Cooker V0.5",5,_sizeY-27);
  _myGLCD->print("Alberto Naranjo - July 2013",5, _sizeY-15);


  butTop0 = _myButtons->addButton(_sizeX-_buttonHeight-2, 2,  _buttonHeight,  _buttonHeight, "<");
 
  int startX=40;
  //myButtons.setTextFont(SmallFont);
  buttonsLine[0]=_myButtons->addButton( 10, startX+0*_buttonHeight+5, _sizeX-10*2,  _buttonHeight,"");
  
  if (_settings->fahrenheit){
    _myButtons->relabelButton(buttonsLine[0],"Temp. Fahrenheit",true);
  }else{
    _myButtons->relabelButton(buttonsLine[0],"Temp. Celsious",true);
  }

  buttonsLine[1]=_myButtons->addButton( 10, startX+1*_buttonHeight+5, _sizeX-10*2,  _buttonHeight, "");  
  if (_settings->preheating){
//    str_tmp="Preheating is ON";
  _myButtons->relabelButton(buttonsLine[1],"Preheating is ON",true);
  }else{
  //  str_tmp="Preheating is OFF";
  _myButtons->relabelButton(buttonsLine[1],"Preheating is OFF",true);
  }
  
  _myButtons->drawButtons();
  
  
  while(isActive){
    
    if (_myTouch->dataAvailable() == true){
      
      int pressed_button = _myButtons->checkButtons();
      
      
      
      if (pressed_button==buttonsLine[0]){
           if (_settings->fahrenheit){
             _settings->fahrenheit=false;
             _myButtons->relabelButton(buttonsLine[0], "Temp. Celsious",true); 
             
           }else{
             _settings->fahrenheit=true;
             _myButtons->relabelButton(buttonsLine[0], "Temp. Fahrenheit",true); 
           }
         }
         if (pressed_button==buttonsLine[1]){
           if (_settings->preheating){
             _settings->preheating=false;
             _myButtons->relabelButton(buttonsLine[1], "Preheating is OFF",true); 
             
           }else{
             _settings->preheating=true;
             _myButtons->relabelButton(buttonsLine[1], "Preheating is ON",true); 
           }
         }
      
      if(pressed_button==butTop0){
        
        isActive=false;
        _eventCallbackFunction(0);
        
      }
      
      if(pressed_button==butTop1){
  
        //drawPresetPanel();
      }
      
      
    }
    
  }
  
  
  
  //_eventCallbackFunction(0);
  
}

