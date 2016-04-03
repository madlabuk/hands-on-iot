const int DATA_PIN = A5;
const int CLOCK_PIN = A3;
const int LATCH_PIN = A2;

void setup() {
  // put your setup code here, to run once:
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  //Note that whilst writing data the latch should be low...
  digitalWrite(LATCH_PIN, LOW);

  //Write the data you want, shiftOut handles the transmission...
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, 0b10101010);

  //Once transmission is done, switch the latch back to high.
  digitalWrite(LATCH_PIN, HIGH);
  delay(500);

  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, 0b01010101);
  digitalWrite(LATCH_PIN, HIGH);
  delay(500);
}
