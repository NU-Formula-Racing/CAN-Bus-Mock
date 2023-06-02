#if defined(ARDUINO_TEENSY40) || defined(ARDUINO_TEENSY41)
#include "teensy_can.h"
#endif

#ifdef ARDUINO_ARCH_ESP32
#include "esp_can.h"
#endif

class LPBus
{
public:
    void Initialize();
    void Randomize();
#if defined(ARDUINO_TEENSY40) || defined(ARDUINO_TEENSY41)
    TeensyCAN<1> can_bus{};
#endif

#ifdef ARDUINO_ARCH_ESP32
    ESPCAN can_bus{};
#endif
    VirtualTimerGroup timer_group{};

private:
    // all signals
    MakeUnsignedCANSignal(float, 0, 16, 0.1, 0) FL_Wheel_Speed_Signal{};
    MakeUnsignedCANSignal(float, 16, 16, 0.1, -40) FL_Brake_Temperature_Signal{};
    MakeUnsignedCANSignal(float, 0, 16, 0.1, 0) FR_Wheel_Speed_Signal{};
    MakeUnsignedCANSignal(float, 16, 16, 0.1, -40) FR_Brake_Temperature_Signal{};
    MakeUnsignedCANSignal(float, 0, 16, 0.1, 0) BL_Wheel_Speed_Signal{};
    MakeUnsignedCANSignal(float, 16, 16, 0.1, -40) BL_Brake_Temperature_Signal{};
    MakeUnsignedCANSignal(float, 0, 16, 0.1, 0) BR_Wheel_Speed_Signal{};
    MakeUnsignedCANSignal(float, 16, 16, 0.1, -40) BR_Brake_Temperature_Signal{};
    MakeUnsignedCANSignal(float, 0, 16, 0.1, -40) Motor_Temperature_Signal{};
    MakeUnsignedCANSignal(float, 16, 16, 0.1, -40) Coolant_Temperature_Signal{};
    MakeUnsignedCANSignal(float, 32, 16, 0.1, -40) Ambient_Temperature_Signal{};
    MakeSignedCANSignal(int32_t, 0, 32, 1.0, 0) Latitude_Signal{};
    MakeSignedCANSignal(int32_t, 32, 32, 1.0, 0) Longitude_Signal{};
    MakeSignedCANSignal(int16_t, 0, 16, 0.0005, 0) Accel_X_Signal{};
    MakeSignedCANSignal(int16_t, 16, 16, 0.0005, 0) Accel_Y_Signal{};
    MakeSignedCANSignal(int16_t, 32, 16, 0.0005, 0) Accel_Z_Signal{};
    MakeSignedCANSignal(int16_t, 0, 16, 0.0005, 0) Gyro_X_Signal{};
    MakeSignedCANSignal(int16_t, 16, 16, 0.0005, 0) Gyro_Y_Signal{};
    MakeSignedCANSignal(int16_t, 32, 16, 0.0005, 0) Gyro_Z_Signal{};
    MakeUnsignedCANSignal(uint32_t, 0, 32, 1.0, 0) RTC_Signal{};
    MakeUnsignedCANSignal(uint16_t, 0, 16, 1.0, 0) Front_Brake_Pressure_Signal{};
    MakeUnsignedCANSignal(uint16_t, 16, 16, 1.0, 0) Back_Brake_Pressure_Signal{};
    // MakeUnsignedCANSignal(dataType, 0, 8, 1.0, 0) Accel_Percentage_Signal{};
    // MakeUnsignedCANSignal(dataType, 8, 8, 1.0, 0) Brake_Percentage_Signal{};
    // MakeUnsignedCANSignal(dataType, 16, 8, 1.0, 0) Torque_Limit_Percentage_Signal{};
    // MakeUnsignedCANSignal(dataType, 0, 12, 0.1, 0) Max_Discharge_Current_Signal{};
    // MakeUnsignedCANSignal(dataType, 12, 12, 0.1, 0) Max_Regen_Current_Signal{};
    // MakeUnsignedCANSignal(dataType, 24, 16, 0.01, 0) Battery_Voltage_Signal{};
    // MakeUnsignedCANSignal(dataType, 40, 8, 1.0, -40) Battery_Temperature_Signal{};
    // MakeUnsignedCANSignal(dataType, 48, 16, 0.01, 0) Battery_Current_Signal{};
    // MakeUnsignedCANSignal(dataType, 0, 1, 1.0, 0) Fault_Summary_Signal{};
    // MakeUnsignedCANSignal(dataType, 1, 1, 1.0, 0) Undervoltage_Fault_Signal{};
    // MakeUnsignedCANSignal(dataType, 2, 1, 1.0, 0) Overvoltage_Fault_Signal{};
    // MakeUnsignedCANSignal(dataType, 3, 1, 1.0, 0) Undertemperature_Fault_Signal{};
    // MakeUnsignedCANSignal(dataType, 4, 1, 1.0, 0) Overtemperature_Fault_Signal{};
    // MakeUnsignedCANSignal(dataType, 5, 1, 1.0, 0) Overcurrent_Fault_Signal{};
    // MakeUnsignedCANSignal(dataType, 6, 1, 1.0, 0) External_Kill_Fault_Signal{};
    // MakeUnsignedCANSignal(dataType, 7, 1, 1.0, 0) Open_Wire_Fault_Signal{};
    // MakeUnsignedCANSignal(dataType, 0, 8, 1.0, 0) BMS_State_Signal{};
    // MakeUnsignedCANSignal(dataType, 8, 8, 1.0, -40) Max_Cell_Temp_Signal{};
    // MakeUnsignedCANSignal(dataType, 16, 8, 1.0, -40) Min_Cell_Temp_Signal{};
    // MakeUnsignedCANSignal(dataType, 24, 8, 0.012, 2) Max_Cell_Voltage_Signal{};
    // MakeUnsignedCANSignal(dataType, 32, 8, 0.012, 2) Min_Cell_Voltage_Signal{};
    // MakeUnsignedCANSignal(dataType, 40, 8, 0.5, 0) BMS_SOC_Signal{};
    // MakeUnsignedCANSignal(dataType, 0, 16, 0.01, 0) Coolant_Flow_Signal{};
    // MakeUnsignedCANSignal(dataType, 0, 8, 1.0, 0) BMS_Command_Signal{};
    // MakeUnsignedCANSignal(dataType, 0, 8, 1.0, 0) Tractive_System_Status_Signal{};
    // MakeUnsignedCANSignal(dataType, 0, 8, 0.02, 0) V5_Rail_Signal{};
    // MakeUnsignedCANSignal(dataType, 8, 8, 0.02, 0) V12_Rail_Signal{};
    // MakeUnsignedCANSignal(dataType, 16, 8, 0.02, 0) Vbat_Rail_Signal{};
    // MakeUnsignedCANSignal(dataType, 24, 16, 0.002, 0) Vbat_Input_Current_Signal{};
    // MakeUnsignedCANSignal(dataType, 40, 8, 0.05, 10) Vbat_Input_Voltage_Signal{};
    // MakeUnsignedCANSignal(dataType, 0, 8, 0.1, 0) Air_Cooling_Fan_Signal{};
    // MakeUnsignedCANSignal(dataType, 8, 8, 0.1, 0) Liquid_Cooling_Fan_Signal{};
    // MakeUnsignedCANSignal(dataType, 16, 8, 0.1, 0) Liquid_Cooling_Pump_Signal{};
    // MakeUnsignedCANSignal(dataType, 24, 8, 0.02, 0) High_Side_Driver_1_Signal{};
    // MakeUnsignedCANSignal(dataType, 32, 8, 0.02, 0) High_Side_Driver_2_Signal{};
    // MakeUnsignedCANSignal(dataType, 0, 8, 1.0, 0) IMD_State_Signal{};

    // all tx messages
    CANTXMessage<2> FL_Wheel_TX_Message{can_bus, 0x400, 4, 10, timer_group, FL_Wheel_Speed_Signal, FL_Brake_Temperature_Signal};
    CANTXMessage<2> FR_Wheel_TX_Message{can_bus, 0x401, 4, 10, timer_group, FR_Wheel_Speed_Signal, FR_Brake_Temperature_Signal};
    CANTXMessage<2> BL_Wheel_TX_Message{can_bus, 0x402, 4, 10, timer_group, BL_Wheel_Speed_Signal, BL_Brake_Temperature_Signal};
    CANTXMessage<2> BR_Wheel_TX_Message{can_bus, 0x403, 4, 10, timer_group, BR_Wheel_Speed_Signal, BR_Brake_Temperature_Signal};
    CANTXMessage<3> Ptrain_Temps_TX_Message{can_bus, 0x420, 6, 1, timer_group, Motor_Temperature_Signal, Coolant_Temperature_Signal, Ambient_Temperature_Signal};
    CANTXMessage<2> GPS_TX_Message{can_bus, 0x430, 8, 10, timer_group, Latitude_Signal, Longitude_Signal};
    CANTXMessage<3> Accelerometer_TX_Message{can_bus, 0x431, 6, 10, timer_group, Accel_X_Signal, Accel_Y_Signal, Accel_Z_Signal};
    CANTXMessage<3> Gyroscope_TX_Message{can_bus, 0x432, 6, 10, timer_group, Gyro_X_Signal, Gyro_Y_Signal, Gyro_Z_Signal};
    CANTXMessage<2> Brake_Pressure_TX_Message{can_bus, 0x410, 4, 10, timer_group, Front_Brake_Pressure_Signal, Back_Brake_Pressure_Signal};
    // CANTXMessage<3> Throttle_Values_TX_Message{can_bus, 0x300, DLC, Freq, timer_group, Accel_Percentage_Signal, Brake_Percentage_Signal, Torque_Limit_Percentage_Signal};
    // CANTXMessage<5> BMS_SOE_TX_Message{can_bus, 0x240, DLC, Freq, timer_group, Max_Discharge_Current_Signal, Max_Regen_Current_Signal, Battery_Voltage_Signal, Battery_Temperature_Signal, Battery_Current_Signal};
    // CANTXMessage<8> BMS_Faults_TX_Message{can_bus, 0x250, DLC, Freq, timer_group, Fault_Summary_Signal, Undervoltage_Fault_Signal, Overvoltage_Fault_Signal, Undertemperature_Fault_Signal, Overtemperature_Fault_Signal, Overcurrent_Fault_Signal, External_Kill_Fault_Signal, Open_Wire_Fault_Signal};
    // CANTXMessage<6> BMS_Status_TX_Message{can_bus, 0x241, DLC, Freq, timer_group, BMS_State_Signal, Max_Cell_Temp_Signal, Min_Cell_Temp_Signal, Max_Cell_Voltage_Signal, Min_Cell_Voltage_Signal, BMS_SOC_Signal};
    // CANTXMessage<5> PDM_Rails_TX_Message{can_bus, 0x500, DLC, Freq, timer_group, V5_Rail_Signal, V12_Rail_Signal, Vbat_Rail_Signal, Vbat_Input_Current_Signal, Vbat_Input_Voltage_Signal};
    // CANTXMessage<5> PDM_Devices_TX_Message{can_bus, 0x501, DLC, Freq, timer_group, Air_Cooling_Fan_Signal, Liquid_Cooling_Fan_Signal, Liquid_Cooling_Pump_Signal, High_Side_Driver_1_Signal, High_Side_Driver_2_Signal};

    // all rx messages
    CANRXMessage<2> FL_Wheel_RX_Message{can_bus, 0x400, FL_Wheel_Speed_Signal, FL_Brake_Temperature_Signal};
    CANRXMessage<2> FR_Wheel_RX_Message{can_bus, 0x401, FR_Wheel_Speed_Signal, FR_Brake_Temperature_Signal};
    CANRXMessage<2> BL_Wheel_RX_Message{can_bus, 0x402, BL_Wheel_Speed_Signal, BL_Brake_Temperature_Signal};
    CANRXMessage<2> BR_Wheel_RX_Message{can_bus, 0x403, BR_Wheel_Speed_Signal, BR_Brake_Temperature_Signal};
    CANRXMessage<3> Ptrain_Temps_RX_Message{can_bus, 0x420, Motor_Temperature_Signal, Coolant_Temperature_Signal, Ambient_Temperature_Signal};
    CANRXMessage<2> GPS_RX_Message{can_bus, 0x430, Latitude_Signal, Longitude_Signal};
    CANRXMessage<3> Accelerometer_RX_Message{can_bus, 0x431, Accel_X_Signal, Accel_Y_Signal, Accel_Z_Signal};
    CANRXMessage<3> Gyroscope_RX_Message{can_bus, 0x432, Gyro_X_Signal, Gyro_Y_Signal, Gyro_Z_Signal};
    CANRXMessage<2> Brake_Pressure_RX_Message{can_bus, 0x410, Front_Brake_Pressure_Signal, Back_Brake_Pressure_Signal};
    //     CANRXMessage<3> Throttle_Values_RX_Message{can_bus, 0x300, Accel_Percentage_Signal, Brake_Percentage_Signal, Torque_Limit_Percentage_Signal};
    //     CANRXMessage<5> BMS_SOE_RX_Message{can_bus, 0x240, Max_Discharge_Current_Signal, Max_Regen_Current_Signal, Battery_Voltage_Signal, Battery_Temperature_Signal, Battery_Current_Signal};
    //     CANRXMessage<8> BMS_Faults_RX_Message{can_bus, 0x250, Fault_Summary_Signal, Undervoltage_Fault_Signal, Overvoltage_Fault_Signal, Undertemperature_Fault_Signal, Overtemperature_Fault_Signal, Overcurrent_Fault_Signal, External_Kill_Fault_Signal, Open_Wire_Fault_Signal};
    //     CANRXMessage<6> BMS_Status_RX_Message{can_bus, 0x241, BMS_State_Signal, Max_Cell_Temp_Signal, Min_Cell_Temp_Signal, Max_Cell_Voltage_Signal, Min_Cell_Voltage_Signal, BMS_SOC_Signal};
    //     CANRXMessage<5> PDM_Rails_RX_Message{can_bus, 0x500, V5_Rail_Signal, V12_Rail_Signal, Vbat_Rail_Signal, Vbat_Input_Current_Signal, Vbat_Input_Voltage_Signal};
    //     CANRXMessage<5> PDM_Devices_RX_Message{can_bus, 0x501, Air_Cooling_Fan_Signal, Liquid_Cooling_Fan_Signal, Liquid_Cooling_Pump_Signal, High_Side_Driver_1_Signal, High_Side_Driver_2_Signal};
};