#include<reg52.h>
#include<intrins.h>
 #define uchar unsigned char
 #define uint unsigned int
 
 uchar code CCW[8]={0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09};   //逆时钟旋转相序表
 uchar code CW[8]={0x09,0x01,0x03,0x02,0x06,0x04,0x0c,0x08};    //正时钟旋转相序表


 sbit S4=P3^2;  //反转按键
 sbit S3=P3^3;  //正转按键
 sbit S2=P3^4;  //停止按键
 sbit FMQ=P3^6;  //  蜂鸣器

 
void delaynms(uint aa)
{
  uchar bb;
  while(aa--)
  {
   for(bb=0;bb<115;bb++)     //1ms基准延时程序
   {
    ;
   }
  }
 
}

void delay500us(void)
{
  int j;
  for(j=0;j<57;j++)
  {
   ;
  }
}

void beep(void)
{
  uchar t;
  for(t=0;t<100;t++)
  {
   delay500us();
 FMQ=!FMQ;   //产生脉冲
  }
  FMQ=1;    //关闭蜂鸣器
}


void motor_ccw(void)
{
  uchar i,j;
  for(j=0;j<8;j++)                 //电机旋转一周，不是外面所看到的一周，是里面的传动轮转了一周
  {
   if(S2==0)
 {
   break;   //如果S2按下，退出此循环
 }
 for(i=0;i<8;i++)  //旋转45度
 {
   P0=CCW[i];
   delaynms(5);   //调节转速
 }
  }
}


void motor_cw(void)
{
  uchar i,j;
  for(j=0;j<8;j++)
  {
   if(S2==0)
 {
   break;   //如果S2按下，退出此循环
 }
 for(i=0;i<8;i++)  //旋转45度
 {
   P0=CW[i];
   delaynms(5);   //调节转速
 }
  }
}



void main(void)
{
 uchar r;
 uchar N=64;          //因为步进电机是减速步进电机，减速比的1/64 ，
       //所以N=64时，步进电机主轴转一圈
 while(1)
 {
   if(S4==0)
   {
		beep();
		while(1)
		{
			int laststate=0;
			for(r=0;r<N;r++)
			{
				motor_ccw();  //电机逆转
				if(S2==0)
				{
					beep();
					laststate=1;
					break;
				}
			}
			if(laststate)
				break;

		}
	}
   else if(S3==0)
   {
		beep();   
		while(1)
		{
			int laststate=0;
			for(r=0;r<N;r++)
			{
				motor_cw();    //电机反转
			}
			if(S2==0)
				{
					beep();
					laststate=1;
					break;
				}
			if(laststate)
				break;
		
		}
   }
   else
		 P0=0xf0;    //电机停止
 }
}      