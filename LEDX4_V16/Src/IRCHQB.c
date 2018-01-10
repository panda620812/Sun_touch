/*****************************
    红外遥控
*****************************/
	//1us 		GCC_DELAY(2) 
 	//1ms 		GCC_DELAY(2000)
 	//2.272ms   GCC_DELAY(4544)
//
unsigned char BOOT_REPEATING_CODE_Judge() 
{ 
    bit TEMP_Flag = 1; 
    while((0 == IR_Out)&&(IRCount<10000))    // 等待高电平避开9毫秒低电平引导脉冲 
 	{
		GCC_CLRWDT();
		IRCount++; 
	}
	
	//GCC_DELAY()  0 <= n < 263690 一个指令周期相当于四个系统时钟周期
 	//8 M 0.000000125 * 4 = 0.0000005  --->0.5us
 	//1us 		GCC_DELAY(2) 
 	//1ms 		GCC_DELAY(2000)
 	//2.272ms   GCC_DELAY(4544)
 	Delay2272us;
    if( IR_Out == 0 ) 
    { 
        TEMP_Flag = 1;      // 是连发码 
    } 
    else 
    { 
        TEMP_Flag = 0;      // 不是连发码，而是引导码 
    } 
    return TEMP_Flag; 
}
unsigned char H_L_LEVEL_Judge()  //单个接收部分
{ 
    while( (IR_Out == 1)&& (IRCount<1000)) 
	{
		GCC_CLRWDT();
		IRCount++; 
	}  // 等待地址码第一位的高电平信号 
	
	IRCount = 0;
   	Delay1150us;  // 测试实际延时约为 
    if ( IR_Out == 1) 
    { 
        return 1; 
    } 
    else 
    { 
        return 0; 
    } 
}
unsigned char START_Judge() 
{ 
    unsigned char TEMP_Flag = 0;  //？？？
    unsigned char i = 0; 
    //在正常无遥控信号时，一体化红外接收头输出是高电平，程序一直在循环。 
    //while ( IR_Out == 1) GCC_CLRWDT();    ; 
    //重复10次，目的是检测在6876~8352微秒内如果出现高电平就退出解码程序 
    GCC_CLRWDT();
 	if(1 != IR_Out)
 	{
 		TEMP_Flag = 1;
	    for(i =0;i <8; i++) 
	    { 
	        //DELAY_Us(800);      // 测试实际延时约为764~928us 
			Delay800us;
	        if ( IR_Out == 1 ) 
	        { 
	            TEMP_Flag = 0; 
	            break; 
	        } 
	    }  	
    }
    return TEMP_Flag; 
}
void DataSave(void)
{
    unsigned char i;
	for(i =0;i <4; i++) 
	{                
		Datachange._bits.b7 = H_L_LEVEL_Judge(); 
		Datachange._bits.b6 = H_L_LEVEL_Judge(); 
		Datachange._bits.b5 = H_L_LEVEL_Judge(); 
		Datachange._bits.b4 = H_L_LEVEL_Judge(); 
		Datachange._bits.b3 = H_L_LEVEL_Judge(); 
		Datachange._bits.b2 = H_L_LEVEL_Judge(); 
		Datachange._bits.b1 = H_L_LEVEL_Judge(); 
		Datachange._bits.b0 = H_L_LEVEL_Judge();                              
		_datasave[i] =  Datachange.data; 
	} 
	//功能处理
}
// 红外功能处理
void IR_FUN(void)
{
  	GCC_CLRWDT();     	
	StartFlag = START_Judge();
	if(1 == StartFlag)
	{
		BOOT_REPEATING_CODE_Flag = BOOT_REPEATING_CODE_Judge(); 			
	}
	if (StartFlag && !BOOT_REPEATING_CODE_Flag )  
	{
		DataSave();
		KeyCountOpenflag = 1;
		switch(_datasave[2])
		{
		 	case 0x40://UP
		 		KeyUpProcess();
		 	break;
		 	case 0x10://Down
		 		KeyDownProcess();
		 	break;		 	
		 	case 0x20://Open
		 		KeySwitchProcess()	;
		 	break;		 	
		 	// case 0x60://Set
		 		
		 	// break;		 	
		 	default : 
		 		//_pd6 =~_pd6;
		 	break;			
		}
	} 
}