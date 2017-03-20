#define SIG_A_PIN 0
#define SIG_B_PIN 1

#define FWD_PIN 3
#define FWD_PIN_MASK 1<<FWD_PIN
#define REV_PIN 4
#define REV_PIN_MASK 1<<REV_PIN

volatile bool AState;
volatile bool BState;

void setup() {

  cli();//disable interrupts
  
  pinMode(FWD_PIN, OUTPUT);
  pinMode(REV_PIN, OUTPUT);
  pinMode(SIG_A_PIN, INPUT);
  pinMode(SIG_B_PIN, INPUT);

  //set inital A and B states
  AState = digitalRead(SIG_A_PIN);
  BState = digitalRead(SIG_B_PIN);

  digitalWrite(FWD_PIN, LOW);
  digitalWrite(REV_PIN, LOW);

  GIMSK |= (1<<PCIE);//enable pin change interrupts
  PCMSK |= (1<<SIG_A_PIN) | (1<<SIG_B_PIN);//set pin change interrupts on pins 0 and 1
  
  sei();//enable interrupts
  
}

ISR(PCINT0_vect){//interrupt routine

  bool newAState = PINB & 1;//(PINB>>SIG_A_PIN) & 1; if SIG_A_PIN != 0
  bool newBState = (PINB>>SIG_B_PIN) & 1;

  if (newAState != AState){//pin change on A
    if (newAState){//rising A
      if (newBState){//high B
        PORTB ^= REV_PIN_MASK;//toggle reverse signal
      } else {//low B
        PORTB ^= FWD_PIN_MASK;//toggle forward signal
      }
    } else {//falling A
      if (newBState){//high B
        PORTB ^= FWD_PIN_MASK;//toggle forward signal
      } else {//low B
        PORTB ^= REV_PIN_MASK;//toggle reverse signal
      }
    }
  } else {//pin change on B
    if (newBState){//rising B
      if (newAState){//high A
        PORTB ^= FWD_PIN_MASK;//toggle forward signal
      } else {//low B
        PORTB ^= REV_PIN_MASK;//toggle reverse signal
      }
    } else {//falling B
      if (newAState){//high A
        PORTB ^= REV_PIN_MASK;//toggle reverse signal
      } else {//low B
        PORTB ^= FWD_PIN_MASK;//toggle forward signal
      }
    }
  }

  //save new states
  AState = newAState;
  BState = newBState;
}

void loop() {
}
