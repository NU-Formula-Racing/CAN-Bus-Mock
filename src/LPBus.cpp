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

void LPBus::RandomValues()
{
    FL_Wheel_Speed_Signal = random(max(0.0, FL_Wheel_Speed_Signal - 0.1) * 1000, min(90.0, FL_Wheel_Speed_Signal + 0.1) * 1000) / 1000.0f;
    FL_Brake_Temperature_Signal = random(max(40.0, FL_Brake_Temperature_Signal - 0.1) * 1000, min(200.0, FL_Brake_Temperature_Signal + 0.1) * 1000) / 1000.0f;
    FR_Wheel_Speed_Signal = random(max(0.0, FR_Wheel_Speed_Signal - 0.1) * 1000, min(90.0, FR_Wheel_Speed_Signal + 0.1) * 1000) / 1000.0f;
    FR_Brake_Temperature_Signal = random(max(40.0, FR_Brake_Temperature_Signal - 0.1) * 1000, min(300.0, FR_Brake_Temperature_Signal + 0.1) * 1000) / 1000.0f;
    BL_Wheel_Speed_Signal = random(max(0.0, BL_Wheel_Speed_Signal - 0.1) * 1000, min(90.0, BL_Wheel_Speed_Signal + 0.1) * 1000) / 1000.0f;
    BL_Brake_Temperature_Signal = random(max(40.0, BL_Brake_Temperature_Signal - 0.1) * 1000, min(400.0, BL_Brake_Temperature_Signal + 0.1) * 1000) / 1000.0f;
    BR_Wheel_Speed_Signal = random(max(0.0, BR_Wheel_Speed_Signal - 0.1) * 1000, min(90.0, BR_Wheel_Speed_Signal + 0.1) * 1000) / 1000.0f;
    BR_Brake_Temperature_Signal = random(max(40.0, BR_Brake_Temperature_Signal - 0.1) * 1000, min(500.0, BR_Brake_Temperature_Signal + 0.1) * 1000) / 1000.0f;
    Motor_Temperature_Signal = random(max(-40.0, Motor_Temperature_Signal - 0.1) * 1000, min(100.0, Motor_Temperature_Signal + 0.1) * 1000) / 1000.0f;
    Coolant_Temperature_Signal = random(max(-40.0, Coolant_Temperature_Signal - 0.1) * 1000, min(100.0, Coolant_Temperature_Signal + 0.1) * 1000) / 1000.0f;
    Ambient_Temperature_Signal = random(max(-40.0, Ambient_Temperature_Signal - 0.1) * 1000, min(100.0, Ambient_Temperature_Signal + 0.1) * 1000) / 1000.0f;
    Latitude_Signal = random(max(420586684.0, Latitude_Signal - 0.1) * 1000, min(420686684.0, Latitude_Signal + 0.1) * 1000) / 1000.0f;
    Longitude_Signal = random(max(-876745819.0, Longitude_Signal - 0.1) * 1000, min(-875745819.0, Longitude_Signal + 0.1) * 1000) / 1000.0f;
    Accel_X_Signal = random(max(-2.0, Accel_X_Signal - 0.1) * 1000, min(2.0, Accel_X_Signal + 0.1) * 1000) / 1000.0f;
    Accel_Y_Signal = random(max(-2.0, Accel_Y_Signal - 0.1) * 1000, min(2.0, Accel_Y_Signal + 0.1) * 1000) / 1000.0f;
    Accel_Z_Signal = random(max(-2.0, Accel_Z_Signal - 0.1) * 1000, min(2.0, Accel_Z_Signal + 0.1) * 1000) / 1000.0f;
    Gyro_X_Signal = random(max(-2.0, Gyro_X_Signal - 0.1) * 1000, min(2.0, Gyro_X_Signal + 0.1) * 1000) / 1000.0f;
    Gyro_Y_Signal = random(max(-2.0, Gyro_Y_Signal - 0.1) * 1000, min(2.0, Gyro_Y_Signal + 0.1) * 1000) / 1000.0f;
    Gyro_Z_Signal = random(max(-2.0, Gyro_Z_Signal - 0.1) * 1000, min(2.0, Gyro_Z_Signal + 0.1) * 1000) / 1000.0f;
    RTC_Signal = random(max(1685735565.0, RTC_Signal - 0.1) * 1000, min(1685735565.0, RTC_Signal + 0.1) * 1000) / 1000.0f;
    Front_Brake_Pressure_Signal = random(max(0.0, Front_Brake_Pressure_Signal - 0.1) * 1000, min(100.0, Front_Brake_Pressure_Signal + 0.1) * 1000) / 1000.0f;
    Back_Brake_Pressure_Signal = random(max(0.0, Back_Brake_Pressure_Signal - 0.1) * 1000, min(100.0, Back_Brake_Pressure_Signal + 0.1) * 1000) / 1000.0f;
    V5_Rail_Signal = random(max(0.0, V5_Rail_Signal - 0.1) * 1000, min(5.0, V5_Rail_Signal + 0.1) * 1000) / 1000.0f;
    V12_Rail_Signal = random(max(0.0, V12_Rail_Signal - 0.1) * 1000, min(12.0, V12_Rail_Signal + 0.1) * 1000) / 1000.0f;
    Vbat_Rail_Signal = random(max(0.0, Vbat_Rail_Signal - 0.1) * 1000, min(5.0, Vbat_Rail_Signal + 0.1) * 1000) / 1000.0f;
    Vbat_Input_Current_Signal = random(max(0.0, Vbat_Input_Current_Signal - 0.1) * 1000, min(300.0, Vbat_Input_Current_Signal + 0.1) * 1000) / 1000.0f;
    Vbat_Input_Voltage_Signal = random(max(10.0, Vbat_Input_Voltage_Signal - 0.1) * 1000, min(20.0, Vbat_Input_Voltage_Signal + 0.1) * 1000) / 1000.0f;
    Air_Cooling_Fan_Signal = random(max(0.0, Air_Cooling_Fan_Signal - 0.1) * 1000, min(100.0, Air_Cooling_Fan_Signal + 0.1) * 1000) / 1000.0f;
    Liquid_Cooling_Fan_Signal = random(max(0.0, Liquid_Cooling_Fan_Signal - 0.1) * 1000, min(100.0, Liquid_Cooling_Fan_Signal + 0.1) * 1000) / 1000.0f;
    Liquid_Cooling_Pump_Signal = random(max(0.0, Liquid_Cooling_Pump_Signal - 0.1) * 1000, min(100.0, Liquid_Cooling_Pump_Signal + 0.1) * 1000) / 1000.0f;
    High_Side_Driver_1_Signal = random(max(0.0, High_Side_Driver_1_Signal - 0.1) * 1000, min(100.0, High_Side_Driver_1_Signal + 0.1) * 1000) / 1000.0f;
    High_Side_Driver_2_Signal = random(max(0.0, High_Side_Driver_2_Signal - 0.1) * 1000, min(100.0, High_Side_Driver_2_Signal + 0.1) * 1000) / 1000.0f;
    IMD_State_Signal = random(max(0.0, IMD_State_Signal - 0.1) * 1000, min(4.0, IMD_State_Signal + 0.1) * 1000) / 1000.0f;
}

// void LPBus::UpdateValues()
// {
//     FL_Wheel_Speed_Signal = Ramp(0, 100, 1, FL_Wheel_Speed_Signal);
//     FL_Brake_Temperature_Signal = Ramp(40, 200, 1, FL_Brake_Temperature_Signal);
//     FR_Wheel_Speed_Signal = Ramp(0, 100, 1, FR_Wheel_Speed_Signal);
//     FR_Brake_Temperature_Signal = Ramp(40, 300, 4, FR_Brake_Temperature_Signal);
//     BL_Wheel_Speed_Signal = Ramp(0, 100, 1, BL_Wheel_Speed_Signal);
//     BL_Brake_Temperature_Signal = Ramp(40, 400, 3, BL_Brake_Temperature_Signal);
//     BR_Wheel_Speed_Signal = Ramp(0, 100, 1, BR_Wheel_Speed_Signal);
//     BR_Brake_Temperature_Signal = Ramp(40, 500, 5, BR_Brake_Temperature_Signal);
//     Motor_Temperature_Signal = Ramp(-40, 100, 1, Motor_Temperature_Signal);
//     Coolant_Temperature_Signal = Ramp(-40, 100, 1, Coolant_Temperature_Signal);
//     Ambient_Temperature_Signal = Ramp(-40, 100, 1, Ambient_Temperature_Signal);
//     Latitude_Signal = Ramp(420586684, 420686684, 10, Latitude_Signal);
//     Longitude_Signal = Ramp(-876745819, -875745819, 10, Longitude_Signal);
//     Accel_X_Signal = Ramp(-2, 2, 0.1, Accel_X_Signal);
//     Accel_Y_Signal = Ramp(-2, 2, 0.1, Accel_Y_Signal);
//     Accel_Z_Signal = Ramp(-2, 2, 0.1, Accel_Z_Signal);
//     Gyro_X_Signal = Ramp(-2, 2, 0.1, Gyro_X_Signal);
//     Gyro_Y_Signal = Ramp(-2, 2, 0.1, Gyro_Y_Signal);
//     Gyro_Z_Signal = Ramp(-2, 2, 0.1, Gyro_Z_Signal);
//     RTC_Signal = Ramp(1685735565, 1685735565, 1, RTC_Signal);
//     Front_Brake_Pressure_Signal = Ramp(0, 100, 1, Front_Brake_Pressure_Signal);
//     Back_Brake_Pressure_Signal = Ramp(0, 100, 1, Back_Brake_Pressure_Signal);
//     V5_Rail_Signal = Ramp(0, 5, 1, V5_Rail_Signal);
//     V12_Rail_Signal = Ramp(0, 12, 1, V12_Rail_Signal);
//     Vbat_Rail_Signal = Ramp(0, 5, 1, Vbat_Rail_Signal);
//     Vbat_Input_Current_Signal = Ramp(0, 300, 1, Vbat_Input_Current_Signal);
//     Vbat_Input_Voltage_Signal = Ramp(10, 20, 1, Vbat_Input_Voltage_Signal);
//     Air_Cooling_Fan_Signal = Ramp(0, 100, 1, Air_Cooling_Fan_Signal);
//     Liquid_Cooling_Fan_Signal = Ramp(0, 100, 1, Liquid_Cooling_Fan_Signal);
//     Liquid_Cooling_Pump_Signal = Ramp(0, 100, 1, Liquid_Cooling_Pump_Signal);
//     High_Side_Driver_1_Signal = Ramp(0, 100, 1, High_Side_Driver_1_Signal);
//     High_Side_Driver_2_Signal = Ramp(0, 100, 1, High_Side_Driver_2_Signal);
//     IMD_State_Signal = Ramp(0, 4, 1, IMD_State_Signal);
// }
