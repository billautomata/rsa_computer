# [Diffie Hellman Key Exchange](https://en.wikipedia.org/wiki/Diffie%E2%80%93Hellman_key_exchange)

Key generation is easier, you just pick a number.  It doesn't have to be prime, just large.  There is also a pre-agreed upon group of numbers used in the equation.  Published as a spec.

### keygen, me
```javascript
// the agreed upon prime components
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


### cracking the keys
Then NSA then needs to find the value for `secret` in the equation.
```
8 = ( 5 ^ x ) mod 23
// solve for x
```
It does that by brute force, performing the equation with values for `x` to see if they equal `8`.
```
// cracking the secret number, using only the public parts
x=1, 5^1 mod 23 = 5   XX (8 != 5)
x=2, 5^2 mod 23 = 2   XX (8 != 2)
x=3, 5^3 mod 23 = 10  XX (8 != 10)
x=4, 5^4 mod 23 = 4   XX (8 != 4)
x=5, 5^5 mod 23 = 20  XX (8 != 20)
x=6, 5^6 mod 23 = 8   !! (8 == 8)
```

### keygen, you
Now let's generate your keys -- just like mine.
```javascript
your_secret_number = 15;
your_public_number = (g ^ secret) mod p
your_public_number = (5 ^ 15) mod 23
your_public_number = 19
```

You then publish, `(19, 5, 23)` as your public key.

_Note_: We both use the same values for `p` and `g`.  These are called the **group**.  The **group** is published as a spec.  We can hardcode the values for `p` and `g`.


### using the keys, together
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

#### important point
We do not encrypt with the keys, using our private number and the other persons public number, we arrive at the same value together. We use that value to encrypt data symmetrically.

#### secrecy chart

![screen shot 2016-02-19 at 9 35 08 pm](https://cloud.githubusercontent.com/assets/432483/13194712/aeabc59e-d750-11e5-843d-75ee06f5cc81.png)

## cracking stats

### MSP430 benchmarks
An MSP430 can perform `~188 tries / second`.
#### estimates
* Cracking a `24 bit` secret number would take `19 days`
* Cracking a `16 bit` secret number would take `~5 minutes`

#### benchmarks
* Cracking `65519` a `16 bit number` took `6 minutes 58 seconds`
* Cracking `167711` a `18 bit number` took `18 minutes 47 seconds` (144/sec)

### MSP432 benchmarks
#### estimates
An MSP432 can perform `4000 - 8000 tries / second`

#### benchmarks
* Cracking `65519` a `16 bit number` took `8 seconds`
* Cracking `167711` a `18 bit number` took `35 seconds`
