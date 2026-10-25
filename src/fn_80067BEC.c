// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80067BEC-0x80067DB4 (456B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_80062D44(void *);
void *Mem_Alloc(s32);
void fn_80062BBC(void *);
extern char lbl_802946F8[];
extern char lbl_80294710[];
extern f32 lbl_802946F4;

void *fn_80067BEC(Unk_DCEB657B *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                 s32 arg5, s32 arg6, s32 arg7) {
    s32 var_r27;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_ctr_3;
    s32 var_ctr_4;
    s32 var_r10;
    s32 fill;
    s32 t128;
    s32 temp_r0;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 temp_r3_3;
    f32 tf;
    void *temp_r29;
    void *var_r30;

    fn_80062D44(arg0);
    var_r27 = arg2 - 1;
    arg0->unk0xF8 = arg1;
    arg0->unk0x84 = arg2;
    arg0->unk0x20 = (s32)lbl_802946F8;
    arg0->unk0x8 = (s32)lbl_80294710;
    arg0->unk0x94 = 0;
    temp_r29 = (void *)((s32)Mem_Alloc((arg2 * 0x30) | 8) + 8);
    *(s32 *)((char *)temp_r29 - 0x8) = arg2;
    var_r30 = temp_r29;
    if (arg2 != 0) {
        do {
            fn_80062BBC(var_r30);
            var_r30 = (void *)((char *)var_r30 + 0x30);
        } while (--var_r27 != -1);
    }
    temp_r0 = arg7 + 1;
    arg0->unk0x100 = temp_r29;
    arg0->unk0x124 = Mem_Alloc((((temp_r0 << 1) + temp_r0) * arg0->unk0x84) * 4);
    temp_r3 = (s32)Mem_Alloc(0x10);
    var_ctr = 4;
    do {
        var_ctr -= 1;
    } while (var_ctr != 0);
    arg0->unk0x114 = temp_r3;
    temp_r3_2 = (s32)Mem_Alloc(0x10);
    var_ctr_2 = 4;
    do {
        var_ctr_2 -= 1;
    } while (var_ctr_2 != 0);
    arg0->unk0x118 = temp_r3_2;
    temp_r3_3 = (s32)Mem_Alloc(0x10);
    var_ctr_3 = 4;
    do {
        var_ctr_3 -= 1;
    } while (var_ctr_3 != 0);
    arg0->unk0x11C = temp_r3_3;
    *(s32 *)((char *)arg0 + 0x170) = arg7 + 1;
    fill = 0x80;
    var_r10 = 0;
    var_ctr_4 = 4;
    do {
        *(u8 *)((char *)(var_r10 + arg0->unk0x114) + 0) = fill;
        *(u8 *)((char *)(var_r10 + arg0->unk0x114) + 1) = fill;
        *(u8 *)((char *)(var_r10 + arg0->unk0x114) + 2) = fill;
        *(u8 *)((char *)(var_r10 + arg0->unk0x114) + 3) = fill;
        *(u8 *)((char *)(var_r10 + arg0->unk0x118) + 0) = fill;
        *(u8 *)((char *)(var_r10 + arg0->unk0x118) + 1) = fill;
        *(u8 *)((char *)(var_r10 + arg0->unk0x118) + 2) = fill;
        *(u8 *)((char *)(var_r10 + arg0->unk0x118) + 3) = fill;
        *(u8 *)((char *)(var_r10 + arg0->unk0x11C) + 0) = fill;
        *(u8 *)((char *)(var_r10 + arg0->unk0x11C) + 1) = fill;
        *(u8 *)((char *)(var_r10 + arg0->unk0x11C) + 2) = fill;
        *(u8 *)((char *)(var_r10 + arg0->unk0x11C) + 3) = fill;
        var_r10 += 4;
        var_ctr_4 -= 1;
    } while (var_ctr_4 != 0);
    t128 = arg0->unk0x128;
    tf = lbl_802946F4;
    arg0->unk0x110 = tf;
    arg0->unk0x128 = t128 | 4;
    return arg0;
}
