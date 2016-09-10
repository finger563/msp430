#include <msp430.h>

void delay( unsigned int delay ) {
  unsigned int i;
  for (i = 0; i < delay; i++) asm("nop");
}

int main() {
  WDTCTL = WDTPW + WDTHOLD; // Stop WatchDogTimer (WDT)
  P1DIR |= BIT6; // P1.6 is LED 2 on the board

  while(1) {
    P1OUT ^= BIT6;
    delay( 50000 );
  }

  return 0;
}
