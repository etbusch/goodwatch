/*! \file sidebutton.c
  \brief Sidebutton driver.

  P1.5 is the Mode button and P1.6 is the Set button.  We leave them
  in input mode, then briefly check by direct scanning.
   
  Additionally, the buttons need to be emulated on the keypad, as
  they are taken by the serial port on debugging units.  Hold / and *
  for Mode, + and - for Set.
  
  The sidebuttons will be deactivated when the UART's first
  transaction occurs.
*/

#include <stdint.h>
#include <msp430.h>

#include "keypad.h"
#include "uart.h"


//! Activate the side butons.
void sidebutton_init(){
  //Both are I/O inputs.
  P1SEL&=~(BIT5|BIT6);
  P1DIR&=~(BIT5|BIT6);
  //Pull both up with internal resistors.
  P1REN|=(BIT5|BIT6); 
  P1OUT|=(BIT5|BIT6);
}

//! Test the Mode button.
int sidebutton_mode(){
  //Side button.
  if(!uartactive && !(P1IN&BIT5))
    return 1;

  //Emulation.
  if(key_scan()==0x31)
    return 1;
  return 0;
}

//! Test the Set button.
int sidebutton_set(){
  //Side button.
  if(!uartactive && !(P1IN&BIT6))
    return 1;

  //Emulation.
  if(key_scan()==0xC1)
    return 1;
  return 0;
}
