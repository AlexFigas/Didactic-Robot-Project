
// #include "Expander.h"

// #define IN1 3
// #define IN2 4
// #define EN 5

// #define INTERRUPT_PIN 2

// Expander expander = Expander();

// int count = 0;

// void setup()
// {
//     expander.begin();
//     expander.setDutyCycle(EN, 100);
//     expander.setDutyCycle(IN1, 100);
//     expander.setDutyCycle(IN2, 0);

//     pinMode(INTERRUPT_PIN, INPUT);
//     attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), counter, RISING);

//     delay(5000);
// }

// void loop()
// {
//     // put your main code here, to run repeatedly:
//     if (count >= 1)
//     {
//         expander.setDutyCycle(EN, 0);
//     }
// }

// void counter()
// {
//     count++;
// }