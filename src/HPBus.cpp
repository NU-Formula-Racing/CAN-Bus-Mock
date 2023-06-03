#include <Arduino.h>
#include <HPBus.h>
#include <can_interface.h>

void HPBus::Initialize()
{
    // initialize bus
    can_bus.Initialize(ICAN::BaudRate::kBaud1M);
#if defined(ARDUINO_TEENSY40) || defined(ARDUINO_TEENSY41)
    // register all messages

    can_bus.RegisterRXMessage(Throttle_Values_RX_Message);
    can_bus.RegisterRXMessage(BMS_SOE_RX_Message);
    can_bus.RegisterRXMessage(BMS_Faults_RX_Message);
    can_bus.RegisterRXMessage(BMS_Status_RX_Message);
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

void HPBus::UpdateValues()
{
    Accel_Percentage_Signal = Ramp(0, 100, 1, Accel_Percentage_Signal);
    Brake_Percentage_Signal = Ramp(0, 100, 1, Brake_Percentage_Signal);
    Torque_Limit_Percentage_Signal = Ramp(0, 100, 1, Torque_Limit_Percentage_Signal);
    Max_Discharge_Current_Signal = Ramp(0, 300, 1, Max_Discharge_Current_Signal);
    Max_Regen_Current_Signal = Ramp(0, 300, 1, Max_Regen_Current_Signal);
    Battery_Voltage_Signal = Ramp(0, 600, 1, Battery_Voltage_Signal);
    Battery_Temperature_Signal = Ramp(0, 100, 1, Battery_Temperature_Signal);
    Battery_Current_Signal = Ramp(-300, 300, 1, Battery_Current_Signal);
    Fault_Summary_Signal = Ramp(0, 1, 1, Fault_Summary_Signal);
    Undervoltage_Fault_Signal = Ramp(0, 1, 1, Undervoltage_Fault_Signal);
    Overvoltage_Fault_Signal = Ramp(0, 1, 1, Overvoltage_Fault_Signal);
    Undertemperature_Fault_Signal = Ramp(0, 1, 1, Undertemperature_Fault_Signal);
    Overtemperature_Fault_Signal = Ramp(0, 1, 1, Overtemperature_Fault_Signal);
    Overcurrent_Fault_Signal = Ramp(0, 1, 1, Overcurrent_Fault_Signal);
    External_Kill_Fault_Signal = Ramp(0, 1, 1, External_Kill_Fault_Signal);
    Open_Wire_Fault_Signal = Ramp(0, 1, 1, Open_Wire_Fault_Signal);
    BMS_State_Signal = Ramp(0, 4, 1, BMS_State_Signal);
    Max_Cell_Temp_Signal = Ramp(0, 100, 1, Max_Cell_Temp_Signal);
    Min_Cell_Temp_Signal = Ramp(0, 100, 1, Min_Cell_Temp_Signal);
    Max_Cell_Voltage_Signal = Ramp(0, 5, 1, Max_Cell_Voltage_Signal);
    Min_Cell_Voltage_Signal = Ramp(0, 5, 1, Min_Cell_Voltage_Signal);
    BMS_SOC_Signal = Ramp(0, 100, 1, BMS_SOC_Signal);
    Coolant_Flow_Signal = Ramp(0, 100, 1, Coolant_Flow_Signal);
    BMS_Command_Signal = Ramp(0, 2, 1, BMS_Command_Signal);
    Tractive_System_Status_Signal = Ramp(0, 4, 1, Tractive_System_Status_Signal);
}
