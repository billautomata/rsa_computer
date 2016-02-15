# every step
* `user` inputs `plaintext message` in `PANEL_A` to encrypt and presses **start**
* `PANEL_A` requests a `key-pair`
* `PANEL_B` generates a `PANEL_B key-pair`
* `PANEL_B` transmits the `PANEL_B public key`
* `NSA` intercepts the `PANEL_B public key`
* `PANEL_A` receives the `PANEL_B public key`
* `PANEL_A` encrypts the `plaintext message` with the `PANEL_B public key` to create the `ciphertext message`
* `PANEL_A` transmits the `ciphertext message` to `PANEL_B`
* `NSA` intercepts the `ciphertext message`
* `PANEL_B` decrypts the `ciphertext message` using the `PANEL_B private key` to create the `decrypted plaintext message`
* `NSA` factors the `PANEL_B public key`
* `NSA` generates the `cracked PANEL_B private key`
* `NSA` decrypts the `ciphertext message` with the `cracked PANEL_B private key` to create the `cracked plaintext message`
