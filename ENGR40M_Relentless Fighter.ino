//  State values live in an enum
enum states {STOP = 0, FORWARD = A2, REVERSE = 6};

const byte LIMIT = 8;
const byte TOGGLE = 7;

// this state variable saves our state between calls to loop()
int state = STOP;


void setup() {
  Serial.begin(115200);
  Serial.println("Setup complete");
  // TO DO: 
  // intialize input and output pins
  pinMode(FORWARD, OUTPUT);
  pinMode(REVERSE, OUTPUT);
  pinMode(LIMIT, INPUT_PULLUP);
  pinMode(TOGGLE, INPUT_PULLUP);
  
  // intialize your initial states
  state = STOP;
}

void loop() {
  // TODO read input pins to get status of toggle and limit
  // Not necessary you can call easily each time during the if statement for more concise code
  switch (state) {
    case STOP: // case for STOP 
      digitalWrite(FORWARD, LOW);
      digitalWrite(REVERSE, LOW);
      // TO DO: Set your outputs for the motor to stop
      if (digitalRead(TOGGLE) == LOW){
          state = STOP;
          break;
      // TO DO: Decide whether to change states and update the state variable accordingly
      }

    case FORWARD: // case for forward 
      // TO DO: Set your outputs for the motor to move forward
      digitalWrite(FORWARD, HIGH);
      digitalWrite(REVERSE, LOW);
      // TO DO: Decides whether to change states by updatin gth Transition for your states depending on your input
      if (digitalRead(TOGGLE) == HIGH){
        state = FORWARD;
        break;
      }

    case REVERSE: // case for backward 
      // TO DO: Set your outputs for the motor to reverse
      // Have the finger press the toggle quickly, then stop before it goes all the way down to see if it is pressed again. 
      // If pressed again, the finger presses it again and repeats this until it goes all the way back down.
      while (digitalRead(TOGGLE) == LOW && digitalRead(LIMIT) == LOW) {
        analogWrite(FORWARD, 127);
        digitalWrite(REVERSE, HIGH);
        delay(200);
        digitalWrite(FORWARD, LOW);
        digitalWrite(REVERSE, LOW);
        delay(2000);
        analogWrite(FORWARD, 127);
        digitalWrite(REVERSE, HIGH); 
      }
      // TO DO: Transition for your states depending on your input
      if (digitalRead(TOGGLE) == LOW && digitalRead(LIMIT) == LOW){
          state = REVERSE;
          break;
      }
      state = STOP;
  }; // end switch
}
