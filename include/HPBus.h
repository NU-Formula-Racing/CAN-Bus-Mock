#include <defines.h>
#if defined(ARDUINO_TEENSY40) || defined(ARDUINO_TEENSY41)
#include "teensy_can.h"
#endif

#ifdef ARDUINO_ARCH_ESP32
#include "esp_can.h"
#endif

class HPBus
{
public:
    void Initialize();
    void UpdateValues();
    void RandomValues();
    void PrintValues();
#if defined(ARDUINO_TEENSY40) || defined(ARDUINO_TEENSY41)
    TeensyCAN<2> can_bus{};
#endif

#ifdef ARDUINO_ARCH_ESP32
    ESPCAN can_bus{};
#endif
    VirtualTimerGroup timer_group{};

private:
    // all signals
    MakeSignedCANSignal(int8_t, 0, 8, 1.0, 0) Accel_Percentage_Signal{};
    MakeUnsignedCANSignal(uint8_t, 8, 8, 1.0, 0) Brake_Percentage_Signal{};
    MakeUnsignedCANSignal(uint8_t, 16, 8, 1.0, 0) Torque_Limit_Percentage_Signal{};
    MakeUnsignedCANSignal(float, 0, 12, 0.1, 0) Max_Discharge_Current_Signal{};
    MakeUnsignedCANSignal(float, 12, 12, 0.1, 0) Max_Regen_Current_Signal{};
    MakeUnsignedCANSignal(float, 24, 16, 0.01, 0) Battery_Voltage_Signal{};
    MakeUnsignedCANSignal(float, 40, 8, 1.0, -40) Battery_Temperature_Signal{};
    MakeSignedCANSignal(float, 48, 16, 0.01, 0) Battery_Current_Signal{};
    MakeUnsignedCANSignal(uint8_t, 0, 8, 1.0, 0) BMS_State_Signal{};
    MakeUnsignedCANSignal(float, 8, 8, 1.0, -40) Max_Cell_Temp_Signal{};
    MakeUnsignedCANSignal(float, 16, 8, 1.0, -40) Min_Cell_Temp_Signal{};
    MakeUnsignedCANSignal(float, 24, 8, 0.012, 2) Max_Cell_Voltage_Signal{};
    MakeUnsignedCANSignal(float, 32, 8, 0.012, 2) Min_Cell_Voltage_Signal{};
    MakeUnsignedCANSignal(uint8_t, 40, 8, 0.5, 0) BMS_SOC_Signal{};
    MakeUnsignedCANSignal(float, 0, 16, 0.01, 0) Coolant_Flow_Signal{};
    MakeUnsignedCANSignal(uint8_t, 0, 8, 1.0, 0) BMS_Command_Signal{};
    MakeUnsignedCANSignal(uint8_t, 0, 8, 1.0, 0) Tractive_System_Status_Signal{};
    MakeUnsignedCANSignal(float, 0, 16, 0.1, -40) Motor_Temperature_Signal{};
    MakeUnsignedCANSignal(float, 16, 16, 0.1, -40) Coolant_Temperature_Signal{};
    MakeUnsignedCANSignal(float, 32, 16, 0.1, -40) Ambient_Temperature_Signal{};

#if defined(Transmit)
    // all tx messages
    CANTXMessage<3> Throttle_Values_TX_Message{can_bus, 0x300, 3, 10, timer_group, Accel_Percentage_Signal, Brake_Percentage_Signal, Torque_Limit_Percentage_Signal};
    CANTXMessage<5> BMS_SOE_TX_Message{can_bus, 0x240, 8, 10, timer_group, Max_Discharge_Current_Signal, Max_Regen_Current_Signal, Battery_Voltage_Signal, Battery_Temperature_Signal, Battery_Current_Signal};
    CANTXMessage<6> BMS_Status_TX_Message{can_bus, 0x241, 6, 10, timer_group, BMS_State_Signal, Max_Cell_Temp_Signal, Min_Cell_Temp_Signal, Max_Cell_Voltage_Signal, Min_Cell_Voltage_Signal, BMS_SOC_Signal};
    CANTXMessage<1> BMS_CMD_Message{can_bus, 0x242, 1, 10, timer_group, BMS_Command_Signal};
    CANTXMessage<1> Throttle_Status_TX_Message{can_bus, 0x301, 1, 10, timer_group, Tractive_System_Status_Signal};
    CANTXMessage<3> Ptrain_Temps_TX_Message{can_bus, 0x420, 6, 1, timer_group, Motor_Temperature_Signal, Coolant_Temperature_Signal, Ambient_Temperature_Signal};
#endif

#if defined(Receive)
    // all rx messages
    CANRXMessage<3> Throttle_Values_RX_Message{can_bus, 0x300, Accel_Percentage_Signal, Brake_Percentage_Signal, Torque_Limit_Percentage_Signal};
    CANRXMessage<5> BMS_SOE_RX_Message{can_bus, 0x240, Max_Discharge_Current_Signal, Max_Regen_Current_Signal, Battery_Voltage_Signal, Battery_Temperature_Signal, Battery_Current_Signal};
    CANRXMessage<8> BMS_Faults_RX_Message{can_bus, 0x250, Fault_Summary_Signal, Undervoltage_Fault_Signal, Overvoltage_Fault_Signal, Undertemperature_Fault_Signal, Overtemperature_Fault_Signal, Overcurrent_Fault_Signal, External_Kill_Fault_Signal, Open_Wire_Fault_Signal};
    CANRXMessage<6> BMS_Status_RX_Message{can_bus, 0x241, BMS_State_Signal, Max_Cell_Temp_Signal, Min_Cell_Temp_Signal, Max_Cell_Voltage_Signal, Min_Cell_Voltage_Signal, BMS_SOC_Signal};
#endif
};