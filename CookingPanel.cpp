#include "Arduino.h"
#include "CookingPanel.h"

CookingPanel::CookingPanel(String headText,String subheadText,UTFT *myGLCD,UTouch *myTouch,UTFT_Buttons *myButtons,SettingsType *settings,CallbackFunction eventCallbackFunction):PanelGUI(headText,subheadText,myGLCD,myTouch,myButtons,eventCallbackFunction), mySensor(PIN_TEMPPROBE),myGraph(myGLCD,settings)
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
 
   long startTimeStamp = millis();
   long updateTimeStamp = startTimeStamp;
   
   int totalTime=0;

  _sizeX=_myGLCD->getDisplayXSize();
  _sizeY=_myGLCD->getDisplayYSize();
   
   clearScreen();
   
   
   isActive=true;
   
 int startY=25;

  _myGLCD->print("Set temperature: "+formatTemperature(_settings->temperature), 10, startY);
  _myGLCD->print("Actual temperature:", 10, startY+12);  
  _myGLCD->print("Total time: 1H:13m", 10, startY+12*2);
  _myGLCD->print("Finish time: 0H:90m", 10, startY+12*3);
  
  
  butTop = _myButtons->addButton(_sizeX-_buttonHeight-3, 2, _buttonHeight,  _buttonHeight, "X");
 
  
  _myButtons->drawButtons();
  
  
  updateTemperature();
  
  //drawGraphFrame();
  
  myGraph.setHeight(160);
  myGraph.drawFrame(tempC);
  
  while(isActive){
    
    if (_myTouch->dataAvailable() == true){
      
      int pressed_button = _myButtons->checkButtons();
      
      if(pressed_button==butTop){
        isActive=false;
        _eventCallbackFunction(0);
      }
      
      
      
    }
    
    
    
    
    if (millis()-updateTimeStamp > 1000){
      
      totalTime++;
      int secs=(millis()-startTimeStamp)/1000;
      secs=secs%60;
      int mins=((millis()-startTimeStamp)/60000)%60;
      //mins=mins%60;
      int hours=(millis()-startTimeStamp)/(60*60000);
      setHeadText("Cooking " + String(hours, DEC) + ":"+ String(mins, DEC) + ":"+ String(secs, DEC)+ " ");
      
     
      updateTimeStamp = millis();
    }
    
    if (totalTime%5==0){
       updateTemperature();
    }
        
    
    
    
    
  }
  
  
  
  //_eventCallbackFunction(0);
  
}

void CookingPanel::updateTemperature(){
    
   tempC = mySensor.getTemp();
   
   int startY=25;
  _myGLCD->print("Actual temperature: "+formatTemperature(tempC)+"  ", 10, startY+12);
  
  myGraph.drawValue(tempC);
  
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
