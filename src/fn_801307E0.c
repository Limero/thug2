// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801307E0-0x80130898 (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 CStruct_dtor(void *);
void *fn_8012B2A0(void *);
void *fn_8012DC0C(void *, void *, s32);
void fn_801307E0(void *arg0) {
    s32 temp_r9_2;
    s32 temp_r0_34;
    s32 dc_ret;
    s32 var_r29;
    s32 var_r30;
    register u8 *temp_r9 __asm__("r9");
    register s32 r3_setup __asm__("r3");
    u8 temp_r0;

    var_r30 = 0;
    var_r29 = 1;
    do {
        temp_r9 = *(s32 *)((char *)arg0 + (s32)0x10);
        temp_r0 = *temp_r9;
        r3_setup = (s32)temp_r9;
        switch ((s32) temp_r0) {
        case 32:
            var_r30 += 1;
            break;
        case 33:
            if (var_r30 != 0) {
                var_r30 -= 1;
            } else {
                var_r29 = 0;
            }
            break;
        case 100:
            /* empty: balance-case pivot (want roots the tree at 33) */
            break;
        }
        *(s32 *)((char *)arg0 + (s32)0x10) = fn_8012B2A0((void *)r3_setup);
    } while (var_r29 != 0);
    CStruct_dtor(*(s32 *)((char *)arg0 + (s32)0x14));
    dc_ret = fn_8012DC0C(*(s32 *)((char *)arg0 + (s32)0x14), *(s32 *)((char *)arg0 + (s32)0x10), 0);
    temp_r9_2 = *(s32 *)((char *)arg0 + (s32)0x1C);
    temp_r0_34 = *(s32 *)((char *)arg0 + (s32)0x34);
    *(s32 *)((char *)arg0 + (s32)0x10) = dc_ret;
    if (temp_r9_2 == temp_r0_34) {
        *(s32 *)((char *)arg0 + (s32)0x1C) = var_r29;
        return;
    }
    *(s32 *)((char *)arg0 + (s32)0x1C) = (s32) (temp_r9_2 - 0x14);
}
