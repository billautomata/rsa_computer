How can we calculate A^B mod C quickly for any B ?

ex `5^117 mod 19`

Step 1: Divide B into powers of 2 by writing it in binary

`117` = `1110101` in binary

Start at the rightmost digit, let k=0 and for each digit:

If the digit is 1, we need a part for 2^k, otherwise we do not
Add 1 to k, and move left to the next digit

```
117 = 2^0 + 2^2 + 2^4 + 2^5 + 2^6
117 = 1 + 4 + 16 + 32 + 64
```


```
5^117 mod 19 = 5^(1+4+16+32+64) mod 19
5^117 mod 19 = (5^1 * 5^5 * 5^16 * 5^32 * 5^64) mod 19
```

Step 2: Calculate mod C of the powers of two ≤ B, even the ones that aren't useful.
```
5^1 mod 19 = 5

5^2 mod 19 = (5^1 * 5^1) mod 19 = (5^1 mod 19 * 5^1 mod 19) mod 19
5^2 mod 19 = (5 * 5) mod 19 = 25 mod 19
5^2 mod 19 = 6

5^4 mod 19 = (5^2 * 5^2) mod 19 = (5^2 mod 19 * 5^2 mod 19) mod 19
5^4 mod 19 = (6 * 6) mod 19 = 36 mod 19
5^4 mod 19 = 17

5^8 mod 19 = (5^4 * 5^4) mod 19 = (5^4 mod 19 * 5^4 mod 19) mod 19
5^8 mod 19 = (17 * 17) mod 19 = 289 mod 19
5^8 mod 19 = 4

5^16 mod 19 = (5^8 * 5^8) mod 19 = (5^8 mod 19 * 5^8 mod 19) mod 19
5^16 mod 19 = (4 * 4) mod 19 = 16 mod 19
5^16 mod 19 = 16

5^32 mod 19 = (5^16 * 5^16) mod 19 = (5^16 mod 19 * 5^16 mod 19) mod 19
5^32 mod 19 = (16 * 16) mod 19 = 256 mod 19
5^32 mod 19 = 9

5^64 mod 19 = (5^32 * 5^32) mod 19 = (5^32 mod 19 * 5^32 mod 19) mod 19
5^64 mod 19 = (9 * 9) mod 19 = 81 mod 19
5^64 mod 19 = 5
```
Step 3: Use modular multiplication properties to combine the calculated mod C values
```
5^117 mod 19 = ( 5^1 * 5^4 * 5^16 * 5^32 * 5^64) mod 19
5^117 mod 19 = ( 5^1 mod 19 * 5^4 mod 19 * 5^16 mod 19 * 5^32 mod 19 * 5^64 mod 19) mod 19
5^117 mod 19 = ( 5 * 17 * 16 * 9 * 5 ) mod 19
5^117 mod 19 = 61200 mod 19 = 1
5^117 mod 19 = 1
```
