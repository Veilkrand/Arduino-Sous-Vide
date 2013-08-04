#include "Arduino.h"
#include "GraphPanel.h"

GraphPanel::GraphPanel(UTFT *myGLCD,SettingsType *settings)
{
  

  _settings=settings;
  _myGLCD=myGLCD;
  
  _graphIndex=0;
  _oldyValue=0;
  
  _height=160;
  
  

//  _maxValue=maxValue;

  
//  presetString="None   ";
  
  //float temperature=_settings->temperature;
  //Serial.print(temperature);

}

void GraphPanel::setHeight(int height){
  _height=height;
}

void GraphPanel::drawFrame(int minValue){
 
  _sizeX=_myGLCD->getDisplayXSize();
  _sizeY=_myGLCD->getDisplayYSize();
  
  //int startY=90;
  
  _minValue=minValue-10;
  _maxValue=_settings->temperature+10.0;
  _graphIndex=0;
  
  //int height=160;
  
  _myGLCD->setColor(VGA_BLACK);
  _myGLCD->fillRect(0,_sizeY-_height,_sizeX,_sizeY);
  delay(50);
  _myGLCD->setColor(VGA_WHITE);
  _myGLCD->drawRect(0,_sizeY-_height,_sizeX-1,_sizeY-2);
  delay(50);  
  
  int startY_setTemp= map(_settings->temperature, _minValue, _maxValue, _sizeY-2, _sizeY-_height);
   
  if (startY_setTemp > _sizeY-_height-2 && startY_setTemp<_sizeY-2){  
    _myGLCD->setColor(VGA_GREEN);
    _myGLCD->print(formatTemperature(_settings->temperature), 4, startY_setTemp-13);
    _myGLCD->drawLine(1,startY_setTemp,_sizeX-2,startY_setTemp);
  }
   //serving temperature 
   int servingTemp=45.5;
   int startY_servingTemp= map(servingTemp, _minValue, _maxValue, _sizeY-2, _sizeY-_height); 
   if (startY_servingTemp>startY_setTemp && startY_servingTemp<_sizeY){
    _myGLCD->setColor(VGA_AQUA);
    _myGLCD->print(formatTemperature(45.5), 4, startY_servingTemp);
    _myGLCD->drawLine(1,startY_servingTemp+13,_sizeX-2,startY_servingTemp+13);
   }
   
   _myGLCD->setColor(VGA_WHITE);
   
   drawValue(minValue);
   //_oldyValue=map(_minValue,_minValue,_settings->temperature+10.0,_sizeY-2, _sizeY-_height);
   
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
  
  _yValue=map(tempValue,_minValue,_maxValue,_sizeY-2, _sizeY-_height);
  
  Serial.print(_graphIndex);
  Serial.print(":");
  Serial.print(_yValue);
  Serial.print(" ");
  Serial.println(_oldyValue);
  
  if (_graphIndex>_sizeX-2 || _yValue >_sizeY-1 || _yValue<_sizeY-_height+1){
    drawFrame(tempValue);
  }

  _myGLCD->setColor(VGA_RED);  
  
    if (_oldyValue==0){
      _myGLCD->drawPixel(_graphIndex,_yValue);
    }else{  
      _myGLCD->drawLine(_graphIndex,_oldyValue,_graphIndex+1,_yValue);
    }
  
  _oldyValue=_yValue;
  
  _graphIndex++;
  
  _myGLCD->setColor(VGA_WHITE);
  
  
  
  
}
