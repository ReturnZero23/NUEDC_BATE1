/********************************************************************
//DM430-L型系统板控制带字库型12864液晶模块显示测试程序，显示2幅图片
//请注意安装位置，左边有字符说明，为靠近1602接口的1X20座子
//注意选择液晶的电源，位于电位器附近，可选5V或3.3V，根据液晶电压进行选择，默认5V
//调试环境：EW430 V5.30
//作者：www.avrgcc.com
//时间：2014.03.01
********************************************************************/
#include <msp430x16x.h>
#include "Config.h"
#include "Data.c"
#include "LCD12864.c"
#include "ADC12.c"


//*************************************************************************
//	初始化IO口子程序
//*************************************************************************
void Port_Init()
{
  P4SEL = 0x00;
  P4DIR = 0xFF;
  P5SEL = 0x00;
  P5DIR|= BIT0 + BIT1 + BIT5 + BIT6 + BIT7;
  PSB_SET;		          //液晶并口方式
  RST_SET;		          //复位脚RST置高
}



//****************************************************************
//函数名称：主函数，调用相关子程序，显示图形
//****************************************************************

int main(void)
{
  WDT_Init();                                   //看门狗设置
  Clock_Init();                                 //系统时钟设置
  Port_Init();                                  //系统初始化，设置IO口属性
  delay_ms(10);                                //延时10ms
  LCD_init();                                   //液晶参数初始化设置
  LCD_clear();                                  //清屏
  DAC12_Init();                             //初始化DAC12
  delay_ms(10);
  Display(); 
  while(1)
  {
    //uchar x_line,y_line;
    
    Display_photo(photo7); 
    //Display_point(3,3,1,photo7);
    //Display_sin(photo7);
    //Display_juchi(photo7);
    //Display_juxing(photo7);
    //Display_changestr(photo7,zhengxian);
    //Display_freq(4321);
    //Display_ampl(4321);
    //Display_shine(1,0,3214);
    /*
    for(int i=0;i<4000;i++)
    {
      DAC12_0DAT = Sin_tab[i%100];                       //数据写入寄存器，写入激活DAC转换
      //delay_us(300);                        //这里延时是为了LED灯有显示效果，由亮到暗，电压输出由小到大，用示波器时去掉
    }
    */
  }
}

