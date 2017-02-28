
#include <EEPROM.h>
#include <Servo.h>
#include<LiquidCrystal.h>                                          
#include <stdlib.h>


//LiquidCrystal lcd(RS, E, D4, D5, D6, D7); 

//============dinh nghia su dung LCD1602====================                                
LiquidCrystal lcd(1, 0, A0, A1, A2, A3);   
AutoDIY robot;
//=====================================================================
void setup(void){                                
  lcd.begin(16,2);
  pinMode(11,INPUT_PULLUP);
  pinMode(12,INPUT_PULLUP);
  robot.init_pin();
  robot.init_adc();
  robot.get_adc();
  //display_adc(ng_adc[0],ng_adc[1],ng_adc[2],ng_adc[3]);
}
 void loop(void){
 int data,i;
 robot.set_adc();
 if(digitalRead(11)==0)
 while(true){
   robot.do_line(30,150);
   }
  if(digitalRead(12)==0)
    while(1){
      robot.control_motor(0,0,120);
      robot.control_motor(1,0,120);
    }
}
