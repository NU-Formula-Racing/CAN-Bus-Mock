#include <Arduino.h>
#include "virtualTimer.h"
#include <fstream>

#if defined(ARDUINO_TEENSY40) || defined(ARDUINO_TEENSY41)
#include "teensy_can.h"
TeensyCAN<1> can_bus{};
#endif

#ifdef ARDUINO_ARCH_ESP32
#include "esp_can.h"
ESPCAN can_bus{GPIO_NUM_32, GPIO_NUM_27};
#endif


constexpr uint8_t potentiometer_pin{34};
VirtualTimerGroup timer_group;

CANSignal<float, 0, 16, CANTemplateConvertFloat(0.1), CANTemplateConvertFloat(0), false> fl_wheel_speed;
CANSignal<float, 0, 16, CANTemplateConvertFloat(0.1), CANTemplateConvertFloat(0), false> fr_wheel_speed;
CANSignal<float, 0, 16, CANTemplateConvertFloat(0.1), CANTemplateConvertFloat(0), false> bl_wheel_speed;
CANSignal<float, 0, 16, CANTemplateConvertFloat(0.1), CANTemplateConvertFloat(0), false> br_wheel_speed;

CANSignal<float, 16, 16, CANTemplateConvertFloat(0.1), CANTemplateConvertFloat(-40), false> fl_brake_temperature;
CANSignal<float, 16, 16, CANTemplateConvertFloat(0.1), CANTemplateConvertFloat(-40), false> fr_brake_temperature;
CANSignal<float, 16, 16, CANTemplateConvertFloat(0.1), CANTemplateConvertFloat(-40), false> bl_brake_temperature;
CANSignal<float, 16, 16, CANTemplateConvertFloat(0.1), CANTemplateConvertFloat(-40), false> br_brake_temperature;

CANRXMessage<2> fl_wheel_msg{can_bus, 0x400, fl_wheel_speed, fl_brake_temperature};
CANRXMessage<2> fr_wheel_msg{can_bus, 0x401, fr_wheel_speed, fr_brake_temperature};
CANRXMessage<2> bl_wheel_msg{can_bus, 0x402, bl_wheel_speed, bl_brake_temperature};
CANRXMessage<2> br_wheel_msg{can_bus, 0x403, br_wheel_speed, br_brake_temperature};

void readBus()
{
  Serial.print(millis());
  Serial.print(",");
  Serial.print(fl_wheel_speed);
  Serial.print(",");
  Serial.print(fr_wheel_speed);
  Serial.print(",");
  Serial.print(bl_wheel_speed);
  Serial.print(",");
  Serial.print(br_wheel_speed);
  Serial.print(",");
  Serial.print(fl_brake_temperature);
  Serial.print(",");
  Serial.print(fr_brake_temperature);
  Serial.print(",");
  Serial.print(bl_brake_temperature);
  Serial.print(",");
  Serial.print(br_brake_temperature);
  Serial.print("\n");
  can_bus.Tick();
}

void setup()
{
  Serial.begin(115200);
  can_bus.Initialize(ICAN::BaudRate::kBaud1M);
  can_bus.RegisterRXMessage(fl_wheel_msg);
  can_bus.RegisterRXMessage(fr_wheel_msg);
  can_bus.RegisterRXMessage(br_wheel_msg);
  can_bus.RegisterRXMessage(bl_wheel_msg);

  timer_group.AddTimer(10, readBus);
}

void loop()
{
  timer_group.Tick(millis());
}