#define NBITS 62

unsigned long long fme(unsigned long long a, unsigned long long b, unsigned long long c){
  
//  Serial.println("calling fme on");
//  Serial.print((long)a); Serial.print(' ');
//  Serial.print((long)b); Serial.print(' ');
//  Serial.println((long)c); 

  // fast decrypt
  // fast_mod_expo(a,b,c)
  //  unsigned long long a = ciphertext;
  //  unsigned long long b = privatekey;
  //  unsigned long long c = publickey;
  
//  Serial.println("Private key in binary");
//  int binary_digit = 0;

//  for(int ii = 63; ii >= 0; ii--){
//    binary_digit = (int)bitRead(b,ii);
//    Serial.print(binary_digit);
//  }
//  Serial.println();

  // find the highest binary position with a value of 1
  unsigned long long highest_index = 0;
  uint8_t ii, n, binary_digit;
  
  for(ii = 0; ii < NBITS; ii++){
    binary_digit = (int)bitRead(b,ii);
    if(binary_digit == 1){
      highest_index = ii;
    }
  }
//  Serial.println();
//  Serial.println("Max Index");
//  Serial.println((unsigned long)highest_index);
  highest_index+=1;
//  return 0;
  
  unsigned long long pow_two_mod_c[highest_index];
  unsigned long long pval;
  
  for(n = 0; n < highest_index; n++){
//    Serial.println(n);
    if(n == 0){
      pow_two_mod_c[n] = ipow(a, 1) % c;
    } else {
      pval = pow_two_mod_c[n-1];
      pow_two_mod_c[n] = (pval*pval) % c;
    }
    
  }
//  Serial.println("Each value in pow_two_mod_c");
  for(n = 0; n < highest_index; n++){
//    Serial.print(n);
//    Serial.print(' ');
//    Serial.println((unsigned long)pow_two_mod_c[n]);
  }

  
  // calculate (a^(2^n)) % c for every possible digit in the binary value, regardless if there is a 1 or not in that slot
  // building the exponents to be used in the next step for each of the binary positions that there is a one found
  // calculate the LUT for each 1 found in the binary string 
  // step through each value in the binary representation, and build the decryption value
  // 

  unsigned long long running_value = 1;  
  for(ii = 0; ii < NBITS; ii++){
    binary_digit = (int)bitRead(b,ii);
    if(binary_digit == 1){
      running_value = running_value * pow_two_mod_c[ii];
      running_value = running_value % c;
//      Serial.print((unsigned long)ii); Serial.print(' ');
//      Serial.println((unsigned long)running_value);
    }
  }
//  Serial.println("Final Value");
//  Serial.println((unsigned long)running_value);
  return running_value;
  
}
