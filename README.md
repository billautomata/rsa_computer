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

## decrypt
