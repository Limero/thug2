// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022DF2C-0x8022E000 (212B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
extern s32 fn_80056080(void *, s32, void *, Unk_C8FEE62D *, s32, s32);
extern s32 fn_800546A0(s32);
extern void fn_80057E7C(Unk_C8FEE62D *, void *);
extern void fn_80057FFC(Unk_C8FEE62D *, s32);
extern s32 fn_80243EF0();
extern void fn_80243E4C(s32, Unk_C7387A53 *);
extern void fn_80230308(Unk_C5855798 *, Unk_DB0E2BAB *);

void fn_8022DF2C(Unk_DB0E2BAB *arg0, Unk_F7887518 *arg1) {
    __ps_t sp8[2];
    s32 *p;
    s32 temp_r3;
    s32 temp_r30;

    p = arg1->unk0x14;
    arg0->unk0x0 = (s32) (arg0->unk0x0 | 0x40);
    if (arg1->unk0x4 & 4) {
        temp_r3 = fn_80056080(arg0->unk0x10, *p, arg0->unk0x14, 1, 0, 0);
    } else {
        temp_r3 = fn_80056080(arg0->unk0x10, *p, arg0->unk0x14, 0, 1, 0);
    }
    arg1->unk0x0 = temp_r3;
    temp_r30 = fn_800546A0(temp_r3);
    sp8[0] = arg1->unk0x18;
    sp8[1] = arg1->unk0x20;
    fn_80057E7C(temp_r30, &sp8[0]);
    fn_80057FFC(temp_r30, arg1->unk0x28);
    if (arg1->unk0x4 & 0x40) {
        fn_80243E4C(fn_80243EF0(), arg1);
    }
    fn_80230308(arg0, arg1);
}
