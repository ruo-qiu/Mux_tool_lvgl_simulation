#ifndef _NES_TYPE_H_
#define _NES_TYPE_H_
 
#include "stdio.h"
 
#define u8 unsigned char       //定义一个8位的无符号变量类型
#define u16 unsigned short     //定义一个16位的无符号变量类型
#define u32 unsigned int       //定义一个32位的无符号变量类型
 
typedef unsigned short WORD;   //定义一个16位的无符号变量类型，主要在6502文件中使用
typedef unsigned char  BYTE;   //定义一个16位的无符号变量类型，主要在6502文件中使用
 
#endif