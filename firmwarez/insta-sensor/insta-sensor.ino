int sensorValue = 0;
int sensorPin = A0;
char resultstr[20] = "";

void setup() {
    pinMode(A0, INPUT);
    Serial.begin(9600);
}

void loop() {
    sensorValue = analogRead(sensorPin);
    Serial.println(sensorValue);
    sprintf(resultstr, "reading: %i", sensorValue);
    Particle.publish("reading", resultstr);
    delay(1000);
}
