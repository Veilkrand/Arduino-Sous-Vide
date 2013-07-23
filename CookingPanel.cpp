#include "Arduino.h"
#include "CookingPanel.h"

CookingPanel::CookingPanel(String headText,String subheadText,UTFT *myGLCD,UTouch *myTouch,UTFT_Buttons *myButtons,SettingsType *settings,CallbackFunction eventCallbackFunction):PanelGUI(headText,subheadText,myGLCD,myTouch,myButtons,eventCallbackFunction)
{
  

  _settings=settings;
  
//  presetString="None   ";
  
  //float temperature=_settings->temperature;
  //Serial.print(temperature);

}

void CookingPanel::show(){
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
   
 int startY=25;

  _myGLCD->print("Set temperature: "+formatTemperature(_settings->temperature), 10, startY);
  _myGLCD->print("Actual temperature: 25C ", 10, startY+12);
  _myGLCD->print("Total time: 1H:13m", 10, startY+12*2);
  _myGLCD->print("Finish time: 0H:90m", 10, startY+12*3);
  
  
  
  butTop = _myButtons->addButton(_sizeX-_buttonHeight-3, 2, _buttonHeight,  _buttonHeight, "X");
 
  
  _myButtons->drawButtons();
  
  drawGraphFrame();
  
  while(isActive){
    
    if (_myTouch->dataAvailable() == true){
      
      int pressed_button = _myButtons->checkButtons();
      
      if(pressed_button==butTop){
        isActive=false;
        _eventCallbackFunction(0);
      }
      
      
      
    }
    
  }
  
  
  
  //_eventCallbackFunction(0);
  
}


//TODO: Implement the class for the cooking panel
void CookingPanel::drawGraphFrame(){
  
  int _sizeX=_myGLCD->getDisplayXSize();
  int _sizeY=_myGLCD->getDisplayYSize();
  
  int startY=90;
  
  int height=160;
  
  
  //myGLCD.setColor(VGA_AQUA);
  _myGLCD->drawRect(0,_sizeY-height,_sizeX-1,_sizeY-2);
  
  
  int minTemp=25;
  int maxTemp=_settings->temperature+10.0;
  
  startY= map(_settings->temperature, minTemp, maxTemp, _sizeY-2, _sizeY-height);
    
  _myGLCD->setColor(VGA_GREEN);
  //_myGLCD->print(formatTemperature(_settings->temperature), 4, startY+10);
  _myGLCD->print(formatTemperature(_settings->temperature), 4, startY-13);
  //_myGLCD->drawLine(1,startY+10+13,_myGLCD->getDisplayXSize()-2,startY+10+13);
  _myGLCD->drawLine(1,startY,_sizeX-2,startY);

   //serving temperature 
   int servingTemp=45.5;
   startY= map(servingTemp, minTemp, maxTemp, _sizeY-2, _sizeY-height); 
  _myGLCD->setColor(VGA_AQUA);
  _myGLCD->print(formatTemperature(45.5), 4, startY);
  _myGLCD->drawLine(1,startY+13,_sizeX-2,startY+13);

  _myGLCD->setColor(VGA_RED);
  
  int x=0;
  float y;
  while(y<height-10){  
    
    y=x*0.5;
    _myGLCD->drawPixel(x+2,_sizeY-3-y);
    x++;
  }

  _myGLCD->setColor(VGA_WHITE);
  
//  panelReady=true;
}



String CookingPanel::getFloatString(float value){
  
  char tmp[10];
  if (_settings->fahrenheit){
    dtostrf(value,1,0,tmp);
  }else{
    dtostrf(value,1,1,tmp);
  }
  return String(tmp);
  
}

String CookingPanel::formatTemperature(float temperature){
  String symbol="C ";
  if (_settings->fahrenheit){
    symbol="F ";
    temperature=round((temperature*9.0/5.0)+32.0);
  }
  return getFloatString(temperature)+symbol;
}
