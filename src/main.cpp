#include <Arduino.h>

#if defined(ARDUINO_TEENSY40) || defined(ARDUINO_TEENSY41)
#include "teensy_can.h"
TeensyCAN<1> can_bus{};
#endif

#ifdef ARDUINO_ARCH_ESP32
#include "esp_can.h"
ESPCAN can_bus{};
#endif

void setup()
{
  ;
}

std::chrono::milliseconds next_tick_time = std::chrono::milliseconds(millis());
std::chrono::milliseconds kTickPeriod{10};

void loop()
{
  ;
}