#define X1address       0x80        //12864�ϰ���X����ʼ��ַ
#define X2address       0x88        //12864�°���X����ʼ��ַ
#define Yaddress        0x80        //Y����ʼ��ַ

//***********************************************************************
//	��ʾ������д�뺯��
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
//	��ʾ������д�뺯��
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
//	��ʾ�������ʾ
//***********************************************************************

void LCD_clear(void) 
{
  LCD_write_com(0x01);
  delay_ms(1);
}

//***********************************************************************
//�������ƣ�DisplayCgrom(uchar hz)��ʾCGROM��ĺ���
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
//�������ƣ�Display()��ʾ���Խ��
//****************************************************************
void Display(void)
{
  DisplayCgrom(0x80,"          123456");
  DisplayCgrom(0x88,"                ");
  DisplayCgrom(0x90,"                ");
  DisplayCgrom(0x98,"                ");
}

//***********************************************************************
//	��ʾ����ʼ������
//***********************************************************************
void LCD_init(void) 
{
  LCD_write_com(FUN_MODE);			//��ʾģʽ����
  delay_ms(1);
  LCD_write_com(FUN_MODE);			//��ʾģʽ����
  delay_ms(1);
  LCD_write_com(DISPLAY_ON);			//��ʾ��
  delay_ms(1);
  LCD_write_com(CLEAR_SCREEN);			//����
  delay_ms(1);
}

//****************************************************************
//�������ƣ�Display_photo(uchar *hz)��ʾ�Զ���ͼ�Σ������°�����д
//****************************************************************

void Display_photo1(const uchar *img1)           //д�ϰ���ͼ�����ݺ���
{
   int i,j;     

   for(i=0;i<32;i++)                             //�ϰ���32��
    {  
	LCD_write_com(FUN_MODEK);                //��չָ�����ͼ��ʾ
        delay_us(50);
     
 	LCD_write_com(Yaddress+i);               //��д��ֱ��ַ����Y��ַ�������Զ���һ
        delay_us(50);

        LCD_write_com(X1address);                //��дˮƽ��ַ����X��ַ
        delay_us(50);
      
 	for(j=0;j<8;j++)                         //����д��2���ֽڵ����ݣ�һ��8�Σ�Ϊһ�У���16*8λ����
        {  			                                     
		LCD_write_data(img1[i*16+j*2]);
		delay_us(50);                     //�����ʱ�Ǳ���ģ���Ϊû�ж�Һ��������æ���������Խ�����ʱ
		LCD_write_data(img1[i*16+j*2+1]); 
		delay_us(50);          
        }

    }
}

void Display_photo2(const uchar *img2)           //д�°���ͼ������
{
	int i,j;

	for(i=0;i<32;i++)                        //�°���32��
	{  

	 LCD_write_com(Yaddress+i);       //��д��ֱ��ַ����Y��ַ�������Զ���һ
	 delay_us(50);
	 LCD_write_com(X2address);        //��дˮƽ��ַ����X��ַ
	 delay_us(50);
	 	 for(j=0;j<8;j++)         //����д��2���ֽڵ����ݣ�һ��8�Σ�Ϊһ�У���16*8λ����
	    {
			
			LCD_write_data(img2[i*16+j*2]);
			delay_us(50);                    
			LCD_write_data(img2[i*16+j*2+1]);  
			delay_us(50);  
      
		}

	}

}

void Display_photo(const uchar *img)           //дȫ��ͼ�����ݺ���
{
   int i,j;     

   for(i=0;i<32;i++)                             //�ϰ���32��
    {  
	LCD_write_com(FUN_MODEK);                //��չָ�����ͼ��ʾ
        delay_us(50);
     
 	LCD_write_com(Yaddress+i);               //��д��ֱ��ַ����Y��ַ�������Զ���һ
        delay_us(50);

        LCD_write_com(X1address);                //��дˮƽ��ַ����X��ַ
        delay_us(50);
      
 	for(j=0;j<8;j++)                         //����д��2���ֽڵ����ݣ�һ��8�Σ�Ϊһ�У���16*8λ����
        {  			                                     
		LCD_write_data(img[i*16+j*2]);
		delay_us(50);                     //�����ʱ�Ǳ���ģ���Ϊû�ж�Һ��������æ���������Խ�����ʱ
		LCD_write_data(img[i*16+j*2+1]); 
		delay_us(50);          
        }

    }
   for(i=0;i<32;i++)                        //�°���32��
	{  

	 LCD_write_com(Yaddress+i);       //��д��ֱ��ַ����Y��ַ�������Զ���һ
	 delay_us(50);
	 LCD_write_com(X2address);        //��дˮƽ��ַ����X��ַ
	 delay_us(50);
	 	 for(j=0;j<8;j++)         //����д��2���ֽڵ����ݣ�һ��8�Σ�Ϊһ�У���16*8λ����
	    {
			
			LCD_write_data(img[i*16+j*2+512]);
			delay_us(50);                    
			LCD_write_data(img[i*16+j*2+1+512]);  
			delay_us(50);  
      
		}

	}
}
//****************************************************************
//�������ƣ�Display_point(uchar *img)���㺯��
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
//�������ƣ�Display_changestr(uchar *d_img,uchar *s_img)��ʾ���ε�����
//****************************************************************
void Display_changestr(uchar *d_img,uchar *s_img)
{
  for(int i = 33;i < 45; i++)
  {
      for(int j = 0 ; j <8;j++)
      {
          d_img[i*16+8+j]=s_img[j+(i-33)*8];
      }
  }
}
//****************************************************************
//�������ƣ�Display_sin(uchar *img)��ʾ����
//****************************************************************
void Display_sin(uchar *img)
{
  for(int i = 0; i <64 ;i++)
  {
      Display_point(i,(int)(Sin_tab[(i*3)%100]*(36.0/3267))+6,1,img);
  }
  Display_changestr(photo7,zhengxian);
}
//****************************************************************
//�������ƣ�Display_juchi(uchar *img)��ʾ���
//****************************************************************
void Display_juchi(uchar *img)
{
  for(int i = 0; i <16 ;i++)
  {
      Display_point(i,32-2*i+6,1,img);
  }
  for(int i = 16; i <32 ;i++)
  {
      Display_point(i,2*(i-16)+6,1,img);
  }
  for(int i = 32; i <48 ;i++)
  {
      Display_point(i,32-2*(i-32)+6,1,img);
  }
  for(int i = 48; i <64 ;i++)
  {
      Display_point(i,2*(i-48)+6,1,img);
  }
  Display_changestr(photo7,juchi);
}
//****************************************************************
//�������ƣ�Display_juxing(uchar *img)��ʾ����
//****************************************************************
void Display_juxing(uchar *img)
{
  for(int i = 0; i <16 ;i++)
  {
      Display_point(i,9,1,img);
  }
  for(int i = 9; i <36 ;i++)
  {
      Display_point(16,i,1,img);
  }
  for(int i = 16; i <32 ;i++)
  {
      Display_point(i,35,1,img);
  }
  for(int i = 9; i <36 ;i++)
  {
      Display_point(32,i,1,img);
  }
  for(int i = 32; i <48 ;i++)
  {
      Display_point(i,9,1,img);
  }
  for(int i = 9; i <36 ;i++)
  {
      Display_point(48,i,1,img);
  }
  for(int i = 48; i <64 ;i++)
  {
      Display_point(i,35,1,img);
  }
  Display_changestr(photo7,juxing);
}
//****************************************************************
//�������ƣ�Display_freq()��ʾƵ��
//****************************************************************
void Display_freq(int freq)
{
  uint qian,bai,shi,ge;
  qian=freq/1000;                       //�ֳ�ǧ���٣�ʮ���͸�λ
  bai=(freq%1000)/100;
  shi=(freq%100)/10;
  ge=(freq%10);
  unsigned char str[] = "          1234";
  //unsigned char str[] = "          1234";
  str[10]=qian+48;
  str[11]=bai+48;
  str[12]=shi+48;
  str[13]=ge+48;
  DisplayCgrom(0x80,str);
  //DisplayCgrom(0x88,"                ");
  //DisplayCgrom(0x90,"                ");
  //DisplayCgrom(0x98,"                ");
}
//****************************************************************
//�������ƣ�Display_ampl()��ʾƵ��
//****************************************************************
void Display_ampl(int ampl)
{
  uint qian,bai,shi,ge;
  qian=ampl/1000;                       //�ֳ�ǧ���٣�ʮ���͸�λ
  bai=(ampl%1000)/100;
  shi=(ampl%100)/10;
  ge=(ampl%10);
  unsigned char str[] = "          1234";
  //unsigned char str[] = "          1234";
  str[10]=qian+48;
  str[11]=bai+48;
  str[12]=shi+48;
  str[13]=ge+48;
  //DisplayCgrom(0x80,str);
  DisplayCgrom(0x90,str);
  //DisplayCgrom(0x90,"                ");
  //DisplayCgrom(0x98,"                ");
}
//****************************************************************
//�������ƣ�Display_shine()��˸
//****************************************************************
void Display_shine(uchar x,uchar y,int num)
{
  static int flag = 0 ;
  uint temp[4];
  temp[0]=num/1000;                       //�ֳ�ǧ���٣�ʮ���͸�λ
  temp[1]=(num%1000)/100;
  temp[2]=(num%100)/10;
  temp[3]=(num%10);
  unsigned char str[] = "          1234";
  //unsigned char str[] = "          1234";
  str[10]=temp[0]+48;
  str[11]=temp[1]+48;
  str[12]=temp[2]+48;
  str[13]=temp[3]+48;
  //unsigned char str[] = "          1234";
  if(flag)
  {
  str[10+y]=temp[y]+48;
  if(x)
  DisplayCgrom(0x90,str);
  else
  DisplayCgrom(0x80,str);
  delay_ms(1000);
  }
  else
  {
  str[10+y]= ' ';
  if(x)
  DisplayCgrom(0x90,str);
  else
  DisplayCgrom(0x80,str);
  delay_ms(1000);
  }
  flag = ~flag;
  //DisplayCgrom(0x80,str);
  
}