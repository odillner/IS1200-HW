/* mipslabwork.c

   This file written 2015 by F Lundevall

   This file should be changed by YOU! So add something here:

   This file modified 2015-12-24 by Ture Teknolog 

   Latest update 2015-08-28 by F Lundevall

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5957;
char textstring[] = "text, more text, and even more text!";

int timeoutcount = 0;
int prime = 1234567;



/* Interrupt Service Routine */
#pragma interrupt user_isr
void user_isr(void){
  if (((IFS(0)>>8)&0xf)==1) {
    IFSCLR(0) = 0x0100;
    timeoutcount++;

    if (timeoutcount==10) {
      timeoutcount = 0;
      time2string( textstring, mytime );
      display_string( 3, textstring );
      display_update();
      tick( &mytime );
    }
  }
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  /*init input ports*/
  volatile int* TRISE_ADR = (int*) 0xBF886100;
  volatile int* PORTE_ADR = (int*) 0xBF886110; 
  volatile int* TRISD_ADR = (int*) 0xBF8860C0; 

  *TRISE_ADR = (*TRISE_ADR) & (~0x11111111);
  *PORTE_ADR = 0;
  *TRISD_ADR = (*TRISD_ADR) | (111111100000);

  /*init timer2 and interrupts*/
  T2CON = 0x0;                /*clear config*/
  TMR2 = 0x0;                 /*clear timer*/
  PR2 =  30472; ;          

  IFSCLR(0) = 0x0100;         /*clear interrupt flag*/
  IECCLR(0) = 0x0100;         /*clear enable interrupts*/
  IPCCLR(2) = 0x001f;         /*clear timer2 priority field*/ 
  IPCSET(2) = 0x0010;         /*set priority to 4*/
  IPCSET(2) = 0x0000;         /*set subpriority to 0*/
  IECSET(0) = 0x0100;         /*enable timer2 interrupts*/


  enable_interrupt();         /*enable global interrupts*/
  T2CONSET = 0x8070;          /*start timer and enable prescaling 1:256*/
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
 prime = nextprime( prime );
 display_string( 0, itoaconv( prime ) );
 display_update();
}
