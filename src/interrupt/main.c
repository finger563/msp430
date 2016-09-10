#include <msp430.h>
#include <stdint.h>

void Port1Int( void ) __attribute__( ( interrupt( PORT1_VECTOR ) ) );
void TimerA0Int( void ) __attribute__( ( interrupt( TIMER0_A0_VECTOR ) ) );

uint16_t counter = 0;
uint16_t seconds = 0;

int main() {
  WDTCTL = WDTPW + WDTHOLD; // Stop WatchDogTimer (WDT)

  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL = CALDCO_1MHZ;

  TA0CCR0 = 25000;
  TA0CCTL0 = CCIE;
  
  P1DIR &= ~BIT3;
  P1REN |= BIT3;
  P1IES |= BIT3;
  P1IFG &= ~BIT3;
  P1IE |= BIT3;

  P1DIR |= BIT0 | BIT6; // P1.6 is LED 2 on the board
  P1OUT &= ~( BIT0 | BIT6 );

  __bis_SR_register( GIE );

  while(1) {
  }

  return 0;
}

void Port1Int(void) {
  switch(P1IFG & BIT3) {
  case BIT3:
    P1IFG &= ~BIT3;
    TA0CTL = TASSEL_2 | ID_2 | MC_1; // run timer
    break;
  }
}

void TimerA0Int(void) {
  P1OUT ^= BIT6;
  if ( counter == 5 ) {
    counter = 0;
    seconds++;
    P1OUT ^= BIT0;
    if (seconds > 7) {
      TA0CTL = 0; // stop timer
      seconds = 0;
    }
  }
  counter++;
}
