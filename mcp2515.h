#ifndef _MCP2515_H_
#define _MCP2515_H_
#define MCP2515_BASE    0x00 //	 定义MCP2515的基址

/*************************************************************************************************
    以下为定义MCP2515的内部特殊功能寄存器的地址，各特殊功能寄存器的具体功能请查阅MCP2515的数据手册
**************************************************************************************************/

#define TXB0CTRL	MCP2515_BASE + 0x30  //发送缓冲区0控制寄存器
#define TXB1CTRL	MCP2515_BASE + 0x40  //发送缓冲区1控制寄存器
#define TXB2CTRL	MCP2515_BASE + 0x50  //发送缓冲区2控制寄存器
#define TXRTSCTRL	MCP2515_BASE + 0x0d  //发送请求引脚配置寄存器
#define TXB0SIDH 	MCP2515_BASE + 0x31  //标准标识符高字节
#define TXB0SIDL 	MCP2515_BASE + 0x32  //标准标识符低字节
#define TXB1SIDH 	MCP2515_BASE + 0x41  //标准标识符高字节
#define TXB1SIDL 	MCP2515_BASE + 0x42  //标准标识符高字节
#define TXB2SIDH 	MCP2515_BASE + 0x51  //标准标识符高字节
#define TXB2SIDL 	MCP2515_BASE + 0x52  //标准标识符低字节
#define TXB0EID8	MCP2515_BASE + 0x33  //扩展标识符高字节
#define TXB0EID0	MCP2515_BASE + 0x34  //扩展标识符低字节
#define TXB1EID8	MCP2515_BASE + 0x43  //扩展标识符高字节
#define TXB1EID0	MCP2515_BASE + 0x44  //扩展标识符低字节
#define TXB2EID8	MCP2515_BASE + 0x53  //扩展标识符高字节
#define TXB2EID0	MCP2515_BASE + 0x54  //扩展标识符低字节
#define TXB0DLC		MCP2515_BASE + 0x35  //发送缓存区0数据长度寄存器
#define TXB1DLC		MCP2515_BASE + 0x45  //发送缓存区0数据长度寄存器
#define TXB2DLC		MCP2515_BASE + 0x55  //发送缓存区0数据长度寄存器
#define TXB0D_BASE	MCP2515_BASE + 0x36  //发送绥冲区0数据寄存器起始地址
#define TXB1D_BASE	MCP2515_BASE + 0x46  //发送绥冲区1数据寄存器起始地址
#define TXB2D_BASE	MCP2515_BASE + 0x56  //发送绥冲区2数据寄存器起始地址
#define RXB0CTRL	MCP2515_BASE + 0x60  //接收缓冲区0控制寄存器
#define RXB1CTRL	MCP2515_BASE + 0x70  //接收缓冲区1控制寄存器
#define BFPCTRL		MCP2515_BASE + 0x0c  //接收引脚控制和状态寄存器
#define RXB0SIDH	MCP2515_BASE + 0x61  //接收缓冲器0标准标识符高字节
#define RXB0SIDL	MCP2515_BASE + 0x62  //接收缓冲器0标准标识符低字节
#define RXB1SIDH	MCP2515_BASE + 0x71  //接收缓冲器1标准标识符高字节
#define RXB1SIDL	MCP2515_BASE + 0x72  //接收缓冲器1标准标识符高字节
#define RXB0EID8	MCP2515_BASE + 0x63  //接收缓冲区0扩展标识符高字节
#define RXB0EID0	MCP2515_BASE + 0x64  //接收缓冲区0扩展标识符低字节
#define RXB1EID8	MCP2515_BASE + 0x73  //接收缓冲区1扩展标识符高字节
#define RXB1EID0	MCP2515_BASE + 0x74  //接收缓冲区1扩展标识符低字节
#define RXB0DLC		MCP2515_BASE + 0x65	 //接收缓冲区0数据码长度
#define RXB1DLC		MCP2515_BASE + 0x75	 //接收缓冲区1数据码长度
#define RXB0D_BASE	MCP2515_BASE + 0x66  //接收缓冲区0数据寄存器起始地址
#define RXB1D_BASE	MCP2515_BASE + 0x76  //接收缓冲区1数据寄存器起始地址

#define RXF0SIDH	MCP2515_BASE + 0x00  //验收滤波器0标准标识符高字节
#define RXF0SIDL	MCP2515_BASE + 0x01  //验收滤波器0标准标识符低字节
#define RXF1SIDH	MCP2515_BASE + 0x04  //验收滤波器1标准标识符高字节
#define RXF1SIDL	MCP2515_BASE + 0x05  //验收滤波器1标准标识符低字节
#define RXF2SIDH	MCP2515_BASE + 0x08  //验收滤波器2标准标识符高字节
#define RXF2SIDL	MCP2515_BASE + 0x09  //验收滤波器2标准标识符低字节
#define RXF3SIDH	MCP2515_BASE + 0x10  //验收滤波器3标准标识符高字节
#define RXF3SIDL	MCP2515_BASE + 0x11  //验收滤波器3标准标识符低字节
#define RXF4SIDH	MCP2515_BASE + 0x14  //验收滤波器4标准标识符高字节
#define RXF4SIDL	MCP2515_BASE + 0x15  //验收滤波器4标准标识符低字节
#define RXF5SIDH	MCP2515_BASE + 0x18  //验收滤波器5标准标识符高字节
#define RXF5SIDL	MCP2515_BASE + 0x19  //验收滤波器5标准标识符低字节

#define RXF0EID8	MCP2515_BASE + 0x02  //验收滤波器0扩展标识符高字节
#define RXF0EID0	MCP2515_BASE + 0x03  //验收滤波器0扩展标识符低字节
#define RXF1EID8	MCP2515_BASE + 0x06  //验收滤波器1扩展标识符高字节
#define RXF1EID0	MCP2515_BASE + 0x07  //验收滤波器1扩展标识符低字节
#define RXF2EID8	MCP2515_BASE + 0x0a  //验收滤波器2扩展标识符高字节
#define RXF2EID0	MCP2515_BASE + 0x0b  //验收滤波器2扩展标识符低字节
#define RXF3EID8	MCP2515_BASE + 0x12  //验收滤波器3扩展标识符高字节
#define RXF3EID0	MCP2515_BASE + 0x13  //验收滤波器3扩展标识符低字节
#define RXF4EID8	MCP2515_BASE + 0x16  //验收滤波器4扩展标识符高字节
#define RXF4EID0	MCP2515_BASE + 0x17  //验收滤波器4扩展标识符低字节
#define RXF5EID8	MCP2515_BASE + 0x1a  //验收滤波器5扩展标识符高字节
#define RXF5EID0	MCP2515_BASE + 0x1b  //验收滤波器5扩展标识符低字节

#define RXM0SIDH	MCP2515_BASE + 0x20  //验收屏蔽寄存器0标准标识符高字节
#define RXM0SIDL	MCP2515_BASE + 0x21  //验收屏蔽寄存器0标准标识符低字节
#define RXM1SIDH	MCP2515_BASE + 0x24  //验收屏蔽寄存器1标准标识符高字节
#define RXM1SIDL	MCP2515_BASE + 0x25  //验收屏蔽寄存器1标准标识符低字节

#define RXM0EID8	MCP2515_BASE + 0x22  //验收屏蔽寄存器0扩展标识符高字节
#define RXM0EID0	MCP2515_BASE + 0x26  //验收屏蔽寄存器0扩展标识符低字节
#define RXM1EID8	MCP2515_BASE + 0x23  //验收屏蔽寄存器1扩展标识符高字节
#define RXM1EID0	MCP2515_BASE + 0x27  //验收屏蔽寄存器1扩展标识符低字节

#define CNF1		MCP2515_BASE + 0x2a  //配置寄存器1
#define CNF2		MCP2515_BASE + 0x29  //配置寄存器2
#define CNF3		MCP2515_BASE + 0x28  //配置寄存器3
#define TEC			MCP2515_BASE + 0x1c  //发送错误计数器
#define REC			MCP2515_BASE + 0x1d  //接收错误计数器
#define EFLG		MCP2515_BASE + 0x2d  //错误标志寄存器，最高2位必须由MCU复位
#define CANINTE		MCP2515_BASE + 0x2b  //中断使能寄存器
#define CANINTF		MCP2515_BASE + 0x2c  //中断标志寄存器，写0则清除相应的中断；
#define CANCTRL		MCP2515_BASE + 0x0f  //CAN控制寄存器
#define CANSTAT		MCP2515_BASE + 0x0e  //CAN状态寄存器

/************************************************************************************
			定义EFLG错误标志寄存器的命令字
************************************************************************************/
#define EWARN		0x01<<0 			//错误警告寄存器，当TEC或REC大于等于96时置1
#define RXWAR		0x01<<1 			//当REC大于等于96时置1
#define TXWAR		0x01<<2 			//当TEC大于等于96时置1
#define RXEP		0x01<<3 			//当REC大于等于128时置1
#define TXEP		0x01<<4 			//当TEC大于等于128时置1
#define TXBO		0x01<<5 			//当TEC大于等于255时置1
#define RX0OVR 		0x01<<6				//接收缓冲区0溢出
#define RX1OVR 		0x01<<7				//接收缓冲区1溢出
/************************************************************************************
			定义TXBnCTRL寄存器的命令字
************************************************************************************/
#define TXREQ		0x08				//报文发送请求位
#define ABTF		0x40				//报文发送中止标记位
/****************TXBnDLC寄存器和RXBnDLC寄存器*********************/
#define RTR 		0x40				//远程发送请求位
/**************TXBnSIDL寄存器和RXFnSIDL寄存器****************/
#define EXIDE 		0x08				//扩展标识符使能位
/**************RXBnSIDL寄存器****************/
#define IDE			0x08				//扩展标识符标志位，该位表明收到的报文是标准帧还是扩展帧
#define SRR			0x10 				//远程发送请求位（只有当IDE位 = 0时有效）
/************************************************************************************
			        定义MCP2515中断使能寄存器的命令字
************************************************************************************/
#define MERRF		0x80				//报文错误中断使能位
#define WAKIF		0x40				//唤醒中断使能位
#define ERRIF		0x20				//错误中断使能位
#define TX2IF		0x10				//发送缓冲器2空中断使能位
#define TX1IF		0x08				//发送缓冲器1空中断使能位
#define TX0IF		0x04				//发送缓冲器0空中断使能位
#define RX1IF		0x02				//接收缓冲器1满中断使能位
#define RX0IF		0x01				//接收缓冲器0满中断使能位
/************************************************************************************
			        定义MCP2515操作的命令字
************************************************************************************/
#define CAN_RESET 		0xc0				//复位命令
#define CAN_W			0x02				//写命令+（地址+数据）
#define CAN_W_BUFFER	0x40			//装载发送缓冲区命令[0-2]
 								//000 指针起始于TXB0SIDH；001指针起始于TXB0D0				
								//010 指针起始于TXB1SIDH；001指针起始于TXB0D1
								//100 指针起如于TXB2SIDH；101指针起始于TXB0D2
#define CAN_R			0x03				//读命令+（地址）
#define CAN_R_BUFFER	0x90				//读绥冲区指令[1-2]00指针起始于RXB0SIDH;01指针起始于RXB0D0
											//10 指针起始于RXB1SIDH;11指针起始于RXB1D0
#define CAN_R_STATE		0xa0				//读状态命令
#define CAN_RX 			0xb0				//读出接收缓冲区的状态
#define CAN_M_BIT		0x01				//位修改命令+地址+屏蔽字节+数据字节
#define CAN_RTS			0x80				//请求发送命令[0-3]000无发送；001 TX0;010 TX1;100 TX2

/************************************************************************************
			        定义MCP2515的CAN工作模式
************************************************************************************/
#define CAN_Config_Mode 		0x80			//配置模式
#define CAN_Listen_Only_Mode	0x60			//仅监听模式
#define CAN_LoopBack_Mode		0x40			//环回模式
#define CAN_Sleep_Mode			0x20			//休眠模式
#define	CAN_Normal_Mode			0x00			//正常工作模式
/************************************************************************************
			        定义MCP2515的CAN工作模式
************************************************************************************/
#define CAN_I_RESET				0xc0			//复位
#define CAN_I_READ				0x03			//从寄存器中读出数据
#define	CAN_I_READ_RX			0x90			//读RX缓冲器指令
#define CAN_I_WRITE				0x02			//向寄存器中写入数据
#define CAN_I_WRITE_TX			0x40			//装载TX缓冲器指令
#define CAN_I_RTS				0x80			//发送请求
#define CAN_I_READ_STATE		0xa0			//读取寄存器状态
#define	CAN_I_RX_STATE			0xb0			//快速确定与报文和报文类型相匹配的滤波器
#define CAN_I_BIT_CHANGE		0x05			//位修改指令
#endif
