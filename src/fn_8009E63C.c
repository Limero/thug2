// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009E63C-0x8009E6D8 (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_80127438(CStruct *, CStruct *);
void fn_80126808(Unk_80577C09 *, Unk_5D1D68CC *, s32);
void fn_8009F4C4(s32 arg0);
s32 GetChecksum(s32, s32);
s32 fn_801288C4(CStruct *arg0, s32 arg1);
bool fn_8009E63C(Unk_C7387A53 *arg0, CStruct *arg1, CStruct *arg2) {
    s32 temp_r30;
    s32 temp_r3;
    s32 var_r31;
    if ((s32) arg0->unk0x24 != 0) {
        var_r31 = arg1->unk0x4;
        while (--var_r31 != -1) {
            /* unnested: with GetChecksum inside the arg list GCC hoists the
             * arg0->unk0x24 load ABOVE the inner call (extra lwz r30);
             * want loads it straight into r3 after the call returns. */
            s32 sum = GetChecksum(arg1, var_r31);
            temp_r3 = fn_801288C4(arg0->unk0x24, sum);
            if (temp_r3 != 0) {
                fn_8009F4C4(0x10);
                temp_r30 = fn_801252BC();
                fn_80126808(temp_r30, temp_r3, 0);
                fn_80127438(arg2, temp_r30);
            }
        }
    }
    return true;
}
