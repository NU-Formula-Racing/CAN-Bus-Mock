#include <Arduino.h>
#include "virtualTimer.h"

#if defined(ARDUINO_TEENSY40) || defined(ARDUINO_TEENSY41)
#include "teensy_can.h"
TeensyCAN<1> can_bus{};
#endif

#ifdef ARDUINO_ARCH_ESP32
#include "esp_can.h"
ESPCAN can_bus{};
#endif

#define WHEELS

VirtualTimerGroup timer_group;

#ifdef WHEELS
CANSignal<float, 0, 16, CANTemplateConvertFloat(0.1), CANTemplateConvertFloat(0), false> fl_wheel_speed;
CANSignal<float, 0, 16, CANTemplateConvertFloat(0.1), CANTemplateConvertFloat(0), false> fr_wheel_speed;
CANSignal<float, 0, 16, CANTemplateConvertFloat(0.1), CANTemplateConvertFloat(0), false> bl_wheel_speed;
CANSignal<float, 0, 16, CANTemplateConvertFloat(0.1), CANTemplateConvertFloat(0), false> br_wheel_speed;

CANSignal<float, 16, 16, CANTemplateConvertFloat(0.1), CANTemplateConvertFloat(-40), false> fl_brake_temperature;
CANSignal<float, 16, 16, CANTemplateConvertFloat(0.1), CANTemplateConvertFloat(-40), false> fr_brake_temperature;
CANSignal<float, 16, 16, CANTemplateConvertFloat(0.1), CANTemplateConvertFloat(-40), false> bl_brake_temperature;
CANSignal<float, 16, 16, CANTemplateConvertFloat(0.1), CANTemplateConvertFloat(-40), false> br_brake_temperature;

CANTXMessage<2> fl_wheel_msg{can_bus, 0x400, 6, 100, timer_group, fl_wheel_speed, fl_brake_temperature};
CANTXMessage<2> fr_wheel_msg{can_bus, 0x401, 6, 100, timer_group, fr_wheel_speed, fr_brake_temperature};
CANTXMessage<2> bl_wheel_msg{can_bus, 0x402, 6, 100, timer_group, bl_wheel_speed, bl_brake_temperature};
CANTXMessage<2> br_wheel_msg{can_bus, 0x403, 6, 100, timer_group, br_wheel_speed, br_brake_temperature};
#endif

enum state
{
  Shutdown = 0,
  Precharge = 1,
  Active = 2,
  Charging = 3,
  Fault = 4
};
enum fault
{
  Faulted = 1,
  NotFaulted = 0
};
CANSignal<state, 48, 8, CANTemplateConvertFloat(1), CANTemplateConvertFloat(0), false> bms_state;
CANTXMessage<1> bms_status_msg{can_bus, 0x241, 8, 100, timer_group, bms_state};
CANSignal<state, 0, 1, CANTemplateConvertFloat(1), CANTemplateConvertFloat(0), false> fault_summary;
CANRXMessage<1> bms_fault_msg{can_bus, 0x250, fault_summary};

void randWrite()
{
  fl_wheel_speed = random(max(1.0, fl_wheel_speed - 1.0) * 1000, min(90.0, fl_wheel_speed + 1.0) * 1000) / 1000.0f;
  fr_wheel_speed = random(max(1.0, fl_wheel_speed - 1.0) * 1000, min(90.0, fl_wheel_speed + 1.0) * 1000) / 1000.0f;
  bl_wheel_speed = random(max(1.0, fl_wheel_speed - 1.0) * 1000, min(90.0, fl_wheel_speed + 1.0) * 1000) / 1000.0f;
  br_wheel_speed = random(max(1.0, fl_wheel_speed - 1.0) * 1000, min(90.0, fl_wheel_speed + 1.0) * 1000) / 1000.0f;

  if (bms_state == Shutdown)
  {
    bms_state = Precharge;
  }
  else
  {
    bms_state = Shutdown;
  }

  Serial.print("Sent fl_wheel_speed: ");
  Serial.print(fl_wheel_speed);
  Serial.print("\n");
  Serial.print("Sent bms_state: ");
  Serial.print(bms_state);
  Serial.print("\n");
  Serial.print("Print fault_summary: ");
  Serial.print(fault_summary);
  Serial.print("\n");
  // Serial.print("\n");
  // Serial.print("Sent front_brake_pressure: ");
  // Serial.print(front_brake_pressure);
  // Serial.print("\n");

  can_bus.Tick();
}

void setup()
{
  Serial.begin(9600);
  Serial.println("Started");
  can_bus.Initialize(ICAN::BaudRate::kBaud1M);
  timer_group.AddTimer(100, randWrite);
}

void loop()
{
  timer_group.Tick(millis());
}