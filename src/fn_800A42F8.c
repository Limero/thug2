// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A42F8-0x800A43A0 (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 CStruct_delete(s32, s32);
void fn_800A42F8(CStruct *arg0, s32 arg1) {
    s32 var_r28 = 0;
    if (var_r28 < (s32) arg0->unk0x4) {
        s32 var_r30 = 0;
        do {
            if (*(s32 *)(var_r30 + arg0->unk0x0) == arg1) {
                s32 zero = 0;
                *(s32 *)(var_r30 + arg0->unk0x0) = zero;
                *(s32 *)(var_r30 + arg0->unk0x0 + 4) = QB_NULL_SCRIPT;
                if (*(s32 *)(var_r30 + arg0->unk0x0 + 0xC) != 0) {
                    CStruct_delete(*(s32 *)(var_r30 + arg0->unk0x0 + 0xC), 3);
                    *(s32 *)(var_r30 + arg0->unk0x0 + 0xC) = zero;
                }
            }
            var_r28 += 1;
            var_r30 += 0x14;
        } while (var_r28 < (s32) arg0->unk0x4);
    }
}
