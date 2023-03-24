#define SENSOR D5

volatile int counter = 0;
int last_counter = 0;

void setup() {
  Serial.begin(9600);
  pinMode(SENSOR, INPUT_PULLUP);

  attachInterrupt(SENSOR, increment, RISING);
}

ICACHE_RAM_ATTR void increment() {
  ++counter;
}

void loop() {

  if (counter > last_counter) {
    Serial.println(counter);
    last_counter = counter;
  }
}
