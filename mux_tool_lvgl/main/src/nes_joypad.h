#ifndef _NES_JOYPAD_H_
#define _NES_JOYPAD_H_
//#include "nes_KeyNum.h"       	//获取按键值头文件
//#include "nes_adcrock.h"      	//获取方向值头文件
#include "nes_type.h"         	//数据类型头文件
 
 
#define JOYPAD_0 	0     	//是否读取键值得开关 0读取
#define JOYPAD_1 	1	  	//是否读取键值开关   1不读取
 
 
extern u8  JOY_key;   		//保存角色1键值
extern u8  JOY_key2;   		//保存角色2键值
typedef struct{
	u8 state;   			//状态
	u8  index;				//当前读取位
	u32 value;				//JoyPad 当前值	
}JoyPadType;
 
/* function ------------------------------------------------------------------*/
void NES_JoyPadInit(void);    		//初始化模拟手柄
void NES_JoyPadReset(void);   		//读取键值，并存入  JOY_key
void NES_JoyPadDisable(void); 		//未用到
u8 NES_GetJoyPadVlaue(int JoyPadNum);//将JOY_key转化为模拟手柄脉冲，次函数供角色1使用
u8 NES_GetJoyPadVlaue2(int JoyPadNum);//将JOY_key转化为模拟手柄脉冲，次函数供角色2使用
 
#endif 