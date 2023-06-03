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
    can_bus.RegisterRXMessage(PDM_Rails_RX_Message);
    can_bus.RegisterRXMessage(PDM_Devices_RX_Message);
#endif
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

void LPBus::UpdateValues()
{
    FL_Wheel_Speed_Signal = (FL_Wheel_Speed_Signal < 100) ? FL_Wheel_Speed_Signal + 0.1 : 0;
    FL_Brake_Temperature_Signal = (FL_Brake_Temperature_Signal < 200) ? FL_Brake_Temperature_Signal + 1 : 40;
    FR_Wheel_Speed_Signal = (FR_Wheel_Speed_Signal < 100) ? FR_Wheel_Speed_Signal + 0.1 : 0;
    FR_Brake_Temperature_Signal = (FR_Brake_Temperature_Signal < 300) ? FR_Brake_Temperature_Signal + 4 : 40;
    BL_Wheel_Speed_Signal = (BL_Wheel_Speed_Signal < 100) ? BL_Wheel_Speed_Signal + 0.1 : 0;
    BL_Brake_Temperature_Signal = (BL_Brake_Temperature_Signal < 400) ? BL_Brake_Temperature_Signal + 3 : 40;
    BR_Wheel_Speed_Signal = (BR_Wheel_Speed_Signal < 100) ? BR_Wheel_Speed_Signal + 0.1 : 0;
    BR_Brake_Temperature_Signal = (BR_Brake_Temperature_Signal < 500) ? BR_Brake_Temperature_Signal + 5 : 40;
    Motor_Temperature_Signal = (Motor_Temperature_Signal < 100) ? Motor_Temperature_Signal + 1 : -40;
    Coolant_Temperature_Signal = (Coolant_Temperature_Signal < 100) ? Coolant_Temperature_Signal + 1 : -40;
    Ambient_Temperature_Signal = (Ambient_Temperature_Signal < 100) ? Ambient_Temperature_Signal + 1 : -40;
    Latitude_Signal = (Latitude_Signal < 420686684) ? Latitude_Signal + 10 : 420586684;
    Longitude_Signal = (Longitude_Signal < -875745819) ? Longitude_Signal + 10 : -876745819;
    Accel_X_Signal = (Accel_X_Signal < 2) ? Accel_X_Signal + 0.1 : -2;
    Accel_Y_Signal = (Accel_Y_Signal < 2) ? Accel_Y_Signal + 0.1 : -2;
    Accel_Z_Signal = (Accel_Z_Signal < 2) ? Accel_Z_Signal + 0.1 : -2;
    Gyro_X_Signal = (Gyro_X_Signal < 2) ? Gyro_X_Signal + 0.1 : -2;
    Gyro_Y_Signal = (Gyro_Y_Signal < 2) ? Gyro_Y_Signal + 0.1 : -2;
    Gyro_Z_Signal = (Gyro_Z_Signal < 2) ? Gyro_Z_Signal + 0.1 : -2;
    RTC_Signal = (RTC_Signal < 1685735565) ? RTC_Signal + 1 : 1685735565;
    Front_Brake_Pressure_Signal = (Front_Brake_Pressure_Signal < 100) ? Front_Brake_Pressure_Signal + 1 : 0;
    Back_Brake_Pressure_Signal = (Back_Brake_Pressure_Signal < 100) ? Back_Brake_Pressure_Signal + 1 : 0;
    V5_Rail_Signal = (V5_Rail_Signal < 5) ? V5_Rail_Signal + 1 : 0;
    V12_Rail_Signal = (V12_Rail_Signal < 12) ? V12_Rail_Signal + 1 : 0;
    Vbat_Rail_Signal = (Vbat_Rail_Signal < 5) ? Vbat_Rail_Signal + 1 : 0;
    Vbat_Input_Current_Signal = (Vbat_Input_Current_Signal < 300) ? Vbat_Input_Current_Signal + 1 : 0;
    Vbat_Input_Voltage_Signal = (Vbat_Input_Voltage_Signal < 20) ? Vbat_Input_Voltage_Signal + 1 : 10;
    Air_Cooling_Fan_Signal = (Air_Cooling_Fan_Signal < 100) ? Air_Cooling_Fan_Signal + 1 : 0;
    Liquid_Cooling_Fan_Signal = (Liquid_Cooling_Fan_Signal < 100) ? Liquid_Cooling_Fan_Signal + 1 : 0;
    Liquid_Cooling_Pump_Signal = (Liquid_Cooling_Pump_Signal < 100) ? Liquid_Cooling_Pump_Signal + 1 : 0;
    High_Side_Driver_1_Signal = (High_Side_Driver_1_Signal < 100) ? High_Side_Driver_1_Signal + 1 : 0;
    High_Side_Driver_2_Signal = (High_Side_Driver_2_Signal < 100) ? High_Side_Driver_2_Signal + 1 : 0;
    IMD_State_Signal = (IMD_State_Signal < 4) ? IMD_State_Signal + 1 : 0;
}
