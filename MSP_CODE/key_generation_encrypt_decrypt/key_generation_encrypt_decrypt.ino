#include <msp430.h>             

#define BIT0 (0x0001)  
#define BIT6 (0x0040)

unsigned long long modular_exponentiation(unsigned long long cipher_text, unsigned long long exponent, unsigned long long publickey);
unsigned long long modular_multiplicative_inverse(unsigned long long E, unsigned long long PHI);

unsigned long long p;
unsigned long long q;
unsigned long long n;
unsigned long long phi;
unsigned long long exponent = 5;

unsigned long long plaintext = 30;
unsigned long long ciphertext = 0;
unsigned long long decrypted_plaintext = 0;

unsigned long long publickey;
unsigned long long privatekey;

void setup()
{
  
  Serial.begin(9600); 
  
  // put your setup code here, to run once:
   WDTCTL = WDTPW | WDTHOLD;       // Stop watchdog timer
    P1DIR |= (BIT0 | BIT6);                 // Set P1.0 to output direction
    P1OUT = 0;

//  p = 251; q = 241; exponent = 7;  // 8 bit
//  p = 409; q = 983;                // 10 bit
//  p = 48619; q = 48623;            // 16 bit
//  p = 157211; q = 167711;          // 18 bit
//  p = 975383; q = 695243;          // 20 bit 
//  p = 14384393; q = 15053471;      // 24 bit
//  p = 4158903607; q = 4165674413;  // 32 bit

  n = p*q;
  phi = (p-1) * (q-1); 
  
  publickey = n;
  
  privatekey = modular_multiplicative_inverse(exponent,phi);
  
  Serial.println("public key");
  Serial.println((unsigned long)publickey);
  Serial.println("private key");
  Serial.println((unsigned long)privatekey);

  // smaller test values
  // exponent = 17
  // public key = 3233
  // private key = 2753
  // plaintext = 65
  // ciphertext = 2790

  // larger
  // p = 409, q = 983
  // exponent = 5
  // public key = 402047
  // private key = 320525
  // plaintext = 30
  // ciphertext = 177180

  // encrypt

  // (plaintext^exponent) mod publickey
  // (PT^E) mod N
  ciphertext = modular_exponentiation(plaintext, exponent, publickey);

  // decrypt
  // (ciphertext^secretkey) mod publickey
  // (CT^D) mod N
  decrypted_plaintext = modular_exponentiation(ciphertext, privatekey, publickey);

  if(plaintext == decrypted_plaintext){
//  if(test_key == privatekey){
    // set the GREEN led
    P1OUT = BIT6;
  } else {
    // set the RED led
    P1OUT = BIT0;
  }

  //return 0;
    
}

void loop()
{
  // put your main code here, to run repeatedly:
  
}


unsigned long long modular_exponentiation (unsigned long long cipher_text, unsigned long long exponent, unsigned long long publickey){
  unsigned long long c = 1;
  unsigned long long e_prime = 0; // our counter variable
  while(e_prime < exponent){
      e_prime = e_prime + 1;
      if(e_prime % 1000 == 0){ Serial.println((unsigned long)e_prime); Serial.println((double)(100.0*((double)e_prime/(double)exponent))); }
//      if(e_prime % 2){
//       P1OUT = BIT0;
//      } else {
//       P1OUT = BIT6;
//      }
      c = c * cipher_text;
      c = c % publickey;
  }
  // c is the plaintext
  P1OUT = 0;
  return c;
}

unsigned long long modular_multiplicative_inverse(unsigned long long E, unsigned long long PHI){
  long long D  = 0;
  long long nt = 1;
  long long r = PHI;
  long long nr = E % PHI;

  // correct values to acceptable input range
  if (PHI < 0){
    PHI = -PHI;
  }
  if (E < 0){
    E = PHI - (-E % PHI);
  }

  // perform operations to calculate the MMI
  long long quot;
  long long tmp;
  while (nr != 0) {
    quot = (r/nr) | 0;
    tmp = nt;  
    nt = D - quot*nt;  
    D = tmp;
    tmp = nr;  
    nr = r - quot*nr;  
    r = tmp;
  }
  if (r > 1) { return -1; }
  if (D < 0) { D += PHI; }
  return (unsigned long long)D;
}
