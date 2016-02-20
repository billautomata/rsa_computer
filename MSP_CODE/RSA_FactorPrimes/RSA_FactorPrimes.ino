//int pushButtonPin = 73;
int redLED = 78;

int ledState = true;

uint32_t counter = 0;
unsigned long idx = 3;
unsigned long long p;
unsigned long long q;
unsigned long long n;

// the setup routine runs once when you press reset:
void setup() {

  Serial.begin(9600); 
  
//  p = 48619;        q = 48623;
//  p = 104743;       q = 224743;
//  p = 1299721;      q = 152271479;
  p = 32749;    q = 32719;  // largest 15 bit primes
  
  n = p*q;    
  redLED = RED_LED;
  pinMode(redLED, OUTPUT);
  
}

// the loop routine runs over and over again forever:
void loop() {
  
  if(n % idx == 0){
    
    // success
    digitalWrite(redLED, LOW);
    
    Serial.println("Success! ");
    Serial.println(idx);
    Serial.println();
    
    delay(10000);
    
  } else {
    
    idx+=2;
    counter+=1;
    
    if(counter % 1000 == 0){
      Serial.println(idx);
    }
    if(ledState){
      digitalWrite(redLED, HIGH);
    } else {
      digitalWrite(redLED, LOW);
    }
    ledState = !ledState;
  }
  
  // read the input pin:
//  int buttonState = digitalRead(pushButtonPin);
  // print out the state of the button:

}



