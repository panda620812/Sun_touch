 /*****************************

	Touch

*****************************/
void KeyDownProcess(void)
{
  	LED_DOWN  = 0; 
	if ((0 == Temp_Num1_L)&&(Temp_Num1_H > 0))
	{
		Temp_Num1_L = 5;
		Temp_Num1_H --;
		D_NUM1(Temp_Num1_H);				
		if(0 == Temp_Num1_H)
		{
			Temp_Num1_H;
		}
		D_NUM2(Temp_Num1_L);	
	}
	else if((5 == Temp_Num1_L)&&(3 == Temp_Num1_H ))
	{
					
	}
	else
	{
		Temp_Num1_L = 0;
		D_NUM2(Temp_Num1_L);
	}
}
void KeyUpProcess(void)
{
	LED_UP    = 0;  
	// Beep1 = BeepOpen;	
	if ((5 == Temp_Num1_L)&&(Temp_Num1_H < 10))
	{
		Temp_Num1_L = 0;
		Temp_Num1_H ++;
		if(Temp_Num1_H>9)
		{
			Temp_Num1_H = 9 ;
			Temp_Num1_L = 5;				
		}
		D_NUM1(Temp_Num1_H);
		D_NUM2(Temp_Num1_L);	
	}
	else 
	{
		Temp_Num1_L = 5;
		D_NUM2(Temp_Num1_L);
	}
}
void KeySwitchProcess(void)
{
	LEDSwitch = LedOpen;    //       
}
void KeyValueProcess(void)
{
	//按键结束判定
	//按键状态 Open Close判定
	// if()
	// {
			if(RelayClose == RelayHeatFlag)
			{
				Relay_HEAT = RelayOpen;
				//显示加热
				//开启定时器 60分钟
				RelayHeatFlag = RelayOpen;//加热中状态标记						
			}
	// }		
	// else
	// {
			if(RelayOpen == RelayHeatFlag )
			{
				//时间判定
				
				//时间计时中
					//保温标记
					if(R_value > Temp_Num1)//温度判断
					{
						//显示保温
						//关闭加热显示 + 电磁阀关闭
						Relay_HEAT = RelayClose;
						//保温标记
					}
					else
					{
						
					}
						
				//时间结束
					////关闭加热
			}
	// }
}
 //触摸及显示
 void TouchFun(void)
 {
 	GET_KEY_BITMAP();
	// temp8 = DATA_BUF[0];
	// volatile unsigned int  i,j;	
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
		// temp162 ++;
		if(KeyRelease == KeyStatus)
		{
			KeyStatus = KeyPress;
			KeyDownProcess();
		}		
	}
	else if(DATA_BUF[0]==0x10)
	{
		// 
		        // 	
	//	Beep1 = BeepOpen;
	//	temp16 ++;
	//	temp16 = KEY_STATUS[1];
		if(KeyRelease == KeyStatus)
		{
			KeyStatus = KeyPress;
			KeyUpProcess()	;		
		}
	}		
	else
	{
		LED_UP = LEDSwitch = LED_DOWN = LedClose;
		//Beep1 = BeepClose;
		KeyStatus = KeyRelease ;
	}	
 }