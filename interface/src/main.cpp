#include <Arduino.h>
#include "config.hpp"

void setup() 
{
#ifdef DEBUG
    Serial.begin(9600);
    while (!Serial.availableForWrite())
    {
        // busy wait
    }

    Serial.println("init");
#endif
}

void loop()
{
#ifdef DEBUG
    Serial.println("loop!");
#endif
    delay(1000); // delay for 1 second
}