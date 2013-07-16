// UTFT_Buttons_Demo_320x240 (C)2013 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//
// A small demo to demonstrate the use of some of the
// functions of the UTFT_Buttons add-on library.
//
// This demo was made for modules with a screen resolution 
// of 320x240 pixels, but should work on larger screens as
// well.
//
// This program requires both the UTFT and UTouch libraries
// in addition to the UTFT_Buttons add-on library.
//
#include <avr/EEPROM.h>
#include <UTFT.h>
#include <UTouch.h>
#include <UTFT_Buttons.h>

// Declare which fonts we will be using
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t Dingbats1_XL[];

// Set up UTFT...
// Set the pins to the correct ones for your development board
// -----------------------------------------------------------
// Standard Arduino 2009/Uno/Leonardo shield   : <display model>,19,18,17,16
// Standard Arduino Mega/Due shield            : <display model>,38,39,40,41
// CTE TFT LCD/SD Shield for Arduino Due       : <display model>,25,26,27,28
// Standard chipKit Uno32/uC32                 : <display model>,34,35,36,37
// Standard chipKit Max32                      : <display model>,82,83,84,85
// AquaLEDSource All in One Super Screw Shield : <display model>,82,83,84,85
//
// Remember to change the model parameter to suit your display module!
UTFT myGLCD(ITDB32S,38,39,40,41);

// Set up UTouch...
// Set the pins to the correct ones for your development board
// -----------------------------------------------------------
// Standard Arduino 2009/Uno/Leonardo shield   : 15,10,14,9,8
// Standard Arduino Mega/Due shield            : 6,5,4,3,2
// CTE TFT LCD/SD Shield for Arduino Due       : 6,5,4,3,2
// Standard chipKit Uno32/uC32                 : 20,21,22,23,24
// Standard chipKit Max32                      : 62,63,64,65,66
// AquaLEDSource All in One Super Screw Shield : 62,63,64,65,66
UTouch        myTouch(6,5,4,3,2);

// Finally we set up UTFT_Buttons :)
UTFT_Buttons  myButtons(&myGLCD, &myTouch);

  //Panels
  #define mainPanel 0
  #define presetPanel 1
  #define cookingPanel 2  
  #define configPanel 3    
  int actualPanel=mainPanel;
  
  boolean panelReady=false;
  
  //buttons
  int butPlusTemp,butMinusTemp;
  int butPlusTime,butMinusTime;  
  int butHourPlusTime,butHourMinusTime;  
  int butStart;
  
  int butTop[2];
  
  int buttonsLine[10];
  
  int buttonWidth= 75;
  int buttonHeight=35;
   
   //for the GUI
  int xButStart=28;
  int yButStart=70;

  //Preset string
  String presetString="None";

  //Control Variables
  float temperature=50.5;
  int time=15;
  
  //configuration options
  boolean fahrenheit=false;
  boolean preheating=true;

  //Settings type
  typedef struct
  {
    float temperature;
    int time;
    boolean fahrenheit;
    boolean preheating;
  }  settingsType;
  settingsType settings;


void setup()
{
  myGLCD.InitLCD();
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  //myGLCD.setFont(BigFont);

  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);
  
  myButtons.setTextFont(BigFont);
  myButtons.setSymbolFont(Dingbats1_XL);
  
  /*
  //Write factory settings. Only first time!!!
  settingsType settings={temperature,time,fahrenheit,preheating};
  eeprom_write_block((void*)&settings, (void*)0, sizeof(settingsType));
  */
  
  //Load Settings
  eeprom_read_block((void*)&settings, (void*)0, sizeof(settingsType));
  
    temperature=settings.temperature;
    time=settings.time;
    fahrenheit=settings.fahrenheit;
    preheating=settings.preheating;
    

  
  drawMainPanel();
  
}

String getFloatString(float value){
  
  char tmp[10];
  if (fahrenheit){
    dtostrf(value,1,0,tmp);
  }else{
    dtostrf(value,1,1,tmp);
  }
  return String(tmp);
  
}

String formatTemperature(float temperature){
  String symbol="C ";
  if (fahrenheit){
    symbol="F ";
    temperature=round((temperature*9.0/5.0)+32.0);
  }
  return getFloatString(temperature)+symbol;
}

void updateTemperatureLabel(){
  int maxTemp=110;
  int minTemp=30;
  if (temperature<minTemp)temperature=minTemp;
  if (temperature>maxTemp)temperature=maxTemp;
  
  myGLCD.setFont(BigFont);
  myGLCD.print(formatTemperature(temperature), xButStart, yButStart+buttonHeight+5);
}

void updateTimeLabel(){
  int maxTime=60*24;
  if (time<1)time=1;
  if (time>maxTime)time=maxTime;
  
  int hours = time / 60;
  int minutes = time % 60;
  
  myGLCD.setFont(BigFont);
  //myGLCD.print(" "+String(time, DEC)+"m  ", xButStart+110, yButStart+buttonHeight+5);
  String str_hours=String(hours, DEC);
  String str_minutes=String(minutes, DEC);
  //if (hours<10)str_hours="0"+str_hours;
  //if (minutes<10)str_minutes="0"+str_minutes;
  myGLCD.print(" "+String(hours, DEC)+"H:"+String(minutes, DEC)+"m ", xButStart+110, yButStart+buttonHeight+5);
}

void clearPanel(){
           panelReady=false;
           myButtons.deleteAllButtons();
           myGLCD.clrScr();
           delay(500);
}

void updatePresetLabel(String presetString){
  //String preset="None";
  myGLCD.setFont(SmallFont);
  myGLCD.print("Preset: "+ presetString, 10, 5+20);
}

void drawGraphFrame(){
  int startY=90;
  //myGLCD.setColor(VGA_AQUA);
  myGLCD.drawRect(0,startY,myGLCD.getDisplayXSize()-1,myGLCD.getDisplayYSize()-2);
  myGLCD.setColor(VGA_GREEN);
  
  myGLCD.print(formatTemperature(temperature), 4, startY+10);
  myGLCD.drawLine(1,startY+10+13,myGLCD.getDisplayXSize()-2,startY+10+13);

  myGLCD.setColor(VGA_RED);
  
  int x=0;
  float y;
  while(y<myGLCD.getDisplayYSize()-startY-10){  
    
    y=x*0.5;
    myGLCD.drawPixel(x+2,myGLCD.getDisplayYSize()-3-y);
    x++;
  }

  myGLCD.setColor(VGA_WHITE);
  
  panelReady=true;
}

void drawCookingPanel(){
  actualPanel=cookingPanel;
  int startY=5;
  myGLCD.setFont(BigFont);
  myGLCD.print("Preheating", 5, startY);
  myGLCD.setFont(SmallFont);
  myGLCD.print("Set temperature: "+formatTemperature(temperature), 10, startY+20);
  myGLCD.print("Actual temperature: 25C ", 10, startY+20+15);
  myGLCD.print("Total time: 1H:13m", 10, startY+20+15*2);
  myGLCD.print("Time to finish: 0H:90m", 10, startY+20+15*3);
  
  
  
  butTop[0] = myButtons.addButton(myGLCD.getDisplayXSize()-buttonHeight-2, 2,  buttonHeight,  buttonHeight, "X");
  
  myButtons.drawButtons();
  
  drawGraphFrame();
  
  panelReady=true;
}

void drawConfigPanel(){
  actualPanel=configPanel;
  myGLCD.setFont(BigFont);
  myGLCD.print("Configuration", 5, 5);

//  myGLCD.setFont(SmallFont);
//  myGLCD.print("Select a cooking preset", 10, 5+20);

  myGLCD.setFont(SmallFont);
  myGLCD.print("Sous-Vide Cooker V0.5",5, myGLCD.getDisplayYSize()-27);
  myGLCD.print("Alberto Naranjo - July 2013", 5, myGLCD.getDisplayYSize()-15);


  butTop[0] = myButtons.addButton(myGLCD.getDisplayXSize()-buttonHeight-2, 2,  buttonHeight,  buttonHeight, "<");
 
  int startX=40;
  //myButtons.setTextFont(SmallFont);
  buttonsLine[0]=myButtons.addButton( 10, startX+0*buttonHeight+5, myGLCD.getDisplayXSize()-10*2,  buttonHeight,"");
  
  if (fahrenheit){
    myButtons.relabelButton(buttonsLine[0],"Temp. Fahrenheit",true);
  }else{
    myButtons.relabelButton(buttonsLine[0],"Temp. Celsious",true);
  }

buttonsLine[1]=myButtons.addButton( 10, startX+1*buttonHeight+5, myGLCD.getDisplayXSize()-10*2,  buttonHeight, "");  
  if (preheating){
//    str_tmp="Preheating is ON";
  myButtons.relabelButton(buttonsLine[1],"Preheating is ON",true);
  }else{
  //  str_tmp="Preheating is OFF";
  myButtons.relabelButton(buttonsLine[1],"Preheating is OFF",true);
  }


//  buttonsLine[2]=myButtons.addButton( 10, startX+2*buttonHeight+5, myGLCD.getDisplayXSize()-10*2,  buttonHeight, "Chicken: 63.5C 2H");
//  buttonsLine[3]=myButtons.addButton( 10, startX+3*buttonHeight+5, myGLCD.getDisplayXSize()-10*2,  buttonHeight, "Fish: 60C 45m");  
//  buttonsLine[4]=myButtons.addButton( 10, startX+4*buttonHeight+5, myGLCD.getDisplayXSize()-10*2,  buttonHeight, "Vegetables: 84C 1H");

  myButtons.drawButtons();
  myButtons.setTextFont(BigFont);
  
}

void drawPresetPanel(){
  actualPanel=presetPanel;
  myGLCD.setFont(BigFont);
  myGLCD.print("Presets", 5, 5);

  myGLCD.setFont(SmallFont);
  myGLCD.print("Select a cooking preset", 10, 5+20);
  
  butTop[0] = myButtons.addButton(myGLCD.getDisplayXSize()-buttonHeight-2, 2,  buttonHeight,  buttonHeight, "<");
  
  int startX=40;
  //myButtons.setTextFont(SmallFont);
  buttonsLine[0]=myButtons.addButton( 10, startX+0*buttonHeight+5, myGLCD.getDisplayXSize()-10*2,  buttonHeight, "Eggs yolk: 64C 1H");
  buttonsLine[1]=myButtons.addButton( 10, startX+1*buttonHeight+5, myGLCD.getDisplayXSize()-10*2,  buttonHeight, "Steak: 55C 2H30m");
  buttonsLine[2]=myButtons.addButton( 10, startX+2*buttonHeight+5, myGLCD.getDisplayXSize()-10*2,  buttonHeight, "Chicken: 63.5C 2H");
  buttonsLine[3]=myButtons.addButton( 10, startX+3*buttonHeight+5, myGLCD.getDisplayXSize()-10*2,  buttonHeight, "Fish: 60C 45m");  
  buttonsLine[4]=myButtons.addButton( 10, startX+4*buttonHeight+5, myGLCD.getDisplayXSize()-10*2,  buttonHeight, "Vegetables: 84C 1H");

  myButtons.drawButtons();
  myButtons.setTextFont(BigFont);
  

}

void drawMainPanel(){
  actualPanel=mainPanel;
  myGLCD.setFont(BigFont);
  myGLCD.print("Cook Settings", 5, 5);
  updatePresetLabel(presetString);
   
  myGLCD.print("Temperature: ", xButStart, yButStart-15);
  butPlusTemp= myButtons.addButton( xButStart,  yButStart, buttonWidth,  buttonHeight, "+");
  updateTemperatureLabel();
  butMinusTemp = myButtons.addButton( xButStart,  yButStart+buttonHeight+5+16+5, buttonWidth,  buttonHeight, "-");

  myGLCD.setFont(SmallFont);
  myGLCD.print("Time: ", xButStart+110, yButStart-15);
  butHourPlusTime= myButtons.addButton( xButStart+110,  yButStart, buttonWidth,  buttonHeight, "+H");
  butPlusTime= myButtons.addButton( xButStart+110+buttonWidth+5,  yButStart, buttonWidth,  buttonHeight, "+m");
  updateTimeLabel();
  butHourMinusTime = myButtons.addButton( xButStart+110,  yButStart+buttonHeight+5+16+5, buttonWidth,  buttonHeight, "-H");
  butMinusTime = myButtons.addButton( xButStart+110+buttonWidth+5,  yButStart+buttonHeight+5+16+5, buttonWidth,  buttonHeight, "-m");
  
  butStart=myButtons.addButton( 15, myGLCD.getDisplayYSize()-buttonHeight-15, myGLCD.getDisplayXSize()-15*2,  buttonHeight, "START");
  
  //but1 = myButtons.addButton( 10,  20, 300,  30, "Button 1");
  //but2 = myButtons.addButton( 10,  60, 300,  30, "Button 2");
  //but3 = myButtons.addButton( 10, 100, 300,  30, "Button 3");
  //but4 = myButtons.addButton( 10, 140, 300,  30, "Button 4", BUTTON_DISABLED);
  butTop[0] = myButtons.addButton(myGLCD.getDisplayXSize()-buttonHeight-3, 2,  buttonHeight,  buttonHeight, "w", BUTTON_SYMBOL);
  butTop[1] = myButtons.addButton(myGLCD.getDisplayXSize()-buttonHeight*2-6, 2,  buttonHeight,  buttonHeight, "d", BUTTON_SYMBOL);
  //butY = myButtons.addButton(  0, 199, 100,  40, "I", BUTTON_SYMBOL | BUTTON_SYMBOL_REP_3X);
  
  myButtons.drawButtons();
  
    panelReady=true;
}

void loop()
{
      
    if (myTouch.dataAvailable() == true){
      
      int pressed_button = myButtons.checkButtons();
      
      if (actualPanel==presetPanel){
        if (pressed_button==buttonsLine[0]){
          presetString="Eggs yolk";
          temperature=64;
          time=60;
          actualPanel=mainPanel;
          clearPanel();
          drawMainPanel();
        }
        if (pressed_button==buttonsLine[1]){
          presetString="Steak";
          temperature=55;
          time=150;
          actualPanel=mainPanel;
           clearPanel();
           drawMainPanel();
        }
          
        if (pressed_button==buttonsLine[2]){
          presetString="Chicken";
          temperature=63.5;
          time=120;
          clearPanel();
          drawMainPanel();
        }
        if (pressed_button==buttonsLine[3]){
          presetString="Fish";
          temperature=60;
          time=45;
          actualPanel=mainPanel;
          clearPanel();
          drawMainPanel();
        }
        if (pressed_button==buttonsLine[4]){
          presetString="Vegetables";
          temperature=84;
          time=60;
          actualPanel=mainPanel;
          clearPanel();
           drawMainPanel();
        }
          
          
      }else{
      
      if(actualPanel==mainPanel){

      

        
      if (pressed_button==butPlusTemp){
        updatePresetLabel("None          ");  
        temperature+=0.5;
        updateTemperatureLabel();
      }
      if (pressed_button==butMinusTemp){
        updatePresetLabel("None          ");  
        temperature-=0.5;
        updateTemperatureLabel();
      }
      
      if (pressed_button==butPlusTime){
        updatePresetLabel("None          ");          
        time+=1;
        updateTimeLabel();
      }
      if (pressed_button==butMinusTime){
        updatePresetLabel("None          ");          
        time-=1;
        updateTimeLabel();
      }
      if (pressed_button==butHourPlusTime){
        updatePresetLabel("None          ");          
        time+=60;
        updateTimeLabel();
      }
      if (pressed_button==butHourMinusTime){
        updatePresetLabel("None          ");          
        time-=60;
        updateTimeLabel();
      }
      
      if (pressed_button==butStart){
           //actualPanel=cookingPanel;
           saveSettings();
           clearPanel();
           drawCookingPanel();
      }
      
      if(pressed_button==butTop[1]){
        clearPanel();
        drawPresetPanel();
      }
      
     }else{
       if (actualPanel==configPanel){
         if (pressed_button==buttonsLine[0]){
           if (fahrenheit){
             fahrenheit=false;
             myButtons.relabelButton(buttonsLine[0], "Temp. Celsious",true); 
             
           }else{
             fahrenheit=true;
             myButtons.relabelButton(buttonsLine[0], "Temp. Fahrenheit",true); 
           }
         }
         if (pressed_button==buttonsLine[1]){
           if (preheating){
             preheating=false;
             myButtons.relabelButton(buttonsLine[1], "Preheating is OFF",true); 
             
           }else{
             preheating=true;
             myButtons.relabelButton(buttonsLine[1], "Preheating is ON",true); 
           }
         }
       }
     }
    }

    

      
      if (pressed_button==butTop[0]){
       switch(actualPanel){
         case mainPanel:
           clearPanel();
           drawConfigPanel();
         break;
         case configPanel:
          saveSettings();
         case presetPanel:
         case cookingPanel:
           clearPanel();
           drawMainPanel();  
         break;         
       }
      }
      
      /*
      

      if (pressed_button==butX)
      {
        if (myButtons.buttonEnabled(but4))
          myButtons.disableButton(but4, true);
        else
          myButtons.enableButton(but4, true);
      }
      else if (pressed_button==butY)
      {
        if (default_colors)
        {
          myButtons.setButtonColors(VGA_YELLOW, VGA_RED, VGA_YELLOW, VGA_BLUE, VGA_GRAY);
          myButtons.relabelButton(butY, "_");
          myButtons.drawButtons();
          default_colors=false;
        }
        else
        {
          myButtons.setButtonColors(VGA_WHITE, VGA_GRAY, VGA_WHITE, VGA_RED, VGA_BLUE);
          myButtons.relabelButton(butY, "I");
          myButtons.drawButtons();
          default_colors=true;
        }
      }
      if (pressed_button==but1)
        myGLCD.print("Button 1", 110, 220);
      if (pressed_button==but2)
        myGLCD.print("Button 2", 110, 220);
      if (pressed_button==but3)
        myGLCD.print("Button 3", 110, 220);
      if (pressed_button==but4)
        myGLCD.print("Button 4", 110, 220);
      if (pressed_button==-1)
        myGLCD.print("None    ", 110, 220);
    }
    
   */ 

 }
}

void saveSettings(){
    settings.temperature=temperature;
    settings.time=time;
    settings.fahrenheit=fahrenheit;
    settings.preheating=preheating;
    eeprom_write_block((void*)&settings, (void*)0, sizeof(settingsType));
}




