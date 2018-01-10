#ifndef _IRCHQB_H
#define _IRCHQB_H

union DatachangeType
{
   struct {
    unsigned char b0 : 1;
    unsigned char b1 : 1;
    unsigned char b2 : 1;
    unsigned char b3 : 1;
    unsigned char b4 : 1;
    unsigned char b5 : 1;
    unsigned char b6 : 1;
    unsigned char b7 : 1;                       
    } _bits;
    unsigned char data;
}Datachange;

unsigned char BOOT_REPEATING_CODE_Judge(); 
unsigned char H_L_LEVEL_Judge();  //单个接收部分
unsigned char START_Judge(); 
void DataSave(void);
void IR_FUN(void);

#endif
