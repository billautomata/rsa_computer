# rsa_computer
msp430 based rsa computer


## key generation

1. Choose two prime numbers, P & Q.

```
P = 409
Q = 983
```

2. Multiply them to get N, one half of your public key.

```
N = P * Q
N = 409 * 983
N = 402047
```

3. Compute the totient of N, PHI.

```
PHI = (P-1) * (Q-1)
PHI = 409-1 * 983-1
PHI = 408 * 982
PHI = 400656
```

4. Compute E, the second half of the public key, by choosing a small prime number that does not divide PHI evenly.

```
check 2, 400656 / 2 = 200328 [X]
check 3, 400656 / 3 = 133552 [X]
check 5, 400656 / 5 = 80131.2 - bingo!

E = 5
```

5. Compute D, the secret key.

```
D = e^-1 ( mod PHI )
```

A numeric solution lives in the form of this function.

```c++
int modular_multiplicative_inverse(E, PHI){
  int D  = 0;
  int nt = 1;
  int r = PHI;
  int nr = E % PHI;

  // correct values to acceptable input range
  if (PHI < 0){
    PHI = -PHI;
  }
  if (E < 0){
    E = PHI - (-E % PHI);
  }

  // perform operations to calculate the MMI
  int quot;
  int tmp;
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
  return D;
}
```

```c++
D = modular_multiplicative_inverse(5, 400656)
D = 320525
```

## encrypt

Choose an integer to represent the bytes of your plain-text message, PT.

```
PT = 30
```

Create the cipher-text (CT) from the plain-text (PT) and the public key (E, N)

```
CT = PT^E mod N
CT = 30^5 mod 40247
CT = 117180
```
[wolfram alpha link to results of this calculation](http://www.wolframalpha.com/input/?i=30%5E5+mod+40247)

## decrypt

The decryption routine is similar but involves much larger numbers.

```
PT = CT^D mod N
PT = 117180^320525 mod 402047
```

`117180^320525` cannot fit into memory.  It is a 1.6 million digit long number.

There is a memory efficient algorithm to perform the `CT^D mod N` calculation.

```c++
// memory efficient modular exponentiation for MSP430
//
// calculate PT, where - (CT^E) mod N = PT
// CT is the ciphertext
// E is the secret key
// N the the public key

//
// (CT^E) could be huge, thousands of digits, so we use this algorithm to calculate the value of PT
// after performing 'E' routines.  In this case 320525 iterations of the while loop are performed.

// this is a memory efficient encrypt and decrypt operations
#define BIT0 (0x0001)
#define BIT6 (0x0040)

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer
	P1DIR |= (BIT0 | BIT6);					// Set P1.0 to output direction
	P1OUT = 0;


  // exponent = 5
  // public key = 402047
  // private key = 320525

  // encrypt
  unsigned int plaintext = 30;

  // (plaintext^exponent) mod publickey
  // (PT^E) mod N
  unsigned int CT = modular_exponentiation(plaintext, 5, 402047)

  // CT = 117180

  // decrypt
  // (ciphertext^secretkey) mod publickey
  // (CT^D) mod N
  unsigned int decrypted_plaintext = modular_exponentiation(CT, 320525, 402047)

  if(plaintext == decrypted_plaintext){
    // set the GREEN led
    P1OUT = BIT6;
  } else {
    // set the RED led
    P1OUT = BIT0;
  }

	return 0;
}

unsigned int modular_exponentiation(unsigned int CT, unsigned int E, unsigned int N){
  unsigned int c = 1;
  //unsigned int CT = 4;
  //unsigned int E = 13;
  unsigned int e_prime = 0; // our counter variable
  //unsigned int N = 497;
	while(e_prime < E){
		e_prime = e_prime + 1;
		c = c * b;
		c = c % m;
	}
  // c is the plaintext
  return c;
}

```
