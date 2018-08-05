
/********************************************************/
/*�� �ߣ�Dyingstraw
/*�޸����ڣ�2015.5.2
/*��    ����V1.0
/*�����ܣ���51��Ƭ������ws2812 RGB�������ʾȫɫ��
/*��        ע��51��Ƭ������24M
/********************************************************/
 
#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char
sbit Send_Dat=P1^0;               //�����������IN��
sbit Key=P3^2;                      //�����ȴ�
sbit Send_Dat1=P1^2;   //�ж�״̬��
uchar RGB_BUF[24];
void delay();
void delays();
void init();
uchar Led_Tab[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E};        
//�洢һ��ת�����RGB2������  ��24bits
struct My_24bits                    //�ṹ��
{
       uchar G_VAL;                 //��ɫ  0-255
       uchar R_VAL;                  //��ɫ 0-255
       uchar B_VAL;                  //��ɫ0-255
};
 
 
/*д������ʱ��*/
void Send_A_bit(uchar VAL)
{
//     Send_Dat=0;
       if (VAL==1)
       {
       //     Send_Dat=0;
              Send_Dat=1;
              _nop_();
              //_nop_();
              Send_Dat=0;            //2.17us
              //_nop_();
       //     Send_Dat=1;                 //2.17us
       }
       else
       {
       //     Send_Dat=0;
              Send_Dat=1;
              //_nop_();
              //_nop_();
              Send_Dat=0;           
              _nop_();
       //     Send_Dat=1;
       }           
      
}
 
 
/*����24λ�ַ�������RGB��Ϣ��8λ��*/
void Send_24bits(struct My_24bits RGB_VAL )                      
{
       uchar i;
       for   (i=0;i<8;i++)
       {
              RGB_BUF[i]=RGB_VAL.R_VAL>>i&0x01;                          //ת��R_VAL
       }
              for   (i=8;i<16;i++)
       {
              RGB_BUF[i]=RGB_VAL.G_VAL>>(i-8)&0x01;               //ת��G_VAL
       }
              for   (i=16;i<24;i++)                                                       //ת��B_VAL
       {
              RGB_BUF[i]=RGB_VAL.B_VAL>>(i-16)&0x01;     
       }
       for (i=0;i<24;i++)
       {
              Send_A_bit(RGB_BUF[i]);
       }
      
}
 
/*������*/
void main()
{
 
       struct My_24bits a,b,c,d,e,f,g;
       a.R_VAL=0xff;
       a.G_VAL=0x00;                      //1                   ��ɫ˳����ͬ
       a.B_VAL=0x00;
 
       b.R_VAL=0x00;
       b.G_VAL=0xff;                       //2
       b.B_VAL=0x00;
 
       c.R_VAL=0x00;
       c.G_VAL=0x00;                          //3
       c.B_VAL=0xff;
 
       d.R_VAL=0xff;                           //4
       d.G_VAL=0xff;
       d.B_VAL=0x00;
 
       e.R_VAL=0xff;
       e.G_VAL=0x00;                             //5
       e.B_VAL=0xff;
 
       f.R_VAL=0x00;
       f.G_VAL=0xff;                                  //6
       f.B_VAL=0xff;
 
       g.R_VAL=0xff;                                  //7
       g.G_VAL=0xff;
       g.B_VAL=0xff;
       init();
       while(1)
       {
       Send_Dat=0;
       Send_24bits(a);
       Send_Dat=0;   P0=0xF9;
       delays();
       while(Key==1);                                        //�����ȴ�����Key=1ʱֹͣ������0ʱ������ɫ��ˮ��ѭ������ͬ����Ҫ����۲���ɫ��
 
       Send_24bits(b);
       Send_Dat=0;          P0=0xa4;               //�������������ʾ��ɫ˳����ͬ
       delays();
       while(Key==1);
 
       Send_24bits(c);
       Send_Dat=0;   P0=0xb0;
       delays();
       while(Key==1);
 
       Send_24bits(d);
       Send_Dat=0;   P0=Led_Tab[4];
       delays();
       while(Key==1);
 
       Send_24bits(e);
       Send_Dat=0;   P0=Led_Tab[5];
       delays();
       while(Key==1);
 
       Send_24bits(f);
       Send_Dat=0;   P0=Led_Tab[6];
       delays();
       while(Key==1);
 
       Send_24bits(g);
       Send_Dat=0;   P0=Led_Tab[7];
       delays();
       while(Key==1);
//     PCON|=0x01;                      //����ģʽ
             
       }
}
 
 
 
/*�жϻ��Ѳ��Ժ���*/
void INT1_ISR(void) interrupt 2
{
       P2=1;
}
 
 
/*С��ʱ����*/
/*���1S�ɣ����д��*/
void delay()
{
uchar i,j;
       for (i=0;i<250;i++)
       {
              for (j=0;j<250;j++);
       }
}
 
 
/*����ʱ����*/
/*ʮ����*/
void delays()
{
       delay();
       delay();
       delay();
       delay();
       delay();
       delay();
       delay();
       delay();
       delay();  
       delay();
       delay();
       delay();
}
 
 
 
/*ϵͳ��ʼ��*/
void init()
{
  P0=0x00;
  P1=0x00;
  P2=0x00;
  P3=0x00;
 
  TCON=0x05;
  TMOD=0x00;
  TH0=0x00;
  TL0=0x00;
  TH1=0x00;
  TL1=0x00;
 
  T2CON=0x00;
  RCAP2H=0x00;
  RCAP2L=0x00;
 
  IP=0x00;
  IE=0x85;
  PCON=0x00;
  SCON=0x00;
}