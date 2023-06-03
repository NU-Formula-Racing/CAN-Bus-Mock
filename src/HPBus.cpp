#include <Arduino.h>
#include <HPBus.h>
#include <can_interface.h>

void HPBus::Initialize()
{
    // initialize bus
    can_bus.Initialize(ICAN::BaudRate::kBaud1M);
#if (defined(ARDUINO_TEENSY40) || defined(ARDUINO_TEENSY41)) && defined(Receive)
    // register all messages
    can_bus.RegisterRXMessage(Throttle_Values_RX_Message);
    can_bus.RegisterRXMessage(BMS_SOE_RX_Message);
    can_bus.RegisterRXMessage(BMS_Faults_RX_Message);
    can_bus.RegisterRXMessage(BMS_Status_RX_Message);
#endif
}

void HPBus::RandomValues()
{
    Accel_Percentage_Signal = random(max(0.0, Accel_Percentage_Signal - 0.1) * 1000, min(100.0, Accel_Percentage_Signal + 0.1) * 1000) / 1000.0f;
    Brake_Percentage_Signal = random(max(0.0, Brake_Percentage_Signal - 0.1) * 1000, min(100.0, Brake_Percentage_Signal + 0.1) * 1000) / 1000.0f;
    Torque_Limit_Percentage_Signal = random(max(0.0, Torque_Limit_Percentage_Signal - 0.1) * 1000, min(100.0, Torque_Limit_Percentage_Signal + 0.1) * 1000) / 1000.0f;
    Max_Discharge_Current_Signal = random(max(0.0, Max_Discharge_Current_Signal - 0.1) * 1000, min(300.0, Max_Discharge_Current_Signal + 0.1) * 1000) / 1000.0f;
    Max_Regen_Current_Signal = random(max(0.0, Max_Regen_Current_Signal - 0.1) * 1000, min(300.0, Max_Regen_Current_Signal + 0.1) * 1000) / 1000.0f;
    Battery_Voltage_Signal = random(max(0.0, Battery_Voltage_Signal - 0.1) * 1000, min(600.0, Battery_Voltage_Signal + 0.1) * 1000) / 1000.0f;
    Battery_Temperature_Signal = random(max(0.0, Battery_Temperature_Signal - 0.1) * 1000, min(100.0, Battery_Temperature_Signal + 0.1) * 1000) / 1000.0f;
    Battery_Current_Signal = random(max(-300.0, Battery_Current_Signal - 0.1) * 1000, min(300.0, Battery_Current_Signal + 0.1) * 1000) / 1000.0f;
    Fault_Summary_Signal = random(0, 1);
    Undervoltage_Fault_Signal = random(0, 1);
    Overvoltage_Fault_Signal = random(0, 1);
    Undertemperature_Fault_Signal = random(0, 1);
    Overtemperature_Fault_Signal = random(0, 1);
    Overcurrent_Fault_Signal = random(0, 1);
    External_Kill_Fault_Signal = random(0, 1);
    Open_Wire_Fault_Signal = random(0, 1);
    BMS_State_Signal = random(0, 4);
    Max_Cell_Temp_Signal = random(max(0.0, Max_Cell_Temp_Signal - 0.1) * 1000, min(100.0, Max_Cell_Temp_Signal + 0.1) * 1000) / 1000.0f;
    Min_Cell_Temp_Signal = random(max(0.0, Min_Cell_Temp_Signal - 0.1) * 1000, min(100.0, Min_Cell_Temp_Signal + 0.1) * 1000) / 1000.0f;
    Max_Cell_Voltage_Signal = random(max(0.0, Max_Cell_Voltage_Signal - 0.1) * 1000, min(5.0, Max_Cell_Voltage_Signal + 0.1) * 1000) / 1000.0f;
    Min_Cell_Voltage_Signal = random(max(0.0, Min_Cell_Voltage_Signal - 0.1) * 1000, min(5.0, Min_Cell_Voltage_Signal + 0.1) * 1000) / 1000.0f;
    BMS_SOC_Signal = random(max(0.0, BMS_SOC_Signal - 0.1) * 1000, min(100.0, BMS_SOC_Signal + 0.1) * 1000) / 1000.0f;
    Coolant_Flow_Signal = random(max(0.0, Coolant_Flow_Signal - 0.1) * 1000, min(100.0, Coolant_Flow_Signal + 0.1) * 1000) / 1000.0f;
    BMS_Command_Signal = random(0, 2);
    Tractive_System_Status_Signal = random(0, 4);
}

void HPBus::UpdateValues()
{
    Accel_Percentage_Signal = (Accel_Percentage_Signal < 100) ? Accel_Percentage_Signal + 1 : 0;
    Brake_Percentage_Signal = (Brake_Percentage_Signal < 100) ? Brake_Percentage_Signal + 1 : 0;
    Torque_Limit_Percentage_Signal = (Torque_Limit_Percentage_Signal < 100) ? Torque_Limit_Percentage_Signal + 1 : 0;
    Max_Discharge_Current_Signal = (Max_Discharge_Current_Signal < 300) ? Max_Discharge_Current_Signal + 1 : 0;
    Max_Regen_Current_Signal = (Max_Regen_Current_Signal < 300) ? Max_Regen_Current_Signal + 1 : 0;
    Battery_Voltage_Signal = (Battery_Voltage_Signal < 600) ? Battery_Voltage_Signal + 1 : 0;
    Battery_Temperature_Signal = (Battery_Temperature_Signal < 100) ? Battery_Temperature_Signal + 1 : 0;
    Battery_Current_Signal = (Battery_Current_Signal < 300) ? Battery_Current_Signal + 1 : -300;
    Fault_Summary_Signal = (Fault_Summary_Signal < 1) ? Fault_Summary_Signal + 1 : 0;
    Undervoltage_Fault_Signal = (Undervoltage_Fault_Signal < 1) ? Undervoltage_Fault_Signal + 1 : 0;
    Overvoltage_Fault_Signal = (Overvoltage_Fault_Signal < 1) ? Overvoltage_Fault_Signal + 1 : 0;
    Undertemperature_Fault_Signal = (Undertemperature_Fault_Signal < 1) ? Undertemperature_Fault_Signal + 1 : 0;
    Overtemperature_Fault_Signal = (Overtemperature_Fault_Signal < 1) ? Overtemperature_Fault_Signal + 1 : 0;
    Overcurrent_Fault_Signal = (Overcurrent_Fault_Signal < 1) ? Overcurrent_Fault_Signal + 1 : 0;
    External_Kill_Fault_Signal = (External_Kill_Fault_Signal < 1) ? External_Kill_Fault_Signal + 1 : 0;
    Open_Wire_Fault_Signal = (Open_Wire_Fault_Signal < 1) ? Open_Wire_Fault_Signal + 1 : 0;
    BMS_State_Signal = (BMS_State_Signal < 4) ? BMS_State_Signal + 1 : 0;
    Max_Cell_Temp_Signal = (Max_Cell_Temp_Signal < 100) ? Max_Cell_Temp_Signal + 1 : 0;
    Min_Cell_Temp_Signal = (Min_Cell_Temp_Signal < 100) ? Min_Cell_Temp_Signal + 1 : 0;
    Max_Cell_Voltage_Signal = (Max_Cell_Voltage_Signal < 5) ? Max_Cell_Voltage_Signal + 0.1 : 0;
    Min_Cell_Voltage_Signal = (Min_Cell_Voltage_Signal < 5) ? Min_Cell_Voltage_Signal + 0.1 : 0;
    BMS_SOC_Signal = (BMS_SOC_Signal < 100) ? BMS_SOC_Signal + 1 : 0;
    Coolant_Flow_Signal = (Coolant_Flow_Signal < 100) ? Coolant_Flow_Signal + 1 : 0;
    BMS_Command_Signal = (BMS_Command_Signal < 2) ? BMS_Command_Signal + 1 : 0;
    Tractive_System_Status_Signal = (Tractive_System_Status_Signal < 4) ? Tractive_System_Status_Signal + 1 : 0;
}
