void blinkLED(uint32_t count, uint32_t t_delay)
{
    pinMode(LED_BUILTIN, OUTPUT);
    while (count--)
    {
        digitalWrite(LED_BUILTIN, LOW);  // turn the LED on (HIGH is the voltage level)
        delay(t_delay);                  // wait for a bit
        digitalWrite(LED_BUILTIN, HIGH); // turn the LED off by making the voltage LOW
        delay(t_delay);                  // wait for a bit
    }
}

void blinkRed(uint32_t count, uint32_t t_delay)
{
    pinMode(LEDR, OUTPUT);
    while (count--)
    {
        digitalWrite(LEDR, LOW);        // turn the LED on (HIGH is the voltage level)
        delay(t_delay);                 // wait for a bit
        digitalWrite(LEDR, HIGH);       // turn the LED off by making the voltage LOW
        delay(t_delay);                 // wait for a bit
    }
}

void blinkBlue(uint32_t count, uint32_t t_delay)
{
    pinMode(LEDB, OUTPUT);
    while (count--)
    {
        digitalWrite(LEDB, LOW);        // turn the LED on (HIGH is the voltage level)
        delay(t_delay);                 // wait for a bit
        digitalWrite(LEDB, HIGH);       // turn the LED off by making the voltage LOW
        delay(t_delay);                 // wait for a bit
    }
}
