#include <cfg_items.h>

__CFG_BEGIN(0)

__root CFG_HDR cfghdr_0 = {CFG_LEVEL, "CPU load", 1, 0};
    __root CFG_HDR cfghdr_0_1 = {CFG_CHECKBOX, "Enabled", 0, 2};
    __root int CFG_CPU_LOAD_ENABLED = 1;
    __root CFG_HDR cfghdr_0_2 = {CFG_UINT,"Width",0,64};
    __root int CFG_CPU_LOAD_WIDTH = 24;
    __root CFG_HDR cfghdr_0_3 = {CFG_UINT,"Height",0,64};
    __root int CFG_CPU_LOAD_HEIGHT = 20;
    __root CFG_HDR cfghdr_0_4 = {CFG_COLOR, "Color 208", 0, 0};
    __root char CFG_CPU_LOAD_COLOR_208[] = {0xFF, 0x00, 0x00, 0x64};
    __root CFG_HDR cfghdr_0_5 = {CFG_COLOR, "Color 104", 0, 0};
    __root char CFG_CPU_LOAD_COLOR_104[] = {0xFF, 0xFF, 0x00, 0x64};
    __root CFG_HDR cfghdr_0_6 = {CFG_COLOR, "Color 52", 0, 0};
    __root char CFG_CPU_LOAD_COLOR_52[] = {0x4A, 0x65, 0xFF, 0x64};
__root CFG_HDR cfghdr_0_={CFG_LEVEL, "", 0, 0};

__root CFG_HDR cfghdr_1 = {CFG_LEVEL, "Countdown", 1, 0};
    __root CFG_HDR cfghdr_1_1 = {CFG_CHECKBOX, "Enabled", 0, 2};
    __root int CFG_COUNTDOWN_ENABLED = 1;
    __root CFG_HDR cfghdr_1_2 = {CFG_UINT,"Icon",0,10000};
    __root int CFG_COUNTDOWN_ICON = 487;
__root CFG_HDR cfghdr_1_={CFG_LEVEL, "", 0, 0};

__CFG_END(0)
