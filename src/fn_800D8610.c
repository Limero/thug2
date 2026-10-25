// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D8610-0x800D871C (268B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct Unk4140_8610 {
    char pad0x000[0x138];
    s32 unk138;
    char pad0x13C[0x0C4];
    void *unk200;
} Unk4140_8610;

s32 fn_800F0598(void *);
bool GetInteger(CStruct *, s32, s32 *, s32);
s32 Mth_Rnd(s32);
bool ContainsFlag(CStruct *, s32);
CStruct *fn_800F0670(void *, s32);
s32 fn_800F0AFC(CStruct *);
void fn_800F078C(CStruct *, f32 *);
s32 fn_800D81F0(Unk4140_8610 *, CStruct *, s32, f32 *, s32);
void fn_800D68B8(Unk4140_8610 *, s32);

void fn_800D8610(Unk4140_8610 *arg0, CStruct *arg1, s32 arg2) {
    f32 sp8[4];
    f32 sp18[4];
    s32 nlinks;
    CStruct *node;
    s32 name;
    s32 sp28;
    sp28 = 0;
    nlinks = fn_800F0598(arg0->unk200);
    if (nlinks != 0) {
        if (GetInteger(arg1, QB_LINKNUM, &sp28, 0) != 0) {
            sp28--;
        } else if (nlinks > 1) {
            if (ContainsFlag(arg1, QB_UNKNOWN_0x90A1C52A) != 0) {
                sp28 = Mth_Rnd(nlinks);
            }
        }
        node = fn_800F0670(arg0->unk200, sp28);
        name = fn_800F0AFC(node);
        fn_800F078C(node, sp8);
        ((__ps_t *)sp18)[0] = ((__ps_t *)sp8)[0];
        ((__ps_t *)sp18)[1] = ((__ps_t *)sp8)[1];
        if (fn_800D81F0(arg0, arg1, arg2, sp18, 0) != 0) {
            fn_800D68B8(arg0, name);
        } else {
            arg0->unk138 = name;
        }
    }
}
