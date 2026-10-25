// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80015E34-0x80015EE0 (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_80314640[];
extern s32 CARDDelete(s32, void *);
#include "structs.h"

s32 fn_80015E34(Unk_C8FEE62D *arg0, u8 *arg1) {
    s32 temp_r3;
    u8 *var_r4;
    register u8 *b __asm__("r11");
    register s32 pg __asm__("r9");
    u8 temp_r0;
    s8 temp_r0s;
    s8 temp_r9s;
    u8 temp_r0_2;
    u8 temp_r9;
    s32 var_r10;

    var_r4 = arg1;
    temp_r9 = *(u8 *)var_r4;
    temp_r9s = *(s8 *)var_r4;
    var_r10 = 0;
    *(u8 *)lbl_80314640 = temp_r9;
    if (temp_r9s != 0) {
        __asm__("lis %0,%1@ha" : "=r"(pg) : "s"(lbl_80314640));
        b = (u8 *)((char *)pg + 0x4640);
        do {
            temp_r0_2 = b[var_r10];
            if (((s8) temp_r0_2 != 0x2F) && ((s8) temp_r0_2 != 0x5C) && ((s8) temp_r0_2 != 0x2E)) {
                var_r10 += 1;
            }
            var_r4 = (u8 *)((char *)var_r4 + 1);
            temp_r0 = *(u8 *)var_r4;
            temp_r0s = *(s8 *)var_r4;
            *(u8 *)((char *)var_r10 + (s32)b) = temp_r0;
        } while (temp_r0s != 0);
    }
    temp_r3 = CARDDelete(arg0->unk0x18,(void *)lbl_80314640);
    if (temp_r3 == -5) {
        arg0->unk0x10 = 1;
    }
    return (temp_r3 == 0);
}
