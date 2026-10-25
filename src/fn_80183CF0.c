// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80183CF0-0x80183D5C (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct {
    char _0[0x70];
    s16 unk0x70;
    void *unk0x74;
} VT;
extern s32 GoalManager_GetGoal(s32, s32, s32);
s32 fn_80183CF0(s32 arg0) {
    s32 r;
    s32 gap;
    VT *vt;

    r = GoalManager_GetGoal(arg0, gap, 1);
    if (r != 0) {
        vt = ((VT *)((Unk_C8FEE62D *)r)->unk0x14);
        ((void (*)(void *, s32, s32))vt->unk0x74)((char *)r + vt->unk0x70, 0, 1);
    }
    return r != 0 ? 1 : 0;
}
