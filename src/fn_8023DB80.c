// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023DB80-0x8023DC38 (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns2
#include "types.h"
#include "structs.h"
void *fn_80240B0C(Unk_F96D0DC8 *, s32, s32, s32, s32, s32, s32);
void fn_8023DA64(Unk_71EAD930 *, Unk_F96D0DC8 *);
s32 fn_80230BEC(s32);
void fn_80230C54(void);
s32 fn_80233428(s32, s32, s32);
extern char lbl_8029FBE8[];
bool fn_8023DB80(Unk_71EAD930 *arg0) {
    struct {
        u8 sp8[16];
        s32 sp18;
        s32 sp1C;
    } locals;
    Unk_F96D0DC8 *p;
    s32 temp;
    fn_80240B0C((Unk_F96D0DC8 *)locals.sp8, 0, 0, 0, 0, 0, 0);
    p = (Unk_F96D0DC8 *)locals.sp8;
    fn_8023DA64(arg0, p);
    if ((locals.sp8[3] <= 0xAU) && (p->unk0x5 <= 0xAU)) {
        locals.sp1C = (s32)lbl_8029FBE8;
        temp = fn_80230BEC(0);
        locals.sp18 = temp;
        __asm__ volatile("" ::: "memory");
        if (fn_80233428(temp, p->unk0x3, p->unk0x5) != 0) {
            locals.sp1C = (s32)lbl_8029FBE8;
            fn_80230C54();
            return false;
        }
        locals.sp1C = (s32)lbl_8029FBE8;
        fn_80230C54();
        goto block_5;
    }
block_5:
    return true;
}
