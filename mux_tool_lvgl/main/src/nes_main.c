#include "nes_main.h"
#include "nes_6502.h"
int nesruning = 0;       //初始化为真
int frame_cnt;           //统计帧数
//uint8_t  *rom_file;          //NES游戏rom的存储地址
//NES 帧周期循环

static int clocks; //CPU执行时间
static int NES_time;
//启动模拟器循环，检查VROM设置，若卡带为0，初始化VROM
//if ( NesHeader.byVRomSize == 0)
//设置VROM存储区位置。
void NesFrameCycle(void)
{
    // while (nesruning)
    {
 
        //scanline: 0~19 VBANK 段，若PPU使能NMI，将产生NMI 中断
        frame_cnt++;//帧计数器
        SpriteHitFlag = 0;
        for (PPU_scanline = 0; PPU_scanline < 20; PPU_scanline++)
        {
            exec6502(CLOCKS_PER_SCANLINE);
        }
        //scanline: 20, PPU加载设置，执行一次空的扫描时间
        exec6502(CLOCKS_PER_SCANLINE);
        //NesHBCycle();  //水平周期
        PPU_scanline++;   //20++
        PPU_Reg.NES_R2 &= ~R2_SPR0_HIT;
        //scanline: 21~261
 
        for (; PPU_scanline < SCAN_LINE_DISPALY_END_NUM; PPU_scanline++)
        {
 
            if ((SpriteHitFlag == 1) && ((PPU_Reg.NES_R2 & R2_SPR0_HIT) == 0))
            {
                clocks = sprite[0].x * CLOCKS_PER_SCANLINE / NES_DISP_WIDTH;
                exec6502(clocks);  //需重点优化
                PPU_Reg.NES_R2 |= R2_SPR0_HIT;
                exec6502(CLOCKS_PER_SCANLINE - clocks);
            }
            else exec6502(CLOCKS_PER_SCANLINE);   //耗时大户
 
 
            if ((PPU_Reg.NES_R1 & (R1_BG_VISIBLE | R1_SPR_VISIBLE)) || (PPU_Reg.NES_R1 & (R1_BG_LEFT8 | R1_SPR_LEFT8))) //若为假，关闭显示
            {
                if (SpriteHitFlag == 0)
                    NES_GetSpr0HitFlag(PPU_scanline - SCAN_LINE_DISPALY_START_NUM);//查找Sprite #0 碰撞标志
            }
            if ((frame_cnt % 3) == 0) //每3帧显示一次      //耗时大户
            {
                // NES_time = micros();
                NES_RenderLine(PPU_scanline - SCAN_LINE_DISPALY_START_NUM);//水平同步与显示一行
                // printf("%d\n", micros() - NES_time);
            }
        }
 
        //scanline: 262 完成一帧
        exec6502(CLOCKS_PER_SCANLINE);
        PPU_Reg.NES_R2 |= R2_VBlank_Flag;//设置VBANK 标志
        //若使能PPU VBANK中断，则设置VBANK
        if (PPU_Reg.NES_R0 & R0_VB_NMI_EN)
        {
            NMI_Flag = SET1;//完成一帧扫描，产生NMI中断
        }
        //设置帧IRQ标志，同步计数器，APU等
        //A mapper function in V-Sync 存储器切换垂直VBANK同步
        //MapperVSync();
        //读取控制器JoyPad状态,更新JoyPad控制器值*/
        // NES_JoyPadUpdateValue();   //systick 中断读取按键值
 
 
        //单独的返回键（KEY6）扫描程序
        //  if(KEY_Scan_f())break;        //退出 //退出模拟器
    }
}
const unsigned char* ronfile_addr = NULL;
//返回值:0,执行OK;
//    其他,错误代码
uint8_t nes_main(uint8_t select)
{
    uint16_t offset = 0;
    uint8_t res;
    switch(select)
    {
    case 1:
    {
        ronfile_addr = &rom_file0[0];
    }break;
    case 2:
    {
        ronfile_addr = &rom_file1[0];
    }break;
    case 3:
    {
        ronfile_addr = &rom_file2[0];
    }break;
    case 4:
    {
        ronfile_addr = &rom_file3[0];
    }break;
    case 5:
    {
        ronfile_addr = &rom_file4[0];
    }break;
    default:
        break;
    }
//    ronfile_addr = &rom_file0[0];
    NesHeader *neshreader = (NesHeader *) ronfile_addr;
    //由于NES文件头类型以0x1A结束，（0x1a是Ctrl+Z,这是模拟文件结束的符号）
    //所以使用strcncmp比较前3个字节。
    if (strncmp(neshreader->filetype, "NES", 3) != 0)
    {
        return 1;
    }
    else
    {
        if ((neshreader->romfeature & 0x01) == 0)
        {
        }
        else
        {
        }
 
        if ((neshreader->romfeature & 0x02) == 0)
        {
        }
        else
        {
        }
 
        if ((neshreader->romfeature & 0x04) == 0)
        {
        }
        else
        {
            offset = 512;
        }
 
        if ((neshreader->romfeature & 0x08) == 0)
        {
        }
        else
        {
        }
 
    }
    res = nes_mem_creat(); //申请内存
    if (res == 0) //申请成功了.则运行游戏
    {
        init6502mem(0,   //exp_rom                                                                                         
                    0,   //sram 由卡类型决定, 暂不支持                                                                                            
                  ((uint8_t *)&ronfile_addr[offset + 0x10]),  //prg_rombank, 存储器大小 由卡类型决定                                                              
                    neshreader->romnum);                                                                             
        reset6502();  //初始化6502存储器镜像

        PPU_Init(((uint8_t *)&ronfile_addr[offset + 0x10] + 
                 (neshreader->romnum * 0x4000)),
                 (neshreader->romfeature & 0x01)
                ); //PPU_初始化
        NES_JoyPadInit(); //初始化模拟手柄
        clocks = 0; //CPU执行时间
        NES_time = 0;
    //启动模拟器循环，检查VROM设置，若卡带为0，初始化VROM
    //if ( NesHeader.byVRomSize == 0)
    //设置VROM存储区位置。
        frame_cnt = 0;
        nesruning = 1;

    }
    // nes_mem_delete();//释放内存
    return res;
}
 
 
// uint8_t *ram6502;        //RAM  2K字节,由malloc申请
// portMUX_TYPE isr_nes_creat = portMUX_INITIALIZER_UNLOCKED;
 
//开辟nes运行所需的RAM.
//返回值:0,成功;
//    其他,错误代码.
uint8_t nes_mem_creat(void)
{
    // portENTER_CRITICAL_ISR(&isr_nes_creat);
    ram6502 = (uint8_t *)malloc(2048); //申请2K内存
    if (ram6502 == NULL)return 1;       //申请失败
    NameTable = (uint8_t *)malloc(2048); //申请2K内存
    if (NameTable == NULL)return 2;
    Buffer_scanline = (uint16_t *)malloc((8 + 256 + 8) * 2);
    if (Buffer_scanline == NULL)return 3;
    // portEXIT_CRITICAL_ISR(&isr_nes_creat);
    return 0;
}
//删除nes运行时申请的RAM
void nes_mem_delete(void)
{
    free(ram6502);
    free(NameTable);
    free(Buffer_scanline);
}