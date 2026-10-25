// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006712C-0x80067338 (524B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_80062D44(void *);
void *Mem_Alloc(s32);
void fn_80062BBC(void *);
extern char lbl_80294450[];
extern char lbl_80294468[];
extern f32 lbl_8029444C;
typedef struct {
    char pad0x0[0x8];
    s32 unk0x8;
    char pad0xC[0x14];
    s32 unk0x20;
    char pad0x24[0x60];
    s32 unk0x84;
    char pad0x88[0xC];
    s32 unk0x94;
    char pad0x98[0x60];
    s32 unk0xF8;
    char pad0xFC[0x4];
    s32 unk0x100;
    char pad0x104[0xC];
    f32 unk0x110;
    s32 unk0x114;
    s32 unk0x118;
    s32 unk0x11C;
    char pad0x120[0x4];
    s32 unk0x124;
    s32 unk0x128;
    char pad0x12C[0x44];
    s32 unk0x170;
} S6712C;
void *fn_8006712C(S6712C *arg0, s32 arg1, s32 arg2, s32 a3, s32 a4, s32 a5, s32 a6, s32 arg7) {
    s32 var_r28;
    register s32 r9 __asm__("r9");
    s32 x3;
    s32 n1;
    s32 n2;
    s32 n3;
    void *p114;
    void *p118;
    void *p11c;
    s32 var_r7;
    s32 var_r10;
    s32 fill;
    s32 t128;
    f32 tf;
    void *temp_r29;
    void *var_r30;

    var_r28 = arg2 - 1;
    fn_80062D44(arg0);
    arg0->unk0xF8 = arg1;
    arg0->unk0x84 = arg2;
    arg0->unk0x20 = (s32)lbl_80294450;
    arg0->unk0x8 = (s32)lbl_80294468;
    arg0->unk0x94 = 0;
    arg0->unk0x170 = arg7 + 1;
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
    x3 = arg7 + 1;
    arg0->unk0x124 = Mem_Alloc(((x3 << 1) + x3) * arg0->unk0x84 * 4);
    n1 = arg0->unk0x170;
    p114 = Mem_Alloc(n1 * 4);
    r9 = n1 - 1;
    if (r9 != -1) {
        do {
        } while (--r9 != -1);
    }
    arg0->unk0x114 = p114;
    n2 = arg0->unk0x170;
    p118 = Mem_Alloc(n2 * 4);
    r9 = n2 - 1;
    if (r9 != -1) {
        do {
        } while (--r9 != -1);
    }
    arg0->unk0x118 = p118;
    n3 = arg0->unk0x170;
    p11c = Mem_Alloc(n3 * 4);
    r9 = n3 - 1;
    if (r9 != -1) {
        do {
        } while (--r9 != -1);
    }
    arg0->unk0x11C = p11c;
    var_r7 = 0;
    if (var_r7 < arg0->unk0x170) {
        fill = 0x80;
        var_r10 = 0;
        do {
            var_r7 += 1;
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
        } while (var_r7 < arg0->unk0x170);
    }
    t128 = arg0->unk0x128;
    tf = lbl_8029444C;
    arg0->unk0x110 = tf;
    arg0->unk0x128 = t128 | 4;
    return arg0;
}
