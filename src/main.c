#include <swilib.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include "config_loader.h"

#define CPU_LOAD_ICON 10000

typedef struct {
    CSM_RAM csm;
} MAIN_CSM;

typedef struct {
    char check_name[8];
    void (*f)(short *num);
} ICONBAR_H;

extern int CFG_CPU_LOAD_ENABLED, CFG_CPU_LOAD_WIDTH, CFG_CPU_LOAD_HEIGHT;
extern int CFG_COUNTDOWN_ENABLED, CFG_COUNTDOWN_ICON;

const int minus11 =- 11;
unsigned short maincsm_name_body[140];

IMGHDR IMG_CPU_LOAD;
GBSTMR TMR_CPU_LOAD;

void UpdateCPULoad() {
    extern char CFG_CPU_LOAD_COLOR_208[], CFG_CPU_LOAD_COLOR_104[], CFG_CPU_LOAD_COLOR_52[];

    static int w = 0;
    uint8_t *bitmap = IMG_CPU_LOAD.bitmap;
    if (w >= IMG_CPU_LOAD.w) {
        w = IMG_CPU_LOAD.w - 1;
        for (int x = 1; x < IMG_CPU_LOAD.w; x++) {
            for (int y = 0; y < IMG_CPU_LOAD.h; y++) {
                const int i = (x * 4) + (y * IMG_CPU_LOAD.w * 4);
                const int prev = ((x - 1) * 4) + (y * IMG_CPU_LOAD.w * 4);
                memcpy(&bitmap[prev], &bitmap[i], 4);
            }
        }
    }
    float h_load = (float)IMG_CPU_LOAD.h * (float)GetCPULoad() / 100 + 0.5f;
    for (int y = 0; y < IMG_CPU_LOAD.h; y++) {
        const int max_y = IMG_CPU_LOAD.h - MAX((int)h_load, 1);
        const int i = (w * 4) + (y * IMG_CPU_LOAD.w * 4);
        if (y < max_y) {
            zeromem(&bitmap[i], 4);
        } else {
            char *color;
            uint8_t clock = GetCPUClock();
            if (clock == 208) {
                color = CFG_CPU_LOAD_COLOR_208;
            } else if (clock == 104) {
                color = CFG_CPU_LOAD_COLOR_104;
            } else {
                color = CFG_CPU_LOAD_COLOR_52;
            }
            bitmap[i + 0] = color[2];
            bitmap[i + 1] = color[1];
            bitmap[i + 2] = color[0];
            bitmap[i + 3] = (uint8_t)((float)color[3] * 2.55f + 0.5f);
        }
    }
    w++;
}

void UpdateCPULoadProc() {
    if (*RamIconBar() && IsIconBarDisabled()) {
        UpdateCPULoad();
    }
    GBS_StartTimerProc(&TMR_CPU_LOAD, MsToTicks(500), UpdateCPULoadProc);
}

void AddCPULoadToIconBar(short *num) {
    UpdateCPULoad();
    AddIconToIconBar(CPU_LOAD_ICON, num);
}

void AddIconBar(short *num) {
    if (CFG_CPU_LOAD_ENABLED) {
        AddCPULoadToIconBar(num);
    }
    if (CFG_COUNTDOWN_ENABLED) {
        if (Countdown_IsEnabled()) {
            AddIconToIconBar(CFG_COUNTDOWN_ICON, num);
        }
    }
}

void InitCPULoadImage() {
    LockSched();
    PIT_ResetImage(CPU_LOAD_ICON);
    IMG_CPU_LOAD.w = CFG_CPU_LOAD_WIDTH;
    IMG_CPU_LOAD.h = CFG_CPU_LOAD_HEIGHT;
    IMG_CPU_LOAD.bpnum = IMGHDR_TYPE_BGRA8888;
    size_t size = CalcBitmapSize((short)IMG_CPU_LOAD.w, (short)IMG_CPU_LOAD.h, IMG_CPU_LOAD.bpnum);
    IMG_CPU_LOAD.bitmap = realloc(IMG_CPU_LOAD.bitmap, size); //NOLINT
    zeromem(IMG_CPU_LOAD.bitmap, (int)size);
    PIT_SetImage(CPU_LOAD_ICON, &IMG_CPU_LOAD);
    UnlockSched();
}

int OnMessage(CSM_RAM *data, GBS_MSG *msg) {
    extern char CFG_PATH[];
    if (msg->msg == MSG_RECONFIGURE_REQ) {
        if (strcmp(CFG_PATH, msg->data0) == 0) {
            InitConfig();
            InitCPULoadImage();
            ShowMSG(1, (int)"SieBar config updated!");
        }
    }
    return 1;
}

void OnCreate(CSM_RAM *data) {
    IMG_CPU_LOAD.bitmap = NULL;
    InitCPULoadImage();
    UpdateCPULoadProc();
}

void OnClose(CSM_RAM *csm) {
    GBS_DelTimer(&TMR_CPU_LOAD);
    PIT_ResetImage(CPU_LOAD_ICON);
    mfree(IMG_CPU_LOAD.bitmap);
    SUBPROC(kill_elf);
}

struct {
    CSM_DESC maincsm;
    WSHDR maincsm_name;
    ICONBAR_H iconbar_h;
} MAINCSM = {
        {
                OnMessage,
                OnCreate,
#ifdef NEWSGOLD
                0,
                0,
                0,
                0,
#endif
                OnClose,
                sizeof(MAIN_CSM),
                1,
                &minus11
        },
        {
                maincsm_name_body,
                NAMECSM_MAGIC1,
                NAMECSM_MAGIC2,
                0x0,
                139,
                0
        },
        {
            {"IconBar"},
        }
};

void UpdateCSMname(void) {
    wsprintf((WSHDR *)(&MAINCSM.maincsm_name), "SieBar");
}

int main() {
    char dummy[sizeof(MAIN_CSM)];
    UpdateCSMname();
    InitConfig();
    MAINCSM.iconbar_h.f = AddIconBar;
    LockSched();
    CSM_RAM *save_cmpc = CSM_root()->csm_q->current_msg_processing_csm;
    CSM_root()->csm_q->current_msg_processing_csm = CSM_root()->csm_q->csm.first;
    CreateCSM(&MAINCSM.maincsm, dummy, 0);
    CSM_root()->csm_q->current_msg_processing_csm = save_cmpc;
    UnlockSched();
    return 0;
}
