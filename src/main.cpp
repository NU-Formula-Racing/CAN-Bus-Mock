#include <Arduino.h>
#include <HPBus.h>
#include <LPBus.h>
#include <defines.h>

HPBus hp_bus{};
LPBus lp_bus{};
VirtualTimerGroup timer_group{};

void setup()
{
    hp_bus.Initialize();
    lp_bus.Initialize();
#if defined(Transmit)
    timer_group.AddTimer(10, []()
                         { hp_bus.UpdateValues(); });
    timer_group.AddTimer(10, []()
                         { lp_bus.UpdateValues(); });
#endif
    // timer_group.AddTimer(10, []()
    //                      { hp_bus.RandomValues(); });
    // timer_group.AddTimer(10, []()
    //                      { lp_bus.RandomValues(); });
}

void loop()
{
    timer_group.Tick(millis());
    hp_bus.timer_group.Tick(millis());
    lp_bus.timer_group.Tick(millis());
    hp_bus.can_bus.Tick();
    lp_bus.can_bus.Tick();
}