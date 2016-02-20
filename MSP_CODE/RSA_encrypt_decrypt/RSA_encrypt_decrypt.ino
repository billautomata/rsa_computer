#include <msp430.h>             

unsigned long long ipow(unsigned long long b, unsigned long long e);
unsigned long long fme(unsigned long long a, unsigned long long b, unsigned long long c);

unsigned long long exponent;
unsigned long long publickey;
unsigned long long privatekey;

unsigned long long plaintext = 30;
unsigned long long ciphertext = 0;
unsigned long long decrypted_plaintext = 0;

void setup()
{
  
  Serial.begin(9600); 

  P1DIR |= (BIT0 | BIT6);                 // Set P1.0 to output direction
  P1OUT = 0;
  
  // smaller test values
  // exponent = 3
  // publickey = 3233
  // privatekey = 2753
  // plaintext = 65
  // ciphertext = 2790

  // larger
  // p = 409, q = 983
  // 14 bit
//   exponent = 3; publickey = 259201351; privatekey = 172779435;
   
  // 15 bit
//   exponent = 5; publickey = 1071514531; privatekey = 214289813;
   exponent = 35801; publickey = 1071514531; privatekey = 301673321;
   
  // 16 bit
//  exponent = 19; publickey = 4292870399; privatekey = 3840872059;
//  exponent = 65413; publickey = 4292870399; privatekey = 3149155117;
  
   plaintext = 30;

  // encrypt

  // (plaintext^exponent) mod publickey
  // (PT^E) mod N
  Serial.println("Encrypting... ");
  ciphertext = fme(plaintext, exponent, publickey);

//  Serial.println("Cipher Text");
//  Serial.println((unsigned long)ciphertext);
  
  // decrypt
  // (ciphertext^secretkey) mod publickey
  // (CT^D) mod N
  Serial.println("Decrypting... ");
  decrypted_plaintext = fme(ciphertext, privatekey, publickey);

//  Serial.println("Plain Text");
//  Serial.println((unsigned long) plaintext);
//  Serial.println("Decrypted Plain Text");
//  Serial.println((unsigned long) decrypted_plaintext);
    
  if(plaintext == decrypted_plaintext){
    // set the GREEN led
    P1OUT = BIT6;
  } else {
    // set the RED led
    P1OUT = BIT0;
  }
}

void loop(){}

//unsigned long long modular_exponentiation (unsigned long long cipher_text, unsigned long long exponent, unsigned long long publickey){
//  unsigned long long c = 1;
//  unsigned long long e_prime = 0; // our counter variable
//  while(e_prime < exponent){
//      e_prime = e_prime + 1;
//      if(e_prime % 100000 == 0){ Serial.println((unsigned long)e_prime); Serial.println((double)(100.0*((double)e_prime/(double)exponent))); }
////      if(e_prime % 2){
////       P1OUT = BIT0;
////      } else {
////       P1OUT = BIT6;
////      }
//      c = c * cipher_text;
//      c = c % publickey;
//  }
////  P1OUT = 0;
//  // c is the plaintext  
//  return c;
//}

//unsigned long long modular_multiplicative_inverse(unsigned long long E, unsigned long long PHI){
//  long long D  = 0;
//  long long nt = 1;
//  long long r = PHI;
//  long long nr = E % PHI;
//
//  // correct values to acceptable input range
//  if (PHI < 0){
//    PHI = -PHI;
//  }
//  if (E < 0){
//    E = PHI - (-E % PHI);
//  }
//
//  // perform operations to calculate the MMI
//  long long quot;
//  long long tmp;
//  while (nr != 0) {
//    quot = (r/nr) | 0;
//    tmp = nt;  
//    nt = D - quot*nt;  
//    D = tmp;
//    tmp = nr;  
//    nr = r - quot*nr;  
//    r = tmp;
//  }
//  if (r > 1) { return -1; }
//  if (D < 0) { D += PHI; }
//  return (unsigned long long)D;
//}

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
