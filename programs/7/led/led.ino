#define LED    2

int light;

void setup()
{
    pinMode(LED, OUTPUT);
    light = LOW;
}

void loop()
{
    digitalWrite(LED, light);
    if (light == HIGH) {
        light = LOW;
    } else {
        light = HIGH;
    }
    delay(1000);
}
