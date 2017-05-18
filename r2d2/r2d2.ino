// Volume Library Demo Sketch (c) 2016 Connor Nishijima
// Released under the GPLv3 license

#include <avr/sleep.h> 

#include <avr/power.h> 
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include "Volume.h" // Include the Volume library

byte firstRun = 1;
Volume vol; // Plug your speaker into the default pin for your board type:
            // https://github.com/connornishijima/arduino-volume#supported-pins 

void setup()
{

  pinMode(2,INPUT_PULLUP); // interrupt pin for activation
  pinMode(13, OUTPUT); // LED pin


  // disable all unused features to preseve power
  wdt_disable();
  power_adc_disable();
  power_spi_disable();
  power_timer2_disable();
  power_twi_disable();

  // set all unused pins to output low to preseve power
  // left
  pinMode(31, OUTPUT);
  digitalWrite(31, LOW);
  //  pinMode(30, OUTPUT);
  //  digitalWrite(30, LOW);
  pinMode(29, OUTPUT);
  digitalWrite(29, LOW);
  pinMode(32, OUTPUT);
  digitalWrite(32, LOW);
  pinMode(1, OUTPUT);
  digitalWrite(1, LOW);
  //  pinMode(2, OUTPUT);
  //  digitalWrite(2, LOW);
  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);
  pinMode(11, OUTPUT);
  digitalWrite(11, LOW);
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);
  //  pinMode(13, OUTPUT);
  //  digitalWrite(13, LOW);

  // right
  pinMode(26, OUTPUT);
  digitalWrite(26, LOW);
  pinMode(25, OUTPUT);
  digitalWrite(25, LOW);
  pinMode(24, OUTPUT);
  digitalWrite(24, LOW);
  pinMode(23, OUTPUT);
  digitalWrite(23, LOW);
  pinMode(17, OUTPUT);
  digitalWrite(17, LOW);
  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  pinMode(15, OUTPUT);
  digitalWrite(15, LOW);
  pinMode(14, OUTPUT);
  digitalWrite(14, LOW);

  pinMode(28, OUTPUT);
  digitalWrite(28, LOW);
  pinMode(27, OUTPUT);
  digitalWrite(27, LOW);
  pinMode(22, OUTPUT);
  digitalWrite(22, LOW);
  pinMode(19, OUTPUT);
  digitalWrite(19, LOW);

  vol.begin(); // After calling this, delay() and delayMicroseconds will no longer work
               // correctly! Instead, use blinkDelay() and vol.delayMicroseconds() for
               // the correct timing

  vol.setMasterVolume(1.00); // Self-explanatory enough, right? Try lowering this value if the speaker is too loud! (0.00 - 1.00)
  randomSeed(analogRead(0));
  attachInterrupt(0, wakeUpNow, LOW); // use interrupt 0 (pin 2) and run function wakeUpNow when pin 2 gets LOW  
  //blinkDelay(500);
}

void blinkDelay(int delayTime) {

  if ( digitalRead(13)) {
    digitalWrite(13, LOW);
  } else {
    digitalWrite(13, HIGH);
  }
  
  vol.delay(delayTime);

}

void loop()
{
  if (firstRun) {
    firstRun = 0;
  } else {
      digitalWrite(13, HIGH); //LED on
    switch (random(15)) {
    //switch (15) {
      case 0:
        wolfWhistle();  // Wee-woo!
        break;
      case 1:
        R2D2();         // BRRT doo doo doo doo doo doo doo doo DIOooo BRRT!
        break;
      case 2:
        wolfWhistle2();  // Weeowit!
        break;
      case 3:
        R2D2_2();
        break;
      case 4:
        sadR2();
        break;
      case 5:
        R2D2_3();
        break;
      case 6:
        R2D2_4();
        break;
      case 7:
        R2D2_5();
        break;
      case 8:
        R2D2_3();
        break;
      case 9:
        R2D2_4();
        break;
      case 10:
        R2D2_5();
        break;
      case 11:
        squeak();
        break;
      case 12:
        ohhh();
        break;
      case 13:
        uhoh();
        break;
      case 14:
        waka();
        break;
      case 15:
        laugh();
        break;
    }
    blinkDelay(500);
    digitalWrite(13, LOW); //LED off
  }
  sleepNow();     // sleep function called here  
}

void sleepNow() {  
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);// sleep mode is set here  
    sleep_enable();                     // enables the sleep bit in the mcucr register  
    attachInterrupt(0,wakeUpNow, LOW);  // use interrupt 0 (pin 2) and run function  
    power_timer0_disable();             // disable all timers during sleep
    power_timer1_disable();
//    sleep_bod_disable();              // not available on 168

    sleep_mode();                       // here the device is actually put to sleep!!  
    // THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP  
    sleep_disable();                    // first thing after waking from sleep: disable sleep...  
    power_timer0_enable();
    power_timer1_enable();
    detachInterrupt(0);                 // disables interrupt 0 on pin 2 so the wakeUpNow code will not be executed during normal running time.  
}  

void wakeUpNow() {  
  // execute code here after wake-up before returning to the loop() function  
  // timers and code using timers (serial.print and more...) will not work here.  
  // we don't really need to execute any special functions here, since we  
  // just want the thing to wake up  
}  

//------------------------------------------------------------------------------------
// Below are some demo sounds I've made - if you have any questions about
// these email me directly at connornishijima@gmail.com :) Feel free to
// use the R2D2 function for your own Star Wars project!
//------------------------------------------------------------------------------------

/*
void gameboy(){
  vol.tone(1025,255); // pa
  blinkDelay(70);
  int v = 255;
  while(v > 0){
    vol.tone(2090,v); // ting!
    blinkDelay(3);
    v--;
  }
}
*/
void wolfWhistle() {
  int f = 122; // starting frequency
  int v = 0;   // starting volume
  while (f < 4000) {  // slide up to 4000Hz
    vol.tone(f, v);
    v = 255 * (f / 4000.00);
    f += 25;
    blinkDelay(1);
  }
  vol.noTone();
  blinkDelay(100); // wait a moment
  f = 122; // starting frequency
  v = 0;   // starting volume
  while (f < 3000) { // slide up to 3000Hz
    vol.tone(f, v);
    v = 255 * (f / 4000.00); 
    f += 25;
    blinkDelay(2);
  }
  while (f > 125) { // slide down to 125Hz
    vol.tone(f, v);
    v = 255 * (f / 4000.00);
    f -= 25;
    blinkDelay(2);
  }
  vol.noTone(); // end tone production
}

void wolfWhistle2() {
  int f = 122; // starting frequency
  int v = 0;   // starting volume
  while (f < 3000) { // slide up
    vol.tone(f, v);
    v = 255 * (f / 4000.00); 
    f += 25;
    blinkDelay(2);
  }
  while (f > 1500) { // slide down
    vol.tone(f, v);
    v = 255 * (f / 4000.00);
    f -= 25;
    blinkDelay(2);
  }
  f = 1495; // starting frequency
  v = 0;   // starting volume
  while (f < 4000) {  // slide up to 4000Hz
    vol.tone(f, v);
    v = 255 * (f / 4000.00);
    f += 25;
    blinkDelay(1);
  }
  vol.noTone(); // end tone production
}

void sadR2() {  //or missile crash, dunno...
  int buzzVols[] = {144, 180, 216, 252, 252, 252, 252, 216, 180, 144};
  int f = 660; // starting frequency
  int v = 0;   // starting volume
  while (f < 880) { // slide up 
    vol.tone(f, v);
    v = 255 * (f / 4000.00); 
    f += 25;
    blinkDelay(3);
  }
  while (f > 330) { // slide down 
    vol.tone(f, v);
    v = 255 * (f / 4000.00);
    f -= 5;
    blinkDelay(10);
  }

  int i = 19;
  while (i >= 0) {
    vol.tone(440, buzzVols[i]);
    vol.delayMicroseconds(20);
    vol.tone(440, buzzVols[i] / 8);
    vol.delayMicroseconds(40);
    i--;
  }

  vol.noTone(); // end tone production
}

void R2D2_2() {
  int beeps[] = {1933, 2156, 1863, 1505, 1816, 1933, 1729, 2291};
  int buzzVols[] = {144, 180, 216, 252, 252, 252, 252, 216, 180, 144};

  int i = 9;
  while (i >= 0) {
    vol.tone(1050, buzzVols[i]);
    vol.delayMicroseconds(20);
    vol.tone(1050, buzzVols[i] / 8);
    vol.delayMicroseconds(40);
    i--;
  }

  blinkDelay(35);

  i = 0;
  while (i < 8) {
    int v = 0;
    while (v < 250) { // 12.5 mS fade up time
      vol.tone(beeps[8-i], v);
      v += 10;
      vol.delayMicroseconds(2);
    }
    blinkDelay(20);
    v = 250;
    while (v > 0) { // 12.5 mS fade down time
      vol.tone(beeps[8-i], v);
      v -= 10;
      vol.delayMicroseconds(5);
    }
    vol.noTone();
    blinkDelay(35);
    i++;
  }

  i = 20;
  while (i > 0) {
    vol.tone(1050, buzzVols[i]);
    vol.delayMicroseconds(20);
    vol.tone(1050, buzzVols[i] / 8);
    vol.delayMicroseconds(40);
    i--;
  }
  vol.noTone();
}
void R2D2_3() {
  int beeps[8];
  int buzzVols[] = {144, 180, 216, 252, 252, 252, 252, 216, 180, 144};

  int i = 9;
  while (i >= 0) {
    vol.tone(1050, buzzVols[i]);
    vol.delayMicroseconds(20);
    vol.tone(1050, buzzVols[i] / 8);
    vol.delayMicroseconds(40);
    i--;
  }
  blinkDelay(35);
  int f = 2466;
  while (f < 2825) {
    vol.tone(f, 255);
    f += 3;
    blinkDelay(1);
  }
  f = 2825;
  int v = 255;
  while (f > 2000) {
    vol.tone(f, v);
    f -= 6;
    v -= 1;
    blinkDelay(1);
  }
  vol.noTone();
  blinkDelay(35);

  i = 0;
  while (i < 8) {
    beeps[i] = 1500+random(2500);
    i++;
  }  
  i = 0;
  while (i < 8) {
    int v = 0;
    while (v < 250) { // 12.5 mS fade up time
      vol.tone(beeps[i], v);
      v += 10;
      vol.delayMicroseconds(2);
    }
    blinkDelay(20);
    v = 250;
    while (v > 0) { // 12.5 mS fade down time
      vol.tone(beeps[i], v);
      v -= 10;
      vol.delayMicroseconds(5);
    }
    vol.noTone();
    blinkDelay(35);
    i++;
  }

  i = 10;
  while (i > 0) {
    vol.tone(1050, buzzVols[i]);
    vol.delayMicroseconds(20);
    vol.tone(1050, buzzVols[i] / 8);
    vol.delayMicroseconds(40);
    i--;
  }
  vol.noTone();
}
void R2D2_4() {
  int beeps[8];
  int buzzVols[] = {144, 180, 216, 252, 252, 252, 252, 216, 180, 144};

  int i = 9;
  while (i >= 0) {
    vol.tone(1050, buzzVols[i]);
    vol.delayMicroseconds(20);
    vol.tone(1050, buzzVols[i] / 8);
    vol.delayMicroseconds(40);
    i--;
  }
  blinkDelay(35);
  
  i = 0;
  while (i < 8) {
    beeps[i] = 1500+random(2500);
    i++;
  }  
  i = 0;
  while (i < 8) {
    int v = 0;
    while (v < 250) { // 12.5 mS fade up time
      vol.tone(beeps[i], v);
      v += 10;
      vol.delayMicroseconds(2);
    }
    blinkDelay(20);
    v = 250;
    while (v > 0) { // 12.5 mS fade down time
      vol.tone(beeps[i], v);
      v -= 10;
      vol.delayMicroseconds(5);
    }
    vol.noTone();
    blinkDelay(35);
    i++;
  }

  i = 10;
  while (i > 0) {
    vol.tone(1050, buzzVols[i]);
    vol.delayMicroseconds(20);
    vol.tone(1050, buzzVols[i] / 8);
    vol.delayMicroseconds(40);
    i--;
  }
  vol.noTone();
}


void R2D2_5() {
  int beeps[8];
  int buzzVols[] = {144, 180, 216, 252, 252, 252, 252, 216, 180, 144};

  int i = 9;
  while (i >= 0) {
    vol.tone(1050, buzzVols[i]);
    vol.delayMicroseconds(20);
    vol.tone(1050, buzzVols[i] / 8);
    vol.delayMicroseconds(40);
    i--;
  }

  blinkDelay(35);
  
  i = 0;
  while (i < 8) {
    beeps[i] = 1500+random(2500);
    i++;
  } 
  
  i = 0;
  while (i < 8) {
    int v = 0;
    while (v < 250) { // 12.5 mS fade up time
      vol.tone(beeps[i], v);
      v += 10;
      vol.delayMicroseconds(2);
    }
    blinkDelay(20);
    v = 250;
    while (v > 0) { // 12.5 mS fade down time
      vol.tone(beeps[i], v);
      v -= 10;
      vol.delayMicroseconds(5);
    }
    vol.noTone();
    blinkDelay(35);
    i++;
  }

  int f = 2466;
  while (f < 2825) {
    vol.tone(f, 255);
    f += 3;
    blinkDelay(1);
  }
  f = 2825;
  int v = 255;
  while (f > 2000) {
    vol.tone(f, v);
    f -= 6;
    v -= 1;
    blinkDelay(1);
  }
  vol.noTone();
  blinkDelay(35);

  i = 10;
  while (i > 0) {
    vol.tone(1050, buzzVols[i]);
    vol.delayMicroseconds(20);
    vol.tone(1050, buzzVols[i] / 8);
    vol.delayMicroseconds(40);
    i--;
  }
  vol.noTone();
}

void R2D2() {
  int beeps[] = {1933, 2156, 1863, 1505, 1816, 1933, 1729, 2291};
  int buzzVols[] = {144, 180, 216, 252, 252, 252, 252, 216, 180, 144};

  int i = 9;
  while (i >= 0) {
    vol.tone(1050, buzzVols[i]);
    vol.delayMicroseconds(20);
    vol.tone(1050, buzzVols[i] / 8);
    vol.delayMicroseconds(40);
    i--;
  }

  blinkDelay(35);

  i = 0;
  while (i < 8) {
    int v = 0;
    while (v < 250) { // 12.5 mS fade up time
      vol.tone(beeps[i], v);
      v += 10;
      vol.delayMicroseconds(2);
    }
    blinkDelay(20);
    v = 250;
    while (v > 0) { // 12.5 mS fade down time
      vol.tone(beeps[i], v);
      v -= 10;
      vol.delayMicroseconds(5);
    }
    vol.noTone();
    blinkDelay(35);
    i++;
  }

  int f = 2466;
  while (f < 2825) {
    vol.tone(f, 255);
    f += 3;
    blinkDelay(1);
  }
  f = 2825;
  int v = 255;
  while (f > 2000) {
    vol.tone(f, v);
    f -= 6;
    v -= 1;
    blinkDelay(1);
  }
  vol.noTone();
  blinkDelay(35);

  i = 10;
  while (i > 0) {
    vol.tone(1050, buzzVols[i]);
    vol.delayMicroseconds(20);
    vol.tone(1050, buzzVols[i] / 8);
    vol.delayMicroseconds(40);
    i--;
  }
  vol.noTone();
}


void squeak() {
  int v = 220;
  for (int i=100; i<5000; i=i*1.45) { 
    vol.tone(i,v);
    blinkDelay(60);
  }
  blinkDelay(10);
  for (int i=100; i<6000; i=i*1.5) {
    vol.tone(i,v);
    blinkDelay(20);
  }
  vol.noTone();
}

void ohhh() {
  int v = 0;
  for (int i=1000; i<2000; i=i*1.02) {
    v = 255 * (i / 4000.00);
    vol.tone(i,v);
    blinkDelay(10);
  }
  for (int i=2000; i>1000; i=i*.98) {
    v = 255 * (i / 4000.00);
    vol.tone(i,v);
    blinkDelay(10);
  }
  vol.noTone();
}

void uhoh() {
  int v = 0;
  for (int i=1000; i<1244; i=i*1.01) {
    v = 255 * (i / 4000.00);
    vol.tone(i,v);
    blinkDelay(30);
  }
  delay(200);
  for (int i=1244; i>1108; i=i*.99) {
    v = 255 * (i / 4000.00);
    vol.tone(i,v);
    blinkDelay(10);
  }
  vol.noTone();
}


void waka() {
  int v = 120;
  for (int i=1000; i<3000; i=i*1.05) {
    vol.tone(i,v);
    blinkDelay(10);
  }
  vol.noTone();
  blinkDelay(100);
  for (int i=2000; i>1000; i=i*.95) {
    vol.tone(i,v);
    blinkDelay(10);
  }
    for (int i=1000; i<3000; i=i*1.05) {
    vol.tone(i,v);
    blinkDelay(10);
  }
  vol.noTone();
  blinkDelay(100);
  for (int i=2000; i>1000; i=i*.95) {
    vol.tone(i,v);
    blinkDelay(10);
  }
    for (int i=1000; i<3000; i=i*1.05) {
    vol.tone(i,v);
    blinkDelay(10);
  }
  vol.noTone();
  blinkDelay(100);
  for (int i=2000; i>1000; i=i*.95) {
    vol.tone(i,v);
    blinkDelay(10);
  }
    for (int i=1000; i<3000; i=i*1.05) {
    vol.tone(i,v);
    blinkDelay(10);
  }
  vol.noTone();
  blinkDelay(100);
  for (int i=2000; i>1000; i=i*.95) {
    vol.tone(i,v);
    blinkDelay(10);
  }
  vol.noTone();
}

void laugh() {
  int v = 170;
  for (int i=1000; i<2000; i=i*1.10) {
    vol.tone(i,v);
    blinkDelay(10);
  }
  vol.noTone();
  blinkDelay(50);
  for (int i=1000; i>500; i=i*.90) {
    vol.tone(i,v);
    blinkDelay(10);
  }
  vol.noTone();
  blinkDelay(50);
  for (int i=1000; i<2000; i=i*1.10) {
    vol.tone(i,v);
    blinkDelay(10);
  }
  vol.noTone();
  blinkDelay(50);
  for (int i=1000; i>500; i=i*.90) {
    vol.tone(i,v);
    blinkDelay(10);
  }
  vol.noTone();
  blinkDelay(50);
    for (int i=1000; i<2000; i=i*1.10) {
    vol.tone(i,v);
    blinkDelay(10);
  }
  vol.noTone();
  blinkDelay(50);
  for (int i=1000; i>500; i=i*.90) {
    vol.tone(i,v);
    blinkDelay(10);
  }
  vol.noTone();
  blinkDelay(50);
    for (int i=1000; i<2000; i=i*1.10) {
    vol.tone(i,v);
    blinkDelay(10);
  }
  vol.noTone();
  blinkDelay(50);
  for (int i=1000; i>500; i=i*.90) {
    vol.tone(i,v);
    blinkDelay(10);
  }
  vol.noTone();
  blinkDelay(50);
}

/*
void jetsons() {

  int f = 659;       // MEET
  int v = 254;
  while(v > 0){
    vol.tone(f,v);
    v-=2;
    blinkDelay(1);
  }
  blinkDelay(250);
  f = 831;           // GEORGE
   v = 254;
  while(v > 0){
    vol.tone(f,v);
    v-=2;
    blinkDelay(1);
  }
  blinkDelay(250);
  f = 932;           // JET
  v = 254;
  while(v > 0){
    vol.tone(f,v);
    v-=2;
    blinkDelay(1);
  }
  blinkDelay(50);
  f = 988;           // SON!
  v = 254;
  while(v > 32){
    vol.tone(f,v);
    v-=1;
    blinkDelay(2);
  }
  delay(250);
  int fadeV = 1;
  
  while (f < 7000) {
    vol.tone(f / 4, constrain(v,0,255));
    f += 3;

    if (v < 200 && fadeV == 1) {
      v += ((f/7000.00)*100)/10;
    }
    else {
      fadeV = 0;
    }

    if (v > -50 && fadeV == 0) {
      v -= ((f/7000.00)*100)/10;
    }
    else {
      fadeV = 1;
    }

    blinkDelay(1);
  }

  int i = 8000;
  float multiplier = 1.00;
  while(i > 0){
    vol.tone(f / 4, constrain(v,0,255)*multiplier);
    
    if (v < 200 && fadeV == 1) {
      v += ((f/8000.00)*100)/10;
    }
    else {
      fadeV = 0;
    }

    if (v > -20 && fadeV == 0) {
      v -= ((f/8000.00)*100)/10;
    }
    else {
      fadeV = 1;
    }

    if(multiplier > 0){
      multiplier -= 0.0002;
    }
    else{
      multiplier = 0;
    }
    if(i % 4 == 0){
      f-=1;
    }
    blinkDelay(1);
    i--;
  }
  vol.noTone();
}
*/
