#include "nes_joypad.h"
#include "lvgl_page_ctrl.h"
u8 JOY_key = 0xFF;
u8 JOY_key2 = 0xFF;
JoyPadType JoyPad[2];
 
u8 NES_GetJoyPadVlaue(int JoyPadNum) //	 得到手柄脉冲
{
	u8 retval = 0;
	if (JoyPadNum == 0)
	{
		retval = (u8)(keysend >> (u8)(JoyPad[0].index)) & 0X01;
		// retval = (u8)(JOY_key >> (u8)(JoyPad[0].index)) & 0X01;
		if (JoyPad[0].index == 20)
			retval = 1; //20位表示控制器在位.
				//	printf("\r\n 按键: %d",retval);	 //我写的代码 测试用
		JoyPad[0].index++;
	}
	return retval;
}
u8 NES_GetJoyPadVlaue2(int JoyPadNum) //	 得到手柄脉冲
{
	u8 retval = 0;
	if (JoyPadNum == 0)
	{
		// retval = (u8)((u32)JOY_key >> (u8)(JoyPad[1].index)) & 0X01;
		if (JoyPad[1].index == 19)
			retval = 1; //20位表示控制器在位.
				//	printf("\r\n 按键: %d",retval);	 //我写的代码 测试用
		JoyPad[1].index++;
	}
	return retval;
}
//读取手柄按键值.
//FC手柄数据输出格式:
//每给一个脉冲,输出一位数据,输出顺序:
//A->B->SELECT->START->UP->DOWN->LEFT->RIGHT.
//总共8位,对于有C按钮的手柄,按下C其实就等于A+B同时按下.
//按下是0,松开是1.
//[0]:右  0--->7
//[1]:左
//[2]:下
//[3]:上
//[4]:Start
//[5]:Select
//[6]:B
//[7]:A
void NES_JoyPadReset(void)
{
	JoyPad[0].state = 1;
    JoyPad[0].index = 0;
    JoyPad[1].state = 1;
    JoyPad[1].index = 0;
	// u8 ROCK_DIRCTION;
	// u8 KEY_value;
	// static u32 key_time = 0;
	// if (1)
	// {
	// 	switch (keysend)
	// 	{
	// 	case 2:
	// 		KEY_value = 0X01; //按键A
	// 		break;
	// 	case 1:
	// 		KEY_value = 0x02; //按键B
	// 		break;
	// 	case 3:
	// 		KEY_value = 0x03; //按键A和B同时按
	// 		break;
	// 	case 7:
	// 		KEY_value = 0x04; //按键Select
	// 		break;
	// 	case 9:
	// 		KEY_value = 0x08; //按键Select
	// 		break;
	// 	default:
	// 		KEY_value = 0x00;
	// 	}
	// 	switch (keysend)
	// 	{
	// 	case 1:
	// 		ROCK_DIRCTION = 0x10; //遥感上
	// 		break;
	// 	case 2:
	// 		ROCK_DIRCTION = 0x20; //遥感下
	// 		break;
	// 	case 3:
	// 		ROCK_DIRCTION = 0x40; //遥感左
	// 		break;
	// 	case 4:
	// 		ROCK_DIRCTION = 0x80; //遥感右
	// 		break;
	// 	default:
	// 		ROCK_DIRCTION = 0x00; //按键Select
	// 	}
	// 	// JOY_key=0xFF-((右  <<7)|(左  <<6)|(下  <<5)|(上  <<4)|Start<<3)|Select<<2)|(B  <<1)|A   );
	// 	//	JOY_key=0xFF-((KEY5<<7)|(KEY3<<6)|(0X01<<5)|(0X01<<4)|(KEY1<<3)|(KEY2<<2)|(0X01<<1)|KEY4);
	// 	JOY_key = keysend;//ROCK_DIRCTION | KEY_value;
	// 	printf("%d\r\n", JOY_key);
	// 		// JOYPAD_LAT=1;//   锁存一下
	// 		// JOYPAD_LAT=0;
	// }
	// else
	// 	JOY_key = 0;
	JoyPad[0].state = 1;
    JoyPad[0].index = 0;
    JoyPad[1].state = 1;
    JoyPad[1].index = 0;
}
 
void NES_JoyPadInit(void)
{
 
	JoyPad[0].state = 0; //状态为0,表示禁止
	JoyPad[0].index = 0;
	JoyPad[0].value = 1 << 20;
 
	JoyPad[1].state = 0;
	JoyPad[1].index = 0;
	JoyPad[1].value = 1 << 19;
}
 
void NES_JoyPadDisable(void)
{
}