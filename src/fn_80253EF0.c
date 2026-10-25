// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80253EF0-0x80253FB8 (200B). Byte-identical.
#include "types.h"
#include "structs.h"

s32 fn_80253EF0(Unk_C8FEE62D *arg0, s32 *arg1, s32 *arg2) {
    CStruct *temp_r12;
    s32 temp_r9;
    s32 var_r7;
    s32 var_r6;
    s32 m;

    temp_r12 = *(void **)arg0;
    *arg2 = 0;
    temp_r9 = arg0->unk0x18;
    if ((temp_r9 > -1) && (temp_r9 < arg0->unk0x14)) {
        if (arg1 != NULL) {
            var_r7 = 0;
            if (var_r7 < temp_r12->unk0x4) {
                m = 1;
                var_r6 = 0;
                do {
                    if (arg0->unk0x54 & (m << var_r7)) {
                        *(s32 *)(arg0->unk0xC + (*arg2 * 4)) =
                            *(s32 *)(char *)(var_r6 + arg0->unk0x8) +
                            (arg0->unk0x18 * 2);
                        *arg2 += 1;
                    }
                    var_r7 += 1;
                    var_r6 += 4;
                } while (var_r7 < temp_r12->unk0x4);
            }
            *arg1 = arg0->unk0xC;
        }
        return arg0->unk0x14 - arg0->unk0x18;
    }
    return 0;
}
