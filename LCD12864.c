#define X1address       0x80        //12864上半屏X轴起始地址
#define X2address       0x88        //12864下半屏X轴起始地址
#define Yaddress        0x80        //Y轴起始地址

//***********************************************************************
//	显示屏命令写入函数
//***********************************************************************
void LCD_write_com(unsigned char com) 
{	
  RS_CLR;
  RW_CLR;
  EN_SET;
  DataPort = com;
  delay_us(10);
  EN_CLR;
}

//***********************************************************************
//	显示屏数据写入函数
//***********************************************************************
void LCD_write_data(unsigned char data) 
{
  RS_SET;
  RW_CLR;
  EN_SET;
  DataPort = data;
  delay_us(10);
  EN_CLR;
}

//***********************************************************************
//	显示屏清空显示
//***********************************************************************

void LCD_clear(void) 
{
  LCD_write_com(0x01);
  delay_ms(1);
}

//***********************************************************************
//函数名称：DisplayCgrom(uchar hz)显示CGROM里的汉字
//***********************************************************************
void DisplayCgrom(uchar addr,uchar *hz)
{
  LCD_write_com(addr);
  delay_ms(1);
  while(*hz != '\0')  
  {
    LCD_write_data(*hz);
    hz++;
    delay_ms(1);
  }

} 

//****************************************************************
//函数名称：Display()显示测试结果
//****************************************************************
void Display(void)
{
  DisplayCgrom(0x80,"欣世纪电子欢迎你");
  DisplayCgrom(0x88,"旺:jingyehanxing");
  DisplayCgrom(0x90,"www.avrgcc.com  ");
  DisplayCgrom(0x98,"电话057487476870");
}

//***********************************************************************
//	显示屏初始化函数
//***********************************************************************
void LCD_init(void) 
{
  LCD_write_com(FUN_MODE);			//显示模式设置
  delay_ms(1);
  LCD_write_com(FUN_MODE);			//显示模式设置
  delay_ms(1);
  LCD_write_com(DISPLAY_ON);			//显示开
  delay_ms(1);
  LCD_write_com(CLEAR_SCREEN);			//清屏
  delay_ms(1);
}

//****************************************************************
//函数名称：Display_photo(uchar *hz)显示自定义图形，分上下半屏来写
//****************************************************************

void Display_photo1(const uchar *img1)           //写上半屏图形数据函数
{
   int i,j;     

   for(i=0;i<32;i++)                             //上半屏32行
    {  
	LCD_write_com(FUN_MODEK);                //扩展指令，开绘图显示
        delay_us(50);
     
 	LCD_write_com(Yaddress+i);               //先写垂直地址，即Y地址，不能自动加一
        delay_us(50);

        LCD_write_com(X1address);                //再写水平地址，即X地址
        delay_us(50);
      
 	for(j=0;j<8;j++)                         //连续写入2个字节的数据，一共8次，为一行，即16*8位数据
        {  			                                     
		LCD_write_data(img1[i*16+j*2]);
		delay_us(50);                     //这个延时是必须的，因为没有对液晶进行判忙操作，所以进行延时
		LCD_write_data(img1[i*16+j*2+1]); 
		delay_us(50);          
        }

    }
}

void Display_photo2(const uchar *img2)           //写下半屏图形数据
{
	int i,j;

	for(i=0;i<32;i++)                        //下半屏32行
	{  

	 LCD_write_com(Yaddress+i);       //先写垂直地址，即Y地址，不能自动加一
	 delay_us(50);
	 LCD_write_com(X2address);        //再写水平地址，即X地址
	 delay_us(50);
	 	 for(j=0;j<8;j++)         //连续写入2个字节的数据，一共8次，为一行，即16*8位数据
	    {
			
			LCD_write_data(img2[i*16+j*2]);
			delay_us(50);                    
			LCD_write_data(img2[i*16+j*2+1]);  
			delay_us(50);  
      
		}

	}

}

void Display_photo(const uchar *img)           //写全屏图形数据函数
{
   int i,j;     

   for(i=0;i<32;i++)                             //上半屏32行
    {  
	LCD_write_com(FUN_MODEK);                //扩展指令，开绘图显示
        delay_us(50);
     
 	LCD_write_com(Yaddress+i);               //先写垂直地址，即Y地址，不能自动加一
        delay_us(50);

        LCD_write_com(X1address);                //再写水平地址，即X地址
        delay_us(50);
      
 	for(j=0;j<8;j++)                         //连续写入2个字节的数据，一共8次，为一行，即16*8位数据
        {  			                                     
		LCD_write_data(img[i*16+j*2]);
		delay_us(50);                     //这个延时是必须的，因为没有对液晶进行判忙操作，所以进行延时
		LCD_write_data(img[i*16+j*2+1]); 
		delay_us(50);          
        }

    }
   for(i=0;i<32;i++)                        //下半屏32行
	{  

	 LCD_write_com(Yaddress+i);       //先写垂直地址，即Y地址，不能自动加一
	 delay_us(50);
	 LCD_write_com(X2address);        //再写水平地址，即X地址
	 delay_us(50);
	 	 for(j=0;j<8;j++)         //连续写入2个字节的数据，一共8次，为一行，即16*8位数据
	    {
			
			LCD_write_data(img[i*16+j*2+512]);
			delay_us(50);                    
			LCD_write_data(img[i*16+j*2+1+512]);  
			delay_us(50);  
      
		}

	}
}
//****************************************************************
//函数名称：Display_point(uchar *img)画点函数
//****************************************************************
void Display_point(uchar y,uchar x,int con,uchar *img)
{
    uchar temp;
    temp=img[x*16+(y/8)];
    switch(y%8)
    {
    case 0:if(con)
              temp |= 0x80;
           else
              temp &= ~0x80;
           break;
    case 1:if(con)
              temp |= 0x40;
           else
              temp &= ~0x40;
           break;
    case 2:if(con)
              temp |= 0x20;
           else
              temp &= ~0x20;
           break;
    case 3:if(con)
              temp |= 0x10;
           else
              temp &= ~0x10;
           break;   
    case 4:if(con)
              temp |= 0x08;
           else
              temp &= ~0x08;
           break;
    case 5:if(con)
              temp |= 0x04;
           else
              temp &= ~0x04;
           break;
    case 6:if(con)
              temp |= 0x02;
           else
              temp &= ~0x02;
           break;
    case 7:if(con)
              temp |= 0x01;
           else
              temp &= ~0x01;
           break;   
    }
    img[x*16+(y/8)]=temp;
}
//****************************************************************
//函数名称：Display_changestr(uchar *d_img,uchar *s_img)显示波形的文字
//****************************************************************
void Display_changestr(uchar *d_img,uchar *s_img)
{
  for(int i = 29;i < 41; i++)
  {
      for(int j = 0 ; j <8;j++)
      {
          d_img[i*16+8+j]=s_img[j+(i-29)*8];
      }
  }
}
//****************************************************************
//函数名称：Display_sin(uchar *img)显示正弦
//****************************************************************
void Display_sin(uchar *img)
{
  for(int i = 0; i <64 ;i++)
  {
      Display_point(i,(int)(Sin_tab[(i*3)%100]*(36.0/3267))+3,1,img);
  }
  Display_changestr(photo7,zhengxian);
}
//****************************************************************
//函数名称：Display_juchi(uchar *img)显示锯齿
//****************************************************************
void Display_juchi(uchar *img)
{
  for(int i = 0; i <16 ;i++)
  {
      Display_point(i,32-2*i+3,1,img);
  }
  for(int i = 16; i <32 ;i++)
  {
      Display_point(i,2*(i-16)+3,1,img);
  }
  for(int i = 32; i <48 ;i++)
  {
      Display_point(i,32-2*(i-32)+3,1,img);
  }
  for(int i = 48; i <64 ;i++)
  {
      Display_point(i,2*(i-48)+3,1,img);
  }
  Display_changestr(photo7,juchi);
}
//****************************************************************
//函数名称：Display_juxing(uchar *img)显示矩形
//****************************************************************
void Display_juxing(uchar *img)
{
  for(int i = 0; i <16 ;i++)
  {
      Display_point(i,6,1,img);
  }
  for(int i = 6; i <33 ;i++)
  {
      Display_point(16,i,1,img);
  }
  for(int i = 16; i <32 ;i++)
  {
      Display_point(i,32,1,img);
  }
  for(int i = 6; i <33 ;i++)
  {
      Display_point(32,i,1,img);
  }
  for(int i = 32; i <48 ;i++)
  {
      Display_point(i,6,1,img);
  }
  for(int i = 6; i <33 ;i++)
  {
      Display_point(48,i,1,img);
  }
  for(int i = 48; i <64 ;i++)
  {
      Display_point(i,32,1,img);
  }
  Display_changestr(photo7,juxing);
}
