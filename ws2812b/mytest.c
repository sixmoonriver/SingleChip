#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char
sbit Send_Dat=P1^0;               //数据输出，接IN脚
sbit Key=P3^2;                      //按键等待
sbit Send_Dat1=P1^2;   //中断状态灯
uchar RGB_BUF[24];
void delay();
void delays();
void init();
uchar Led_Tab[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E};    

uchar send_BUF[24];
struct My24bit
{
	uchar Green_val;
	uchar Red_val;
	uchar Blue_val;
}a,b,c,d,e,f,g,h;


delayreset()
{
int i;
Send_Dat=0;
for(i=0;i<60;i++)
	_nop_();
}

/*写入数据时序*/
void Send_A_bit(uchar VAL)
{
//	for(i=0;i<8;i++)
	//{
	
		if (VAL==1)
       {
              Send_Dat=1;
              _nop_();
              Send_Dat=0; 
       }
       else
       {
             Send_Dat=1;
              Send_Dat=0;           
              _nop_();
       }           
	//} 
}
/* send fram */

void Send_One_Pix(struct My24bit RGB)
{
	int k,j;		
	for(k=0;k<3;k++ ) //发送24个bit，也就是一个LED的控制
		{
			for(j=0;j<8;j++)
			{
				if(k==0)
				{
					Send_A_bit(RGB.Green_val>>j&0x01);
				}
				else if(k==1)
				{
					Send_A_bit(RGB.Red_val>>j&0x01); 
				}
				else if(k==2)
				{
					Send_A_bit(RGB.Blue_val>>j&0x01);;
				}
				
			}
		} 
	
	
/*	int i,j;
	for(i=0;i<8;i--)
	{
//	  send_BUF[i] = RGB.Green_val>>i&0x01;
	  Send_A_bit(RGB.Green_val<<i&0x80);
	}
	for(i=8;i<16;i++)
		{
//		send_BUF[i] = RGB.Red_val>>(i-8)&0x01;
		Send_A_bit(RGB.Red_val<<(i-8)&0x80);
		}
	for(i=16;i<24;i++)
		{
//		send_BUF[i] = RGB.Blue_val>>(i-16)&0x01;
		Send_A_bit(RGB.Blue_val<<(i-16)&0x80);
		}
	for(i=0;i<24;i++)
		{	
			Send_A_bit(send_BUF[i]);
		}*/
}
void Send_Fram(int ledcount,struct My24bit leddata)
{
	int i;
	for(i=0;i<ledcount;i++)
	
	{
		Send_One_Pix(leddata);
	}
}


main()
{
	a.Green_val = 0x10;
	a.Red_val = 0x00;
	a.Blue_val = 0x00;
	b.Green_val = 0x00;
	b.Red_val = 0x00;
	b.Blue_val = 0xff;
	c.Green_val = 0x00;
	c.Red_val = 0x00;
	c.Blue_val = 0xff;
	d.Green_val = 0x00;
	d.Red_val = 0x00;
	d.Blue_val = 0xff;
	e.Green_val = 0x00;
	e.Red_val = 0x00;
	e.Blue_val = 0xff;
	f.Green_val = 0x00;
	f.Red_val = 0x00;
	f.Blue_val = 0xff;
	g.Green_val = 0x00;
	g.Red_val = 0x00;
	g.Blue_val = 0xff;
	h.Green_val = 0x00;
	h.Red_val = 0x00;
	h.Blue_val = 0xff;
	
	// My24bit light[8] = {};
	while(1)
{
	int i,k,j;
	for(i=0;i<6;i++)
{
		int k,j;		
	for(k=0;k<3;k++ ) //发送24个bit，也就是一个LED的控制
		{
			for(j=0;j<8;j++)
			{
				if(k==0)
				{
					Send_A_bit(a.Green_val>>j&0x01);
				}
				else if(k==1)
				{
					Send_A_bit(a.Red_val>>j&0x01); 
				}
				else if(k==2)
				{
					Send_A_bit(a.Blue_val>>j&0x01);;
				}
				
			}
		} 
}

	delayreset();
}
}
