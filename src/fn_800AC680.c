// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AC680-0x800AC7A0 (288B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_800ACC2C(void *, void *);
void AddChecksum(void *, void *, void *);
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_80129528(s32, s32);

void GetArray(CStruct *, s32, s32 *, s32);
void GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_80014100(CStruct *arg0, s32 arg1, s32 arg2);
void fn_800AC680(Unk_9B16FFA5 *arg0) {
    s32 sp10;
    void *spC;
    s32 sp8;
    s32 temp_r30;
    s32 var_r3;
    u32 var_r31;

    sp8 = 0;
    GetInteger(arg0->unk0x34D4, QB_VERSION, &sp8, 1);
    spC = NULL;
    var_r31 = 0U;
    GetArray(arg0->unk0x34D4, QB_OBJECTS, &spC, 1);
    while (1) {
        CStruct *cs = (CStruct *)spC;
        if (var_r31 >= (u32) cs->unk0x4) {
            break;
        }
        temp_r30 = fn_80129528(spC, var_r31);
        if (sp8 > 1) {
            var_r3 = GetChecksum_2(temp_r30, QB_OBJECTNAME, &sp10, 0);
        } else {
            var_r3 = GetChecksum_2(temp_r30, QB_MODELNAME, &sp10, 0);
        }
        if ((var_r3 != 0) && (fn_80014100(arg0->unk0x4, sp10, QB_SKIN) != 0)) {
            AddChecksum(temp_r30, 0, QB_ISSKINNEDMODEL);
        }
        var_r31 += 1;
    }
    if ((s32) arg0->unk0x34B8 != 0) {
        fn_800ACC2C(arg0, arg0->unk0x34D4);
    }
}
