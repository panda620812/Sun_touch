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
void __attribute__((interrupt(0x0c))) isr_timer(void) ;		//��ʱ��	

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
      _tmr= 0 ;//256-250;    // ����2MS�ж� 
      //��Ԥ�üĴ����������ֵ��ʼ������ �� FFH ʱ��ʱ������һ����ISR
      _tmrc=0x06;	   // TS=FSYS, TON=0��64��Ƶ	
       //	0b00000011
       //   	|| |||
       //		|| ��Ƶ
       //		|����λ
       //       |ʱ��Դ	  
       //		
		//ǰ���ʾ�ж����͵���д�� �����ŵ���ĸ��E������ʹ�� / ����λ�� ��F�����������־λ��	
		//Ҫʹ��ʱ / �������жϷ����� ���жϿ���λ EMI ����Ӧ���ڲ��ж�ʹ��λ TE�����ȱ���λ 
		//�ϵ��Ԥ�üĴ���_tmr����δ֪״̬�� Ϊ�˵õ���ʱ���������㷶ΧFFH�� Ԥ�üĴ�����Ҫ����Ϊ��
		//�����ʱ / �������ڹر������£� д���ݵ�Ԥ�üĴ����� ������д��ʵ�ʵĶ�ʱ���� �������ʱ / �������Ѿ���
		//�����ڼ����� �����������д�뵽Ԥ�üĴ������κ������ݽ�������Ԥ�üĴ����� ֱ���������ʱ�ű�д��ʵ�ʶ�ʱ����
		//��ʱ / �������ƼĴ����ĵ� 4 λ�� TON�� ���ڶ�ʱ�����ؿ��ƣ� �趨Ϊ�߼���ʱ�� ��������ʼ������ ������ʱ��ֹͣ������ ��ʱ / �������ƼĴ����ĵ� 0~2
		//λ������������ʱ��Ԥ��Ƶ���� TS λ����ѡ���ڲ�ʱ��Դ��
	  _te=1; 		   // ����ʱ���ж�     
	  _tf=0;           // ����������
      _emi=1;          // �����ж�
      _ton=0;	       // ��ʱ����ʼ����	
}
//***********************************************************
	
//		TouchFun
 
//***********************************************************
 //��������ʾ
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
//��ֵ ���ַ�
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
    if(_eocb==0)//adת���������
	{
		dat = _adrh;        // ��8λADת�� 
		dat <<=4;
		dat += (_adrl>>4);  	 		      	  
      	  
		intTemp1 = (4095 - dat);//��������20K
		//longTemp1	= 200UL * dat ;
		
		R_value	= 200UL* dat/intTemp1;
		if(R_value < 20) R_value = 1750;//��ʼ��⣬��ֵ��Ϊ��0
		
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
		_start=0;//0 �� 1 �� 0�� ����
		_start=1;
		_start=0; 
	} 
}    
void ErrorProcess(void)
{
	unsigned char i;
	RelayHeatClose;	// Heat Close ; PV Open
	RelayPVClose;
	TimerClose;//��ʱ�� �ر�		
	for(i = 0;i<10;i++ )//����������10��	
	{
		Beep1 =  BeepOpen;
		delay();
		delay();
		Beep1 =  BeepClose;
		delay();			
		//ι��
	}
}
unsigned char ADC_Check(void)
{	
	// unsigned char i;

	if((T_valueGet < 3)&&(0 == E2WaringFlag)&&(1!= E1WaringFlag))
	{
		E2WaringFlag = 1;//�������
		D_E2;//��ʾ��E2��				
		ErrorProcess();
		return 0;
	}	
	else if(( T_valueGet > 90)&&(0 == E1WaringFlag)&&(1 != E2WaringFlag))
	{
		E1WaringFlag = 1;
		D_E1;//��ʾ��E1��	
		ErrorProcess();
		return 0;
	}
	if((1 == E2WaringFlag)||(1 == E2WaringFlag))
	{
		return 0;
	}
	else
	{	
		E1WaringFlag = E2WaringFlag = 0;	//������� Clear 
		//����״̬��飬�Ƿ��ǿ���
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
//LED 	0 	��
//Beep 	0 	�ر�
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
//��������ų�ʼ��
	CLK1_C	= 0;
	CLK1	= 0;
	DIO1_C	= 0;
	DIO1	= 0;
	STB1_C	= 0;//
	STB1	= 0;
//�����Ӧ
	_pdpu7	= 1;	
	_pdc7 	= 1;//		 
	_pd7 	= 0;		
//�������ų�ʼ��
	_pbpu5  =  1;  //������������
	_pbc5   =  1;	//����Ϊ����
	_pbpu4  =  1;  //������������
	_pbpu7  =  1;  //������������
	// _pdpu0  =  1;
//adc ��ʼ��	
	 _adcr0=0b00000000;   // ѡ�� A/D ͨ��AN0--Pd0   
	 _adcr1=0b00000100;   // ���� ADC ʱ��Դ=Fsys/16
	 _acerl=0b00000001;   // ���� Pd0 Ϊ A/D ����AN0		
	
	_start=0;
	_start=1;
	_start=0;
//����initial	
	
//Time��ʼ��
	timerInit();
	//A ��ͨ��Դ ����������һ�������������еƵ�������
	delay()	;
	Beep1 = BeepClose;
	//�����All Open
	displayClear(0xffff);
	// displayTwst(0xc0,0xffff); 
	delay()	;	
	delay()	;
	delay()	;	
	delay()	;	
	//�������ʾ����	
	displayClear(0);
	C_Display = 0x70;
	Temp_Num1_L	= 5 ;
	Temp_Num1_H	= 8 ;
	//Ĭ�������¶�Ϊ85��
	//��ʾ����ʾ�ڵ���ǰ�¶�	
	LEDSwitch = LED_DOWN = LED_UP = LedClose;	
	//
	NoneFlag = 0;
}
void HeatCompleteBeep(void)
{
	if(timerCount > 1800000 - 300)//��ʱ
	{
		Beep1 = BeepOpen;
		KeyCountOpenflag = 1;
		ControlFlag = StatusSwitchOFF;//������Ƚ���״̬	//
	}	
}
void PersonCheckDisableFun(void)//������ʧЧ����
{
	if((1 == PersonCheck))//����
	{
		RelayPVClose;
		RelayHeatClose;//��ŷ��ر�
		ND_Heat();
		ND_PV();
	}
	else
	{	
		D_Heat();
		D_PV();
		RelayHeatOpen;//��ŷ���
		RelayPVOpen;
	}					
}

void SunControl(void)
{	
	switch(ControlFlag)
	{
		case StatusIdle:
			if(T_valueGet  < 35)//�ڵ��¶ȵ���35��,�Զ����ȣ��Ƿ���������������
			{
				PersonCheckDisableFun();
			}
			else if(T_valueGet < 85)
			{
				if((1 == PersonCheck))//����
				{
					RelayPVClose;
					RelayHeatClose;//��ŷ��ر�
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
				ControlFlag = StatusHeatOpen;//�������״̬
			}
		break;
		case StatusSwitchOFF: //StatusHeatComplete
			KeySwitchStatus = KeySitchOFF;	
			LEDSwitch = LedClose;
			
			timer1hourFlag = timer3sFlag = timerFlag = Close;	
			timerCount = 0;
			
			TimerClose;		
			//RelayHeatClose;//���ȹر�
			//ND_Heat();//�رռ�����ʾ
			ND_WarmKeep();//�رձ�����ʾ
			ControlFlag = StatusIdle;	
			KeyFirstPressFlag = 0;
		break;
		case StatusHeatOpen:
			KeyFirstPressFlag = 0;	
			
			if(Close == timerFlag)//��ʱ������
			{
				if(Close == timer1hourFlag)
				{
					timer1hourFlag = Open;
					TimerSetFun(1800000);//30000	
				}
				//��ʼ
			}
			if(T_valueGet > Temp_Num1)//ADC ���˲�
			{
				RelayHeatClose;//�رռ���
				RelayPVClose;
				ND_PV();
				ND_Heat(); 
				
				D_WarmKeep();
				ControlFlag = StatusWarmHold;//�����¶ȱ���	
			}
			else
			{					
				PersonCheckDisableFun();
				HeatCompleteBeep();
			}	
		break;
		case StatusWarmHold:
			KeyFirstPressFlag = 0;			
			if(T_valueGet < Temp_Num1-5)//ADC ���˲�
			{
				ND_WarmKeep();
				ControlFlag = StatusHeatOpen;//�������״̬	
			}
			HeatCompleteBeep();	
		break;
		default: break;
	}
}
//��Ļ��ʾ
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
	if(KeyStatus == KeyPress)//�ĳ�while������
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
		if(NoneTimerCount > 20000)//3min   10000 ---��30s
		{								//60000 --- ��160s
			NoneFlag = 1;//����
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
	if((1 == NoneFlag)&&(1 == KeyFirstPressFlag))//��Ļ�ر�״̬�£��а���
	{
		// KeyFirstPressFlag = 0;
		NoneFlag = 0;	
	}
	if(0 == NoneFlag)//����
	{
		ScreenDisplay();
	}
	else			//����
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
	 _tf=0;	       // ��������� 
	 timerCount ++;
	 if(timerCount > timerCountSet)   //1S LED8����˸һ��
	 { 
		timerCount = 0;		
		timerFlag = Close;
		timer3sFlag = Close;
		TimerClose;	
	 }  
}

