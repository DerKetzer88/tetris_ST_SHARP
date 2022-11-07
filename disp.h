#ifndef DISP_H
#define DISP_H

#define D_H	240
#define D_W 320
#define G_BUF_SIZE	9600


int sh_sendLine(unsigned short* data, unsigned int linenum);
void sh_sendLineSel(short* data, unsigned int* sel);
void sh_sendData(short* data);
void sh_showData(void);
void sh_sendDataBMP(unsigned short* data);
void sh_allClear(void);
void sh_clearLine(int linenum, int vcom);
void sh_clearDisp(void);
void sh_inv_disp(void);
void sh_dispEnable(void);
void sh_dispDisable(void);
void sh_delay(int cyc);
//MACROS
#define  SH_CS_UP GPIOB->BSRR |= 1 << 13
#define  SH_CS_DOWN GPIOB->BSRR |= (1 << (13 + 16))


#endif
