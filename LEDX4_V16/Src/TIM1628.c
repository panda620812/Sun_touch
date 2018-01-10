/*****************************

	TM1628

*****************************/

//向TM1628发送8位数据,从低位开始
 void send_8bit(unsigned char dat) 
{ 
  	unsigned char i; 
	for(i=0;i<8;i++) 
   	{ 
		if(dat&0x01)
			DIO1=1; 
	  	else 
	  		DIO1=0; 
	   	CLK1=0; //下降沿输出数据
	   	// _nop();//还需要修改，_nop() 函式只需一個指令週期 us(微秒)，这个需要结合具体芯片   	CLK1=1; 
	   	CLK1=1; //下降沿输出数据

    	dat=dat>>1; 
	} 
}
//向TM1628发送16位数据,从低位开始
 void send_16bit(unsigned short dat) 
{ 
  	unsigned char i; 
	// unsigned char value ;
	// value = dat;
	// send_8bit(value);
	// value = dat<<8;
	// send_8bit(value);
	
	 for(i=0;i<16;i++) 
   	 { 
		if(dat&0x01)
			DIO1=1; 
	  	else 
	  		DIO1=0; 
	   	CLK1=0; //下降沿输出数据
	   	CLK1=1; //下降沿输出数据
    	dat=dat>>1; 
	 } 
}
//向TM1628发送命令 
void command(unsigned char com) 
{ 
	STB1 = 1; //为低后第一个字节为命令
	STB1 = 0; 
	send_8bit(com); 
}
// command(0x8F);      //显示控制命令，打开显示并设置为最亮 
// command(0x88);      //显示控制命令，打开显示并设置为最暗  
// 显示初始化清除所有
void displayClear(unsigned short value) 
{ 
  	unsigned char i; 
  	command(0x03);      //设置显示模式，7位10段模式  //	2 6位11段 --	//待修改
  	command(0x40);      //设置数据命令,采用地址自动加1模式 	//
  	command(0xc0);      //设置显示地址，从C0H开始 			//	
  	for(i=0;i<10;i++)    //发送显示数据 
  	{ 
		send_16bit(value);     //从C0H
	} 
	command(0x8F);          //
	STB1=1; 
}
//设置地址和显示内容---数字  status 显示的标记 eg: C c PV Heat 等
void display16(unsigned char adress,unsigned char NUM) 
{ 

	command(0x03);      	//设置显示模式，7位10段模式  //	2 6位11段 --	//待修改
  	command(0x40);      	//设置数据命令,采用地址自动加1模式 	//
  	command(adress);      	//设置显示地址，从C0H开始 			//	
  	
	switch ( adress)
	{
		case 0xc0 :
			send_16bit(CODE[NUM] + BarDisplayNum1 );  			
			// send_16bit(CODE[NUM]);  
			send_16bit(CODE[NUM] + BarDisplayNum2);  		////加上C加上c	
		break;
		case 0xc4:
			send_16bit(CODE[NUM] + BarDisplayNum3);  
			send_16bit(CODE[NUM]+ C_Display);  ////加上C加上c		
		break;		
		case 0xc8:
			send_16bit(CODE[NUM] + C8Value + C8Value2); 
		break;			
		case 0xca:
			send_16bit(CODE[NUM] + BarDisplayNum4 + CaValue); 
		break;		
		default:
			send_16bit(0x0040);  
		break;
	}
}
//单个字符显示 
void displayTwst(unsigned char adress,unsigned short test) 
{ 
  	command(0x03);      	//设置显示模式，7位10段模式  //	2 6位11段 --	//待修改
  	command(0x40);      	//设置数据命令,采用地址自动加1模式 	//
  	command(adress);      	//设置显示地址	
	send_16bit(test);  		//
	command(0x8F);          //
	STB1=1; 
} 