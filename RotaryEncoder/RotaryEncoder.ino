#include "TM1637Display.h"

#define CLK 2
#define DIO 3

#define outputA 6
#define outputB 7

#define greLed 8
#define yelLed 9
#define redLed 10

int multiplier = 5;

int counter = 50;
int aState;
int aLastState;

TM1637Display display(CLK, DIO);

void setup() {
  pinMode(outputA, INPUT);
  pinMode(outputB, INPUT);
  
  pinMode(redLed, OUTPUT);
  pinMode(yelLed, OUTPUT);
  pinMode(greLed, OUTPUT);

  Serial.begin(9600);

  aLastState = digitalRead(outputA);

  digitalWrite(yelLed, HIGH); // default to on

  // brightness of our display, can go much higher
  display.setBrightness(2); 
  
  // set default display value
  display.showNumberDec(counter, false); 
}

void loop() {
  aState = digitalRead(outputA);
  if(aState != aLastState) {
    if(digitalRead(outputB) != aState) {
      counter -= multiplier;
    } else {
      counter += multiplier;
    }
    
    display.showNumberDec(counter, false);
    
    if(counter < 25) {
      digitalWrite(redLed, HIGH);
      digitalWrite(yelLed, LOW);
      digitalWrite(greLed, LOW);
    } else if (counter >= 25 && counter <= 65) {
      digitalWrite(redLed, LOW);
      digitalWrite(yelLed, HIGH);
      digitalWrite(greLed, LOW);
    } else  if (counter > 65) {
      digitalWrite(redLed, LOW);
      digitalWrite(yelLed, LOW);
      digitalWrite(greLed, HIGH);
    }
    Serial.println(counter);
  }
  aLastState = aState;
}
