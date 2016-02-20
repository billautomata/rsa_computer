#include <msp430.h>             

unsigned long long ipow(unsigned long long b, unsigned long long e);
unsigned long long fme(unsigned long long a, unsigned long long b, unsigned long long c);

unsigned long long p = 23;
unsigned long long g = 5;
unsigned long long alice_secret = 14384393;
unsigned long long alice_public;
unsigned long long bob_secret = 15053471;
unsigned long long bob_public;

void setup()
{
  
  p = 157211; g = 167711;
  
  Serial.begin(9600); 

  P1DIR |= (BIT0 | BIT6);                 // Set P1.0 to output direction
  P1OUT = 0;
  
  alice_public = fme(g, alice_secret, p);
  bob_public = fme(g, bob_secret, p);
    
  if(fme(bob_public,alice_secret,p) == fme(alice_public, bob_secret, p)){
    // set the GREEN led
    P1OUT = BIT6;
  } else {
    // set the RED led
    P1OUT = BIT0;
  }
}

void loop(){}


unsigned long long ipow(unsigned long long b, unsigned long long e)
{
  // this breaks for values > 32
    unsigned long long result = 1;
    while (e != 0)
    {
        if (e & 1)
            result *= b;
        e >>= 1;
        b *= b;
    }
 return result;
}
