# include<REG52.H>
# include "MCP2515.h"
# include "MCP2515.c"
sbit LED_g = P3^4;  			//����LEDָʾ��
sbit LED_r = P3^5;
bit flag = 0 ;					//����λ��־
unsigned char TX_DATA[8];		//CAN���ͻ�����
unsigned char RX_DATA[8];		//CAN���ջ�����
/*****************************************************************************
** �������ƣ�delayms(unsigned int num)
** ������������ʱ������numԽ����ʱԽ��
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
** �������ƣ�void CAN_ISR()
** ����������CAN�жϴ���������ӦINT1�ж�
*****************************************************************************/
void CAN_ISR(void) interrupt 2
{
	unsigned char num1,num2,num3;
	unsigned int num;
	unsigned int i;
	LED_g = ~LED_g;    					//ָʾ��״̬�仯
	num1 = CAN_Read(CANINTF);			//���жϱ�־�Ĵ����������ж����ͣ��ֱ���
	if(num1 & MERRF)					//���Ĵ����ж�
	{
		CAN_Write(CANINTF,num1 & ~MERRF); //���жϱ�־
	}
	if(num1 & WAKIF)
	{
		CAN_Write(CANINTF,num1 & ~WAKIF); //���жϱ�־
		CAN_Write(CANCTRL,CAN_Normal_Mode);		//���Ѻ��ڽ�����ģʽ�������ý�����������ģʽ
		do										//�ж��Ƿ������������ģʽ
		{
			num = CAN_Read(CANSTAT);
		}
		while(num != CAN_Normal_Mode);
	}
	if(num1 & ERRIF)							//�����ж�
	{
		CAN_Write(CANINTF,num1 & ~ERRIF);		//���жϱ�־
		Pro_CAN_ERROR(); 						//�ֱ����������
	}
	if(num1 & TX2IF)							//����2�ɹ��ж�
	{
		CAN_Write(CANINTF,num1 & ~TX2IF);		//���жϱ�־
	}
	if(num1 & TX1IF)							//����1�ɹ��ж�
	{
		CAN_Write(CANINTF,num1 & ~TX1IF);		//���жϱ�־
	}
	if(num1 & TX0IF)							//����0�ɹ��ж�
	{
		CAN_Write(CANINTF,num1 & ~TX0IF);		//���жϱ�־
	}
	if(num1 & RX1IF)							//����1�ɹ��ж�
	{
		CAN_Write(CANINTF,num1 & ~RX1IF);		//���жϱ�־
	}
	if(num0 & RX0IF)							//����0�ɹ��ж�
	{
		CAN_Write(CANINTF,num1 & ~RX0IF); 	   //���жϱ�־
		num2 = CAN_Read(RXB0SIDL);
		num3 = CAN_Read(RXB0DLC);
		num = num3 & 0x0f; 						//�����ݳ���
		if(num2 & IDE)							//�յ���չ֡
		{
			if(num3 & RTR)						//Զ��֡�����ȡ��ʶ�������մ˱�ʶ������Ҫ�������
			{;}
			else								//����֡�����մ�������
			{
				for(i=0;i<num;i++)
				{
					RX_DATA[i] = CAN_Read(RXB0D_BASE + i);
				}
			}
		}
		else
		{
			if(num2 & SRR)						//Զ��֡�����ȡ��ʶ�������մ˱�ʶ������Ҫ�������
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
** �������ƣ�InitSys()
** ������������ʼ��ϵͳ
*****************************************************************************/
void InitSys(void)
{
	IT1 = 0;									
	EX1 = 1;									//�ⲿ�ж�1����
	EA = 1;										//����ȫ���ж�
}

/*****************************************************************************
** �������ƣ�main()
** ����������������
*****************************************************************************/
void main(void)
{
	InitSys();									//ϵͳ��ʼ����
	CAN_Init();									//CAN��ʼ����
	Set_CAN_Baudrate(100);						//����CAN������100Kbit/s
	CAN_Write(CANCTRL,CAN_Normal_Mode);			//��������ģʽ
	delayms(100);								//С��ʱ
	LED_g = 0;									//����ָʾ��
	while(1)
	{
		CAN_TX_D_Frame(0,8,&TX_DATA[0]);		//ͨ��CAN���ͻ�����0����8���ֽڵ�����֡
		delayms(300);							
		LED_r = ~LED_r;							//ָʾ��ȡ��	
	}

}