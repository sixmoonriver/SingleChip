# include<REG52.H>
# include "MCP2515.h"
# include "MCP2515.c"
sbit LED_g = P3^4;  			//定义LED指示灯
sbit LED_r = P3^5;
bit flag = 0 ;					//定义位标志
unsigned char TX_DATA[8];		//CAN发送缓冲区
unsigned char RX_DATA[8];		//CAN接收缓冲区
/*****************************************************************************
** 函数名称：delayms(unsigned int num)
** 功能描述：延时，变量num越大，延时越长
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
** 函数名称：void CAN_ISR()
** 功能描述：CAN中断处理函数，响应INT1中断
*****************************************************************************/
void CAN_ISR(void) interrupt 2
{
	unsigned char num1,num2,num3;
	unsigned int num;
	unsigned int i;
	LED_g = ~LED_g;    					//指示灯状态变化
	num1 = CAN_Read(CANINTF);			//读中断标志寄存器，根据中断类型，分别处理
	if(num1 & MERRF)					//报文错误中断
	{
		CAN_Write(CANINTF,num1 & ~MERRF); //清中断标志
	}
	if(num1 & WAKIF)
	{
		CAN_Write(CANINTF,num1 & ~WAKIF); //清中断标志
		CAN_Write(CANCTRL,CAN_Normal_Mode);		//唤醒后，在仅监听模式，须设置进入正常工作模式
		do										//判断是否进入正常工作模式
		{
			num = CAN_Read(CANSTAT);
		}
		while(num != CAN_Normal_Mode);
	}
	if(num1 & ERRIF)							//错误中断
	{
		CAN_Write(CANINTF,num1 & ~ERRIF);		//清中断标志
		Pro_CAN_ERROR(); 						//分别处理各个错误
	}
	if(num1 & TX2IF)							//发送2成功中断
	{
		CAN_Write(CANINTF,num1 & ~TX2IF);		//清中断标志
	}
	if(num1 & TX1IF)							//发送1成功中断
	{
		CAN_Write(CANINTF,num1 & ~TX1IF);		//清中断标志
	}
	if(num1 & TX0IF)							//发送0成功中断
	{
		CAN_Write(CANINTF,num1 & ~TX0IF);		//清中断标志
	}
	if(num1 & RX1IF)							//接收1成功中断
	{
		CAN_Write(CANINTF,num1 & ~RX1IF);		//清中断标志
	}
	if(num0 & RX0IF)							//接收0成功中断
	{
		CAN_Write(CANINTF,num1 & ~RX0IF); 	   //清中断标志
		num2 = CAN_Read(RXB0SIDL);
		num3 = CAN_Read(RXB0DLC);
		num = num3 & 0x0f; 						//求数据长度
		if(num2 & IDE)							//收到扩展帧
		{
			if(num3 & RTR)						//远程帧，则读取标识符，按照此标识符发送要求的数据
			{;}
			else								//数据帧，接收处理数据
			{
				for(i=0;i<num;i++)
				{
					RX_DATA[i] = CAN_Read(RXB0D_BASE + i);
				}
			}
		}
		else
		{
			if(num2 & SRR)						//远程帧，则读取标识符，按照此标识府发送要求的数据
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
** 函数名称：InitSys()
** 功能描述：初始化系统
*****************************************************************************/
void InitSys(void)
{
	IT1 = 0;									
	EX1 = 1;									//外部中断1允许
	EA = 1;										//开放全局中断
}

/*****************************************************************************
** 函数名称：main()
** 功能描述：主函数
*****************************************************************************/
void main(void)
{
	InitSys();									//系统初始化；
	CAN_Init();									//CAN初始化；
	Set_CAN_Baudrate(100);						//设置CAN波特率100Kbit/s
	CAN_Write(CANCTRL,CAN_Normal_Mode);			//进入正常模式
	delayms(100);								//小延时
	LED_g = 0;									//点亮指示灯
	while(1)
	{
		CAN_TX_D_Frame(0,8,&TX_DATA[0]);		//通过CAN发送缓冲区0发送8个字节的数据帧
		delayms(300);							
		LED_r = ~LED_r;							//指示灯取反	
	}

}