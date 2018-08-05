
/********************************************************/
/*作 者：Dyingstraw
/*修改日期：2015.5.2
/*版    本：V1.0
/*程序功能：用51单片机控制ws2812 RGB输出，显示全色彩
/*备        注：51单片机晶振24M
/********************************************************/
 
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
//存储一个转化后的RGB2进制数  共24bits
struct My_24bits                    //结构体
{
       uchar G_VAL;                 //绿色  0-255
       uchar R_VAL;                  //红色 0-255
       uchar B_VAL;                  //蓝色0-255
};
 
 
/*写入数据时序*/
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
 
 
/*发送24位字符（包含RGB信息各8位）*/
void Send_24bits(struct My_24bits RGB_VAL )                      
{
       uchar i;
       for   (i=0;i<8;i++)
       {
              RGB_BUF[i]=RGB_VAL.R_VAL>>i&0x01;                          //转化R_VAL
       }
              for   (i=8;i<16;i++)
       {
              RGB_BUF[i]=RGB_VAL.G_VAL>>(i-8)&0x01;               //转化G_VAL
       }
              for   (i=16;i<24;i++)                                                       //转化B_VAL
       {
              RGB_BUF[i]=RGB_VAL.B_VAL>>(i-16)&0x01;     
       }
       for (i=0;i<24;i++)
       {
              Send_A_bit(RGB_BUF[i]);
       }
      
}
 
/*主函数*/
void main()
{
 
       struct My_24bits a,b,c,d,e,f,g;
       a.R_VAL=0xff;
       a.G_VAL=0x00;                      //1                   颜色顺序，下同
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
       while(Key==1);                                        //按键等待，当Key=1时停止，等于0时七种颜色流水灯循环，下同（主要方便观察颜色）
 
       Send_24bits(b);
       Send_Dat=0;          P0=0xa4;               //共阴极数码管显示颜色顺序，下同
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
//     PCON|=0x01;                      //空闲模式
             
       }
}
 
 
 
/*中断唤醒测试函数*/
void INT1_ISR(void) interrupt 2
{
       P2=1;
}
 
 
/*小延时函数*/
/*大概1S吧，随便写的*/
void delay()
{
uchar i,j;
       for (i=0;i<250;i++)
       {
              for (j=0;j<250;j++);
       }
}
 
 
/*大延时函数*/
/*十几秒*/
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
 
 
 
/*系统初始化*/
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