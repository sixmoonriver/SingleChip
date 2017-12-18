#include <REG52.H>
#include "MCP2515.h"
#include <intrins.h>
/*****************************************************************************
						¶¨ÒåI/O¿Ú£¬ÓÃÓÚÄ£ÄâSPI×ÜÏß
*****************************************************************************/
sbit CAN_SCK 	= P1^7;
sbit CAN_MISO	= P1^6;
sbit CAN_MOSI	= P1^5;
sbit CAN_CS		= P1^3;
sbit CAN_RST	= P1^4;
/******************************º¯ÊýÉùÃ÷***************************************/
void 				Set_CAN_Baudrate(unsigned int baudrate); 		//ÉèÖÃCANµÄÍ¨ÐÅ²¨ÌØÂÊ
void 				CAN_Init(void);								//CANµÄ³õÊ¼»¯
void 				CAN_Write(unsigned char address,unsigned char num); //Ïò¼Ä´æÆ÷µØÖ·Ð´ÈëÊý¾Ý
unsigned char 		CAN_Read(unsigned char address);		//´Ó¼Ä´æÆ÷µØÖ·¶ÁÈ¡ÊýÖµ
void 				ProCAN_ERROR(void);							//CAN×ÜÏß´íÎó
static void 		SPI_Write(unsigned char num);				//SPIÐ´º¯Êý
static unsigned char 	SPI_Read(void);							//SPI¶Áº¯Êý
/*****************************************************************************
** º¯ÊýÃû³Æ£ºCAN_Init()
** ¹¦ÄÜÃèÊö£ºCAN³õÊ¼»¯£¬ÉèÖÃ²¨ÌØÂÊ£¬ÑéÊÕÂË²¨Æ÷¡¢ÆÁ±ÎÂË²¨Æ÷¡¢ÖÐ¶Ï¡¢·¢ËÍÃèÊö·û¡¢Òý½ÅÊä³öÅäÖÃµÈ
*****************************************************************************/
void CAN_Init(void)
{
	unsigned char num = 0 ; 						//¶¨Òå¾Ö²¿±äÁ¿
	CAN_RST	=	1;
	CAN_SCK	=	1;
	CAN_CS	=	1;
	CAN_MISO	=	1;
	CAN_MOSI	=	1;
	CAN_CS	=	0;	 								//Ñ¡ÖÐMCP2515
	SPI_Write(CAN_I_RESET);							//¸´Î»£¬½øÈëÅäÖÃÄ£Ê½£¬ÒÔ±ãÅäÖÃ¼Ä´æÆ÷
	CAN_CS	=	1;
	do
	{
		num	=	CAN_Read(CANSTAT) & CAN_Config_Mode;
	}
	while(num != CAN_Config_mode);					//ÅÐ¶ÏÊÇ·ñ½øÈëÅäÖÃÄ£Ê½
	CAN_Write(CNF1,0x09); 							//ÅäÖÃ¼Ä´æÆ÷1£¬Ä¬ÈÏCAN²¨ÌØÂÊÎª100Kbit/s
	CAN_Write(CNF2,0xa1);							//ÅäÖÃ¼Ä´æÆ÷2£¬Î»Ê±¼äÎª12TQ£¬Í¬²½¶Î---1TQ£¬
													//´«²¥¶Î----2TQ£¬PS1 = 5TQ£¬PS2 = 4TQ
	CAN_Write(CNF3,0x43);							//ÅäÖÃ¼Ä´æÆ÷3£¬»½ÐÑÂË²¨Æ÷Ê¹ÄÜ£»
	CAN_Write(TXRTSCTRL,0x00);						//TXnRST×÷ÎªÊý¾ÝÒý½Å£¬·Ç·¢ËÍÇëÇóÒý½Å
/****************************ÅäÖÃÑéÊÕÂË²¨Æ÷0***************************************/
	CAN_Write(RXF0SIDH,0x00);						//±ê×¼±êÊ¶·û¸ß×Ö½Ú
	CAN_Write(RXF0SIDL,0x00 | EXIDE);						//±ê×¼±êÊ¶·ûµÍ×Ö½Ú
	CAN_Write(RXF0EID8,0x00);						//À©Õ¹±êÊ¶·û¸ß×Ö½Ú
	CAN_Write(RXF0EID0,0x00);						//À©Õ¹±êÊ¶·ûµÍ×Ö½Ú
/****************************ÅäÖÃÑéÊÕÂË²¨Æ÷1***************************************/
	CAN_Write(RXF1SIDH,0x00);						//±ê×¼±êÊ¶·û¸ß×Ö½Ú
	CAN_Write(RXF1SIDL,0x00);						//±ê×¼±êÊ¶·ûµÍ×Ö½Ú
	CAN_Write(RXF1EID8,0x00);						//À©Õ¹±êÊ¶·û¸ß×Ö½Ú
	CAN_Write(RXF1EID0,0x00);						//À©Õ¹±êÊ¶·ûµÍ×Ö½Ú
/****************************ÅäÖÃÑéÊÕÂË²¨Æ÷2***************************************/
	CAN_Write(RXF2SIDH,0x00);						//±ê×¼±êÊ¶·û¸ß×Ö½Ú
	CAN_Write(RXF2SIDL,0x00);						//±ê×¼±êÊ¶·ûµÍ×Ö½Ú
	CAN_Write(RXF2EID8,0x00);						//À©Õ¹±êÊ¶·û¸ß×Ö½Ú
	CAN_Write(RXF2EID0,0x00);						//À©Õ¹±êÊ¶·ûµÍ×Ö½Ú
/****************************ÅäÖÃÑéÊÕÂË²¨Æ÷3***************************************/
	CAN_Write(RXF3SIDH,0x00);						//±ê×¼±êÊ¶·û¸ß×Ö½Ú
	CAN_Write(RXF3SIDL,0x00);						//±ê×¼±êÊ¶·ûµÍ×Ö½Ú
	CAN_Write(RXF3EID8,0x00);						//À©Õ¹±êÊ¶·û¸ß×Ö½Ú
	CAN_Write(RXF3EID0,0x00);						//À©Õ¹±êÊ¶·ûµÍ×Ö½Ú
/****************************ÅäÖÃÑéÊÕÂË²¨Æ÷4***************************************/
	CAN_Write(RXF4SIDH,0x00);						//±ê×¼±êÊ¶·û¸ß×Ö½Ú
	CAN_Write(RXF4SIDL,0x00);						//±ê×¼±êÊ¶·ûµÍ×Ö½Ú
	CAN_Write(RXF4EID8,0x00);						//À©Õ¹±êÊ¶·û¸ß×Ö½Ú
	CAN_Write(RXF4EID0,0x00);						//À©Õ¹±êÊ¶·ûµÍ×Ö½Ú
/****************************ÅäÖÃÑéÊÕÂË²¨Æ÷5***************************************/
	CAN_Write(RXF5SIDH,0x00);						//±ê×¼±êÊ¶·û¸ß×Ö½Ú
	CAN_Write(RXF5SIDL,0x00);						//±ê×¼±êÊ¶·ûµÍ×Ö½Ú
	CAN_Write(RXF5EID8,0x00);						//À©Õ¹±êÊ¶·û¸ß×Ö½Ú
	CAN_Write(RXF5EID0,0x00);						//À©Õ¹±êÊ¶·ûµÍ×Ö½Ú
/****************************ÅäÖÃÑéÊÕÆÁ±ÎÂË²¨Æ÷0***************************************/
	CAN_Write(RXM0SIDH,0x00);					
	CAN_Write(RXM0SIDL,0x00);						
	CAN_Write(RXM0EID8,0x00);						
	CAN_Write(RXM0EID0,0x00);						
/****************************ÅäÖÃÑéÊÕÆÁ±ÎÂË²¨Æ÷1***************************************/
	CAN_Write(RXM1SIDH,0x00);					
	CAN_Write(RXM1SIDL,0x00);						
	CAN_Write(RXM1EID8,0x00);						
	CAN_Write(RXM1EID0,0x00);
	
	CAN_Write(CANCTRL,CAN_Normal_Mode);				//½øÈëÕý³£Ä£Ê½
	do{
		num = CAN_Read(CANSTAT)& CAN_Normal_Mode;
	}	
	while(num != CAN_Normal_Mode);                 //ÅÐ¶ÏÊÇ·ñ½øÈëÕý³£¹¤×÷Ä£Ê½
	CAN_Write(BFPCTRL,0x00);						//RXnRST½ûÖ¹Êä³ö
	CAN_Write(CANINTE,RX0IE);						//ÖÐ¶ÏÈÝÐí
/****************************ÅäÖÃ·¢ËÍ»º³åÇø0£¬·¢ËÍ±ê×¼Êý¾ÝÖ¡µ½ID£º0x000µÄCAN½Úµã***************************************/
	CAN_Write(TXB0SIDH,0x00);						//±ê×¼±êÊ¶·û¸ß×Ö½Ú
	CAN_Write(TXB0SIDL,0x00);						//±ê×¼±êÊ¶·ûµÍ×Ö½Ú
	CAN_Write(TXB0EID8,0x00);						//À©Õ¹±êÊ¶·û¸ß×Ö½Ú
	CAN_Write(TXB0EID0,0x00);						//À©Õ¹±êÊ¶·ûµÍ×Ö½Ú
/****************************ÅäÖÃ·¢ËÍ»º³åÇø1***************************************/
	CAN_Write(TXB1SIDH,0x00);						//±ê×¼±êÊ¶·û¸ß×Ö½Ú
	CAN_Write(TXB1SIDL,0x00);						//±ê×¼±êÊ¶·ûµÍ×Ö½Ú
	CAN_Write(TXB1EID8,0x00);						//À©Õ¹±êÊ¶·û¸ß×Ö½Ú
	CAN_Write(TXB1EID0,0x00);						//À©Õ¹±êÊ¶·ûµÍ×Ö½Ú
/****************************ÅäÖÃ·¢ËÍ»º³åÇø2***************************************/
	CAN_Write(TXB2SIDH,0x00);						//±ê×¼±êÊ¶·û¸ß×Ö½Ú
	CAN_Write(TXB2SIDL,0x00);						//±ê×¼±êÊ¶·ûµÍ×Ö½Ú
	CAN_Write(TXB2EID8,0x00);						//À©Õ¹±êÊ¶·û¸ß×Ö½Ú
	CAN_Write(TXB2EID0,0x00);						//À©Õ¹±êÊ¶·ûµÍ×Ö½Ú
	CAN_Write(RXB0CTRL,0x00);						//ÊäÈë»º³åÆ÷0¿ØÖÆ¼Ä´æÆ÷£¬½ÓÊÕËùÓÐ·ûºÏÂË²¨Ìõ¼þµÄ±¨ÎÄ£¬
													//¹ö´æ½ûÖ¹£¬Ê¹ÄÑÑéÊÕÂË²¨¼Ä´æÆ÷0
	CAN_Write(RXB1CTRL,0x00);						//ÊäÈë»º³åÆ÷0¿ØÖÆ¼Ä´æÆ÷£¬½ÓÊÕËùÓÐ·ûºÏÂË²¨Ìõ¼þµÄ±¨ÎÄ	
/**********************************************************************************/
}
/*****************************************************************************
** º¯ÊýÃû³Æ£ºRro_CAN_ERROR()
** ¹¦ÄÜÃèÊö£ºCAN×ÜÏß´íÎó´¦Àí
*****************************************************************************/
void Pro_CAN_ERROR(void)
{
	unsigned char num;
	num = CAN_Read(EFLG);  							//¶Á´íÎó±êÖ¾¼Ä´æÆ÷£¬ÅÐ¶Ï´íÎóÀàÐÍ
	if(num & EWARN)									//´íÎó¾¯¸æ¼Ä´æÆ÷£¬µ±TEC»òÕßREC´óÓÚµÈÓÚ96Ê±ÖÃ1
	{
		CAN_Write(TEC,0);
		CAN_Write(RED,0); 
	}
	if(num & RXWAR)									//µ±REC´óÓÚµÈÓÚ96Ê±ÖÃ1
	{;   }
	if(num & TXWAR)						  			//µ±TEC´óÓÚµÈÓÚ96Ê±ÖÃ1	
	{;   }
	if(num & RXEP) 									//µ±REC´óÓÚµÈÓÚ128Ê±ÖÃ1
	{;   }
	if(num & TXEP)									//µ±TEC´óÓÚµÈÓÚ128Ê±ÖÃ1
	{;   }
	if(num & TXB0)									//µ±TEC´óÓÚµÈÓÚ255Ê±ÖÃ1
	{;   }
	if(num & RX0OVR) 								//½ÓÊÕ»º³åÇø0Òç³ö
	{
		;  				//¸ù¾ÝÊµ¼ÊÇé¿ö´¦Àí£¬Ò»ÖÖ´¦Àí·½·¨ÊÇ·¢ËÍÔ¶³ÌÖ¡£¬ÇëÇóÊý¾ÝÖØÐÂ·¢ËÍ
	}
	if(num & RX1OVR) 								//½ÓÊÕ»º³åÇø1Òç³ö
	{;   }
}
/*****************************************************************************
** º¯ÊýÃû³Æ£ºSet_CAN_Baudrate(unsigned int baudrate)
** ¹¦ÄÜÃèÊö£ºÉèÖÃCAN×ÜÏß²¨ÌØÂÊ
** ±¸×¢ ¾§Õñ 24Mhz
** 			baudrate = [1000,500,250,200,100,50.25,20]K
*****************************************************************************/
void Set_CAN_Baudrate(unsigned int baudrate)
{
	unsigned char BRP;
	unsigned char num;
	switch(baudrate)
	{
		case 1000:		BRP = 0 ; break;
		case 500:		BRP = 1 ; break;
		case 250:		BRP = 3 ; break;
		case 200:		BRP = 4 ; break;
		case 100:		BRP = 9 ; break;
		case 50:		BRP = 19 ; break;
		case 25:		BRP = 39 ; break;
		case 20:		BRP = 49 ; break;
		default:		break;
	}
	CAN_Write(CANCTRL,CAN_Config_Mode); 			//½øÈëÅäÖÃÄ£Ê½
	do
	{
		num = CAN_Read(CANSTAT) & CAN_Config_Mode;
	}
	while(num != CAN_Config_Mode); 
	CAN_Write(CNF1,BRP);
	CAN_Write(CANCTRL,CAN_Normal_Mode);
	do
	{
		num = CAN_Read(CANSTAT) & CAN_Normal_Mode; 
	}
	while(num != CAN_Normal_Mode); 
}
/*****************************************************************************
** º¯ÊýÃû³Æ£ºCAN_Read()
** ¹¦ÄÜÃèÊö£ºCAN¶Áº¯Êý
** ·µ»ØÖµ£º  ¶ÁÈ¡µØÖ·µÄÊý¾ÝÄÚÈÝ
*****************************************************************************/
unsigned char CAN_Read(unsigned char address) reentrant
{
	unsigned char num;
	CAN_CS = 0;			  				//Ñ¡ÖÐMCP2515
	SPI_Write(CAN_I_READ);				//·¢ËÍ¶ÁÃüÁî
	SPI_Write(address);					//¶ÁÈ¡µÄµØÖ·
	num = SPI_Read();					//¶ÁÈ¡Ä¿µÄµØÖ·µÄÄÚÈÝ
	CAN_CS = 1;							//ÍË³öMCP2515
	return(num); 						//·µ»Ø¶ÁÈ¡µÄÊý¾Ý
}
/*****************************************************************************
** º¯ÊýÃû³Æ£ºCAN_Write()
** ¹¦ÄÜÃèÊö£ºCANÐ´º¯Êý
*****************************************************************************/
void CAN_Write(unsigned char address,unsigned char num) reentrant
{
	CAN_CS = 0;
	SPI_Write(CAN_I_WRITE);				//·¢ËÍÐ´ÃüÁî
	SPI_Write(address);					//ÒªÐ´ÈëµÄµØÖ·
	SPI_Write(num);						//ÒªÐ´ÈëµÄÄÚÈÝ
	CAN_CS = 1;
}

/*****************************************************************************
** º¯ÊýÃû³Æ£º
void CAN_TX_D_Frame(unsigned char buffer_num,unsigned char data_num,unsigned char * Ptr)
** ¹¦ÄÜÃèÊö£ºCAN·¢ËÍÊý¾ÝÐÅÏ¢Ö¡
** ²ÎÊýËµÃ÷£ºbuffer_num ·¢ËÍ»º³åÆ÷±àºÅ£¬data_num Êý¾ÝÁ¿£¬* Ptr´ý·¢ËÍÊý¾ÝÖ¸Õë
*****************************************************************************/
void CAN_TX_D_Frame(unsigned char buffer_num,unsigned char data_num,unsigned char *Ptr)
{
	unsigned char i ;
	if(data_num > 8)
	{
		return;
	}
	else
	{
		switch(buffer_num)					  		//ÅÐ¶Ï·¢ËÍ»º³åÆ÷±àºÅ
		{
			case 0:
				CAN_Write(TXB0DLC,data_num);  		//Êý¾ÝÁ¿£»
				for(i = 0; i<data_num;i++)
				{
					CAN_Write(TXB0D_BASE + i,*(Ptr + i)); 	//Ð´ÈëÊý¾Ý	
				}
				CAN_Write(TXB0CTRL,TXREQ | 0x03); 			//×î¸ßÓÅÏÈ¼¶£¬ÇëÇó·¢ËÍÊý¾Ý
				break;
			case 1:
				CAN_Write(TXB1DLC,data_num);				//Êý¾ÝÁ¿
				for(i = 0; i<data_num;i++)
				{
					CAN_Write(TXB1D_BASE + i,*(Ptr + i)); 	//Ð´ÈëÊý¾Ý	
				}
				CAN_Write(TXB1CTRL,TXREQ | 0x03); 			//×î¸ßÓÅÏÈ¼¶£¬ÇëÇó·¢ËÍÊý¾Ý
				break;
			case 2:
				CAN_Write(TXB2DLC,data_num);				//Êý¾ÝÁ¿
				for(i = 0; i<data_num;i++)
				{
					CAN_Write(TXB2D_BASE + i,*(Ptr + i)); 	//Ð´ÈëÊý¾Ý	
				}
				CAN_Write(TXB2CTRL,TXREQ | 0x03); 			//×î¸ßÓÅÏÈ¼¶£¬ÇëÇó·¢ËÍÊý¾Ý
				break;
			default:
				break;
		}
	}
}
/*****************************************************************************
** º¯ÊýÃû³Æ£ºvoid CAN_TX_R_Frame(unsigned char buffer_num)
** ¹¦ÄÜÃèÊö£ºCAN·¢ËÍÔ¶³ÌÐÅÏ¢Ö¡
** ²ÎÊýËµÃ÷£ºbuffer_num ·¢ËÍ»º³åÆ÷±àºÅ
*****************************************************************************/
void CAN_TX_R_Frame(unsigned char buffer_num)
{
	switch(buffer_num)
	{
		case 0:
			CAN_Write(TXB0DLC,RTR);	  					//Ô¶³ÌÖ¡
			CAN_Write(TXB0CTRL,TXREQ | 0x03);			//×î¸ßÓÅÏÈ¼¶£¬ÇëÇó·¢ËÍÊý¾Ý
			break;
		case 1:
			CAN_Write(TXB1DLC,RTR);	  					//Ô¶³ÌÖ¡
			CAN_Write(TXB1CTRL,TXREQ | 0x03);			//×î¸ßÓÅÏÈ¼¶£¬ÇëÇó·¢ËÍÊý¾Ý
			break;
		case 2:
			CAN_Write(TXB2DLC,RTR);	  					//Ô¶³ÌÖ¡
			CAN_Write(TXB2CTRL,TXREQ | 0x03);			//×î¸ßÓÅÏÈ¼¶£¬ÇëÇó·¢ËÍÊý¾Ý
			break;
		default:
			break;
	}
}

/*****************************************************************************
** º¯ÊýÃû³Æ£ºSPI_Write()
** ¹¦ÄÜÃèÊö£ºSPIÐ´º¯Êý
*****************************************************************************/
static void SPI_Write(unsigned char num)
{
	unsigned char i; 
	for(i=0;i<8;i++)
	{
		if(num & 0x80)
		{CAN_MOSI = 1;}
		else
		{CAN_MOSI = 0;}
		CAN_SCK = 0;
		_nop_();
		CAN_SCK = 1	;
		_nop_();
		num = num * 2;
	}
}
/*****************************************************************************
** º¯ÊýÃû³Æ£ºSPI_Read()
** ¹¦ÄÜÃèÊö£ºSPI¶Áº¯Êý
** ¾²Ì¬º¯Êý£¬Ö»ÓÐÔÚÆäËùÔÚµÄÄ£¿é³ÌÐòÖÐ²ÅÐ§£¬ÓÐ
*****************************************************************************/
static unsigned char SPI_Read(void)
{
	unsigned char num = 0,i;
	for(i=0;i<8;i++)
	{
		CAN_SCK = 0;
		_nop_();
		num = num * 2;
		if(CAN_MISO)
		{num |= 0x01;}
		else
		{num &= 0xfe;}
		CAN_SCK = 1;
		_nop_();
	}
	return(num);
}