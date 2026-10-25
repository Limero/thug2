// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018D7BC-0x8018D8D0 (276B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
CStruct *fn_80127358(CStruct *, CStruct *);
s32 GetInteger(CStruct *, void *, s32 *, void *);
s32 ContainsFlag(CStruct *, void *);
s32 fn_8018D7BC(Unk_C7387A53 *arg0) {
    s32 sp10;
    s32 spC;
    s32 sp8;
    register CStruct *var_r30 __asm__("r30");
    CStruct *temp_r31;

    sp8 = arg0->unk0x5C;
    GetInteger(arg0->unk0x20, QB_NUM_FLAGS_TO_WIN, &sp8, 0);
    if (ContainsFlag(arg0->unk0x24, QB_SKATER_FLAGS) != 0) {
        var_r30 = fn_80127358(arg0->unk0x24, NULL);
        if (var_r30 == NULL) return 1;
        do {
            temp_r31 = fn_80127358(arg0->unk0x24, var_r30);
            if ((var_r30->unk0x0 & 0x7F0000) == 0xA0000) {
                var_r30 = var_r30->unk0x8;
                GetInteger(var_r30, QB_NUM_FLAGS_SET, &spC, 1);
                GetInteger(var_r30, QB_NUM_FLAGS, &sp10, 1);
                if (spC < sp10) return 0;
            }
            var_r30 = temp_r31;
        } while (var_r30 != NULL);
        return 1;
    }
    if (sp8 == 0) {
        return 0;
    }
    return (*(s32 *)((char *)arg0 + 0x60) >= sp8) ? 1 : 0;
}
