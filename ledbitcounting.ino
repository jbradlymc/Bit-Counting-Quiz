const int blueleds[3] = {2, 3, 4};                 
const int redleds[7]  = {5, 6, 7, 8, 9, 10, 11};  
const int allleds[10] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

const int button1 = A0;  
const int button2 = A1;   
const int button3 = A2;  

int lastbuttonstate1 = HIGH;
int lastbuttonstate2 = HIGH;
int lastbuttonstate3 = HIGH;

int buttonstate1;
int buttonstate2;
int buttonstate3;

unsigned long lastdebounce1 = 0;
unsigned long lastdebounce2 = 0;
unsigned long lastdebounce3 = 0;
unsigned long debouncedelay = 50;

int bluecount = 0;
int redcount = 0;

void setup() {
  for (int i = 0; i < 10; i++) pinMode(allleds[i], OUTPUT);

  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
}

void loop() {
  int read1 = digitalRead(button1);
    if (read1 != lastbuttonstate1) lastdebounce1 = millis();
    if ((millis() - lastdebounce1) > debouncedelay) {
      if (read1 != buttonstate1) {
       buttonstate1 = read1;
       if (buttonstate1 == LOW) {
         for (int i = 0; i < 10; i++) digitalWrite(allleds[i], LOW);
          bluecount = 0;
          redcount = 0;
          sequence1(); 
       } 
     }   
   }     
   lastbuttonstate1 = read1;

  int read2 = digitalRead(button2);
    if (read2 != lastbuttonstate2) lastdebounce2 = millis();
    if ((millis() - lastdebounce2) > debouncedelay) {
      if (read2 != buttonstate2) {
       buttonstate2 = read2;
       if (buttonstate2 == LOW) {
         for (int i = 0; i < 10; i++) digitalWrite(allleds[i], LOW);
          bluecount = 0;
          redcount = 0;
          sequence2();
       }
     }
   }
   lastbuttonstate2 = read2;
  
  int read3 = digitalRead(button3);
    if (read3 != lastbuttonstate3) lastdebounce3 = millis();
    if ((millis() - lastdebounce3) > debouncedelay) {
      if (read3 != buttonstate3) {
       buttonstate3 = read3;
       if (buttonstate3 == LOW) {
        sequence3(); 
       }
     }
   }
   lastbuttonstate3 = read3;
}

void sequence1() {
  for (int i = 0; i < 10; i++) {
    digitalWrite(allleds[i], HIGH);
    delay(200);
  }
  
  for (int i = 9; i >= 0; i--) {
    digitalWrite(allleds[i], LOW);
    delay(200);
  }
}

void sequence2() {
  int totalcount = 0;
  int maxcount = 128*8;
  
  while (totalcount < maxcount) {
    displayBinary(bluecount, blueleds, 3);
    displayBinary(redcount, redleds, 7);

    delay(300);
    
    bluecount++;

    if (bluecount > 7) {
      bluecount = 0;   
      redcount++; 
     
      if (redcount > 127) {
        redcount = 0;
        for (int i = 0; i < 10; i++) digitalWrite(allleds[i], LOW);
      }
    }
    totalcount++;
  }
}

void sequence3() {
  bluecount++;

  if (bluecount > 7) {
    bluecount = 0;
    redcount++;
    if (redcount > 127) redcount = 0;
  }

  displayBinary(bluecount, blueleds, 3);
  displayBinary(redcount, redleds, 7);
}


void displayBinary(int number, const int ledpins[], int bits) {
  for (int i = 0; i < bits; i++) {
    int bitval = (number >> i) & 1;
    digitalWrite(ledpins[i], bitval);
  }
}
