#ifndef _TIM1628_H
#define _TIM1628_H

 
 void send_8bit(unsigned char dat) ;
 void send_16bit(unsigned short dat) ;
 void command(unsigned char com) ;
 void displayClear(unsigned short value); 
 void display16(unsigned char adress,unsigned char NUM) ;
 void displayTwst(unsigned char adress,unsigned short test) ;
 
#endif 
 