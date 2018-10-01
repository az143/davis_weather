/*
 * $Id$
 *
 * File:		notdavis.c
 * Date:		2015-09-07 Mon 19:13
 * Author:		Alexander Zangerl <az@snafu.priv.at>
 *
 * Abstract: make pic16f88 authenticate as a green dot logger
 */

#include <xc.h>

#ifdef __16F88__
#define _XTAL_FREQ 8000000	/* max speed that the 16f88 can do by itself */

#pragma config CPD=OFF, CP=OFF, DEBUG=OFF, WRT=OFF, LVP=OFF, BOREN=OFF, PWRTE=ON, MCLRE=OFF, WDTE=OFF
#pragma config FOSC=INTOSCIO, IESO=OFF, FCMEN=OFF
/* signal lines: pin 7/rb1 mosi, pin8/rb2 miso, pin 10/rb4 clock, pin 11/rb5 select */
#endif

#ifdef __16F18313__

#define _XTAL_FREQ 32000000

#pragma config FCMEN=OFF, RSTOSC=HFINT32, FEXTOSC=OFF
#pragma config PPS1WAY=OFF, BOREN=OFF, WDTE=OFF, PWRTE=ON, MCLRE=OFF
#pragma config LVP=OFF
#pragma config CPD=OFF, CP=OFF

#define SSPIF SSP1IF				/* new name */

#endif

static unsigned char inbyte, nextidx;
static struct {
   unsigned char spidone:1, secreg:1;
} status;

/* random secreg */
const unsigned char secregister[128+3] = {
   0, 0, 0,
   0x8d, 0x83, 0x5f, 0xf3, 0x8c, 0x7b, 0x77, 0x56, 0x35, 0x6b, 0xbd, 0xa5, 0x18, 0x10, 0x08, 0xde,
   0xe3, 0x4e, 0xca, 0xa1, 0xce, 0xf3, 0x0c, 0x8c, 0x31, 0x5e, 0x39, 0x25, 0xc2, 0x35, 0x46, 0x18,
   0x80, 0xbd, 0x7b, 0xe3, 0x46, 0x2d, 0x29, 0x31, 0xce, 0xca, 0x63, 0x77, 0x39, 0x67, 0x8c, 0x80,
   0x42, 0x88, 0xe7, 0x4e, 0x84, 0x6b, 0x77, 0x3d, 0xe7, 0xfb, 0xd6, 0x08, 0xbd, 0x35, 0x5a, 0x18,
   0x49, 0xc9, 0xbf, 0xf1, 0xe6, 0xd0, 0x16, 0xd7, 0x05, 0xc8, 0x60, 0x9b, 0x7e, 0xc1, 0x36, 0xf0,
   0x2a, 0x01, 0xe8, 0x5a, 0xe7, 0x29, 0xed, 0xd3, 0xae, 0x81, 0x2e, 0xa8, 0x16, 0xf0, 0x38, 0x6b,
   0x03, 0x49, 0xb3, 0x17, 0xec, 0x9c, 0xe4, 0xe5, 0x09, 0x07, 0x35, 0x2f, 0x98, 0xeb, 0x7e, 0xf4,
   0x27, 0xf0, 0x09, 0x6b, 0xb4, 0x9c, 0x5a, 0x8e, 0x7f, 0x03, 0xfd, 0xc7, 0x2e, 0x8a, 0x5d, 0x8d };

/* man manufacturer id */
const unsigned char manid[4] = { 0x1f, 0x22, 0, 0 };

void main(void)
{
#ifdef __16F88__
   OSCCON|=0x70;		/* 8mhz pls */
   while(!IOFS);		/* wait until freq is stable */

   TRISB2 = 0;		/* miso is the only output line */
   ANSEL = 0;			/* disable default analog input */

   /* setup serial port for spi slave mode
      davis wants cpol 1, clock is active LOW idle HIGH
      davis wants cpha 1, capture on clock RISE and send on clock FALL
      (or send on leading edge, sample on trailing edge) */
   SSPCON = 0x04;	/* spi slave with select enabled */
   SSPCONbits.CKP = 1;		/* cpol 1 */
   SSPSTATbits.CKE = 0;		/* cpha 1 */

   status.spidone = 1;
	 SSPIF=0;		   /* no spurious port non-interrupts please */
   SSPCONbits.SSPEN = 1;		/* serial port enable */
#endif

#ifdef __16F18313__
	 /* disable peripherals we don't need, default is all on */
	 PMD0 = 0x7f;									/* leave syscmd on, rest off */
	 PMD1 = 0xff;										/* all off */
	 PMD2 = 0xff;										/* all off */
	 PMD3 = 0xff;										/* all off */
	 PMD4bits.UART1MD = 1;				/* leave serial port on, but uart off */
	 PMD5 = 0xff;										/* all off */

	 ANSELA = 0;									/* disable default analog input */
	 TRISA5 = 0;									/* enable output for ra5, miso; rest remain inputs */

	 /* assign pins for our desired signal line routing:
			pin 2/ra5 miso, pin 3/ra4 clock, pin 5/ra2 select, pin 6/ra1 mosi */
	 RA5PPS = 0b11001;						/* miso out ra5 */
	 SSP1CLKPPS = 0b00100;				/* clock in ra4 */
	 SSP1DATPPS = 0b00001;				/* mosi in ra1 */
	 SSP1SSPPS = 0b00010;					/* select in ra2 */

	 /* setup serial port for spi slave
      davis wants cpol 1, clock is active LOW idle HIGH
      davis wants cpha 1, capture on clock RISE and send on clock FALL
      (or send on leading edge, sample on trailing edge) */
	 SSP1CON1bits.SSPM = 0x04;				/* spi slave, select enabled */
	 SSP1CON1bits.CKP = 1;					/* cpol 1 */
	 SSP1STATbits.CKE = 0;				/* cpha 1 */
	 SSP1CON3bits.BOEN = 1;				/* overwrite input buffer */

	 status.spidone = 1;
	 SSP1IF=0; 	 /* no spurious port non-interrupts please */
   SSP1CON1bits.SSPEN = 1;		/* serial port enable */
	 inbyte = SSPBUF;							/* clear any leftovers */
#endif

	 while (1)
   {
      while (!SSPIF);
      SSPIF = 0;
      inbyte = SSPBUF;

      if (status.spidone)
      {
				 if (inbyte == 0xd7)	/* chip status request */
				 {
						SSPBUF = 0x8c;
				 }
				 else if (inbyte == 0x77) 	/* start to send security register */
				 {
						SSPBUF = secregister[0];

						status.spidone = 0;
						status.secreg = 1;
						nextidx = 1;
				 }
				 /* 16f88 at 8mhz is too slow for any fancies */
#ifdef __16F18313__
				 else if (inbyte == 0x9f) /* start to send manufacturer id */
				 {
						SSPBUF = manid[0];
						
						status.spidone = 0;
						status.secreg = 0;
						nextidx = 1;
				 }
#endif
			}
      else
      {
#ifdef __16F18313__				 
				 if (status.secreg)
				 {
#endif
						SSPBUF = secregister[nextidx];
						++nextidx;
						if (nextidx == 131)
						{
							 status.spidone = 1;
						}
				 }
#ifdef __16F18313__				 
				 else
				 {
						SSPBUF = manid[nextidx];
						++nextidx;
						if (nextidx == 5)
						{
							 status.spidone = 1;
						}
				 }
#endif
      }
	 }
}
