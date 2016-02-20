unsigned long long find_exponent(unsigned long long phi){
//  unsigned long long possible_exponents[16] = { 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59 };
//  unsigned long long possible_exponents[12] = { 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59 };
//  unsigned long long possible_exponents[10] = { 35801, 35803, 35809, 35831, 35837, 35839, 35851, 35863, 35869, 35879 };
  unsigned long long possible_exponents[10] = {   65413, 65419, 65423, 65437, 65447, 65449, 65479, 65497, 65519, 65521 };
  unsigned long long exponent;
  boolean exponent_found = false; 
  uint8_t exponent_index = 0;
  while(!exponent_found){
    if(phi % possible_exponents[exponent_index] != 0){
      exponent = possible_exponents[exponent_index];
      exponent_found = true;
    } else {
      exponent_index++;
      if(exponent_index >= 16){
        Serial.println("No good exponent found.");
        return 0;
      }
    }
  }
  return exponent;
}
