https://en.wikipedia.org/wiki/Diffie%E2%80%93Hellman_key_exchange

Key generation is easier, you just pick a number.  It doesn't have to be prime, just large.  There is also a pre-agreed upon group of numbers used in the equation.  Published as a spec.

```javascript
// the agreed upon components
p = 23
g = 5
```

```javascript
my_secret_number = 6;
my_public_number = (g ^ secret) mod p
my_public_number = (5 ^ 6) mod 23
my_public_number = 8
```
I then publish, `(8, 5, 23)` as my key.

Then NSA then needs to find the value for `secret` in the equation.
```
8 = ( 5 ^ x ) mod 23
// solve for x
```
It does that by brute force, performing the equation with values for `x` to see if they equal `8`.

```
// cracking the secret number, using only the public parts
x=1, 5^1 mod 23 = 5
x=2, 5^2 mod 23 = 2
x=3, 5^3 mod 23 = 10
x=4, 5^4 mod 23 = 4
x=5, 5^5 mod 23 = 20
x=6, 5^6 mod 23 = 8
```

```javascript
your_secret_number = 15;
your_public_number = (g ^ secret) mod p
your_public_number = (5 ^ 15) mod 23
your_public_number = 19
```

You then publish, `(19, 5, 23)` as your public key.

You take my public key `(8, 5, 23)` and combine it with your secret number `15` to create
```
(my_public_key[0] ^ your_secret_number) mod my_public_key[2]
(8 ^ 15) mod 23 = 2
2, is our secret.
```
I take your public key `(19, 5, 23)` and combine it with my secret number `6` to create
```
(your_public_key[0] ^ my_secret_number) mod my_public_key[2]
(19 ^ 6) mod 23 = 2
2, is our secret.
```

```
// all combined
(my_public_key ^ your_secret_number) mod 23 = (your_public_key ^ my_secret_number) mod 23
```

# We do not encrypt with the keys, we arrive at the same value together, using the other persons public key and our private key.  We use that value to encrypt the data symmetrically.

![screen shot 2016-02-19 at 9 35 08 pm](https://cloud.githubusercontent.com/assets/432483/13194712/aeabc59e-d750-11e5-843d-75ee06f5cc81.png)
