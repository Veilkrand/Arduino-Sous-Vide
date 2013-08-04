#include "Arduino.h"
#include "GraphPanel.h"

GraphPanel::GraphPanel(int height,UTFT *myGLCD,SettingsType *settings)
{
  

  _settings=settings;
  _myGLCD=myGLCD;
  _height=height;
  
  _graphIndex=0;
  
  

//  _maxValue=maxValue;

  
//  presetString="None   ";
  
  //float temperature=_settings->temperature;
  //Serial.print(temperature);

}


void GraphPanel::drawFrame(int minValue){
 
  _sizeX=_myGLCD->getDisplayXSize();
  _sizeY=_myGLCD->getDisplayYSize();
  
  //int startY=90;
  
  _minValue=minValue-5;
  _graphIndex=0;
  
  int height=160;
  
  
  //myGLCD.setColor(VGA_AQUA);
  _myGLCD->drawRect(0,_sizeY-height,_sizeX-1,_sizeY-2);
  
  
  int maxTemp=_settings->temperature+10.0;
  
  int startY_setTemp= map(_settings->temperature, _minValue, maxTemp, _sizeY-2, _sizeY-height);
    
  _myGLCD->setColor(VGA_GREEN);
  //_myGLCD->print(formatTemperature(_settings->temperature), 4, startY+10);
  _myGLCD->print(formatTemperature(_settings->temperature), 4, startY_setTemp-13);
  //_myGLCD->drawLine(1,startY+10+13,_myGLCD->getDisplayXSize()-2,startY+10+13);
  _myGLCD->drawLine(1,startY_setTemp,_sizeX-2,startY_setTemp);

   //serving temperature 
   int servingTemp=45.5;
   int startY_servingTemp= map(servingTemp, _minValue, maxTemp, _sizeY-2, _sizeY-height); 
   if (startY_servingTemp>startY_setTemp && startY_servingTemp<_sizeY){
  _myGLCD->setColor(VGA_AQUA);
  _myGLCD->print(formatTemperature(45.5), 4, startY_servingTemp);
  _myGLCD->drawLine(1,startY_servingTemp+13,_sizeX-2,startY_servingTemp+13);
   }
   
   _myGLCD->setColor(VGA_WHITE);
   
   _oldyValue=map(_minValue,_minValue,_settings->temperature+10.0,_sizeY-2, _sizeY-_height);
   
}

String GraphPanel::formatTemperature(float temperature){
  String symbol="C ";
  if (_settings->fahrenheit){
    symbol="F ";
    temperature=round((temperature*9.0/5.0)+32.0);
  }
  return getFloatString(temperature)+symbol;
}

String GraphPanel::getFloatString(float value){
  
  char tmp[10];
  if (_settings->fahrenheit){
    dtostrf(value,1,0,tmp);
  }else{
    dtostrf(value,1,1,tmp);
  }
  return String(tmp);
  
}


void GraphPanel::drawValue(float tempValue){

  _myGLCD->setColor(VGA_RED);
  
  _yValue=map(tempValue,_minValue,_settings->temperature+10.0,_sizeY-2, _sizeY-_height);
  
  
  _myGLCD->drawLine(_graphIndex,_oldyValue,_graphIndex+1,_yValue);
  
  _oldyValue=_yValue;
  
  _graphIndex++;
  
  _myGLCD->setColor(VGA_WHITE);
  
  if (_graphIndex>_sizeX-2){
    drawFrame(tempValue-5);
  }
  
  
}
