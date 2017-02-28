#include "Arduino.h"
#include <EEPROM.h>
#include "AutoDIY.h"
//=======================================
#define PWM1 6
#define DIR1 7
#define PWM2 5
#define DIR2 4
//=======================================
//======khoi tao adc========================================
void AutoDIY::init_adc()
{
pinMode(10,INPUT_PULLUP);
pinMode(A4,INPUT);
pinMode(A5,INPUT);
pinMode(A6,INPUT);
pinMode(A7,INPUT);
analogReference(EXTERNAL);
}
//====set nguong adc========================================
void AutoDIY::set_adc(){
  int i;
  if((digitalRead(10)==0)&&(tmp==0))
    {
     while(digitalRead(10)==0){
    read_adc();
   
    for(i=0;i<4;i++)
      min_adc[i]=adc[i];
    tmp=1;
    }}
  if((digitalRead(10)==0)&&(tmp==1))
  {
    while(digitalRead(10)==0){
    read_adc();
    
    for(i=0;i<4;i++)
    max_adc[i]=adc[i];
    tmp=2;                                             
    }}
  if(tmp==2)
    {
    for(i=0;i<4;i++){
    ng_adc[i]=(min_adc[i]+max_adc[i])/2;
    EEPROM.put(i*2, ng_adc[i]);}
    }
}

//===lay gia tri nguong adc tu EEPROM=======================
void AutoDIY::get_adc()
{
  int i;
  for(i=0;i<4;i++) 
    {
    EEPROM.get(i*2,ng_adc[i]);
    }
}

//========doc gia tri adc===================================
void AutoDIY::read_adc(){
  int i;
 for(i=0;i<4;i++)
adc[i]=analogRead(i+4);
}
void display_adc(int a,int b, int c, int d){
lcd.setCursor(0, 0);  lcd.print(a);    
lcd.setCursor(6, 0);  lcd.print(b);   
lcd.setCursor(0, 1);  lcd.print(c);   
lcd.setCursor(6, 1);  lcd.print(d);                    
}
//=========doc gia tri adc cho viec do` duong`===============
void AutoDIY::read_line(void)    // thuc hien viec doc
{
    int i,j;
    k = 0;
    read_adc();
        if(adc[0] > ng_adc[0])  k |= 0b00100000;   //thuc hien cong don gia tri                  
        if(adc[1] > ng_adc[1])  k |= 0b00010000;
        if(adc[2] > ng_adc[2])  k |= 0b00001000;
        if(adc[3] > ng_adc[3])  k |= 0b00000100;
        lcd.setCursor(12,0);
        lcd.print(k);
        if((adc[0]>ng_adc[0])&&(adc[1]>ng_adc[1])&&(adc[2]>ng_adc[2])&&(adc[3]>ng_adc[3])&&(nho==0))
        {
        ngatu++;
        nho=1;
        }
        else if((analogRead(0)<ng_adc[0])||(analogRead(1)<ng_adc[1])||(analogRead(2)<ng_adc[2])||(analogRead(3)<ng_adc[3]))
        {
        nho=0;
        } 
}

//============ham do duong==================================
void AutoDIY::do_line(int kp,int spd){
  int udk1=0,udk2=0;
  int e;
   unsigned char et=0;                                                
    read_line();   
    if(k==0b00011000)e=0;   //24  Vi tri trung tam cua xe   
    if(k==0b00010000)e=-1;  //16   Do lech cua robot so voi vach den...
    if(k==0b00110000)e=-2;  // 48  ... lech cang nhieu, sai so e cang lon
    if(k==0b00100000)e=-3;  //32
    if(k==0b00001000)e=1;  //8
    if(k==0b00001100)e=2; //12
    if(k==0b00000100)e=3; //4
    if((e>0)&&(et<0)){e=-e;}
    udk1=spd+kp*e;                //Ham dieu khien toc do banh trai
    udk2=spd-kp*e;
    if(udk1>255){udk1=255;}
    if(udk2>255){udk2=255;}
    if(udk1<00){udk1=00;}
    if(udk2<00){udk2=00;}
    control_motor(0,0,udk1);     //Dieu khien motor khi do duong
    control_motor(1,0,udk2);
    delay(2);
    et=e;
}

//=========Khoi tao chan dieu khien dong co=================
void AutoDIY::init_pin(void){
  pinMode(DIR1,OUTPUT);  //DIR1;
  pinMode(PWM1,OUTPUT);  //PWM1
  pinMode(PWM2,OUTPUT);  //PWM2
  pinMode(DIR2,OUTPUT);  //DIR2
}
//========Ham dieu khien dong co============================
void AutoDIY::control_motor(int dc, int dir, int spd){
  switch (dc){
    case 0:{
    if(dir==0)
      {
      digitalWrite(DIR1,0);
      analogWrite(PWM1, spd);
     // digitalWrite(PWM1, 1);
      }
    else
      {
      digitalWrite(DIR1,1);
      analogWrite(PWM1, 255-spd);  
      //digitalWrite(PWM1, 0);
      }
    }
    case 1:{
    if(dir==0)
      {
      digitalWrite(DIR2,0);
      analogWrite(PWM2, spd);
     // digitalWrite(PWM2, 1);
      }
    else
      {
      digitalWrite(DIR2,1);
      analogWrite(PWM2, 255-spd);  
      //digitalWrite(PWM2, 0);
      }
    }
  }
}
