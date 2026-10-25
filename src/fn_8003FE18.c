// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003FE18-0x8003FED0 (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "qb_constants.h"

extern s32 lbl_80301A78;
extern f32 lbl_80292318;

void fn_800A54AC(s32, s32, s32, s32, s32, s32, f32);

// CScreenElement_SetChildLockState @ 0x8003FE18
void CScreenElement_SetChildLockState(void *arg0, s32 arg1) {
    register s32 o __asm__("r3");
    register s32 flags __asm__("r0");
    s32 cur;
    s32 mgr;

    o = (s32)arg0;
    flags = *(s32 *)((char *)o + 0xC);
    cur = 0;
    if (flags & 0x4000) {
        cur = 1;
    }
    if (arg1 != cur) {
        if (arg1 == 1) {
            flags |= 0x4000;
        } else {
            flags &= 0xFFFFBFFF;
        }
        *(s32 *)((char *)o + 0xC) = flags;
        mgr = lbl_80301A78;
        if (arg1 == 1) {
            fn_800A54AC(mgr, QB_NOTIFY_CHILD_LOCK, *(s32 *)((char *)o + 0x18), QB_SYSTEM, 0, 0, lbl_80292318);
        } else {
            fn_800A54AC(mgr, QB_NOTIFY_CHILD_UNLOCK, *(s32 *)((char *)o + 0x18), QB_SYSTEM, 0, 0, lbl_80292318);
        }
    }
}
