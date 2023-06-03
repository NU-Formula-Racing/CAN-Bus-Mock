#include <Arduino.h>
#include <LPBus.h>
#include <can_interface.h>

void LPBus::Initialize()
{
    // initialize bus
    can_bus.Initialize(ICAN::BaudRate::kBaud1M);
#if defined(ARDUINO_TEENSY40) || defined(ARDUINO_TEENSY41)
    // register all messages
    can_bus.RegisterRXMessage(FL_Wheel_RX_Message);
    can_bus.RegisterRXMessage(FR_Wheel_RX_Message);
    can_bus.RegisterRXMessage(BL_Wheel_RX_Message);
    can_bus.RegisterRXMessage(BR_Wheel_RX_Message);
    can_bus.RegisterRXMessage(Ptrain_Temps_RX_Message);
    can_bus.RegisterRXMessage(GPS_RX_Message);
    can_bus.RegisterRXMessage(Accelerometer_RX_Message);
    can_bus.RegisterRXMessage(Gyroscope_RX_Message);
    can_bus.RegisterRXMessage(Brake_Pressure_RX_Message);
#endif
}

template <typename Signal_Value>
Signal_Value Ramp(int16_t start, int16_t finish, int16_t step, Signal_Value signal)
{
    if (signal < finish)
    {
        signal += step;
    }
    else
    {
        signal = start;
    }
    return signal;
}

void LPBus::UpdateValues()
{
    FL_Wheel_Speed_Signal = Ramp(0, 100, 1, FL_Wheel_Speed_Signal);
    FL_Brake_Temperature_Signal = Ramp(40, 200, 1, FL_Brake_Temperature_Signal);
    FR_Wheel_Speed_Signal = Ramp(0, 100, 1, FR_Wheel_Speed_Signal);
    FR_Brake_Temperature_Signal = Ramp(40, 300, 4, FR_Brake_Temperature_Signal);
    BL_Wheel_Speed_Signal = Ramp(0, 100, 1, BL_Wheel_Speed_Signal);
    BL_Brake_Temperature_Signal = Ramp(40, 400, 3, BL_Brake_Temperature_Signal);
    BR_Wheel_Speed_Signal = Ramp(0, 100, 1, BR_Wheel_Speed_Signal);
    BR_Brake_Temperature_Signal = Ramp(40, 500, 5, BR_Brake_Temperature_Signal);
    Motor_Temperature_Signal = Ramp(-40, 100, 1, Motor_Temperature_Signal);
    Coolant_Temperature_Signal = Ramp(-40, 100, 1, Coolant_Temperature_Signal);
    Ambient_Temperature_Signal = Ramp(-40, 100, 1, Ambient_Temperature_Signal);
    Latitude_Signal = Ramp(420586684, 420686684, 10, Latitude_Signal);
    Longitude_Signal = Ramp(-876745819, -875745819, 10, Longitude_Signal);
    Accel_X_Signal = Ramp(-2, 2, 0.1, Accel_X_Signal);
    Accel_Y_Signal = Ramp(-2, 2, 0.1, Accel_Y_Signal);
    Accel_Z_Signal = Ramp(-2, 2, 0.1, Accel_Z_Signal);
    Gyro_X_Signal = Ramp(-2, 2, 0.1, Gyro_X_Signal);
    Gyro_Y_Signal = Ramp(-2, 2, 0.1, Gyro_Y_Signal);
    Gyro_Z_Signal = Ramp(-2, 2, 0.1, Gyro_Z_Signal);
    RTC_Signal = Ramp(1685735565, 1685735565, 1, RTC_Signal);
    Front_Brake_Pressure_Signal = Ramp(0, 100, 1, Front_Brake_Pressure_Signal);
    Back_Brake_Pressure_Signal = Ramp(0, 100, 1, Back_Brake_Pressure_Signal);
}
