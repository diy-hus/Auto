 
#ifndef AutoDIY_h
#define AutoDIY_h

#include "Arduino.h"
class AutoDIY
{
  public:
	void init_adc(void);
	void set_adc(void);
	void get_adc(void);
	void read_adc(void);
	void read_line(void);
	void do_line(int kp,int spd)
	void init_pin();
	void control_motor(int dc, int dir, int spd);  
  private:
	int adc[4], min_adc[4], max_adc[4], ng_adc[4];
	int adc_press = 13;
	int ngatu,nho, tmp;
	int k; 
};

#endif