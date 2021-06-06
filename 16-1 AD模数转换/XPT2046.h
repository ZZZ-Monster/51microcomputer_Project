
#ifndef __XPT2046_H__
#define __XPT2046_H__

#define XPT2046_XP   0x9c		 //¿ØÖÆ×Ö
#define XPT2046_YP 	 0xdc
#define XPT2046_AUX  0xec
#define XPT2046_VBAT 0xac 








unsigned int XPT2046_readAD(unsigned char Command);

#endif