/*****************************
    ����ң��
*****************************/
	//1us 		GCC_DELAY(2) 
 	//1ms 		GCC_DELAY(2000)
 	//2.272ms   GCC_DELAY(4544)
//
unsigned char BOOT_REPEATING_CODE_Judge() 
{ 
    bit TEMP_Flag = 1; 
    while((0 == IR_Out)&&(IRCount<10000))    // �ȴ��ߵ�ƽ�ܿ�9����͵�ƽ�������� 
 	{
		GCC_CLRWDT();
		IRCount++; 
	}
	
	//GCC_DELAY()  0 <= n < 263690 һ��ָ�������൱���ĸ�ϵͳʱ������
 	//8 M 0.000000125 * 4 = 0.0000005  --->0.5us
 	//1us 		GCC_DELAY(2) 
 	//1ms 		GCC_DELAY(2000)
 	//2.272ms   GCC_DELAY(4544)
 	Delay2272us;
    if( IR_Out == 0 ) 
    { 
        TEMP_Flag = 1;      // �������� 
    } 
    else 
    { 
        TEMP_Flag = 0;      // ���������룬���������� 
    } 
    return TEMP_Flag; 
}
unsigned char H_L_LEVEL_Judge()  //�������ղ���
{ 
    while( (IR_Out == 1)&& (IRCount<1000)) 
	{
		GCC_CLRWDT();
		IRCount++; 
	}  // �ȴ���ַ���һλ�ĸߵ�ƽ�ź� 
	
	IRCount = 0;
   	Delay1150us;  // ����ʵ����ʱԼΪ 
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
    unsigned char TEMP_Flag = 0;  //������
    unsigned char i = 0; 
    //��������ң���ź�ʱ��һ�廯�������ͷ����Ǹߵ�ƽ������һֱ��ѭ���� 
    //while ( IR_Out == 1) GCC_CLRWDT();    ; 
    //�ظ�10�Σ�Ŀ���Ǽ����6876~8352΢����������ָߵ�ƽ���˳�������� 
    GCC_CLRWDT();
 	if(1 != IR_Out)
 	{
 		TEMP_Flag = 1;
	    for(i =0;i <8; i++) 
	    { 
	        //DELAY_Us(800);      // ����ʵ����ʱԼΪ764~928us 
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
	//���ܴ���
}
// ���⹦�ܴ���
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