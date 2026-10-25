// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80089D5C-0x80089DF8 (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8005CF80(Unk_9994C3F5 *, void *);
s32 fn_80081794(s32);
void *fn_8006800C(Unk_DCEB657B *, s32, s32, s32);
extern s32 lbl_80366478;
extern char lbl_802969C0[];
extern char lbl_802969D8[];
void *fn_80089D5C(Unk_3FE1622A *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s8 arg5, f32 farg0) {
    Unk_C7387A53 *temp_r3;
    volatile double pad;

    fn_8006800C((Unk_DCEB657B *)arg0, arg1, arg2, arg3);
    arg0->unk0x20 = (s32)lbl_802969C0;
    arg0->unk0x8 = (s32)lbl_802969D8;
    arg0->unk0x180 = 0;
    temp_r3 = fn_8005CF80((Unk_9994C3F5 *)lbl_80366478, (void *)arg3);
    if (temp_r3 != NULL) {
        arg0->unk0x180 = (s32) temp_r3->unk0xC;
    }
    *(s8 *)&arg0->unk0x178 = (s8)fn_80081794((void *)arg4);
    *(s8 *)((char *)arg0 + 0x179) = arg5;
    *(f32 *)&arg0->unk0x17C = farg0;
    return arg0;
}