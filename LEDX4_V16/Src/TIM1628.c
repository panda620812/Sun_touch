/*****************************

	TM1628

*****************************/

//��TM1628����8λ����,�ӵ�λ��ʼ
 void send_8bit(unsigned char dat) 
{ 
  	unsigned char i; 
	for(i=0;i<8;i++) 
   	{ 
		if(dat&0x01)
			DIO1=1; 
	  	else 
	  		DIO1=0; 
	   	CLK1=0; //�½����������
	   	// _nop();//����Ҫ�޸ģ�_nop() ��ʽֻ��һ��ָ���L�� us(΢��)�������Ҫ��Ͼ���оƬ   	CLK1=1; 
	   	CLK1=1; //�½����������

    	dat=dat>>1; 
	} 
}
//��TM1628����16λ����,�ӵ�λ��ʼ
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
	   	CLK1=0; //�½����������
	   	CLK1=1; //�½����������
    	dat=dat>>1; 
	 } 
}
//��TM1628�������� 
void command(unsigned char com) 
{ 
	STB1 = 1; //Ϊ�ͺ��һ���ֽ�Ϊ����
	STB1 = 0; 
	send_8bit(com); 
}
// command(0x8F);      //��ʾ�����������ʾ������Ϊ���� 
// command(0x88);      //��ʾ�����������ʾ������Ϊ�  
// ��ʾ��ʼ���������
void displayClear(unsigned short value) 
{ 
  	unsigned char i; 
  	command(0x03);      //������ʾģʽ��7λ10��ģʽ  //	2 6λ11�� --	//���޸�
  	command(0x40);      //������������,���õ�ַ�Զ���1ģʽ 	//
  	command(0xc0);      //������ʾ��ַ����C0H��ʼ 			//	
  	for(i=0;i<10;i++)    //������ʾ���� 
  	{ 
		send_16bit(value);     //��C0H
	} 
	command(0x8F);          //
	STB1=1; 
}
//���õ�ַ����ʾ����---����  status ��ʾ�ı�� eg: C c PV Heat ��
void display16(unsigned char adress,unsigned char NUM) 
{ 

	command(0x03);      	//������ʾģʽ��7λ10��ģʽ  //	2 6λ11�� --	//���޸�
  	command(0x40);      	//������������,���õ�ַ�Զ���1ģʽ 	//
  	command(adress);      	//������ʾ��ַ����C0H��ʼ 			//	
  	
	switch ( adress)
	{
		case 0xc0 :
			send_16bit(CODE[NUM] + BarDisplayNum1 );  			
			// send_16bit(CODE[NUM]);  
			send_16bit(CODE[NUM] + BarDisplayNum2);  		////����C����c	
		break;
		case 0xc4:
			send_16bit(CODE[NUM] + BarDisplayNum3);  
			send_16bit(CODE[NUM]+ C_Display);  ////����C����c		
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
//�����ַ���ʾ 
void displayTwst(unsigned char adress,unsigned short test) 
{ 
  	command(0x03);      	//������ʾģʽ��7λ10��ģʽ  //	2 6λ11�� --	//���޸�
  	command(0x40);      	//������������,���õ�ַ�Զ���1ģʽ 	//
  	command(adress);      	//������ʾ��ַ	
	send_16bit(test);  		//
	command(0x8F);          //
	STB1=1; 
} 