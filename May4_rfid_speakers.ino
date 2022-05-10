#include <Tone.h>
#include <SPI.h>
#include <MFRC522.h>
#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above
#define RST_PIN2 9
#define SS_PIN2 3
const byte buttonPin1 = 7;
const byte buttonPin2 = 8;

Tone tone1;
Tone tone2;
const int numTones = 46;
int tones1[] = {587, 784, 880, 988, 988, 988, 988, 988, 988, 988, 932, 988, 784, 784, 784, 784, 784, 784, 784, 880, 988, 1047, 1047, 1319, 1319, 1319, 1319, 1175, 1047, 988, 988, 988, 784, 880, 988, 1047, 1047, 1319, 1319, 1319, 1319, 1175, 1047, 988, 988, 784, 784, 784, 784, 880, 988, 988, 988, 1047, 880, 880, 880, 988, 784, 784, 784, 784};

#define  c        261.626    // 261 Hz
#define  d        293.665    // 294 Hz
#define  e        329.628    // 329 Hz
#define  f        349.228    // 349 Hz
#define  g        391.995    // 392 Hz
#define  a        440.000    // 440 Hz
#define  b        493.883    // 493 Hz
#define  C        523.251    // 523 Hz
#define  R1        0
#define  R -1

int mapa[10000];

int melody[] = {  c, c, d, e, e, R1,
                  e, d, e, c, c, R1,
                  c, d, e, f, a, R1,
                  a, g, f, e, R1,
                  c, d, e, f, a, R1,
                  a, g, f, e, c, R1,
                  g, c, d, e, f, R1, 
                  d, d, e, c, R1
};
int noteDurations[] = { 4, 4, 4, 4, 4, 8,
                        4, 4, 4, 4, 4, 8,
                        4, 4, 4, 4, 4, 8,
                        4, 4, 4, 4, 8,
                        4, 4, 4, 4, 4, 8,
                        4, 4, 4, 4, 4, 8,
                        4, 4, 4, 4, 4, 8,
                        4, 4, 4, 4, 8
                      };

                  
int chords[] = { R, R, R, R, R, R,
                 R, R, R, R, R, R, 
                 R, R, R, R, R, R,
                 R, R, R, R, R,
                 R, R, R, R, R, R,
                 R, R, R, R, R, R,
                 R, R, R, R, R, R,
                 R, R, R, R, R, R,
                 R, R, R, R, R};  
                                 
int chords1[] = { R, R, R, 0, 0, R,
                 R, R, R, 0, 0, R, 
                 R, R, R, 3, 3, R,
                 R, R, 0, 0, R,
                 R, R, R, 3, 3, R,
                 R, R, R, 0, 0, R,
                 R, R, R, 0, 0, R,
                 R, R, R, 0, 0, R,
                 4, 4, R, 0, R};  
int minor1[] = {c, d, e, f, g, a, b};
int minor2[] = {g, f, g, c, d, c, d};
MFRC522 mfrc522[2];  // Create MFRC522 instance

void setup() {
  Serial.begin(9600);
  
  tone1.begin(5);
  tone2.begin(6);
  tone1.stop();
  tone2.stop();
  //mapa[177] = 0;
  //mapa[6832] = 3;
  
  while (!Serial); 
  SPI.begin();    
  mfrc522[0].PCD_Init(); 
  mfrc522[1].PCD_Init(); 
  delay(4);      
}
void loop() {
  // put your main code here, to run repeatedly:
  
  int state1 = digitalRead(buttonPin1);
  int state2 = digitalRead(buttonPin2);
  if (state1 == HIGH){
        Serial.println("1");

    //woChords();
   
   }
  if (state2 == HIGH){
      Serial.println("2");
      readers();
      
      //withChords();
    }
     tone1.stop();
}

unsigned long getID(int i){
  if ( ! mfrc522[i].PICC_ReadCardSerial()) { //Since a PICC placed get Serial and continue
    return -1;
  }
  unsigned long hex_num;
  hex_num =  mfrc522[i].uid.uidByte[0] << 24;
  hex_num += mfrc522[i].uid.uidByte[1] << 16;
  hex_num += mfrc522[i].uid.uidByte[2] <<  8;
  hex_num += mfrc522[i].uid.uidByte[3];
  mfrc522[i].PICC_HaltA(); // Stop reading
  return hex_num;
}
void readers() {
  mfrc522[0].PCD_Init();
  
  if (mfrc522[0].PICC_IsNewCardPresent() || mfrc522[0].PICC_ReadCardSerial()) {
      unsigned long uid = getID(0);
      if(uid != -1){
         Serial.print("1 Card detected, UID: "); 
         Serial.println(uid);
      }
    }
    mfrc522[0].PICC_HaltA();
    mfrc522[0].PCD_StopCrypto1();
  
    mfrc522[1].PCD_Init();
    if (mfrc522[1].PICC_IsNewCardPresent() || mfrc522[1].PICC_ReadCardSerial()) {
      unsigned long uid = getID(1);
      if(uid != -1){
         Serial.print("2 Card detected, UID: "); 
         Serial.println(uid);
      }
    } 
    mfrc522[1].PICC_HaltA();
    mfrc522[1].PCD_StopCrypto1();
}

void woChords() {
 
   //tone2.begin(6);
   //tone2.play(0);
  for (int i=0; i<numTones; i++) {
    int dur = 2000/noteDurations[i];
    Serial.println(noteDurations[i]);
    tone1.play(melody[i]);
    //digitalWrite(led1, 1);

    delay(dur);
  }
  tone1.stop();
  //tone2.stop();
  //digitalWrite(led1, 0);
  //digitalWrite(led2, 0);
}
void withChords() {
  //tone2.play(0);
  for (int i=0; i<numTones; i++) {
    int dur = 2000/noteDurations[i];
    if (melody[i]==-1 && chords[i]!=R1){
      tone1.play(minor2[chords[i]]);
}
    else{
      tone1.play(melody[i]);
}
    if (chords[i] == R){
      tone2.stop();
}
    else{
      tone2.play(minor1[chords[i]]);
}
   
    delay(dur);
  }
  tone1.stop();
  tone2.stop();


}
