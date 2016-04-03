// headers
int blip(String len);

int ledPin = D7;      // built-in LED
int anotherPin = D0;  // not the built-in LED
int d = 0;

// app
void setup() {
    pinMode(ledPin, OUTPUT);
    pinMode(anotherPin, OUTPUT);
    digitalWrite(ledPin, LOW);
    digitalWrite(anotherPin, LOW);
    Spark.function("blip", blip);
}

void loop() {
}

// functions
int blip(String len) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(anotherPin, HIGH);
    if (len == "SLOW") {
        delay(2000);
    } else if (len == "FAST") {
        delay(100);
    }
    digitalWrite(ledPin, LOW);
    digitalWrite(anotherPin, LOW);

    if ((len != "SLOW") && (len != "FAST")) {
        return -1;
    } else {
        return 1;
    }
}
