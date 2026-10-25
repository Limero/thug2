// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DCD30-0x800DCE30 (256B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_800DCBD4(Unk_C7387A53 *, CStruct *, s32, s32, void *);
s32 fn_800DC804(Unk_C7387A53 *, CStruct *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_800F0838(void *, f32 *);
s32 fn_800DCD30(Unk_C7387A53 *arg0, u32 arg1, CStruct *arg2, s32 arg3) {
    Unk_C7387A53 *manager = arg0;
    CStruct *params = arg2;
    s32 extra = arg3;
    f32 position[4];
    s32 node;
    s32 found;
    register Unk_C7387A53 *a0 __asm__("r3");
    register CStruct *a1 __asm__("r4");
    register s32 a2 __asm__("r5");
    register s32 a3 __asm__("r6");
    register void *a4 __asm__("r7");

    switch (arg1) {
    case QB_OBJ_OBJECTINRADIUS:
        a0 = manager;
        a1 = params;
        a2 = extra;
        a3 = 0;
        a4 = NULL;
radius_call:
        found = fn_800DCBD4(a0, a1, a2, a3, a4);
normalize:
        if (found == 0) {
            return 0;
        }
        return 1;
    case QB_OBJ_OBJECTINRADIUSOFNODE:
        if (GetChecksum_2(params, QB_NODE, &node, 0) != 0) {
            fn_800F0838(node, position);
            a0 = manager;
            a1 = params;
            a2 = extra;
            a3 = 0;
            a4 = position;
            goto radius_call;
        }
        goto node_missing;
node_missing:
        return 0;
    case QB_OBJ_OBJECTINRECT:
        found = fn_800DC804(manager, params, extra);
        goto normalize;
    default:
        return 2;
    }
}
