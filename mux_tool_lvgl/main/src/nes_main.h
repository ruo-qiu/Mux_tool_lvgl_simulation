#ifndef _NES_MAIN_H_
#define _NES_MAIN_H_
 
 
 
 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h> 
#include "nes_type.h" 
#include "nes_rom.h"
 
 
 
typedef struct
{
	char filetype[4]; 	//字符串“NES^Z”用来识别.NES文件 		 
	uint8_t romnum;			//16kB ROM的数目 						 
	uint8_t vromnum;			//8kB VROM的数目				 
	uint8_t romfeature;		//D0：1＝垂直镜像，0＝水平镜像 
						// D1：1＝有电池记忆，SRAM地址$6000-$7FFF
						// D2：1＝在$7000-$71FF有一个512字节的trainer 
						// D3：1＝4屏幕VRAM布局 
						//  D4－D7：ROM Mapper的�4� 	  
	uint8_t rommappernum;	// D0－D3：保留，必须是0（准备作为副Mapper号^_^）
						// D4－D7：ROM Mapper的高4位 		    
	//uint8_t reserve[8];	// 保留，必须是0 					    
	//OM段升序排列，如果存在trainer，它的512字节摆在ROM段之前 
	//VROM段, 升序排列 
}NesHeader;	
 
 
 
 
uint8_t nes_main(uint8_t select);
void NesFrameCycle(void);
uint8_t nes_mem_creat(void);		//开辟nes运行所需的RAM.
void nes_mem_delete(void);	//删除nes运行时申请的RAM	
 
 
 
//PPU使用
extern uint8_t *NameTable;			//2K的变量
extern uint16_t	*Buffer_scanline;	//行显示缓存,上下标越界最大为7，显示区 7 ~ 263  0~7 263~270 为防止溢出区
//CPU使用
extern uint8_t *ram6502;  			//RAM  2K字节,由malloc申请
 
 
 
#endif