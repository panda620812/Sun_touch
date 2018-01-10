// ==============================================
// LEDX4_V16.C: create by CompSysFileMaker.
// November 22, 2017 10:43:23
// ==============================================
#include "LEDX4_V16.h"
#include ".\Inc\TIM1628.h"
#include ".\Inc\Key.h"
#include ".\Inc\IRCHQB.h"

#include ".\Src\TIM1628.c"
#include ".\Src\Key.c"
#include ".\Src\IRCHQB.c"

//Timer Interrupt
void __attribute__((interrupt(0x0c))) isr_timer(void) ;		//定时器	

void TimerSetFun( unsigned long TimerCountValieSet )
{
	TimerClose;\
	timerCount = 0;\
	timerCountSet = TimerCountValieSet;\
	TimerOpen;\
	timerFlag = Open;
}
void delay()
{
     volatile unsigned int  i,j;
     for(i=0;i<50;i++)
     for(j=0;j<1000;j++)     
     {
     	GCC_CLRWDT();
     }	
}
//***********************************************************
//	Timer
//***********************************************************
void timerInit(void)
{
      _tmr= 0 ;//256-250;    // 设置2MS中断 
      //从预置寄存器所载入的值开始计数， 到 FFH 时定时器溢出且会产生ISR
      _tmrc=0x06;	   // TS=FSYS, TON=0，64分频	
       //	0b00000011
       //   	|| |||
       //		|| 分频
       //		|控制位
       //       |时钟源	  
       //		
		//前面表示中断类型的缩写， 紧接着的字母“E”代表使能 / 除能位， “F”代表请求标志位。	
		//要使定时 / 计数器中断发生， 总中断控制位 EMI 和相应的内部中断使能位 TE必须先被置位 
		//上电后预置寄存器_tmr处于未知状态。 为了得到定时器的最大计算范围FFH， 预置寄存器需要先清为零
		//如果定时 / 计数器在关闭条件下， 写数据到预置寄存器， 会立即写入实际的定时器。 而如果定时 / 计数器已经打开
		//且正在计数， 在这个周期内写入到预置寄存器的任何新数据将保留在预置寄存器， 直到溢出发生时才被写入实际定时器。
		//定时 / 计数控制寄存器的第 4 位即 TON， 用于定时器开关控制， 设定为逻辑高时， 计数器开始计数， 而清零时则停止计数。 定时 / 计数控制寄存器的第 0~2
		//位用来控制输入时钟预分频器。 TS 位用来选择内部时钟源。
	  _te=1; 		   // 开定时器中断     
	  _tf=0;           // 清零溢出标记
      _emi=1;          // 开总中断
      _ton=0;	       // 定时器开始运行	
}
//***********************************************************
	
//		TouchFun
 
//***********************************************************
 //触摸及显示
 void TouchFun(void)
 {
 	GET_KEY_BITMAP();
	if(DATA_BUF[0]==0x01)  
	{
		if(KeyRelease == KeyStatus)
		{
			KeyStatus = KeyPress;
			KeySwitchProcess()	;
		}			
	}
	else if(DATA_BUF[0]==0x08) 
	{
		if(KeyRelease == KeyStatus)
		{
			KeyStatus = KeyPress;
			KeyDownProcess();
		}		
	}
	else if(DATA_BUF[0]==0x10)
	{
		if(KeyRelease == KeyStatus)
		{
			KeyStatus = KeyPress;
			KeyUpProcess()	;		
		}
	}		
	else
	{
		KeyStatus = KeyRelease ;
	}	
 }
//***********************************************************
	
//	Adc
 
//***********************************************************
//查值 二分法
/**/ 
unsigned char TempValueSearch(unsigned short Res) 
{
	volatile unsigned char low = 0, mid =0, high = 100;
	while(high - low >= 1)
	{
		mid = (low +high)/2;
		if(Res <  TempForm[mid])
		{
			low = mid; //+1
			if(high -low<2)
			{
				return mid;
			}
		}
		else if(Res >  TempForm[mid] )
		{
			high = mid 	;//-1	
			if(high -low<2)
			{
				return mid;
			}	
		}
		else
		{
			return mid;
		}		
	}
 	return mid;
 }
void ADCGetFun(void)
{
    if(_eocb==0)//ad转换结束标记
	{
		dat = _adrh;        // 高8位AD转换 
		dat <<=4;
		dat += (_adrl>>4);  	 		      	  
      	  
		intTemp1 = (4095 - dat);//串联电阻20K
		//longTemp1	= 200UL * dat ;
		
		R_value	= 200UL* dat/intTemp1;
		if(R_value < 20) R_value = 1750;//初始检测，无值认为是0
		
		R_valueSum = R_valueSum + R_value ;
		ADCCount ++;
		if(100 == ADCCount)
		{
			R_value 		= R_valueSum/100;
			T_valueGet 		= TempValueSearch(R_value);
					
			ADCCount 		= 0;
			R_valueSum 		= 0;
			ADCCompleteFlag = 1;
		}
		_start=0;//0 → 1 → 0： 启动
		_start=1;
		_start=0; 
	} 
}    
void ErrorProcess(void)
{
	unsigned char i;
	RelayHeatClose;	// Heat Close ; PV Open
	RelayPVClose;
	TimerClose;//定时器 关闭		
	for(i = 0;i<10;i++ )//蜂鸣器报警10声	
	{
		Beep1 =  BeepOpen;
		delay();
		delay();
		Beep1 =  BeepClose;
		delay();			
		//喂狗
	}
}
unsigned char ADC_Check(void)
{	
	// unsigned char i;

	if((T_valueGet < 3)&&(0 == E2WaringFlag)&&(1!= E1WaringFlag))
	{
		E2WaringFlag = 1;//报警标记
		D_E2;//显示“E2”				
		ErrorProcess();
		return 0;
	}	
	else if(( T_valueGet > 90)&&(0 == E1WaringFlag)&&(1 != E2WaringFlag))
	{
		E1WaringFlag = 1;
		D_E1;//显示“E1”	
		ErrorProcess();
		return 0;
	}
	if((1 == E2WaringFlag)||(1 == E2WaringFlag))
	{
		return 0;
	}
	else
	{	
		E1WaringFlag = E2WaringFlag = 0;	//报警标记 Clear 
		//工作状态检查，是否是空闲
		SunControl();
		return 1;
	}	
}

//***********************************************************
//*SUB. NAME:USER INITIAL PROGRAM                           *
//*INPUT    :                                               *
//*OUTPUT   :                                               *
//*USED REG.:                                               *
//*FUNCTION :                                               *
//***********************************************************
void LEDX4_V16_INITIAL()
{
//LED BEEP INITIAL
//LED 	0 	打开
//Beep 	0 	关闭
	LEDSwitch_C = 0;
	LEDSwitch	= LedOpen;//Open
  	LED_DOWN_C	= 0;
	LED_DOWN  	= LedOpen;
 	LED_UP_C 	= 0;
 	LED_UP  	= LedOpen;
 	Beep1_C = 0;//Close
 	Beep1   = BeepOpen; 
// Relay 
	Relay_HEAT_C  	=  0;
	RelayHeatClose;
	Relay_PV_C 		=  0;
	RelayPVOpen;
//数码管引脚初始化
	CLK1_C	= 0;
	CLK1	= 0;
	DIO1_C	= 0;
	DIO1	= 0;
	STB1_C	= 0;//
	STB1	= 0;
//人体感应
	_pdpu7	= 1;	
	_pdc7 	= 1;//		 
	_pd7 	= 0;		
//红外引脚初始化
	_pbpu5  =  1;  //设置上拉电阻
	_pbc5   =  1;	//设置为输入
	_pbpu4  =  1;  //设置上拉电阻
	_pbpu7  =  1;  //设置上拉电阻
	// _pdpu0  =  1;
//adc 初始化	
	 _adcr0=0b00000000;   // 选择 A/D 通道AN0--Pd0   
	 _adcr1=0b00000100;   // 定义 ADC 时钟源=Fsys/16
	 _acerl=0b00000001;   // 定义 Pd0 为 A/D 输入AN0		
	
	_start=0;
	_start=1;
	_start=0;
//变量initial	
	
//Time初始化
	timerInit();
	//A 接通电源 蜂鸣器短鸣一声，数码屏所有灯点亮二秒
	delay()	;
	Beep1 = BeepClose;
	//数码管All Open
	displayClear(0xffff);
	// displayTwst(0xc0,0xffff); 
	delay()	;	
	delay()	;
	delay()	;	
	delay()	;	
	//数码管显示清零	
	displayClear(0);
	C_Display = 0x70;
	Temp_Num1_L	= 5 ;
	Temp_Num1_H	= 8 ;
	//默认设置温度为85℃
	//显示屏显示内胆当前温度	
	LEDSwitch = LED_DOWN = LED_UP = LedClose;	
	//
	NoneFlag = 0;
}
void HeatCompleteBeep(void)
{
	if(timerCount > 1800000 - 300)//计时
	{
		Beep1 = BeepOpen;
		KeyCountOpenflag = 1;
		ControlFlag = StatusSwitchOFF;//进入加热结束状态	//
	}	
}
void PersonCheckDisableFun(void)//红外检测失效处理
{
	if((1 == PersonCheck))//有人
	{
		RelayPVClose;
		RelayHeatClose;//电磁阀关闭
		ND_Heat();
		ND_PV();
	}
	else
	{	
		D_Heat();
		D_PV();
		RelayHeatOpen;//电磁阀打开
		RelayPVOpen;
	}					
}

void SunControl(void)
{	
	switch(ControlFlag)
	{
		case StatusIdle:
			if(T_valueGet  < 35)//内胆温度低于35℃,自动加热，是否有其他开启条件
			{
				PersonCheckDisableFun();
			}
			else if(T_valueGet < 85)
			{
				if((1 == PersonCheck))//有人
				{
					RelayPVClose;
					RelayHeatClose;//电磁阀关闭
					ND_Heat();
					ND_PV();
				}
				else
				{	
					D_PV();
					RelayPVOpen;
				}
			}
			else
			{
				RelayHeatClose;
				RelayPVClose;
				ND_PV();
				ND_Heat();
			}	
		break;
		case StatusSwitchON:
			if(Close == timer3sFlag)
			{
				if((Close == timerFlag)&&(KeyRelease == KeyStatus  ))
				{
					TimerSetFun(2000);	
					timer3sFlag = Open;
				}
			}
			if(timerCount > 1800)
			{
				Beep1 = BeepOpen;
				KeyCountOpenflag = 1;
				ControlFlag = StatusHeatOpen;//进入加热状态
			}
		break;
		case StatusSwitchOFF: //StatusHeatComplete
			KeySwitchStatus = KeySitchOFF;	
			LEDSwitch = LedClose;
			
			timer1hourFlag = timer3sFlag = timerFlag = Close;	
			timerCount = 0;
			
			TimerClose;		
			//RelayHeatClose;//加热关闭
			//ND_Heat();//关闭加热显示
			ND_WarmKeep();//关闭保温显示
			ControlFlag = StatusIdle;	
			KeyFirstPressFlag = 0;
		break;
		case StatusHeatOpen:
			KeyFirstPressFlag = 0;	
			
			if(Close == timerFlag)//定时器空闲
			{
				if(Close == timer1hourFlag)
				{
					timer1hourFlag = Open;
					TimerSetFun(1800000);//30000	
				}
				//开始
			}
			if(T_valueGet > Temp_Num1)//ADC 加滤波
			{
				RelayHeatClose;//关闭加热
				RelayPVClose;
				ND_PV();
				ND_Heat(); 
				
				D_WarmKeep();
				ControlFlag = StatusWarmHold;//进入温度保持	
			}
			else
			{					
				PersonCheckDisableFun();
				HeatCompleteBeep();
			}	
		break;
		case StatusWarmHold:
			KeyFirstPressFlag = 0;			
			if(T_valueGet < Temp_Num1-5)//ADC 加滤波
			{
				ND_WarmKeep();
				ControlFlag = StatusHeatOpen;//进入加热状态	
			}
			HeatCompleteBeep();	
		break;
		default: break;
	}
}
//屏幕显示
void ScreenDisplay(void)
{
	BarTimerCount ++;
	if(BarTimerCount>250)
	{
		if(BarNum >10)
		{
			BarDisplayNum1 = BarDisplayNum2 = BarDisplayNum3 = BarDisplayNum4 = 0;				
			BarNum = 0;
		}
		if(StatusHeatOpen == ControlFlag)
		{
		}
		else
		{
			BarDisplayNum1 = BarDisplayNum2 = BarDisplayNum3 =	BarDisplayNum4 = 0;			
		}	
		if(BarNum == 0)				BarDisplayNum1 = BarDisplayNum1 + 0x10;			
		else if(BarNum == 1)		BarDisplayNum1 = BarDisplayNum1 + 0x20;			
		else if(BarNum == 2)		BarDisplayNum1 = BarDisplayNum1 + 0x40;			
		else if(BarNum == 3)		BarDisplayNum2 = BarDisplayNum2 + 0x10;			
		else if(BarNum == 4)		BarDisplayNum2 = BarDisplayNum2 + 0x20;			
		else if(BarNum == 5)		BarDisplayNum2 = BarDisplayNum2 + 0x40;			
		else if(BarNum == 6)		BarDisplayNum3 = BarDisplayNum3 + 0x10;			
		else if(BarNum == 7)		BarDisplayNum3 = BarDisplayNum3 + 0x20;			
		else if(BarNum == 8)		BarDisplayNum3 = BarDisplayNum3 + 0x40; 	
		else if(BarNum == 9)		BarDisplayNum4 = BarDisplayNum4 + 0x40; 		
		
		BarTimerCount = 0;
		D_NUM1(Temp_Num2_H);
		D_NUM2(Temp_Num2_L);
		D_NUM3(Temp_Num1_H);
	 	D_NUM4(Temp_Num1_L);
		BarNum ++;
	}		
}
void NoPersonCheckFun(void)
{
	if(KeyStatus == KeyPress)//改成while？？？
	{
		KeyCountOpenflag = 1;// delay();		
	}
	if(1 == KeyCountOpenflag)
	{
		KeyCount++;
		if(KeyCount>150)
		{
			KeyCount = 0;
			KeyCountOpenflag = 0;
			//Beep1 = BeepClose;
			LED_UP = LED_DOWN = LedClose;//	= LEDSwitch 		
		}
	}	
	if(0 == PersonCheck)//
	{	
		NoneTimerCount ++;
		personTimerCount = 0;
		if(NoneTimerCount > 20000)//3min   10000 ---》30s
		{								//60000 --- 》160s
			NoneFlag = 1;//无人
			NoneTimerCount = 0;
		}
	}	
	else
	{	
		NoneTimerCount = 0;
		personTimerCount ++;
	
		if(personTimerCount > 300)
		{
			personTimerCount = 0;
			NoneFlag = 0;
		}
	}
	if((1 == NoneFlag)&&(1 == KeyFirstPressFlag))//屏幕关闭状态下，有按键
	{
		// KeyFirstPressFlag = 0;
		NoneFlag = 0;	
	}
	if(0 == NoneFlag)//有人
	{
		ScreenDisplay();
	}
	else			//无人
	{
		displayClear(0);
	}		
	
}
//***********************************************************
//*SUB. NAME:USER Main PROGRAM                              *
//*INPUT    :                                               *
//*OUTPUT   :                                               *
//*USED REG.:                                               *
//*FUNCTION :                                               *
//***********************************************************
void LEDX4_V16()
{
	unsigned char flag;
	if(1 == Beep1)
	{
		BeepCount++;
		if(BeepCount > 150)
			Beep1 = 0;
	}
	else
		BeepCount = 0;
	
	Temp_Num2_L = T_valueGet%10;
	Temp_Num2_H = T_valueGet/10;
	ADCGetFun();
	if(1 == ADCCompleteFlag)
	{ 
		ADCCompleteFlag = 0;
		flag =  ADC_Check();	//1;//
	}		
	if(1 == flag)
	{
		NoPersonCheckFun();	
		TouchFun();
		IR_FUN();
	}
}
/******************************/
//void  time( )
/******************************/
void  isr_timer(void)
{
	 _tf=0;	       // 清除溢出标记 
	 timerCount ++;
	 if(timerCount > timerCountSet)   //1S LED8灯闪烁一次
	 { 
		timerCount = 0;		
		timerFlag = Close;
		timer3sFlag = Close;
		TimerClose;	
	 }  
}

