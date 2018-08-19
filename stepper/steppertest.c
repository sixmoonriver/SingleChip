#include<reg52.h>
#include<intrins.h>
 #define uchar unsigned char
 #define uint unsigned int
 
 uchar code CCW[8]={0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09};   //��ʱ����ת�����
 uchar code CW[8]={0x09,0x01,0x03,0x02,0x06,0x04,0x0c,0x08};    //��ʱ����ת�����


 sbit S4=P3^2;  //��ת����
 sbit S3=P3^3;  //��ת����
 sbit S2=P3^4;  //ֹͣ����
 sbit FMQ=P3^6;  //  ������

 
void delaynms(uint aa)
{
  uchar bb;
  while(aa--)
  {
   for(bb=0;bb<115;bb++)     //1ms��׼��ʱ����
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
 FMQ=!FMQ;   //��������
  }
  FMQ=1;    //�رշ�����
}


void motor_ccw(void)
{
  uchar i,j;
  for(j=0;j<8;j++)                 //�����תһ�ܣ�����������������һ�ܣ�������Ĵ�����ת��һ��
  {
   if(S2==0)
 {
   break;   //���S2���£��˳���ѭ��
 }
 for(i=0;i<8;i++)  //��ת45��
 {
   P0=CCW[i];
   delaynms(5);   //����ת��
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
   break;   //���S2���£��˳���ѭ��
 }
 for(i=0;i<8;i++)  //��ת45��
 {
   P0=CW[i];
   delaynms(5);   //����ת��
 }
  }
}



void main(void)
{
 uchar r;
 uchar N=64;          //��Ϊ��������Ǽ��ٲ�����������ٱȵ�1/64 ��
       //����N=64ʱ�������������תһȦ
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
				motor_ccw();  //�����ת
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
				motor_cw();    //�����ת
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
		 P0=0xf0;    //���ֹͣ
 }
}      