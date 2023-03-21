#define IN1 3
#define IN2 4
#define EN 5

#define INTERRUPT_PIN 33

volatile int count = 0;
volatile unsigned long lastInterruptTime = 0;

int lastCount;

void setup()
{
    Serial.begin(9600);

    pinMode(INTERRUPT_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), counter, RISING);

    lastCount = count;
}

void loop()
{
    int aux = count;
    if (aux != lastCount)
    {
        lastCount = aux;
        Serial.println(lastCount);
    }
}

IRAM_ATTR void counter()
{
    if ((millis() - lastInterruptTime) >= 5)
    {
        lastInterruptTime = millis();
        ++count;
    }
}