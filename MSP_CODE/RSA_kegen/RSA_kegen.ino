#include <msp430.h>             

unsigned long long modular_multiplicative_inverse(unsigned long long E, unsigned long long PHI);
unsigned long long find_exponent(unsigned long long phi);

unsigned long long p;
unsigned long long q;

unsigned long long phi;
unsigned long long exponent;

unsigned long long publickey;
unsigned long long privatekey;

void setup()
{

  Serial.begin(9600); 

//  WDTCTL = WDTPW | WDTHOLD;       // Stop watchdog timer

// p = 41; q = 43;
//  p = 251; q = 241;                // 8 bit
//  p = 409; q = 983;                // 10 bit
//  p = 16007; q = 16193;  // 14 bit
//  p = 32749; q = 32719;  // 15 bit
//  p = 48619; q = 48623;            // 16 bit
//  p = 63313; q = 64747;
  p = 65519; q = 65521;
//  p = 157211; q = 167711;          // 18 bit
//  p = 975383; q = 695243;          // 20 bit 
//  p = 14384393; q = 15053471;      // 24 bit
//  p = 4158903607; q = 4165674413;  // 32 bit

  phi = (p-1) * (q-1);
  exponent = find_exponent(phi);
  publickey = p*q;
  
  privatekey = modular_multiplicative_inverse(exponent,phi);
  
  Serial.print("p = ");
  Serial.println((unsigned long)p);
  Serial.print("q = ");
  Serial.println((unsigned long)q);  
  Serial.print("publickey = ");
  Serial.println((unsigned long)publickey);
  Serial.print("exponent = ");
  Serial.println((unsigned long)exponent);
  Serial.print("private key = ");
  Serial.println((unsigned long)privatekey);
  Serial.println();

  return;

}

void loop(){}



