#include <Arduino.h>

#if defined(ARDUINO_TEENSY40) || defined(ARDUINO_TEENSY41)
#include "teensy_can.h"
TeensyCAN<1> can_bus{};
#endif

#ifdef ARDUINO_ARCH_ESP32
#include "esp_can.h"
ESPCAN can_bus{};
#endif

#define WHEELS
#define BRAKE_PRESSURE

#ifdef WHEELS
CANSignal<float, 0, 16, CANTemplateConvertFloat(0.1), CANTemplateConvertFloat(0)> fl_wheel_speed;
CANSignal<float, 0, 16, CANTemplateConvertFloat(0.1), CANTemplateConvertFloat(0)> fr_wheel_speed;
CANSignal<float, 0, 16, CANTemplateConvertFloat(0.1), CANTemplateConvertFloat(0)> bl_wheel_speed;
CANSignal<float, 0, 16, CANTemplateConvertFloat(0.1), CANTemplateConvertFloat(0)> br_wheel_speed;

CANSignal<float, 16, 16, CANTemplateConvertFloat(0.1), CANTemplateConvertFloat(-40)> fl_brake_temperature;
CANSignal<float, 16, 16, CANTemplateConvertFloat(0.1), CANTemplateConvertFloat(-40)> fr_brake_temperature;
CANSignal<float, 16, 16, CANTemplateConvertFloat(0.1), CANTemplateConvertFloat(-40)> bl_brake_temperature;
CANSignal<float, 16, 16, CANTemplateConvertFloat(0.1), CANTemplateConvertFloat(-40)> br_brake_temperature;

CANTXMessage<2> fl_wheel_msg{can_bus, 0x400, 6, std::chrono::milliseconds{100}, fl_wheel_speed, fl_brake_temperature};
CANTXMessage<2> fr_wheel_msg{can_bus, 0x401, 6, std::chrono::milliseconds{100}, fr_wheel_speed, fr_brake_temperature};
CANTXMessage<2> bl_wheel_msg{can_bus, 0x402, 6, std::chrono::milliseconds{100}, bl_wheel_speed, bl_brake_temperature};
CANTXMessage<2> br_wheel_msg{can_bus, 0x403, 6, std::chrono::milliseconds{100}, br_wheel_speed, br_brake_temperature};
#endif

#ifdef BRAKE_PRESSURE
CANSignal<uint16_t, 0, 16, CANTemplateConvertFloat(1), CANTemplateConvertFloat(0)> front_brake_pressure;
CANSignal<uint16_t, 16, 16, CANTemplateConvertFloat(1), CANTemplateConvertFloat(0)> rear_brake_pressure;

CANTXMessage<2> brake_pressure_msg{can_bus, 0x410, 4, std::chrono::milliseconds{100}, front_brake_pressure, rear_brake_pressure};
#endif

constexpr uint8_t potentiometer_pin{34};

void setup()
{
  can_bus.Initialize(ICAN::BaudRate::kBaud1M);
}

std::chrono::milliseconds next_tick_time = std::chrono::milliseconds(millis());
std::chrono::milliseconds kTickPeriod{10};

void loop()
{
  fl_wheel_speed = random(max(0.0, fl_wheel_speed - 0.1) * 1000, min(90.0, fl_wheel_speed + 0.1) * 1000) / 1000.0f;
  fr_wheel_speed = random(max(0.0, fl_wheel_speed - 0.1) * 1000, min(90.0, fl_wheel_speed + 0.1) * 1000) / 1000.0f;
  bl_wheel_speed = random(max(0.0, fl_wheel_speed - 0.1) * 1000, min(90.0, fl_wheel_speed + 0.1) * 1000) / 1000.0f;
  br_wheel_speed = random(max(0.0, fl_wheel_speed - 0.1) * 1000, min(90.0, fl_wheel_speed + 0.1) * 1000) / 1000.0f;

  fl_brake_temperature = 90;
  fr_brake_temperature = 90;
  bl_brake_temperature = 90;
  br_brake_temperature = 90;

  front_brake_pressure = map(analogRead(potentiometer_pin), 0, 4096, 0, 10000);
  rear_brake_pressure = map(analogRead(potentiometer_pin), 0, 4096, 0, 10000);
  while (std::chrono::milliseconds(millis()) < next_tick_time)
  {
  }
  next_tick_time = std::chrono::milliseconds(millis()) + kTickPeriod;
  fl_wheel_msg.Tick(kTickPeriod);
  fr_wheel_msg.Tick(kTickPeriod);
  bl_wheel_msg.Tick(kTickPeriod);
  br_wheel_msg.Tick(kTickPeriod);
  brake_pressure_msg.Tick(kTickPeriod);
}