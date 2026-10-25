// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80067DFC-0x80067FC4 (456B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_80062D44(void *);
void *Mem_Alloc(s32);
void fn_80062BBC(void *);
extern char lbl_80294780[];
extern char lbl_80294798[];
extern f32 lbl_8029477C;
void *fn_80067DFC(Unk_DCEB657B *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, f32 farg0) {
    volatile double _dummy;
    s32 var_r27;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_ctr_3;
    s32 var_ctr_4;
    s32 var_r10;
    s32 fill;
    s32 t128;
    f32 tf;
    void *temp_r28;
    void *var_r30;
    void *p114;
    void *p118;
    void *p11c;

    fn_80062D44(arg0);
    var_r27 = arg2 - 1;
    arg0->unk0xF8 = arg1;
    arg0->unk0x84 = arg2;
    arg0->unk0x20 = (s32)lbl_80294780;
    arg0->unk0x8 = (s32)lbl_80294798;
    arg0->unk0x94 = 0;
    temp_r28 = (void *)((s32)Mem_Alloc((arg2 * 0x30) | 8) + 8);
    *(s32 *)((char *)temp_r28 - 0x8) = arg2;
    var_r30 = temp_r28;
    if (arg2 != 0) {
        do {
            fn_80062BBC(var_r30);
            var_r30 = (void *)((char *)var_r30 + 0x30);
        } while (--var_r27 != -1);
    }
    arg0->unk0x100 = temp_r28;
    arg0->unk0x124 = Mem_Alloc(((arg2 << 1) + arg2) << 2);
    p114 = Mem_Alloc(0xC);
    var_ctr = 3;
    do {
        var_ctr -= 1;
    } while (var_ctr != 0);
    arg0->unk0x114 = p114;
    p118 = Mem_Alloc(0xC);
    var_ctr_2 = 3;
    do {
        var_ctr_2 -= 1;
    } while (var_ctr_2 != 0);
    arg0->unk0x118 = p118;
    p11c = Mem_Alloc(0xC);
    var_ctr_3 = 3;
    do {
        var_ctr_3 -= 1;
    } while (var_ctr_3 != 0);
    arg0->unk0x11C = p11c;
    fill = 0x80;
    var_r10 = 0;
    var_ctr_4 = 3;
    do {
        *(u8 *)((char *)(var_r10 + arg0->unk0x114)) = fill;
        *(u8 *)((char *)(var_r10 + arg0->unk0x114) + 1) = fill;
        *(u8 *)((char *)(var_r10 + arg0->unk0x114) + 2) = fill;
        *(u8 *)((char *)(var_r10 + arg0->unk0x114) + 3) = fill;
        *(u8 *)((char *)(var_r10 + arg0->unk0x118)) = fill;
        *(u8 *)((char *)(var_r10 + arg0->unk0x118) + 1) = fill;
        *(u8 *)((char *)(var_r10 + arg0->unk0x118) + 2) = fill;
        *(u8 *)((char *)(var_r10 + arg0->unk0x118) + 3) = fill;
        *(u8 *)((char *)(var_r10 + arg0->unk0x11C)) = fill;
        *(u8 *)((char *)(var_r10 + arg0->unk0x11C) + 1) = fill;
        *(u8 *)((char *)(var_r10 + arg0->unk0x11C) + 2) = fill;
        *(u8 *)((char *)(var_r10 + arg0->unk0x11C) + 3) = fill;
        var_r10 += 4;
        var_ctr_4 -= 1;
    } while (var_ctr_4 != 0);
    t128 = arg0->unk0x128;
    tf = lbl_8029477C;
    *(s32 *)((char *)arg0 + 0x170) = arg6;
    arg0->unk0x110 = tf;
    *(f32 *)((char *)arg0 + 0x174) = farg0;
    arg0->unk0x128 = t128 | 4;
    return arg0;
}
