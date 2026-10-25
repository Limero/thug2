// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8017755C-0x80177610 (180B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305F9C;

s32 fn_8021D358(s32 arg0, s32 arg1);

s32 fn_8017755C(s32 arg0, s32 arg1, Unk_EE36B018 *arg2) {
    s32 var_r3;
    CScript *temp_r3;
    Unk_9D99273B *temp_r3_2;
    Unk_31DE137E *temp_r6;
    s32 temp_r10;
    register s32 pin10 __asm__("r10");

    temp_r3 = fn_8021D358(lbl_80305F9C, arg2->unk0x1A);
    if ((temp_r3 != NULL) && (temp_r3 != (void *)arg1)) {
        temp_r3_2 = temp_r3->unk0x18;
        temp_r6 = *((void * *)&temp_r3_2->unk0x2A8);
        temp_r10 = temp_r6->unk0x1C;
        pin10 = temp_r10;
        if (pin10 != 0) {
            s32 *base = (s32 *)((char *)arg1 + 0x74);
            s32 m;
            s32 off;
            char *addr;
            var_r3 = 0;
            m = (pin10 - 1) % 20;
            off = m * 0x88;
            __asm__("add %0,%1,%0" : "=r"(addr) : "r"(temp_r6), "0"(off));
            if (*(u16 *)(addr + 0x98) != *(s32 *)((char *)base + (temp_r3_2->unk0x18 << 2))) {
                var_r3 = 1;
            }
            return var_r3;
        }
    }
    return 0;
}
