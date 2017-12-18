#include <REG52.H>
#include "MCP2515.h"
#include <intrins.h>
/*****************************************************************************
						定义I/O口，用于模拟SPI总线
*****************************************************************************/
sbit CAN_SCK 	= P1^7;
sbit CAN_MISO	= P1^6;
sbit CAN_MOSI	= P1^5;
sbit CAN_CS		= P1^3;
sbit CAN_RST	= P1^4;
/******************************函数声明***************************************/
void 				Set_CAN_Baudrate(unsigned int baudrate); 		//设置CAN的通信波特率
void 				CAN_Init(void);								//CAN的初始化
void 				CAN_Write(unsigned char address,unsigned char num); //向寄存器地址写入数据
unsigned char 		CAN_Read(unsigned char address);		//从寄存器地址读取数值
void 				ProCAN_ERROR(void);							//CAN总线错误
static void 		SPI_Write(unsigned char num);				//SPI写函数
static unsigned char 	SPI_Read(void);							//SPI读函数
/*****************************************************************************
** 函数名称：CAN_Init()
** 功能描述：CAN初始化，设置波特率，验收滤波器、屏蔽滤波器、中断、发送描述符、引脚输出配置等
*****************************************************************************/
void CAN_Init(void)
{
	unsigned char num = 0 ; 						//定义局部变量
	CAN_RST	=	1;
	CAN_SCK	=	1;
	CAN_CS	=	1;
	CAN_MISO	=	1;
	CAN_MOSI	=	1;
	CAN_CS	=	0;	 								//选中MCP2515
	SPI_Write(CAN_I_RESET);							//复位，进入配置模式，以便配置寄存器
	CAN_CS	=	1;
	do
	{
		num	=	CAN_Read(CANSTAT) & CAN_Config_Mode;
	}
	while(num != CAN_Config_mode);					//判断是否进入配置模式
	CAN_Write(CNF1,0x09); 							//配置寄存器1，默认CAN波特率为100Kbit/s
	CAN_Write(CNF2,0xa1);							//配置寄存器2，位时间为12TQ，同步段---1TQ，
													//传播段----2TQ，PS1 = 5TQ，PS2 = 4TQ
	CAN_Write(CNF3,0x43);							//配置寄存器3，唤醒滤波器使能；
	CAN_Write(TXRTSCTRL,0x00);						//TXnRST作为数据引脚，非发送请求引脚
/****************************配置验收滤波器0***************************************/
	CAN_Write(RXF0SIDH,0x00);						//标准标识符高字节
	CAN_Write(RXF0SIDL,0x00 | EXIDE);						//标准标识符低字节
	CAN_Write(RXF0EID8,0x00);						//扩展标识符高字节
	CAN_Write(RXF0EID0,0x00);						//扩展标识符低字节
/****************************配置验收滤波器1***************************************/
	CAN_Write(RXF1SIDH,0x00);						//标准标识符高字节
	CAN_Write(RXF1SIDL,0x00);						//标准标识符低字节
	CAN_Write(RXF1EID8,0x00);						//扩展标识符高字节
	CAN_Write(RXF1EID0,0x00);						//扩展标识符低字节
/****************************配置验收滤波器2***************************************/
	CAN_Write(RXF2SIDH,0x00);						//标准标识符高字节
	CAN_Write(RXF2SIDL,0x00);						//标准标识符低字节
	CAN_Write(RXF2EID8,0x00);						//扩展标识符高字节
	CAN_Write(RXF2EID0,0x00);						//扩展标识符低字节
/****************************配置验收滤波器3***************************************/
	CAN_Write(RXF3SIDH,0x00);						//标准标识符高字节
	CAN_Write(RXF3SIDL,0x00);						//标准标识符低字节
	CAN_Write(RXF3EID8,0x00);						//扩展标识符高字节
	CAN_Write(RXF3EID0,0x00);						//扩展标识符低字节
/****************************配置验收滤波器4***************************************/
	CAN_Write(RXF4SIDH,0x00);						//标准标识符高字节
	CAN_Write(RXF4SIDL,0x00);						//标准标识符低字节
	CAN_Write(RXF4EID8,0x00);						//扩展标识符高字节
	CAN_Write(RXF4EID0,0x00);						//扩展标识符低字节
/****************************配置验收滤波器5***************************************/
	CAN_Write(RXF5SIDH,0x00);						//标准标识符高字节
	CAN_Write(RXF5SIDL,0x00);						//标准标识符低字节
	CAN_Write(RXF5EID8,0x00);						//扩展标识符高字节
	CAN_Write(RXF5EID0,0x00);						//扩展标识符低字节
/****************************配置验收屏蔽滤波器0***************************************/
	CAN_Write(RXM0SIDH,0x00);					
	CAN_Write(RXM0SIDL,0x00);						
	CAN_Write(RXM0EID8,0x00);						
	CAN_Write(RXM0EID0,0x00);						
/****************************配置验收屏蔽滤波器1***************************************/
	CAN_Write(RXM1SIDH,0x00);					
	CAN_Write(RXM1SIDL,0x00);						
	CAN_Write(RXM1EID8,0x00);						
	CAN_Write(RXM1EID0,0x00);
	
	CAN_Write(CANCTRL,CAN_Normal_Mode);				//进入正常模式
	do{
		num = CAN_Read(CANSTAT)& CAN_Normal_Mode;
	}	
	while(num != CAN_Normal_Mode);                 //判断是否进入正常工作模式
	CAN_Write(BFPCTRL,0x00);						//RXnRST禁止输出
	CAN_Write(CANINTE,RX0IE);						//中断容许
/****************************配置发送缓冲区0，发送标准数据帧到ID：0x000的CAN节点***************************************/
	CAN_Write(TXB0SIDH,0x00);						//标准标识符高字节
	CAN_Write(TXB0SIDL,0x00);						//标准标识符低字节
	CAN_Write(TXB0EID8,0x00);						//扩展标识符高字节
	CAN_Write(TXB0EID0,0x00);						//扩展标识符低字节
/****************************配置发送缓冲区1***************************************/
	CAN_Write(TXB1SIDH,0x00);						//标准标识符高字节
	CAN_Write(TXB1SIDL,0x00);						//标准标识符低字节
	CAN_Write(TXB1EID8,0x00);						//扩展标识符高字节
	CAN_Write(TXB1EID0,0x00);						//扩展标识符低字节
/****************************配置发送缓冲区2***************************************/
	CAN_Write(TXB2SIDH,0x00);						//标准标识符高字节
	CAN_Write(TXB2SIDL,0x00);						//标准标识符低字节
	CAN_Write(TXB2EID8,0x00);						//扩展标识符高字节
	CAN_Write(TXB2EID0,0x00);						//扩展标识符低字节
	CAN_Write(RXB0CTRL,0x00);						//输入缓冲器0控制寄存器，接收所有符合滤波条件的报文，
													//滚存禁止，使难验收滤波寄存器0
	CAN_Write(RXB1CTRL,0x00);						//输入缓冲器0控制寄存器，接收所有符合滤波条件的报文	
/**********************************************************************************/
}
/*****************************************************************************
** 函数名称：Rro_CAN_ERROR()
** 功能描述：CAN总线错误处理
*****************************************************************************/
void Pro_CAN_ERROR(void)
{
	unsigned char num;
	num = CAN_Read(EFLG);  							//读错误标志寄存器，判断错误类型
	if(num & EWARN)									//错误警告寄存器，当TEC或者REC大于等于96时置1
	{
		CAN_Write(TEC,0);
		CAN_Write(RED,0); 
	}
	if(num & RXWAR)									//当REC大于等于96时置1
	{;   }
	if(num & TXWAR)						  			//当TEC大于等于96时置1	
	{;   }
	if(num & RXEP) 									//当REC大于等于128时置1
	{;   }
	if(num & TXEP)									//当TEC大于等于128时置1
	{;   }
	if(num & TXB0)									//当TEC大于等于255时置1
	{;   }
	if(num & RX0OVR) 								//接收缓冲区0溢出
	{
		;  				//根据实际情况处理，一种处理方法是发送远程帧，请求数据重新发送
	}
	if(num & RX1OVR) 								//接收缓冲区1溢出
	{;   }
}
/*****************************************************************************
** 函数名称：Set_CAN_Baudrate(unsigned int baudrate)
** 功能描述：设置CAN总线波特率
** 备注 晶振 24Mhz
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
	CAN_Write(CANCTRL,CAN_Config_Mode); 			//进入配置模式
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
** 函数名称：CAN_Read()
** 功能描述：CAN读函数
** 返回值：  读取地址的数据内容
*****************************************************************************/
unsigned char CAN_Read(unsigned char address) reentrant
{
	unsigned char num;
	CAN_CS = 0;			  				//选中MCP2515
	SPI_Write(CAN_I_READ);				//发送读命令
	SPI_Write(address);					//读取的地址
	num = SPI_Read();					//读取目的地址的内容
	CAN_CS = 1;							//退出MCP2515
	return(num); 						//返回读取的数据
}
/*****************************************************************************
** 函数名称：CAN_Write()
** 功能描述：CAN写函数
*****************************************************************************/
void CAN_Write(unsigned char address,unsigned char num) reentrant
{
	CAN_CS = 0;
	SPI_Write(CAN_I_WRITE);				//发送写命令
	SPI_Write(address);					//要写入的地址
	SPI_Write(num);						//要写入的内容
	CAN_CS = 1;
}

/*****************************************************************************
** 函数名称：
void CAN_TX_D_Frame(unsigned char buffer_num,unsigned char data_num,unsigned char * Ptr)
** 功能描述：CAN发送数据信息帧
** 参数说明：buffer_num 发送缓冲器编号，data_num 数据量，* Ptr待发送数据指针
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
		switch(buffer_num)					  		//判断发送缓冲器编号
		{
			case 0:
				CAN_Write(TXB0DLC,data_num);  		//数据量；
				for(i = 0; i<data_num;i++)
				{
					CAN_Write(TXB0D_BASE + i,*(Ptr + i)); 	//写入数据	
				}
				CAN_Write(TXB0CTRL,TXREQ | 0x03); 			//最高优先级，请求发送数据
				break;
			case 1:
				CAN_Write(TXB1DLC,data_num);				//数据量
				for(i = 0; i<data_num;i++)
				{
					CAN_Write(TXB1D_BASE + i,*(Ptr + i)); 	//写入数据	
				}
				CAN_Write(TXB1CTRL,TXREQ | 0x03); 			//最高优先级，请求发送数据
				break;
			case 2:
				CAN_Write(TXB2DLC,data_num);				//数据量
				for(i = 0; i<data_num;i++)
				{
					CAN_Write(TXB2D_BASE + i,*(Ptr + i)); 	//写入数据	
				}
				CAN_Write(TXB2CTRL,TXREQ | 0x03); 			//最高优先级，请求发送数据
				break;
			default:
				break;
		}
	}
}
/*****************************************************************************
** 函数名称：void CAN_TX_R_Frame(unsigned char buffer_num)
** 功能描述：CAN发送远程信息帧
** 参数说明：buffer_num 发送缓冲器编号
*****************************************************************************/
void CAN_TX_R_Frame(unsigned char buffer_num)
{
	switch(buffer_num)
	{
		case 0:
			CAN_Write(TXB0DLC,RTR);	  					//远程帧
			CAN_Write(TXB0CTRL,TXREQ | 0x03);			//最高优先级，请求发送数据
			break;
		case 1:
			CAN_Write(TXB1DLC,RTR);	  					//远程帧
			CAN_Write(TXB1CTRL,TXREQ | 0x03);			//最高优先级，请求发送数据
			break;
		case 2:
			CAN_Write(TXB2DLC,RTR);	  					//远程帧
			CAN_Write(TXB2CTRL,TXREQ | 0x03);			//最高优先级，请求发送数据
			break;
		default:
			break;
	}
}

/*****************************************************************************
** 函数名称：SPI_Write()
** 功能描述：SPI写函数
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
** 函数名称：SPI_Read()
** 功能描述：SPI读函数
** 静态函数，只有在其所在的模块程序中才效，有
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