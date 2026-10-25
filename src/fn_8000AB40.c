// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000AB40-0x8000AC98 (344B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_80311294;
extern s32 lbl_80311298;
extern s32 lbl_8031129C;

#define FA ((s32 *)lbl_8031129C)
#define FB ((s32 *)lbl_80311298)
#define FC ((s32 *)lbl_80311294)

void fn_8000AB40(s32 arg0) {
    s32 n;
    s32 t;
    s32 i = arg0;

    if (FA[i] == 0x1000) {
        return;
    }
    if (FB[i] == 0x1000) {
        n = FC[i];
    } else {
        n = FB[i];
        if (FC[i] != 0x1000) {
            n = FC[i];
            if (FB[n] != 0x1000) {
                s32 bpv;
                bpv = (s32)lbl_80311298;
                __asm__("" : "+r"(bpv));
                do {
                    n = ((s32 *)bpv)[n];
                } while (((s32 *)bpv)[n] != 0x1000);
                FB[FA[n]] = FC[n];
                FA[FC[n]] = FA[n];
                FC[n] = FC[i];
                FA[FC[i]] = n;
            }
            FB[n] = FB[i];
            FA[FB[i]] = n;
        }
    }
    FA[n] = FA[i];
    t = FA[i];
    if (FB[t] == arg0) {
        FB[t] = n;
    } else {
        FC[t] = n;
    }
    FA[i] = 0x1000;
}
