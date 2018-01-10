 /*****************************

	Touch

*****************************/
unsigned char KeyDownProcess(void)
{
	Beep1 = BeepOpen;
	if(1 == NoneFlag)//无人下
	{
		if(0 == KeyFirstPressFlag)
		{
			KeyFirstPressFlag = 1;//按键按下标记		
			return 0;
		}
	}
	
	
	//KeyFirstPressFlag = 1;//按键按下标记
	if(KeySitchON != KeySwitchStatus)//switch 开启判定
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
	if(1 == NoneFlag)//无人下
	{
		if(0 == KeyFirstPressFlag)
		{
			KeyFirstPressFlag = 1;//按键按下标记		
			return 0;
		}
	}
	
	//KeyFirstPressFlag = 1;//按键按下标记	
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
		D_NUM3(Temp_Num1_H);//好像有的问题
	}
}
unsigned char KeySwitchProcess(void)
{

	Beep1 = BeepOpen;
	if(1 == NoneFlag)//无人下
	{
		if(0 == KeyFirstPressFlag)
		{
			KeyFirstPressFlag = 1;//按键按下标记		
			return 0;
		}
	}	
	//加热结束或关闭按键后清除
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

