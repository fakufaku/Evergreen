
#include <avr/io.h>
#include <avr/interrupt.h>
#include <limits.h>
#include <stdlib.h>

// We assume 1MHz CPU clock, no prescaler
#define US_PER_OVF 256

// The timer global variables
unsigned long ms_timer = 0;
unsigned long us_timer = 0;

// The timer overflow interrupt routine
SIGNAL(TIMER0_OVF_vect)
{
  us_timer += US_PER_OVF;

  if (us_timer >= 1000)
  {
    ms_timer += 1;
    us_timer = (us_timer % 1000);
  }
}

// This routine does nothing for L ms
void wait(unsigned int L)
{
  unsigned long start = ms_timer;
  unsigned long elapsed;
  do
  {
    elapsed = ms_timer - start;
    if (elapsed < 0)
      elapsed = ULONG_MAX + elapsed;
  }
  while (elapsed < L);
}

// LED Routine main switch
#define MAX_ROUTINE 6;
int routine = 0;

// LED Routine 0
void routine0()
{
  int i;
  for (i = 4 ; i >= 0 ; i--)
  {
    PORTB = (1 << i);
    wait(500);
  }
}

// LED Routine 1
// yellow top on, all other four randomly
void routine1()
{
  PORTB = (1 << 4) | (1 << (random() % 4));
  wait((random() % 30) * 5 + 50);
}

// LED Routine 2
// yellow top on, other alternated
void routine2()
{
  PORTB = (1 << 4) | (1 << 0) | (1 << 2);
  wait(500);
  PORTB = (1 << 4) | (1 << 1) | (1 << 3);
  wait(500);
}

// LED Routine 3
// yellow top on, other alternated 2
void routine3()
{
  PORTB = (1 << 4) | (1 << 0);
  wait(500+(random() % 100)-50);
  PORTB = (1 << 4) | (1 << 1) | (1 << 3);
  wait(500+(random() % 100)-50);
  PORTB = (1 << 4) | (1 << 1) | (1 << 2);
  wait(500+(random() % 100)-50);
  PORTB = (1 << 4) | (1 << 3);
  wait(500+(random() % 100)-50);
  PORTB = (1 << 4) | (1 << 2) | (1 << 0);
  wait(500+(random() % 100)-50);
  PORTB = (1 << 4) | (1 << 1) | (1 << 2);
  wait(500+(random() % 100)-50);
}

// LED Routine 4
// Accelerating spiral
void routine4()
{
  int delay = 200;
  int i;
  while (delay > 0)
  {
    for (i = 4 ; i >= 0 ; i--)
    {
      PORTB = (1 << i);
      wait(delay);
    }
    delay = 10*delay/11;
  }
}

// LED Routine 5
// yellow top on, other alternated 2
void routine5()
{
  int delay = 20;
  int i;
  for (i = 4 ; i >= 0 ; i--)
  {
    PORTB = (1 << i);
    wait(delay);
  }
}

int main()
{
  // enable interrupts
  sei();

  // set all pins as output
  DDRB = (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3) | (1 << DDB4);

  // set up timer
  TCCR0A = 0x00;
  TCCR0B = (1 << CS00);   // set clock to clk/1
  TIMSK = (1 << TOIE0);   // set the overflow interrupt

  // turn off all IO to start
  PORTB = 0;

  // random first routine
  routine = random() % MAX_ROUTINE;

  // the variable for probability of changing routines (1/p)
  int p = 10;

  // The infinite loop
  while (1)
  {
    switch (routine)
    {
      default:
      case 0:
        routine0();
        p = 10;
        break;
        
      case 1:
        routine1();
        p = 120;
        break;

      case 2:
        routine2();
        p = 36;
        break;

      case 3:
        routine3();
        p = 12;
        break;

      case 4:
        routine4();
        p = 2;
        break;

      case 5:
        routine5();
        p = 360;
        break;
    }

    // randomize!
    if ((random() % p) == 0)
      routine = random() % MAX_ROUTINE;
  }

}
