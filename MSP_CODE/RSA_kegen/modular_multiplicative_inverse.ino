unsigned long long modular_multiplicative_inverse(unsigned long long E, unsigned long long PHI){
  long long D  = 0;
  long long nt = 1;
  long long r = PHI;
  long long nr = E % PHI;

  // correct values to acceptable input range
  if (PHI < 0){
    PHI = -PHI;
  }
  if (E < 0){
    E = PHI - (-E % PHI);
  }

  // perform operations to calculate the MMI
  long long quot;
  long long tmp;
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
  return (unsigned long long)D;
}
