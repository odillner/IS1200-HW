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



/* Interrupt Service Routine */
void user_isr( void )
{
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

  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  volatile int* PORTE_ADR = 0xBF886110;
  *PORTE_ADR = *PORTE_ADR + 1;
  
  delay( 1000 );

  int btns = getbtns();
  if (btns>0) {
    int sw = getsw();
    if (btns&1){
       mytime = (mytime&(~0xf0))|(sw<<4);
    }
    if (btns&2){
       mytime = (mytime&(~0xf00))|(sw<<8);
    }
    if (btns&4){
       mytime = (mytime&(~0xf000))|(sw<<12);
    }
    
  }
  
  time2string( textstring, mytime );
  display_string( 3, textstring );
  display_update();
  tick( &mytime );
  display_image(96, icon);
}
