#pragma once

#include <cfg_items.h>

#pragma pack(push, 1)
typedef struct {
    const CFG_HDR cfghdr_cl_b;
    const CFG_HDR cfghdr_cl_0;
    int cpu_load_enabled;
    const CFG_HDR cfghdr_cl_1;
    int cpu_load_width;
    const CFG_HDR cfghdr_cl_2;
    int cpu_load_height;
    const CFG_HDR cfghdr_cl_3;
    char cpu_load_color_208[4];
    const CFG_HDR cfghdr_cl_4;
    char cpu_load_color_104[4];
    const CFG_HDR cfghdr_cl_5;
    char cpu_load_color_52[4];
    const CFG_HDR cfghdr_cl_e;

    const CFG_HDR cfghdr_c_b;
    const CFG_HDR cfghdr_c_0;
    int countdown_enabled;
    const CFG_HDR cfghdr_c_1;
    int countdown_icon;
    const CFG_HDR cfghdr_c_e;
} CONFIG;
#pragma pack(pop)

extern CONFIG CFG;
extern char CFG_PATH[];

void InitConfig();
