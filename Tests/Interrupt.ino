#define IN1 3
#define IN2 4
#define EN 5

#define INTERRUPT_PIN 12

volatile int count = 0;

void setup()
{
    Serial.begin(9600);

    pinMode(INTERRUPT_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), counter, RISING);
}

void loop()
{
    Serial.println(count);
}

void counter()
{
    count++;
}
