// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801BF080-0x801BF230 (432B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern f32 lbl_802AC4DC;
extern f32 lbl_802AC4E0;
extern f32 lbl_802AC4E4;
extern f32 lbl_802AC4E8;
extern f32 lbl_802AC4EC;
extern f32 lbl_802AC4F0;
extern f32 lbl_802AC4F4;
extern f32 lbl_802AC4F8;

void fn_801BF080(Unk_1FAB9257 *arg0, f32 *arg1, f32 *arg2) {
    f32 temp_f0;
    register f32 prod __asm__("fr9");
    register f32 d0v __asm__("fr12");
    register f32 res __asm__("fr0");
    register f32 upd __asm__("fr0");
    f32 temp_f13;
    register f32 e8c __asm__("fr10");
    register f32 temp_f11 __asm__("fr11");
    register f32 lerp_r __asm__("fr0");
    register f32 cmpv __asm__("fr0");
    register f32 outv __asm__("fr12");
    register f32 t114b __asm__("fr11");
    s32 temp_r0;
    s32 var_r0;
    void *temp_r9;
    void *q1;
    Unk_C7387A53 *q2;

    if ((s32)arg0->unk0x17C == 0) {
        return;
    }
    arg0->unk0x118 = lbl_802AC4E4;
    if ((s32)arg0->unk0x110 == 0) {
        temp_r9 = arg0->unk0x180;
        if (((s32)((Unk_7BBF7803 *)temp_r9)->unk0x40 != 0) &&
            ((s32)((Unk_7BBF7803 *)temp_r9)->unk0x64 == 0) &&
            ((s32)((Unk_7BBF7803 *)temp_r9)->unk0xAC == 0) &&
            ((s32)((Unk_7BBF7803 *)temp_r9)->unk0x144 != 0)) {
            var_r0 = 1;
            goto block_5;
        }
        temp_r9 = arg0->unk0x180;
    }
    temp_r9 = arg0->unk0x180;
    if ((((s32)((Unk_7BBF7803 *)temp_r9)->unk0x40 == 0) ||
         ((s32)((Unk_7BBF7803 *)temp_r9)->unk0x64 != 0)) ||
        ((s32)((Unk_7BBF7803 *)temp_r9)->unk0xAC != 0)) {
        var_r0 = 0;
    block_5:
        arg0->unk0x110 = var_r0;
    }
    if ((s32)arg0->unk0x110 != 0) {
        temp_f0 = arg0->unk0x120;
        goto block_8;
    }
    temp_r0 = *(s32 *)(arg0->unk0x180 + (s32)0x1C);
    if (temp_r0 == 4) {
        temp_f0 = arg0->unk0x124;
        goto block_8;
    }
    if (temp_r0 == 3) {
        temp_f0 = arg0->unk0x128;
    block_8:
        arg0->unk0x118 = temp_f0;
    }
    q1 = arg0->unk0x174;
    if ((s32)((Unk_C7387A53 *)q1)->unk0x20 != 0) {
        temp_f13 = *((f32 *)&((Unk_C7387A53 *)q1)->unk0x24);
        if (temp_f13 != lbl_802AC4E4) {
            arg0->unk0x118 =
                arg0->unk0x118 * temp_f13;
        }
    }
    temp_f11 = arg0->unk0x114;
    lerp_r = arg0->unk0x118;
    d0v = arg0->unk0xD0;
    lerp_r = ((lerp_r - temp_f11) * arg0->unk0x11C) + temp_f11;
    e8c = lbl_802AC4E8;
    prod = d0v * lerp_r;
    __asm__ ("" : "+f" (lerp_r));
    arg0->unk0x114 = lerp_r;
    *arg2 = prod;
    q2 = arg0->unk0x174;
    cmpv = *((f32 *)&q2->unk0x28);
    if (cmpv < e8c) {
        upd = prod * ((((cmpv + lbl_802AC4EC) / lbl_802AC4EC) * lbl_802AC4F0) +
                      lbl_802AC4F4);
        *arg2 = upd;
    }
    outv = arg0->unk0xDC;
    if ((s32)*(s32 *)(arg0->unk0x180 + (s32)0x1C) == 3) {
        outv = arg0->unk0x144;
    }
    t114b = arg0->unk0x114;
    if (t114b < lbl_802AC4E4) {
        res = outv - lbl_802AC4F8;
        res = (res * t114b) + lbl_802AC4F8;
        *arg1 = res;
        return;
    }
    *arg1 = outv;
}
