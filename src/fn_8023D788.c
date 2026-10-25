// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023D788-0x8023D848 (192B). Byte-identical.
// extra_cflags: -fno-expensive-optimizations
#include "types.h"
#include "structs.h"
s32 fn_80240B0C(Unk_F96D0DC8 *, s32, s32, s32, s32, s32, s32);
void fn_8023DA64(Unk_71EAD930 *, Unk_F96D0DC8 *);
u8 fn_8023D788(Unk_365B6C9E *arg0) {
    s32 sp8;
    s32 temp_r0;
    register s32 temp_r9 __asm__("r9");
    register u8 *bp __asm__("r9");
    u8 chk;
    register s32 state __asm__("r8");
    register void *temp_r11 __asm__("r11");

    state = arg0->unk0x4C;
    if (state == 0) {
        temp_r11 = (char *)arg0 + 4;
        temp_r0 = arg0->unk0x4;
        __asm__ __volatile__("" ::: "memory");
        temp_r9 = ((Unk_897A0ACF *)temp_r11)->unk0x4;
        *(s32 *)((char *)arg0 + (s32)0x4D) = temp_r0;
        *(u16 *)((char *)arg0 + (s32)0x51) = temp_r9;
        temp_r9 = ((Unk_897A0ACF *)temp_r11)->unk0x4;
        *(s32 *)((char *)arg0 + (s32)0x53) = temp_r0;
        *(u16 *)((char *)arg0 + (s32)0x57) = temp_r9;
        arg0->unk0x4C = 1U;
        arg0->unk0x5C = state;
    } else if (state == 1) {
        fn_80240B0C(&sp8, 0, 0, 0, 0, 0, 0);
        fn_8023DA64(arg0, &sp8);
        __asm__("lbz %0,11(1)" : "=r"(chk));
        __asm__("" : "=r"(bp) : "r"(&sp8));
        if ((chk > 0xAU) || (bp[5] > 0xAU)) {
            goto block_6;
        }
        arg0->unk0x4C = 2U;
    }
block_6:
    return arg0->unk0x4C;
}
