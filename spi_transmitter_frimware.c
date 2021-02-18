/*
 * File:   spi_transmitter_frimware.c
 * Author: original
 * please visit my youtube channel:https://www.youtube.com/channel/UCzt_0MFbJiT93KSR74pW6Jw
 */

#include <xc.h>
#include <stdint.h>
#include "config.h"
#define _XTAL_FREQ 4000000
//--------------------------------
// Functions Declarations
void SPI_Master_Init(void);
void SPI_Write(uint8_t);
void SPI_Write_String(char *);
//--------------------------------
// Main Routine
void main(void) 
{
  //--[ Peripherals & IO Configurations ]--
  SPI_Master_Init(); // Initialize The SPI in Master Mode @ Fosc/64
  //---------------------------
  while(1) 
  {
    // Do Whatever You Want !
    // ...
  } 
  return;
}
//--------------------------------
// Functions Definitions
void SPI_Master_Init()
{
  // Set Spi Mode To Master + Set SCK Rate To Fosc/64 
  SSPM0 = 0;
  SSPM1 = 0;
  SSPM2 = 0;
  SSPM3 = 0;
  // Enable The Synchronous Serial Port
  SSPEN = 1;
  // Configure The Clock Polarity & Phase (SPI Mode Num. 1)
  CKP = 0;
  CKE = 0;
  // Configure The Sampling Time (Let's make it at middle) 
  SMP = 0;
  // Configure The IO Pins For SPI Master Mode
  TRISC5 = 0; // SDO -> Output
  TRISC4 = 1; // SDI -> Input
  TRISC3 = 0; // SCK -> Output
  // If Interrupts Are Needed, Un-comment The Line Below
  // SSPIE = 1; PEIE = 1; GIE = 1;
}
void SPI_Write(uint8_t Data)
{
  SSPBUF = Data; // Transfer The Data To The Buffer Register
  // while(!SSPSTATbits.BF); // Un-comment it if you're Not Using Interrupts!
  // The Above While Loop Protects Against Writing To The Buffer 
  // Before The Previous Transmission Ends
}
void SPI_Write_String(char *text)
{
  uint16_t i;
  for(i=0;text[i]!='\0';i++)
    SPI_Write(text[i]);
}