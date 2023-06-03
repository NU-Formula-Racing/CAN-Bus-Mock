#include <Arduino.h>
#include <HPBus.h>
#include <LPBus.h>

HPBus hp_bus{};
LPBus lp_bus{};
VirtualTimerGroup timer_group{};

void setup()
{
    hp_bus.Initialize();
    lp_bus.Initialize();
    timer_group.AddTimer(10, []()
                         { hp_bus.UpdateValues(); });
    timer_group.AddTimer(10, []()
                         { lp_bus.UpdateValues(); });
}

void loop()
{
    timer_group.Tick(millis());
}