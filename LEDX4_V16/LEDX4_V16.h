/*************************************************************************************************************************
 * Created by: Holtek Touch MCU Workshop, Version 3.5.0.0
 * LEDX4_V16.H
 * 03:02:23 PM Saturday, December 16, 2017
*************************************************************************************************************************/
#include "..\TKS_GLOBE_VARIES.h" 
#include "..\BS84B08A_LIBV413\BS84B08A_LIBV413.cex" 
#include "..\MAIN_PROGRAM_V104\MAIN_PROGRAM_V104.cex" 
#include "..\USER_PROGRAM\USER_PROGRAM.cex" 

#define _LEDX4_V16_ 
#define LEDSwitch       _pa1
#define LEDSwitch_C     _pac1
#define LED_DOWN        _pb2
#define LED_DOWN_C      _pbc2
#define LED_UP          _pb1
#define LED_UP_C        _pbc1
#define Beep1           _pa3
#define Beep1_C         _pac3
#define Temp1           _pd0
#define Temp1_C         _pdc0
#define BeepOpen        1
#define BeepClose       0
#define LedOpen         0
#define LedClose        1
volatile unsigned char BeepCount ;
//Relay
#define RelayOpen       1
#define RelayClose      0
//KeyPress
#define OUTPUT_LEVEL    0  // GND
#define KeyPress        1
#define KeyRelease      0
#define KeySitchON      1
#define KeySitchOFF     0


volatile unsigned char KeySwitchStatus ;
volatile unsigned char KeyCount ;
volatile unsigned char KeyCountOpenflag ;
const unsigned short TempForm[]={	1673, 1589, 1509, 1434, 1363, 1295, 1232, 1172, 1115, 1061, 
									1010, 962, 917, 873, 833, 794, 757, 722, 689, 658, 
									628, 600, 573, 547, 523, 500, 478, 457, 437, 419, 
									401, 384, 367, 352, 337, 323, 310, 297, 285, 273, 
									262, 251, 241, 231, 222, 213, 205, 197, 189, 182, 
									175, 168, 162, 155, 150, 144, 139, 133, 128, 124, 
									119, 115, 111, 107, 103, 99, 95, 92, 89, 86, 
									83, 80, 77, 74, 72, 69, 67, 65, 62, 60, 
									58, 56, 54, 53, 51, 49, 48, 46, 45, 43, 
									42, 40, 39, 38, 37, 36, 34, 33, 32, 31, 
									30 };
//TIM1628
#define CLK1_C 	_pac7
#define CLK1 	_pa7
#define DIO1_C 	_pac4
#define DIO1 	_pa4
#define STB1_C 	_pdc1
#define STB1 	_pd1
//adc relay
#define Relay_HEAT_C    _pac0//加热
#define Relay_HEAT    	_pa0//加热
#define Relay_PV_C   	_pac2//光伏
#define Relay_PV    	_pa2//光伏
#define RelayHeatOpen   _pa0 = 1;//
#define RelayHeatClose  _pa0 = 0;//
#define RelayPVOpen    	_pa2 = 0;//
#define RelayPVClose    _pa2 = 1;//
//去除显示
#define ND_ERROR 	   	display16(0xcc,0x0010); 
//显示
#define D_PV() 			C8Value = 0x10;///display16(0xc8,0 , 0x0010);
#define ND_PV() 		C8Value = 0x00;///display16(0xc8,0 , 0x0010);	
#define D_WarmKeep()	C8Value2 = 0x20;//display16(0xc8,x,0);		
#define ND_WarmKeep()	C8Value2 = 0x00;//display16(0xc8,x,0);	
#define D_Heat() 		CaValue = 0x10;// display16(0xca,0 , 0x1000);
#define ND_Heat() 		CaValue = 0x00;//display16(0xca,0 , 0x0000);
#define D_ERROR() 	   	display16(0xcc,0); 


#define D_NUM1(x) display16(0xc0,x);
#define D_NUM2(x) display16(0xc4,x);
#define D_NUM3(x) display16(0xc8,x);
#define D_NUM4(x) display16(0xca,x);
// #define D_E2 display16(0xc0,0x0e,0);display16(0xc4,0x02,0);
#define D_E2 C_Display = 0;display16(0xc0,0x0e);display16(0xc4,0x02);	display16(0xcc,0x10); 
// #define D_E1 display16(0xc0,0x0e,0);display16(0xc4,0x01,0);
#define D_E1 C_Display = 0;display16(0xc0,0x0e);display16(0xc4,0x01);	display16(0xcc,0x10); 

volatile unsigned char C8Value ;//用与光伏  
volatile unsigned char C8Value2 ;//用与  保温 
volatile unsigned char CaValue ;
volatile unsigned char C_Display;//C c显示
volatile unsigned char KeyFirstPressFlag ;
//volatile unsigned char CCValue = 0;

volatile unsigned char BarNum 		;
volatile unsigned short BarTimerCount ;
short const CODE[]={ 0x0387,0x0180,0x030B,0x0389,0x018C,0x028D,0x028F,0x0380,0x038F,0x038D,\
0x038E,0x008F,0x0207,0x018B,0x020F,0x020E,0x0000}; //数码管0-F的编码  
//a     b      c     d     e      f       
volatile unsigned char BarDisplayNum1 ;
volatile unsigned char BarDisplayNum2 ;
volatile unsigned char BarDisplayNum3 ;
volatile unsigned char BarDisplayNum4 ;

#define Temp_Num1  Temp_Num1_H*10 + Temp_Num1_L
volatile unsigned char Temp_Num1_L;//预设值
volatile unsigned char Temp_Num1_H;
#define Temp_Num2  Temp_Num2_H*10 + Temp_Num2_L
volatile unsigned char Temp_Num2_L ;
volatile unsigned char Temp_Num2_H ;
volatile unsigned char KeyStatus ;



//Timer
#define Open        1
#define Close       0

volatile unsigned long 		timerCountSet ;
//volatile unsigned char 	timerVoerFlag = 0;
volatile unsigned long 		timerCount ;
// volatile unsigned int  		timerBaseCount = 0;

volatile unsigned char 		timerFlag ;

volatile unsigned char 		timer3sFlag ;//switch on/off 3s检查标记
volatile unsigned char 		timer1hourFlag;//HeatOpen 1 hour 检查标记


#define  TimerOpen	_ton = 1;	
#define	 TimerClose _ton = 0;
// 红外
#define IR_Out  	_pb5//对应红外引脚输入
#define Delay1us  	GCC_DELAY(2) 
#define Delay1ms  	GCC_DELAY(2000) 
#define Delay800us  GCC_DELAY(1600) 
#define Delay1150us GCC_DELAY(2300) 
#define Delay2272us GCC_DELAY(4544) 


volatile unsigned long 	IRCount ;



volatile unsigned char _datasave[4] = {};
volatile unsigned char StartFlag ;
volatile unsigned char BOOT_REPEATING_CODE_Flag ;  
//人体感应
#define PersonCheck_C 	_pdc7//对应红外引脚输入
#define PersonCheck 	_pd7//对应红外引脚输入
volatile char NoneFlag;//0 有人 ，1 没人
volatile char PersonCheckDisable;//0 红外缺失  1 红外还在
volatile short personTimerCount;

volatile unsigned long NoneTimerCount;







//Warning
volatile unsigned char E2WaringFlag ;
volatile unsigned char E1WaringFlag ;

//Adc
// volatile float T_value ;
volatile unsigned char T_valueGet ;

volatile unsigned int dat;

volatile unsigned long T_value ;//电阻阻值 
volatile unsigned long R_value ;//电阻阻值 
volatile unsigned long R_valueSum ;//电阻阻值 
volatile unsigned short ADCCount ;//电阻阻值 
volatile unsigned char ADCCompleteFlag ;//电阻阻值 
volatile unsigned int intTemp1 ;//电阻阻值 
// volatile unsigned int intTemp2 ;//电阻阻值 
// volatile unsigned int intTemp3 ;//电阻阻值 
// volatile unsigned long longTemp1 ;//电阻阻值 
// volatile unsigned long longTemp2 ;//电阻阻值 
// volatile unsigned long longTemp3 ;//电阻阻值 
// volatile unsigned long longTemp4 ;//电阻阻值 

// const unsigned char R = 20;	 //串联电阻阻值
// const float a = 0.001021;
// const float b = -0.3775;
// const float c = 32.69;
// const float d = 481.3;
// const float e = -1428;
// const unsigned short f = 1838;
// volatile float a ;
// volatile float b ;
// volatile float c ;
// volatile float d ;
// volatile float e ;
// volatile unsigned short f ;
//	R_value = 33;//预设值，待修改
// 加热
// volatile unsigned char RelayHeatFlag = 0;

//
#define StatusIdle			0 
#define StatusSwitchON		1
#define StatusSwitchOFF		2
#define StatusHeatOpen		3
#define StatusHeatcontinue	4
#define StatusWarmHold 		5
#define StatusHeatComplete	6
#define StatusE1			7
#define StatusE2			8
// #define StatusIdle 			5
volatile unsigned char ControlFlag ;
void TimerSetFun( unsigned long TimerCsountValieSet );
void SunControl(void);
void NoPersonCheckFun(void);

// #define TimerSetFun(x)	TimerClose;\
					// timerCount = 0;\
					// timerCountSet = x;\
					// TimerOpen;\
					// timerFlag = Open;


/*				
					timerCount = 0; //定时器计数清零
					timerCountSet = 2000;//鸣笛定时 3s  //计数量设置
					TimerOpen;//定时器打开
					timerFlag = Open; //定时器 标记 开始	

*/




