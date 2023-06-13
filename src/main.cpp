#include <Arduino.h>
#include <HPBus.h>
#include <LPBus.h>
#include <defines.h>

#ifdef HP
HPBus hp_bus{};
#endif

#ifdef LP
LPBus lp_bus{};
#endif

VirtualTimerGroup timer_group{};

void setup()
{
    Serial.begin(115200);

#ifdef HP
    hp_bus.Initialize();
#endif

#ifdef LP
    lp_bus.Initialize();
#endif

#if defined(Transmit)
#ifdef HP
    timer_group.AddTimer(10, []()
                         { hp_bus.UpdateValues(); });
#endif

#ifdef LP
    timer_group.AddTimer(10, []()
                         { lp_bus.UpdateValues(); });
#endif

#endif
}

void loop()
{
    timer_group.Tick(millis());
#ifdef HP
    hp_bus.timer_group.Tick(millis());
    hp_bus.can_bus.Tick();
#endif

#ifdef LP
    lp_bus.timer_group.Tick(millis());
    lp_bus.can_bus.Tick();
#endif
}