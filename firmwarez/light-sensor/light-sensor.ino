int sensorValue = 0;
int sensorPin = A0;

void setup() {
    pinMode(A0, INPUT);
    Serial.begin(9600);
    Particle.variable("reading", sensorValue);
}

void loop() {
    sensorValue = analogRead(sensorPin);
    Serial.println(sensorValue);
    delay(100);
}
