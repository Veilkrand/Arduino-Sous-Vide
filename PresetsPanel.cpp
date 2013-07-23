#include "Arduino.h"
#include "PresetsPanel.h"

PresetsPanel::PresetsPanel(String headText,String subheadText,UTFT *myGLCD,UTouch *myTouch,UTFT_Buttons *myButtons,SettingsType *settings,CallbackFunction eventCallbackFunction,MainPanel *mainPanel):PanelGUI(headText,subheadText,myGLCD,myTouch,myButtons,eventCallbackFunction)
{
  

  _settings=settings;
  
  _mainPanel=mainPanel;
  
  //float temperature=_settings->temperature;
  //Serial.print(temperature);

}

void PresetsPanel::show(){
  /*
  _myGLCD->clrScr();
  _myButtons->deleteAllButtons();  
  setHeadText(_headText);
  setSubheadText(_subheadText);
 */
 
   
  _sizeX=_myGLCD->getDisplayXSize();
  _sizeY=_myGLCD->getDisplayYSize();
 
   
   isActive=true;
   
   clearScreen();  
  
  
  int startX=40;
  //myButtons.setTextFont(SmallFont);
  
  buttonsLine[0]=_myButtons->addButton( 10, startX+0*_buttonHeight+5, _sizeX-10*2,  _buttonHeight, "Eggs yolk: 64C 1H");
  buttonsLine[1]=_myButtons->addButton( 10, startX+1*_buttonHeight+5, _sizeX-10*2,  _buttonHeight, "Steak: 55C 2H30m");
  buttonsLine[2]=_myButtons->addButton( 10, startX+2*_buttonHeight+5, _sizeX-10*2,  _buttonHeight, "Chicken: 63.5C 2H");
  buttonsLine[3]=_myButtons->addButton( 10, startX+3*_buttonHeight+5, _sizeX-10*2,  _buttonHeight, "Fish: 60C 45m");  
  buttonsLine[4]=_myButtons->addButton( 10, startX+4*_buttonHeight+5, _sizeX-10*2,  _buttonHeight, "Vegetables: 84C 1H");
  
  butTop = _myButtons->addButton(_sizeX-_buttonHeight-2, 2,  _buttonHeight,  _buttonHeight, "<");
  
  
  _myButtons->drawButtons();
  
  
  while(isActive){
    
    if (_myTouch->dataAvailable() == true){
      
      int pressed_button = _myButtons->checkButtons();
       
      
       if (pressed_button==butTop){
     
           //drawCookingPanel();
           isActive=false;
           _eventCallbackFunction(0);
             
      } else if (pressed_button==buttonsLine[0]){
        //updatePresetLabel("None          ");  
        _mainPanel->presetString="Eggs yolk         ";
        _settings->temperature=64;
        _settings->time=60;
        
        isActive=false;
        _eventCallbackFunction(0);
      } else if (pressed_button == buttonsLine[1]){
        //updatePresetLabel("None          ");  
        _mainPanel->presetString="Steak         ";
        _settings->temperature=55;
        _settings->time=150;
        
        isActive=false;
        _eventCallbackFunction(0);
      } else if (pressed_button == buttonsLine[2]){
        //updatePresetLabel("None          ");  
        _mainPanel->presetString="Chicken         ";
        _settings->temperature=63.5;
        _settings->time=120;
        
        isActive=false;
        _eventCallbackFunction(0);
      }else if (pressed_button == buttonsLine[3]){
        //updatePresetLabel("None          ");  
        _mainPanel->presetString="Fish         ";
        _settings->temperature=60;
        _settings->time=45;
        
        isActive=false;
        _eventCallbackFunction(0);
      } else if (pressed_button == buttonsLine[4]){
        //updatePresetLabel("None          ");  
        _mainPanel->presetString="Vegetables         ";
        _settings->temperature=84;
        _settings->time=60;
        
        isActive=false;
        _eventCallbackFunction(0);
      }
      
      
    }
    
  }
  
  
  
}

/*
void MainPanel::updateTemperatureLabel(){
  
  int maxTemp=110;
  int minTemp=30;
  if (_settings->temperature<minTemp)_settings->temperature=minTemp;
  if (_settings->temperature>maxTemp)_settings->temperature=maxTemp;
  _myGLCD->setFont(BigFont);
 _myGLCD->print(formatTemperature(_settings->temperature), _buttonPosX, _buttonPosY+_buttonHeight+5);

  
}


void MainPanel::updateTimeLabel(){
  int maxTime=60*24;
  if (_settings->time<1)_settings->time=1;
  if (_settings->time>maxTime)_settings->time=maxTime;
  
  int hours = _settings->time / 60;
  int minutes = _settings->time % 60;
  
  _myGLCD->setFont(BigFont);
  //myGLCD.print(" "+String(time, DEC)+"m  ", xButStart+110, yButStart+buttonHeight+5);
  String str_hours=String(hours, DEC);
  String str_minutes=String(minutes, DEC);
  //if (hours<10)str_hours="0"+str_hours;
  //if (minutes<10)str_minutes="0"+str_minutes;
  _myGLCD->print(" "+String(hours, DEC)+"H:"+String(minutes, DEC)+"m ", _buttonPosX+110, _buttonPosY+_buttonHeight+5);
}

void MainPanel::updatePresetLabel(String presetString){
  //String preset="None";
  setSubheadText("Preset: "+ presetString);
//  _myGLCD->setFont(SmallFont);
 // _myGLCD->print("Preset: "+ presetString, 10, 5+20);
}

String MainPanel::getFloatString(float value){
  
  char tmp[10];
  if (_settings->fahrenheit){
    dtostrf(value,1,0,tmp);
  }else{
    dtostrf(value,1,1,tmp);
  }
  return String(tmp);
  
}

String MainPanel::formatTemperature(float temperature){
  String symbol="C ";
  if (_settings->fahrenheit){
    symbol="F ";
    temperature=round((temperature*9.0/5.0)+32.0);
  }
  return getFloatString(temperature)+symbol;
}
*/
