// #define __MSP430
#define __MSP432

#ifdef __MSP430
  #include <msp430.h>           
  #define _redled 2
  #define _greenled 14
#endif
#ifdef __MSP432
  #include <msp432.h>           
  #define _redled 78
  #define _greenled 76
#endif

unsigned long long ipow(unsigned long long b, unsigned long long e);
unsigned long long fme(unsigned long long a, unsigned long long b, unsigned long long c);

unsigned long long p = 23;
unsigned long long g = 5;         
unsigned long long alice_secret = 67108864;
unsigned long long alice_public;
unsigned long long bob_secret = 12582912;  // 24 bit
unsigned long long bob_public;

void setup()
{
  
  p = (157211*2)+1; g = 5;  // good (good with 65519, and 167711)
  
  Serial.begin(9600); 
  delay(100);

  pinMode(_redled, OUTPUT);
  pinMode(_greenled, OUTPUT);
  digitalWrite(_redled, HIGH);
  digitalWrite(_greenled, LOW);  
  
  alice_public = fme(g, alice_secret, p);
  bob_public = fme(g, bob_secret, p);
    
  if(fme(bob_public,alice_secret,p) == fme(alice_public, bob_secret, p)){
    // set the GREEN led
    digitalWrite(_greenled, HIGH);
    digitalWrite(_redled, LOW);
  } else {
    // set the RED led
    digitalWrite(_greenled, LOW);
    digitalWrite(_redled, HIGH);    
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
