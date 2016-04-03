int sensorValue = 0;
int sensorPin = A0;

void setup() {
    pinMode(A0, INPUT);
    Serial.begin(9600);
    Spark.variable("reading", &sensorValue, INT);
}

void loop() {
    sensorValue = analogRead(sensorPin);
    Serial.println(sensorValue);
    delay(100);
}
