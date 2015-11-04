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
#define _XTAL_FREQ 8000000	/* max speed that the 16f88 can do by itself */


#pragma config CPD=OFF, CP=OFF, DEBUG=OFF, WRT=OFF, LVP=OFF, BOREN=OFF, PWRTE=ON, MCLRE=OFF, WDTE=OFF
#pragma config FOSC=INTOSCIO, IESO=OFF, FCMEN=OFF

/* signal lines: pin 7/rb1 mosi, pin8/rb2 miso, pin 10/rb4 clock, pin 11/rb5 select */
#define SELECT PORTBbits.RB5
#define CLOCK PORTBbits.RB4

static unsigned char inbyte, nextidx;
static struct {
   unsigned char spidone:1;
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

void main(void)
{
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
	 else if (inbyte == 0x77) 	/* read security register */
	 {
	    SSPBUF = secregister[0];
	       
	    status.spidone = 0;
	    nextidx = 1;
	 }
      }
      else /* implicit if (status.insecreg) */
      {
	 SSPBUF = secregister[nextidx];
	 ++nextidx;
	 if (nextidx == 131)
	 {
	    status.spidone = 1;
	 }
      }
   }
}
