#include <swilib.h>
#include "config.h"

CONFIG CFG = {
    {CFG_LEVEL, "CPU load", 1, 0},
    {CFG_CHECKBOX, "Enabled", 0, 2},
    1,
    {CFG_UINT,"Width",0,64},
    24,
    {CFG_UINT,"Height",0,64},
    20,
    {CFG_COLOR, "Color 208", 0, 0},
    {0xFF, 0x00, 0x00, 0x64},
    {CFG_COLOR, "Color 104", 0, 0},
    {0xFF, 0xFF, 0x00, 0x64},
    {CFG_COLOR, "Color 52", 0, 0},
    {0x4A, 0x65, 0xFF, 0x64},
    {CFG_LEVEL, "", 0, 0},

    {CFG_LEVEL, "Countdown", 1, 0},
    {CFG_CHECKBOX, "Enabled", 0, 2},
    1,
    {CFG_UINT,"Icon",0,10000},
    487,
    {CFG_LEVEL, "", 0, 0},
};

char CFG_PATH[] = "?:\\zbin\\etc\\SieBar.bcfg";

void InitConfig() {
    CFG_PATH[0] = BCFG_GetDefaultDisk();
    if (BCFG_LoadConfig(CFG_PATH, &CFG, sizeof(CONFIG)) == -1) {
        BCFG_SaveConfig(CFG_PATH, &CFG, sizeof(CONFIG));
    }
}
