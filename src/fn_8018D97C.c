// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018D97C-0x8018DA50 (212B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 fn_8009CF2C(s32);
s32 fn_80198F7C(s32);
s32 ContainsFlag(s32, u32);
void fn_8018B90C(void *);
void fn_801907E0(void *, void *);
#include "qb_constants.h"

/* the class descriptor reached through the +0x14 slot: {s16 byte offset from
   the object, entry point} pair. */
typedef struct {
    char pad00[0xA8];
    s16 offA8;
    char padAA[2];
    s32 (*fnAC)(void *);
} GoalVtblD;

typedef struct {
    char pad00[0x14];
    GoalVtblD *vtbl;
    char pad18[8];
    s32 unk0x20;
    char pad24[0x4C];
    s32 unk0x70;
} GoalManagerObj;

extern char lbl_80305F9C[];
extern char lbl_80305EC0[];

void fn_8018D97C(GoalManagerObj *arg0) {
    GoalVtblD *vt;
    s32 res;
    s32 g;

    if (arg0->unk0x70 & QB_UNKNOWN_0x04000000) {
        g = *(s32 *)&lbl_80305F9C;
        arg0->unk0x70 &= QB_UNKNOWN_0xFBFFFFFF;
        if (fn_8009CF2C(g) == 0) {
            vt = arg0->vtbl;
            res = vt->fnAC((char *)arg0 + vt->offA8);
            if (res == 0) goto doit;
            if (fn_80198F7C(*(s32 *)&lbl_80305EC0) == QB_CLASSIC) goto doit;
            if (ContainsFlag(arg0->unk0x20, QB_ALWAYS_INITIALIZE_GOAL) != 0) goto doit;
            if (ContainsFlag(arg0->unk0x20, QB_EDITED_GOAL) == 0) goto unlock;
        doit:
            fn_8018B90C(arg0);
        unlock:
            fn_801907E0(arg0, QB_UNLOCK);
        }
    }
}
