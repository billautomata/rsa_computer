# every step diffie hellman

* 2 user computers, interactive
* 1 internet computer, non-interactive
* 1 NSA computer, non-interactive

## user computer
* 16 x 24 led display
* potentiometer labeled `message rate`,
  * governs the number of messages per second generated
* switch labeled one-time pad
  * governs whether or not messages are always encrypted with fresh keys

#### post message
1. request the public key of the other user from the key server
2. generate new key-pair (g, p, private, public)
3. store key-pair in EEPROM (g, p, private, public)
4. generate shared secret from other user public key and our new secret key
5. encrypt message symmetrically with shared secret
6. post message, our public key, and associated public key to message server
  * (`msg`, `g`, `p`, `our_public`, `their_public`)

#### get message
1. request message from message server
  * (`msg`, `g`, `p`, `our_public`, `their_public`)
2. find related stored `private_key` looking up using `our_public`
3. generate shared secret using `their_public` and `private_key`
  * `(their_public ^ private_key) mod p` = `shared secret`
4. decrypt `msg` with `shared secret`

## NSA computer

#### get message
1. request a message from the internet
  * (`msg`, `g`, `p`, `public_a`, `public_b`)
2. crack either `public_a` or `public_b`
  * crack `private_a` from `public_a`, `g`, and `p`.
    * calculate the `shared secret` = `(public_b ^ private_a) mod p`
  * crack `private_b` from `public_b`, `g`, and `p`.
    * calculate the `shared secret` = `(public_a ^ private_b) mod p`
3. decrypt `msg` with `shared secret`
4. store (`g`,`p`,`private_a`, `public_a`)
  * start generating messages on the internet encrypted with `private_a`
