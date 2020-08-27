/*

  Heating Pad Hand Warmer Blanket Code Example
  SparkFun Electronics, Pamela, 1/24/2013
  Beerware License

  https://learn.sparkfun.com/tutorials/heating-pad-hand-warmer-blanket?_ga=2.51372457.1848584734.1582931667-52716113.1567650930

  Hardware Connections:
  -led1 = D9;
  -led2 = D10;
  -led3 = D11;
  -button = D2;
  -Mofset = D3;

  Usage:
  Hit the switch to power, hit the button to adjust how warm the heating elements get, and three LEDs will indicate low, medium, and high levels.
*/
int btnPinO = 2;  //on off switch
int btnPinU = 4; //raise temp
int btnPinD = 5; // lower temp

int buttonPushCounterO = 0; // counter for the number of btn presses
int buttonStateO = 0; // current state of the button
int lastButtonStateO = 0; //previous state of the button

int buttonPushCounterU = 0; // counter for the number of btn presses
int buttonStateU = 0; // current state of the button
int lastButtonStateU = 0; //previous state of the button

int buttonPushCounterD = 0; // counter for the number of btn presses
int buttonStateD = 0; // current state of the buttonm k
int lastButtonStateD = 0; //previous state of the button

int fetPin = 3;
int led1 = 6;
int mode = 0;

void setup() {
  // initialize the digital pin as an output.
  pinMode(btnPinU, INPUT_PULLUP);
  pinMode(btnPinD, INPUT_PULLUP);
  pinMode(btnPinO, INPUT_PULLUP);
  pinMode(fetPin, OUTPUT);
  pinMode(led1, OUTPUT);


  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {

  buttonStateO = digitalRead(btnPinO);
  buttonStateU = digitalRead(btnPinU);
  buttonStateD = digitalRead(btnPinD);

  if (buttonStateO != lastButtonStateO) {
    // if the state has changed, increment the counter
    if (buttonStateO == HIGH) {
      // if the current state is HIGH then the button went from off to on:
      buttonPushCounterO++;
      Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounterO);
    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
    //Delay a little bit to avoid bouncing
    delay(50);
  }

  //save the current state as the last state, for next time through the loop
  lastButtonStateO = buttonStateO;

  if (buttonPushCounterO % 2 == 0) {
    digitalWrite(led1, HIGH);
  } else {
    digitalWrite(led1, LOW);
    mode = 0;
  }


  if (buttonStateU != lastButtonStateU) {
    // if the state has changed, increment the counter
    if (buttonStateU == LOW) {
      // if the current state is HIGH then the button went from off to on:
      buttonPushCounterU++;
      Serial.println("on");
      Serial.print("number of UP button pushes: ");
      Serial.println(buttonPushCounterU);
      mode += 1;
      Serial.print("mode = ");
      Serial.println(mode);
    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
    //Delay a little bit to avoid bouncing
    delay(50);
  }

  //save the current state as the last state, for next time through the loop
  lastButtonStateU = buttonStateU;

  if (buttonStateD != lastButtonStateD) {
    // if the state has changed, increment the counter
    if (buttonStateD == LOW) {
      // if the current state is HIGH then the button went from off to on:
      buttonPushCounterD++;
      Serial.println("on");
      Serial.print("number of DOWN button pushes: ");
      Serial.println(buttonPushCounterD);
      mode -= 1;
      Serial.print("mode = ");
      Serial.println(mode);
    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
    //Delay a little bit to avoid bouncing
    delay(50);
  }

  //save the current state as the last state, for next time through the loop
  lastButtonStateD = buttonStateD;

  mode = constrain(mode, 0, 3);


//
//  //Increment mode on depress, unless mode = 3, then reset to 0
//  if (buttonPushCounterU > 0) {
//    //    mode = mode == 3 ? 0 : mode + 1;
//    //  Serial.println("changing mode up");
//  }  else {
//    buttonPushCounterU == 0;
//    // Serial.println("reset up button");
//
//  }



  if (buttonStateD && digitalRead(btnPinD) == LOW)
    mode = mode == 3 ? 0 : mode + - 1;

  //Serial.print("mode = ");
  //Serial.println(mode);

  switch (mode)
  {
    case 0:
      //      analogWrite(fetPin, 0); //off
      //  Serial.println("not up or down");
      //
      analogWrite(fetPin, 0); //33% duty cycle
      buttonPushCounterU = 0;
      buttonPushCounterD = 0;
      break;
    case 1:
      analogWrite(fetPin, 85); //33% duty cycle
      Serial.println("power 33%");
      //
      break;
    case 2:
      analogWrite(fetPin, 170); //66% duty cycle
      Serial.println("power 66%");
      //
      break;
    case 3:
      analogWrite(fetPin, 255); //100% duty cycle
      Serial.println("power 100%");
      //
      break;
  }
}
