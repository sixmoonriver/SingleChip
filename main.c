# include<REG52.H>
# include "MCP2515.h"
# include "MCP2515.c"
sbit LED_g = P3^4;  			//¶¨ÒåLEDÖ¸Ê¾µÆ
sbit LED_r = P3^5;
bit flag = 0 ;					//¶¨ÒåÎ»±êÖ¾
unsigned char TX_DATA[8];		//CAN·¢ËÍ»º³åÇø
unsigned char RX_DATA[8];		//CAN½ÓÊÕ»º³åÇø
/*****************************************************************************
** º¯ÊýÃû³Æ£ºdelayms(unsigned int num)
** ¹¦ÄÜÃèÊö£ºÑÓÊ±£¬±äÁ¿numÔ½´ó£¬ÑÓÊ±Ô½³¤
*****************************************************************************/
void delayms(unsigned int num)
{
	unsigned int i,j;
	for(i=0;i<num;i++)
	{
		for(j=0;j<619;j++);
	}
}
/*****************************************************************************
** º¯ÊýÃû³Æ£ºvoid CAN_ISR()
** ¹¦ÄÜÃèÊö£ºCANÖÐ¶Ï´¦Àíº¯Êý£¬ÏìÓ¦INT1ÖÐ¶Ï
*****************************************************************************/
void CAN_ISR(void) interrupt 2
{
	unsigned char num1,num2,num3;
	unsigned int num;
	unsigned int i;
	LED_g = ~LED_g;    					//Ö¸Ê¾µÆ×´Ì¬±ä»¯
	num1 = CAN_Read(CANINTF);			//¶ÁÖÐ¶Ï±êÖ¾¼Ä´æÆ÷£¬¸ù¾ÝÖÐ¶ÏÀàÐÍ£¬·Ö±ð´¦Àí
	if(num1 & MERRF)					//±¨ÎÄ´íÎóÖÐ¶Ï
	{
		CAN_Write(CANINTF,num1 & ~MERRF); //ÇåÖÐ¶Ï±êÖ¾
	}
	if(num1 & WAKIF)
	{
		CAN_Write(CANINTF,num1 & ~WAKIF); //ÇåÖÐ¶Ï±êÖ¾
		CAN_Write(CANCTRL,CAN_Normal_Mode);		//»½ÐÑºó£¬ÔÚ½ö¼àÌýÄ£Ê½£¬ÐëÉèÖÃ½øÈëÕý³£¹¤×÷Ä£Ê½
		do										//ÅÐ¶ÏÊÇ·ñ½øÈëÕý³£¹¤×÷Ä£Ê½
		{
			num = CAN_Read(CANSTAT);
		}
		while(num != CAN_Normal_Mode);
	}
	if(num1 & ERRIF)							//´íÎóÖÐ¶Ï
	{
		CAN_Write(CANINTF,num1 & ~ERRIF);		//ÇåÖÐ¶Ï±êÖ¾
		Pro_CAN_ERROR(); 						//·Ö±ð´¦Àí¸÷¸ö´íÎó
	}
	if(num1 & TX2IF)							//·¢ËÍ2³É¹¦ÖÐ¶Ï
	{
		CAN_Write(CANINTF,num1 & ~TX2IF);		//ÇåÖÐ¶Ï±êÖ¾
	}
	if(num1 & TX1IF)							//·¢ËÍ1³É¹¦ÖÐ¶Ï
	{
		CAN_Write(CANINTF,num1 & ~TX1IF);		//ÇåÖÐ¶Ï±êÖ¾
	}
	if(num1 & TX0IF)							//·¢ËÍ0³É¹¦ÖÐ¶Ï
	{
		CAN_Write(CANINTF,num1 & ~TX0IF);		//ÇåÖÐ¶Ï±êÖ¾
	}
	if(num1 & RX1IF)							//½ÓÊÕ1³É¹¦ÖÐ¶Ï
	{
		CAN_Write(CANINTF,num1 & ~RX1IF);		//ÇåÖÐ¶Ï±êÖ¾
	}
	if(num0 & RX0IF)							//½ÓÊÕ0³É¹¦ÖÐ¶Ï
	{
		CAN_Write(CANINTF,num1 & ~RX0IF); 	   //ÇåÖÐ¶Ï±êÖ¾
		num2 = CAN_Read(RXB0SIDL);
		num3 = CAN_Read(RXB0DLC);
		num = num3 & 0x0f; 						//ÇóÊý¾Ý³¤¶È
		if(num2 & IDE)							//ÊÕµ½À©Õ¹Ö¡
		{
			if(num3 & RTR)						//Ô¶³ÌÖ¡£¬Ôò¶ÁÈ¡±êÊ¶·û£¬°´ÕÕ´Ë±êÊ¶·û·¢ËÍÒªÇóµÄÊý¾Ý
			{;}
			else								//Êý¾ÝÖ¡£¬½ÓÊÕ´¦ÀíÊý¾Ý
			{
				for(i=0;i<num;i++)
				{
					RX_DATA[i] = CAN_Read(RXB0D_BASE + i);
				}
			}
		}
		else
		{
			if(num2 & SRR)						//Ô¶³ÌÖ¡£¬Ôò¶ÁÈ¡±êÊ¶·û£¬°´ÕÕ´Ë±êÊ¶¸®·¢ËÍÒªÇóµÄÊý¾Ý
				{;}
			else
				{
					for(i=0;i<num;i++)
						{
							RX_DATA[i] = CAN_Read(RXB0D_BASE + i) ;
						}
				}
		}
	}
	flag = 1;
}
/*****************************************************************************
** º¯ÊýÃû³Æ£ºInitSys()
** ¹¦ÄÜÃèÊö£º³õÊ¼»¯ÏµÍ³
*****************************************************************************/
void InitSys(void)
{
	IT1 = 0;									
	EX1 = 1;									//Íâ²¿ÖÐ¶Ï1ÔÊÐí
	EA = 1;										//¿ª·ÅÈ«¾ÖÖÐ¶Ï
}

/*****************************************************************************
** º¯ÊýÃû³Æ£ºmain()
** ¹¦ÄÜÃèÊö£ºÖ÷º¯Êý
*****************************************************************************/
void main(void)
{
	InitSys();									//ÏµÍ³³õÊ¼»¯£»
	CAN_Init();									//CAN³õÊ¼»¯£»
	Set_CAN_Baudrate(100);						//ÉèÖÃCAN²¨ÌØÂÊ100Kbit/s
	CAN_Write(CANCTRL,CAN_Normal_Mode);			//½øÈëÕý³£Ä£Ê½
	delayms(100);								//Ð¡ÑÓÊ±
	LED_g = 0;									//µãÁÁÖ¸Ê¾µÆ
	while(1)
	{
		CAN_TX_D_Frame(0,8,&TX_DATA[0]);		//Í¨¹ýCAN·¢ËÍ»º³åÇø0·¢ËÍ8¸ö×Ö½ÚµÄÊý¾ÝÖ¡
		delayms(300);							
		LED_r = ~LED_r;							//Ö¸Ê¾µÆÈ¡·´	
	}

}