#include "msp.h";

uint8_t Data[16] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };
uint8_t CipherKey[32] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f };
uint8_t DataAESencrypted[16];       // Encrypted data
uint8_t DataAESdecrypted[16];       // Decrypted data

void setup()
{
  // put your setup code here, to run once:
  volatile uint32_t i;

  uint16_t sCipherKey, tempVariable;
  WDTCTL = WDTPW | WDTHOLD;               // Stop WDT
  
  P1DIR |= BIT0;                          // P1.0 set as output
  P2DIR |= (BIT0 | BIT1 | BIT2);
  P2OUT |= (BIT2 | BIT1);                        // turn the blue and green LED on
//  P2OUT = (BIT0 | BIT1 | BIT2);
  
  P1OUT &= ~BIT0;                         // Turn off P1.0 LED

  /* Step 1: Load cipher key */
  AESACTL0 &= ~AESOP_3;                   // Set AES module to encrypt mode

  /* Set AES key length to 256 bits */
  AESACTL0 = AESACTL0 & (~(AESKL_1 + AESKL_2))  | AESKL__256BIT;

  /* Load 256-bit cipher key to the AESAKEY register */
  for(i = 0; i < 256/8; i = i + 2){
    /* Concatenate 2 8-bit blocks into one 16-bit block */
    sCipherKey =(uint16_t)(CipherKey[i]);
    sCipherKey = sCipherKey |((uint16_t)(CipherKey[i + 1]) << 8);
    /* Load 16-bit key block to AESAKEY register */
    AESAKEY = sCipherKey;
  }

  /* Wait until key is written */
  while((AESASTAT & AESKEYWR ) == 0);

  /* Step 2: Encrypt data and store to DataAESencrypted */
  /* Load 128-bit block of data to encrypt to module */
  for(i = 0; i < 16; i = i + 2){
    /* Concatenate 2 8-bit blocks into one 16-bit block */
    tempVariable = (uint16_t)(Data[i]);
    tempVariable = tempVariable | ((uint16_t)(Data[i + 1]) << 8);
    /* Load 16-bit key block to AESADIn register */
    AESADIN = tempVariable;
  }

  /* Initiate encryption by setting AESKEYWR to 1 */
  AESASTAT |= AESKEYWR;

  /* Wait unit finished ~167 MCLK */
  while( AESASTAT & AESBUSY );

  /* Write 128-bit block of encrypted data back to DataAESencrypted */
  for(i = 0; i < 16; i = i + 2){
    tempVariable = AESADOUT;
    DataAESencrypted[i] = (uint8_t)tempVariable;
    DataAESencrypted[i+1] = (uint8_t)(tempVariable >> 8);
  }

  /* Step 3: Reload AES key */
  /* Set AES module to decrypt mode */
  AESACTL0 |= AESOP_1;

  /* Set AES key length to 256 bits */
  AESACTL0 = AESACTL0 & (~(AESKL_1 + AESKL_2))  | AESKL__256BIT;
  
  /* Load 256-bit cipher key to the AESAKEY register */
  for(i = 0; i < 256/8; i = i + 2){
    /* Concatenate 2 8-bit blocks into one 16-bit block */
    sCipherKey =(uint16_t)(CipherKey[i]);
    sCipherKey = sCipherKey |((uint16_t)(CipherKey[i + 1]) << 8);
    /* Load 16-bit key block to AESAKEY register */
    AESAKEY = sCipherKey;
  }

  /* Wait until key is written */
  while((AESASTAT & AESKEYWR ) == 0);

  /*Step 4: Decrypt data with keys that were generated during encryption   
   * takes 214 MCLK.
   * This function will generate all round keys needed for decryption first
   * and then the encryption process starts */
   
  // Write 128-bit block of data to decrypt to module
  for (i = 0; i < 16; i = i + 2){
    tempVariable = (uint16_t) (DataAESencrypted[i + 1] << 8);
    tempVariable = tempVariable | ((uint16_t) (DataAESencrypted[i]));
    AESADIN = tempVariable;
  }

  /* Wait until finished ~167 MCLK */
  while(AESASTAT & AESBUSY){
//    P2OUT &= (BIT0);
  }
   

  /* Write 128-bit block of encrypted data back to DataAESdecrypted */
  for(i = 0; i < 16; i = i + 2){
    tempVariable = AESADOUT;
    DataAESdecrypted[i] = (uint8_t)tempVariable;
    DataAESdecrypted[i+1] =(uint8_t)(tempVariable >> 8);
  }

  /* Step 4: Confirm decrypted data is identical to original data */

  boolean all_good = true;
  for(i = 0; i < 16; i ++){
    if (DataAESdecrypted[i] != Data[i]){
      all_good = false;

    }
  }
  
  P1OUT |= BIT0;                          // Turn on P1.0 LED = success  

  if(!all_good){
    P2OUT = BIT0;  // error, red LED
  } else {
    P2OUT = BIT1;  // good, green LED
  }

}

void loop()
{
  // put your main code here, to run repeatedly:
  P2OUT ^= BIT0;
  delay(1000);

}


