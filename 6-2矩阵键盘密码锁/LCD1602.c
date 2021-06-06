#include <REGX52.H>

//Òı½ÅÅäÖÃ£º
sbit LCD_RS=P2^6;
sbit LCD_RW=P2^5;
sbit LCD_EN=P2^7;
#define LCD_DataPort P0

//º¯Êı¶¨Òå£º
/**
  * @brief  LCD1602ÑÓÊ±º¯Êı£¬12MHzµ÷ÓÃ¿ÉÑÓÊ±1ms
  * @param  ÎŞ
  * @retval ÎŞ
  */
void LCD_Delay()
{
	unsigned char i, j;

	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
}

/**
  * @brief  LCD1602Ğ´ÃüÁî
  * @param  Command ÒªĞ´ÈëµÄÃüÁî
  * @retval ÎŞ
  */
void LCD_WriteCommand(unsigned char Command)
{
	LCD_RS=0;
	LCD_RW=0;
	LCD_DataPort=Command;
	LCD_EN=1;
	LCD_Delay();
	LCD_EN=0;
	LCD_Delay();
}

/**
  * @brief  LCD1602Ğ´Êı¾İ
  * @param  Data ÒªĞ´ÈëµÄÊı¾İ
  * @retval ÎŞ
  */
void LCD_WriteData(unsigned char Data)
{
	LCD_RS=1;
	LCD_RW=0;
	LCD_DataPort=Data;
	LCD_EN=1;
	LCD_Delay();
	LCD_EN=0;
	LCD_Delay();
}

/**
  * @brief  LCD1602ÉèÖÃ¹â±êÎ»ÖÃ
  * @param  Line ĞĞÎ»ÖÃ£¬·¶Î§£º1~2
  * @param  Column ÁĞÎ»ÖÃ£¬·¶Î§£º1~16
  * @retval ÎŞ
  */
void LCD_SetCursor(unsigned char Line,unsigned char Column)
{
	if(Line==1)
	{
		LCD_WriteCommand(0x80|(Column-1));
	}
	else if(Line==2)
	{
		LCD_WriteCommand(0x80|(Column-1+0x40));
	}
}
/**
  * @brief  LCD1602³õÊ¼»¯º¯Êı
  * @param  ÎŞ
  * @retval ÎŞ
  */
void LCD_Init()
{
	LCD_WriteCommand(0x38);//å…«ä½æ•°æ®æ¥å£ï¼Œä¸¤è¡Œæ˜¾ç¤ºï¼Œ5*7ç‚¹é˜µ
	LCD_WriteCommand(0x0c);//æ˜¾ç¤ºå¼€ï¼Œå…‰æ ‡å…³ï¼Œé—ªçƒå…³
	LCD_WriteCommand(0x06);//æ•°æ®è¯»å†™æ“ä½œåï¼Œå…‰æ ‡è‡ªåŠ¨åŠ ä¸€ï¼Œç”»é¢ä¸åŠ¨
	LCD_WriteCommand(0x01);//å…‰æ ‡å¤ä½ï¼Œæ¸…å±
}

/**
  * @brief  ÔÚLCD1602Ö¸¶¨Î»ÖÃÉÏÏÔÊ¾Ò»¸ö×Ö·û
  * @param  Line ĞĞÎ»ÖÃ£¬·¶Î§£º1~2
  * @param  Column ÁĞÎ»ÖÃ£¬·¶Î§£º1~16
  * @param  Char ÒªÏÔÊ¾µÄ×Ö·û
  * @retval ÎŞ
  */
void LCD_ShowChar(unsigned char Line,unsigned char Column,char Char)
{
	LCD_SetCursor(Line,Column);
	LCD_WriteData(Char);
}

/**
  * @brief  ÔÚLCD1602Ö¸¶¨Î»ÖÃ¿ªÊ¼ÏÔÊ¾Ëù¸ø×Ö·û´®
  * @param  Line ÆğÊ¼ĞĞÎ»ÖÃ£¬·¶Î§£º1~2
  * @param  Column ÆğÊ¼ÁĞÎ»ÖÃ£¬·¶Î§£º1~16
  * @param  String ÒªÏÔÊ¾µÄ×Ö·û´®
  * @retval ÎŞ
  */
void LCD_ShowString(unsigned char Line,unsigned char Column,char *String)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=0;String[i]!='\0';i++)
	{
		LCD_WriteData(String[i]);
	}
}

/**
  * @brief  ·µ»ØÖµ=XµÄY´Î·½
  */
int LCD_Pow(int X,int Y)
{
	unsigned char i;
	int Result=1;
	for(i=0;i<Y;i++)
	{
		Result*=X;
	}
	return Result;
}

/**
  * @brief  ÔÚLCD1602Ö¸¶¨Î»ÖÃ¿ªÊ¼ÏÔÊ¾Ëù¸øÊı×Ö
  * @param  Line ÆğÊ¼ĞĞÎ»ÖÃ£¬·¶Î§£º1~2
  * @param  Column ÆğÊ¼ÁĞÎ»ÖÃ£¬·¶Î§£º1~16
  * @param  Number ÒªÏÔÊ¾µÄÊı×Ö£¬·¶Î§£º0~65535
  * @param  Length ÒªÏÔÊ¾Êı×ÖµÄ³¤¶È£¬·¶Î§£º1~5
  * @retval ÎŞ
  */
void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		LCD_WriteData(Number/LCD_Pow(10,i-1)%10+'0');
	}
}

/**
  * @brief  ÔÚLCD1602Ö¸¶¨Î»ÖÃ¿ªÊ¼ÒÔÓĞ·ûºÅÊ®½øÖÆÏÔÊ¾Ëù¸øÊı×Ö
  * @param  Line ÆğÊ¼ĞĞÎ»ÖÃ£¬·¶Î§£º1~2
  * @param  Column ÆğÊ¼ÁĞÎ»ÖÃ£¬·¶Î§£º1~16
  * @param  Number ÒªÏÔÊ¾µÄÊı×Ö£¬·¶Î§£º-32768~32767
  * @param  Length ÒªÏÔÊ¾Êı×ÖµÄ³¤¶È£¬·¶Î§£º1~5
  * @retval ÎŞ
  */
void LCD_ShowSignedNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length)
{
	unsigned char i;
	unsigned int Number1;
	LCD_SetCursor(Line,Column);
	if(Number>=0)
	{
		LCD_WriteData('+');
		Number1=Number;
	}
	else
	{
		LCD_WriteData('-');
		Number1=-Number;
	}
	for(i=Length;i>0;i--)
	{
		LCD_WriteData(Number1/LCD_Pow(10,i-1)%10+'0');
	}
}

/**
  * @brief  ÔÚLCD1602Ö¸¶¨Î»ÖÃ¿ªÊ¼ÒÔÊ®Áù½øÖÆÏÔÊ¾Ëù¸øÊı×Ö
  * @param  Line ÆğÊ¼ĞĞÎ»ÖÃ£¬·¶Î§£º1~2
  * @param  Column ÆğÊ¼ÁĞÎ»ÖÃ£¬·¶Î§£º1~16
  * @param  Number ÒªÏÔÊ¾µÄÊı×Ö£¬·¶Î§£º0~0xFFFF
  * @param  Length ÒªÏÔÊ¾Êı×ÖµÄ³¤¶È£¬·¶Î§£º1~4
  * @retval ÎŞ
  */
void LCD_ShowHexNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i,SingleNumber;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		SingleNumber=Number/LCD_Pow(16,i-1)%16;
		if(SingleNumber<10)
		{
			LCD_WriteData(SingleNumber+'0');
		}
		else
		{
			LCD_WriteData(SingleNumber-10+'A');
		}
	}
}

/**
  * @brief  ÔÚLCD1602Ö¸¶¨Î»ÖÃ¿ªÊ¼ÒÔ¶ş½øÖÆÏÔÊ¾Ëù¸øÊı×Ö
  * @param  Line ÆğÊ¼ĞĞÎ»ÖÃ£¬·¶Î§£º1~2
  * @param  Column ÆğÊ¼ÁĞÎ»ÖÃ£¬·¶Î§£º1~16
  * @param  Number ÒªÏÔÊ¾µÄÊı×Ö£¬·¶Î§£º0~1111 1111 1111 1111
  * @param  Length ÒªÏÔÊ¾Êı×ÖµÄ³¤¶È£¬·¶Î§£º1~16
  * @retval ÎŞ
  */
void LCD_ShowBinNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		LCD_WriteData(Number/LCD_Pow(2,i-1)%2+'0');
	}
}
