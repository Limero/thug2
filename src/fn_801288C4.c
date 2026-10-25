// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801288C4-0x80128978 (180B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80125480(s32);
void *fn_801288C4(CStruct *arg0, s32 arg1) {
    s32 r0;
    s32 temp_r3;
    CStruct *var_r31;
    void *var_r3;

    var_r31 = (CStruct *)arg0->unk0x4;
    if (var_r31 != NULL) {
        do {
            r0 = var_r31->unk0x4;
            if (r0 == arg1) {
                return var_r31;
            }
            if (r0 == 0) {
                if ((var_r31->unk0x0 & 0x7F0000) == 0xD0000) {
                    r0 = var_r31->unk0x8;
                    if (r0 == arg1) {
                        return var_r31;
                    }
                    temp_r3 = fn_80125480(r0);
                    if (temp_r3 != 0 && *(s8 *)((char *)temp_r3 + 2) == 0xA) {
                        var_r3 = fn_801288C4((CStruct *)((Unk_5AA7B5D7 *)temp_r3)->unk0xC, arg1);
                        if (var_r3 != NULL) {
                            return var_r3;
                        }
                    }
                }
            }
            var_r31 = (CStruct *)var_r31->unk0xC;
        } while (var_r31 != NULL);
    }
    return NULL;
}