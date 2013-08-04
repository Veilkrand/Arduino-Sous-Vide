/*
  PanelGUI.h - Library for creating panels for UTFT.
  Created by Alberto Naranjo, July 17, 2012.
*/


#include "Arduino.h"
#include "PanelGUI.h"


PanelGUI::PanelGUI(String headText,String subheadText,UTFT *myGLCD,UTouch *myTouch,UTFT_Buttons *myButtons,CallbackFunction eventCallbackFunction){
  
  _eventCallbackFunction=eventCallbackFunction;
  
  _myGLCD=myGLCD;
  _myTouch=myTouch;
  
  _headText=headText;
  _subheadText=subheadText;
  
  _myButtons=myButtons;
  
  
  isActive=true;
  

}

void PanelGUI::setHeadText(String headText){
  _myGLCD->setFont(BigFont);
  _myGLCD->print(headText, _headTextPosX, _headTextPosY);
  _myGLCD->setFont(SmallFont);
}
void PanelGUI::setSubheadText(String subheadText){
  _myGLCD->setFont(SmallFont);
  _myGLCD->print(subheadText, _subheadTextPosX, _subheadTextPosY);
}



void PanelGUI::clearScreen(){
  
  _myGLCD->clrScr();
  _myButtons->deleteAllButtons();  
  setHeadText(_headText);
  setSubheadText(_subheadText);  

  
}
