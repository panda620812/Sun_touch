 /*****************************

	Touch

*****************************/
unsigned char KeyDownProcess(void)
{
	Beep1 = BeepOpen;
	if(1 == NoneFlag)//������
	{
		if(0 == KeyFirstPressFlag)
		{
			KeyFirstPressFlag = 1;//�������±��		
			return 0;
		}
	}
	
	
	//KeyFirstPressFlag = 1;//�������±��
	if(KeySitchON != KeySwitchStatus)//switch �����ж�
	{
		return 1;
	}
	
  	LED_DOWN  = LedOpen; 	
	
	
	if ((0 == Temp_Num1_L)&&(Temp_Num1_H > 0))
	{
		Temp_Num1_L = 5;
		Temp_Num1_H --;
						
		if(0 == Temp_Num1_H)
		{
			Temp_Num1_H;
		}
		D_NUM3(Temp_Num1_H);
		D_NUM4(Temp_Num1_L);	
	}
	else if((5 == Temp_Num1_L)&&(3 == Temp_Num1_H ))
	{
					
	}
	else
	{
		Temp_Num1_L = 0;
		D_NUM4(Temp_Num1_L);
	}
}
unsigned char KeyUpProcess(void)
{	

	Beep1 = BeepOpen;
	if(1 == NoneFlag)//������
	{
		if(0 == KeyFirstPressFlag)
		{
			KeyFirstPressFlag = 1;//�������±��		
			return 0;
		}
	}
	
	//KeyFirstPressFlag = 1;//�������±��	
	if(KeySitchON != KeySwitchStatus)
	{
		return 1;
	}
	LED_UP    = LedOpen;  	


	if ((5 == Temp_Num1_L)&&(Temp_Num1_H < 9))
	{
		Temp_Num1_L = 0;
		Temp_Num1_H ++;
		if(Temp_Num1_H == 9)
		{
			Temp_Num1_H = 8 ;
			Temp_Num1_L = 5;				
		}
		D_NUM3(Temp_Num1_H);
		D_NUM4(Temp_Num1_L);	
	}
	else 
	{
		Temp_Num1_L = 5;
		D_NUM3(Temp_Num1_H);//�����е�����
	}
}
unsigned char KeySwitchProcess(void)
{

	Beep1 = BeepOpen;
	if(1 == NoneFlag)//������
	{
		if(0 == KeyFirstPressFlag)
		{
			KeyFirstPressFlag = 1;//�������±��		
			return 0;
		}
	}	
	//���Ƚ�����رհ��������
	if(KeySitchOFF == KeySwitchStatus)
	{
 
		LEDSwitch = LedOpen;    //  
		KeySwitchStatus = KeySitchON;
		ControlFlag 	= StatusSwitchON;
	}
	else
	{
		LEDSwitch = LedClose;    //  
		KeySwitchStatus = KeySitchOFF;	
		ControlFlag 	= StatusSwitchOFF;
	}
}

