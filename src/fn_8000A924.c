// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000A924-0x8000A990 (108B). Byte-identical.
#include "types.h"
#include "mem.h"
extern s32 lbl_80311290;
extern s32 lbl_80311294;
extern s32 lbl_80311298;
extern s32 lbl_8031129C;
void fn_8000A924(void) {
    if (lbl_8031129C != 0) {
        Mem_Free2(lbl_8031129C);
    }
    if (lbl_80311298 != 0) {
        Mem_Free2(lbl_80311298);
    }
    if (lbl_80311294 != 0) {
        Mem_Free2(lbl_80311294);
    }
    if (lbl_80311290 != 0) {
        Mem_Free2(lbl_80311290);
    }
}
