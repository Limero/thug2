// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80087240-0x80087280 (64B). Byte-identical.
#include "types.h"
extern f32 lbl_802965DC;
extern s32 lbl_803017CC;
extern char lbl_803017D0[];
extern f32 lbl_803017D4;
extern f32 lbl_803017D8;
void fn_80087240(s32 arg0) {
    f32 temp_f0;

    if (arg0 != lbl_803017CC) {
        if (arg0 == 0) {
            temp_f0 = lbl_802965DC;
            *(s32 *)&lbl_803017D0 = arg0;
            lbl_803017D4 = temp_f0;
            lbl_803017D8 = temp_f0;
        }
        lbl_803017CC = arg0;
    }
}
