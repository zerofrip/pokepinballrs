#include "global.h"
#include "gbplayer.h"

#define OMEGA_DE_UNLOCK_PORT_1 (*(vu16 *)0x09FE0000)
#define OMEGA_DE_UNLOCK_PORT_2 (*(vu16 *)0x08000000)
#define OMEGA_DE_UNLOCK_PORT_3 (*(vu16 *)0x08020000)
#define OMEGA_DE_UNLOCK_PORT_4 (*(vu16 *)0x08040000)
#define OMEGA_DE_COMMAND_PORT  (*(vu16 *)0x09E20000)
#define OMEGA_DE_LATCH_PORT    (*(vu16 *)0x09FC0000)
#define OMEGA_DE_RUMBLE_PORT   (*(vu8 *)0x08001000)

extern int gGameBoyPlayerEnabled;
extern vu16 GPIOPortData;
extern vu16 GPIOPortDirection;
extern vu16 GPIOPortReadEnable;

void InitCartridgeRumble(void)
{
    if (gGameBoyPlayerEnabled == TRUE)
        return;

    GPIOPortReadEnable = TRUE;
    GPIOPortDirection = 8;
}

void StopCartridgeRumble(void)
{
    GPIOPortData = 0;
}

void EmitOmegaDEPulse(void)
{
    OMEGA_DE_UNLOCK_PORT_1 = 0xD200;
    OMEGA_DE_UNLOCK_PORT_2 = 0x1500;
    OMEGA_DE_UNLOCK_PORT_3 = 0xD200;
    OMEGA_DE_UNLOCK_PORT_4 = 0x1500;
    OMEGA_DE_COMMAND_PORT = 0xF1;
    OMEGA_DE_LATCH_PORT = 0x1500;

    OMEGA_DE_RUMBLE_PORT = 2;
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    OMEGA_DE_RUMBLE_PORT = 0;
}
