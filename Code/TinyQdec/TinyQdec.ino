#define FWDPIN 3
#define REVPIN 4

void setup() {
  
  pinMode(FWDPIN, OUTPUT);
  pinMode(REVPIN, OUTPUT);

  digitalWrite(FWDPIN, LOW);
  digitalWrite(REVPIN, LOW);
  
}

void loop() {

  
  digitalWrite(REVPIN, HIGH);
  digitalWrite(FWDPIN, HIGH);
  delay(400);
  digitalWrite(REVPIN, LOW);
  digitalWrite(FWDPIN, LOW);
  delay(400);



}
