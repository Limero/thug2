// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B458C-0x800B4648 (188B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
void fn_800B34E4(Unk_6C4C8052 *, Unk_DB0E2BAB *);
s32 fn_80060934(Unk_C8FEE62D *);
s32 fn_800C9780(Unk_31DE137E *);
s32 fn_80060984(s32, void *, s32, s32 *, void *, f32, f32, void *);
s32 fn_800B458C(CScript *arg0, void *arg1, Unk_DB0E2BAB *arg2, f32 farg0, void *arg3, f32 farg1) {
    s32 sp8[20];
    s32 *p;
    s32 temp_r29;
    s32 temp_r3;
    s32 var_ctr;

    temp_r29 = fn_800C9780(arg0->unk0x214);
    temp_r3 = fn_80060934(arg0->unk0x210);
    if (((s32) arg0->unk0x214 == 0) || (temp_r3 == 0)) {
        return 0;
    }
    var_ctr = 4;
    p = sp8;
    do {
        var_ctr -= 1;
    } while (var_ctr != 0);
    fn_800B34E4(arg0, &sp8);
    return fn_80060984(arg0->unk0x210, arg1, temp_r29, p, arg2, farg0, farg1, arg3);
}
