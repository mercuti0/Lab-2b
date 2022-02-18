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
      // Goes halfway up, stops in annoyance, then presses the toggle, holding the toggle pressed in annoyance.
      // Then goes all the way back down, unless the toggle is pressed again before that, at which point the 
      // finger repeats its forward process, but hits it even harder. 
      while (digitalRead(TOGGLE) == HIGH) {
        digitalWrite(FORWARD, HIGH);
        analogWrite(REVERSE, 140);
        delay(355);
        digitalWrite(FORWARD, LOW);
        digitalWrite(REVERSE, LOW);
        delay(2000);
        digitalWrite(FORWARD, HIGH);
        digitalWrite(REVERSE, LOW);
        delay(340);
        digitalWrite(FORWARD, LOW);
        digitalWrite(REVERSE, LOW);
        delay(3000);
      }
        // TO DO: Decides whether to change states by updatin gth Transition for your states depending on your input
        if (digitalRead(TOGGLE) == HIGH){
          state = FORWARD;
          break;
        }

    case REVERSE: // case for backward 
      // TO DO: Set your outputs for the motor to reverse
      digitalWrite(FORWARD, LOW);
      digitalWrite(REVERSE, HIGH);
      // TO DO: Transition for your states depending on your input
      if (digitalRead(TOGGLE) == LOW && digitalRead(LIMIT) == LOW){
          state = REVERSE;
          break;
      }
      state = STOP;
  }; // end switch
}

