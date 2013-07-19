/*
  PanelGUI.h - Library for creating panels for UTFT.
  Created by Alberto Naranjo, July 17, 2012.
*/
#ifndef PanelGUI_h
#define PanelGUI_h

#include "Arduino.h"

#include <UTFT.h>
#include <UTouch.h>
#include <UTFT_Buttons.h>

// Declare which fonts we will be using
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t Dingbats1_XL[];

#define _headTextPosX 5
#define _headTextPosY 5
#define _subheadTextPosX 10
#define _subheadTextPosY 25


#define _topButOffset 2

#define _buttonHeight 35
#define _buttonWidth 75

#define _buttonPosX 28
#define _buttonPosY 70

typedef void (*CallbackFunction) (int toPanel);

class PanelGUI
{
  public:
    
        PanelGUI(String headText,String subheadText,UTFT *myGLCD,UTouch *myTouch,UTFT_Buttons *myButtons,CallbackFunction eventCallbackFunction);
        
        void setHeadText(String headText);
        void setSubheadText(String subheadText);	
        
        void show();
        
        boolean isActive;


  protected:
     CallbackFunction _eventCallbackFunction;
    
    void clearScreen();
    
    UTFT *_myGLCD;
    UTouch *_myTouch;
    UTFT_Buttons *_myButtons;
    
    String _headText;
    String _subheadText;    
    
    int _sizeX;
    int _sizeY;   
    
};

#endif
