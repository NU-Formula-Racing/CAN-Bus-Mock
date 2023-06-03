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
    void UpdateValues();
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
    MakeUnsignedCANSignal(float, 0, 8, 0.02, 0) V5_Rail_Signal{};
    MakeUnsignedCANSignal(float, 8, 8, 0.02, 0) V12_Rail_Signal{};
    MakeUnsignedCANSignal(float, 16, 8, 0.02, 0) Vbat_Rail_Signal{};
    MakeUnsignedCANSignal(float, 24, 16, 0.002, 0) Vbat_Input_Current_Signal{};
    MakeUnsignedCANSignal(float, 40, 8, 0.05, 10) Vbat_Input_Voltage_Signal{};
    MakeUnsignedCANSignal(float, 0, 8, 0.1, 0) Air_Cooling_Fan_Signal{};
    MakeUnsignedCANSignal(float, 8, 8, 0.1, 0) Liquid_Cooling_Fan_Signal{};
    MakeUnsignedCANSignal(float, 16, 8, 0.1, 0) Liquid_Cooling_Pump_Signal{};
    MakeUnsignedCANSignal(float, 24, 8, 0.02, 0) High_Side_Driver_1_Signal{};
    MakeUnsignedCANSignal(float, 32, 8, 0.02, 0) High_Side_Driver_2_Signal{};
    MakeUnsignedCANSignal(uint8_t, 0, 8, 1.0, 0) IMD_State_Signal{};

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
    CANTXMessage<5> PDM_Rails_TX_Message{can_bus, 0x500, 6, 100, timer_group, V5_Rail_Signal, V12_Rail_Signal, Vbat_Rail_Signal, Vbat_Input_Current_Signal, Vbat_Input_Voltage_Signal};
    CANTXMessage<5> PDM_Devices_TX_Message{can_bus, 0x501, 5, 100, timer_group, Air_Cooling_Fan_Signal, Liquid_Cooling_Fan_Signal, Liquid_Cooling_Pump_Signal, High_Side_Driver_1_Signal, High_Side_Driver_2_Signal};

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
    CANRXMessage<5> PDM_Rails_RX_Message{can_bus, 0x500, V5_Rail_Signal, V12_Rail_Signal, Vbat_Rail_Signal, Vbat_Input_Current_Signal, Vbat_Input_Voltage_Signal};
    CANRXMessage<5> PDM_Devices_RX_Message{can_bus, 0x501, Air_Cooling_Fan_Signal, Liquid_Cooling_Fan_Signal, Liquid_Cooling_Pump_Signal, High_Side_Driver_1_Signal, High_Side_Driver_2_Signal};
};