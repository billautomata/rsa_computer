```javascript

function modular_exponentiation (cipher_text, exponent, publickey) {
  c = 1
  e_prime = 0 // our counter variable
  while(e_prime < exponent){
    e_prime = e_prime + 1
    if (e_prime % 2) {
      P1OUT = BIT0
    } else {
      P1OUT = BIT6
    }
    c = c * cipher_text
    c = c % publickey
  }
  // c is the plaintext
  P1OUT = 0
  return c
}


function modular_multiplicative_inverse (E, PHI) {
  var D = 0
  var nt = 1
  var r = PHI
  var nr = E % PHI

  // correct values to acceptable input range
  if (PHI < 0) {
    PHI = -PHI
  }
  if (E < 0) {
    E = PHI - (-E % PHI)
  }

  // perform operations to calculate the MMI
  var quot
  var tmp
  while (nr != 0) {
    quot = (r / nr) | 0
    tmp = nt
    nt = D - quot * nt
    D = tmp
    tmp = nr
    nr = r - quot * nr
    r = tmp

    panel_NT(nt)
    panel_R(r)
    panel_NR(nr)
    panel_tmp(tmp)
    panel_QUOT(quot)
    panel_D(D)
  }
  if (r > 1) { return -1; }
  if (D < 0) { D += PHI; }
  panel_R(r)
  panel_D(D)
  return D
}
```
