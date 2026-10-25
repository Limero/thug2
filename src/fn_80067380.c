// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80067380-0x80067554 (468B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -O2
#include "types.h"
#include "structs.h"
void fn_80062D44(void *);
void fn_80062BBC(void *);
void *Mem_Alloc(s32);
extern char lbl_802944D8[];
extern char lbl_802944F0[];
extern f32 lbl_802944D4;
void *fn_80067380(Unk_DCEB657B *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 t3;
    s32 var_r28;
    s32 var_ctr;
    u32 var_r9;
    u32 var_r9_2;
    u32 var_r9_3;
    s32 var_r10;
    s32 t128;
    f32 tf;
    void *p114;
    void *p118;
    void *p11c;
    s32 fill;
    void *temp_r29;
    void *var_r30;

    fn_80062D44(arg0);
    var_r28 = arg2 - 1;
    arg0->unk0xF8 = arg1;
    arg0->unk0x84 = arg2;
    arg0->unk0x20 = (s32)lbl_802944D8;
    arg0->unk0x8 = (s32)lbl_802944F0;
    arg0->unk0x94 = 0;
    *(s32 *)((char *)arg0 + 0x170) = arg7 + 1;
    temp_r29 = (void *)((s32)Mem_Alloc((arg2 * 0x30) | 8) + 8);
    *(s32 *)((char *)temp_r29 - 0x8) = arg2;
    var_r30 = temp_r29;
    if (arg2 != 0) {
        do {
            fn_80062BBC(var_r30);
            var_r30 = (void *)((char *)var_r30 + 0x30);
        } while (--var_r28 != -1);
    }
    arg0->unk0x100 = temp_r29;
    t3 = (arg7 + 1) * 3;
    arg0->unk0x124 = Mem_Alloc(t3 * arg0->unk0x84 * 4);
    p114 = Mem_Alloc(8);
    var_r9 = 1;
    do {
    } while (var_r9-- != 0u);
    arg0->unk0x114 = (s32)p114;
    p118 = Mem_Alloc(8);
    var_r9_2 = 1;
    do {
    } while (var_r9_2-- != 0u);
    arg0->unk0x118 = (s32)p118;
    p11c = Mem_Alloc(8);
    var_r9_3 = 1;
    do {
    } while (var_r9_3-- != 0u);
    arg0->unk0x11C = (s32)p11c;
    fill = 0x80;
    var_r10 = 0;
    var_ctr = 2;
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
        var_ctr -= 1;
    } while (var_ctr != 0);
    t128 = arg0->unk0x128;
    tf = lbl_802944D4;
    arg0->unk0x110 = tf;
    arg0->unk0x128 = t128 | 4;
    return arg0;
}
