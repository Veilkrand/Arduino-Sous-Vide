#include "Arduino.h"
#include "MainPanel.h"

MainPanel::MainPanel(String headText,String subheadText,UTFT *myGLCD,UTouch *myTouch,UTFT_Buttons *myButtons,SettingsType *settings,CallbackFunction eventCallbackFunction):PanelGUI(headText,subheadText,myGLCD,myTouch,myButtons,eventCallbackFunction)
{
  

  _settings=settings;
  
  //float temperature=_settings->temperature;
  //Serial.print(temperature);

}

void MainPanel::show(){
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
  _myGLCD->print("Temperature: ", _buttonPosX, _buttonPosY-15);
  int butPlusTemp= _myButtons->addButton( _buttonPosX,  _buttonPosY, _buttonWidth,  _buttonHeight, "+");
  
  
  updateTemperatureLabel();
  
  
  _myGLCD->setFont(SmallFont);  
  int butMinusTemp = _myButtons->addButton(_buttonPosX, _buttonPosY+_buttonHeight+5+16+5, _buttonWidth,  _buttonHeight, "-");


  _myGLCD->print("Time: ", _buttonPosX+110, _buttonPosY-15);
  
  int butHourPlusTime= _myButtons->addButton( _buttonPosX+110,  _buttonPosY, _buttonWidth,  _buttonHeight, "+H");
  int butPlusTime= _myButtons->addButton( _buttonPosX+110+_buttonWidth+5,  _buttonPosY, _buttonWidth,  _buttonHeight, "+m");
  updateTimeLabel();
  int butHourMinusTime = _myButtons->addButton( _buttonPosX+110,  _buttonPosY+_buttonHeight+5+16+5, _buttonWidth,  _buttonHeight, "-H");
  int butMinusTime = _myButtons->addButton( _buttonPosX+110+_buttonWidth+5,  _buttonPosY+_buttonHeight+5+16+5, _buttonWidth,  _buttonHeight, "-m");

  int butTop0 = _myButtons->addButton(_sizeX-_buttonHeight-3, 2,  _buttonHeight,  _buttonHeight, "d", BUTTON_SYMBOL);

  int butTop1 = _myButtons->addButton(_sizeX-_buttonHeight*2-6, 2, _buttonHeight,  _buttonHeight, "w", BUTTON_SYMBOL);
  
  int butStart=_myButtons->addButton( 15, _sizeY-_buttonHeight-15, _sizeX-15*2,  _buttonHeight, "START");
 
  
  _myButtons->drawButtons();
  
  
  while(isActive){
    
    if (_myTouch->dataAvailable() == true){
      
      int pressed_button = _myButtons->checkButtons();
      
      
      if (pressed_button==butPlusTemp){
        updatePresetLabel("None          ");  
        _settings->temperature+=0.5;
        updateTemperatureLabel();
      }
      if (pressed_button==butMinusTemp){
        updatePresetLabel("None          ");  
        _settings->temperature-=0.5;
        updateTemperatureLabel();
      }
      
      if (pressed_button==butPlusTime){
        updatePresetLabel("None          ");          
        _settings->time+=1;
        updateTimeLabel();
      }
      if (pressed_button==butMinusTime){
        updatePresetLabel("None          ");          
        _settings->time-=1;
        updateTimeLabel();
      }
      if (pressed_button==butHourPlusTime){
        updatePresetLabel("None          ");          
        _settings->time+=60;
        updateTimeLabel();
      }
      if (pressed_button==butHourMinusTime){
        updatePresetLabel("None          ");          
        _settings->time-=60;
        updateTimeLabel();
      }
      
      if (pressed_button==butStart){
      
           //drawCookingPanel();
           isActive=false;
           _eventCallbackFunction(0);
           
      }
      
      if(pressed_button==butTop0){
  
        //isActive=false;
        //_eventCallbackFunction(3);
      }
      
      if(pressed_button==butTop1){
  
         isActive=false;
        _eventCallbackFunction(3);
      }
      
      
    }
    
  }
  
  
  
  //_eventCallbackFunction(0);
  
}

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
