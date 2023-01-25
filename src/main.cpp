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
// #define BRAKE_PRESSURE

VirtualTimerGroup timer_group;

#ifdef WHEELS
CANSignal<float, 0, 16, CANTemplateConvertFloat(0.1), CANTemplateConvertFloat(0)> fl_wheel_speed;
CANSignal<float, 0, 16, CANTemplateConvertFloat(0.1), CANTemplateConvertFloat(0)> fr_wheel_speed;
CANSignal<float, 0, 16, CANTemplateConvertFloat(0.1), CANTemplateConvertFloat(0)> bl_wheel_speed;
CANSignal<float, 0, 16, CANTemplateConvertFloat(0.1), CANTemplateConvertFloat(0)> br_wheel_speed;

CANSignal<float, 16, 16, CANTemplateConvertFloat(0.1), CANTemplateConvertFloat(-40)> fl_brake_temperature;
CANSignal<float, 16, 16, CANTemplateConvertFloat(0.1), CANTemplateConvertFloat(-40)> fr_brake_temperature;
CANSignal<float, 16, 16, CANTemplateConvertFloat(0.1), CANTemplateConvertFloat(-40)> bl_brake_temperature;
CANSignal<float, 16, 16, CANTemplateConvertFloat(0.1), CANTemplateConvertFloat(-40)> br_brake_temperature;

// CANRXMessage<2> fl_wheel_msg{can_bus, 0x400, test_callback, fl_wheel_speed, fl_brake_temperature};
// CANRXMessage<2> fr_wheel_msg{can_bus, 0x401, test_callback, fr_wheel_speed, fr_brake_temperature};
// CANRXMessage<2> bl_wheel_msg{can_bus, 0x402, test_callback_never_receive, bl_brake_temperature};
// CANRXMessage<2> br_wheel_msg{can_bus, 0x403, test_callback_never_receive, br_brake_temperature};
#endif

#ifdef BRAKE_PRESSURE
CANSignal<uint16_t, 0, 16, CANTemplateConvertFloat(1), CANTemplateConvertFloat(0)> front_brake_pressure;
CANSignal<uint16_t, 16, 16, CANTemplateConvertFloat(1), CANTemplateConvertFloat(0)> rear_brake_pressure;
CANRXMessage<1> front_brake_pressure_msg{can_bus, 0x410, front_brake_pressure};
CANRXMessage<1> back_brake_pressure_msg{can_bus, 0x411, rear_brake_pressure};
#endif

void print()
{
  // rx on teensy
  Serial.print("Received fl_wheel_speed: ");
  Serial.print(float(fl_wheel_speed));
  Serial.print("\n");
  Serial.print("Received fr_wheel_speed: ");
  Serial.print(float(fr_wheel_speed));
  Serial.print("\n");
  Serial.print("Received bl_wheel_speed: ");
  Serial.print(float(bl_wheel_speed));
  Serial.print("\n");
  Serial.print("Received br_wheel_speed: ");
  Serial.print(float(br_wheel_speed));
  Serial.print("\n");
  Serial.print("Received fl_brake_temperature: ");
  Serial.print(float(fl_brake_temperature));
  Serial.print("\n");
  Serial.print("Received fr_brake_temperature: ");
  Serial.print(float(fr_brake_temperature));
  Serial.print("\n");
  Serial.print("Received bl_brake_temperature: ");
  Serial.print(float(bl_brake_temperature));
  Serial.print("\n");
  Serial.print("Received br_brake_temperature: ");
  Serial.print(float(br_brake_temperature));
  Serial.print("\n");
  delay(10);
}

void test_callback(){
  Serial.print("Called back!");
  print();
}

void test_callback_never_receive(){
  Serial.print("I should never be printed!");
}

CANRXMessage<2> fl_wheel_msg{can_bus, 0x400, test_callback, fl_wheel_speed, fl_brake_temperature};
CANRXMessage<2> fr_wheel_msg{can_bus, 0x401, test_callback, fr_wheel_speed, fr_brake_temperature};
CANRXMessage<2> bl_wheel_msg{can_bus, 0x402, test_callback_never_receive, bl_wheel_speed, bl_brake_temperature};
CANRXMessage<2> br_wheel_msg{can_bus, 0x403, test_callback_never_receive, bl_wheel_speed, br_brake_temperature};

void setup()
{
  Serial.begin(9600);
  Serial.println("Started");
  can_bus.Initialize(ICAN::BaudRate::kBaud1M);
  // timer_group.AddTimer(1000, print);
}

void loop()
{
  timer_group.Tick(millis());
  can_bus.Tick();
}