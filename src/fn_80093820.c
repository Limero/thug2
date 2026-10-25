// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80093820-0x80093CB8 (1176B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-gcse
#include "types.h"
#include "structs.h"
extern char lbl_8037B5E8[];
extern char lbl_8037B610[];
extern char lbl_8037B614[];
extern char lbl_8037B644[];
extern char lbl_8037B6E0[];
extern char lbl_8037B734[];

void PSMTX_Concat(void *, void *, void *);
void fn_8001F738(void *, s32);
void fn_8001FAA4(s32, s32, s32, s32, s32);
s32 fn_80060DE4(Unk_C7387A53 *);
void fn_8005B560(void *, s32, s32);
void fn_80059238(void);
void PSMTXCopy(void *, void *);
void fn_8001D39C(void *, void *);
void fn_8001EF84(s32, s32 *);
void GX_InitLightColor(void *, s32 *);
void GX_InitLightPos(void *, f32, f32, f32);
void GX_LoadLightObjImm(void *, s32);
void fn_8001E248(s32, s32, s32, s32, s32, s32, s32);
void fn_8001F83C(void *, s32);
void fn_80098A54(s32);
void GX_SetVtxAttrFmt(s32, s32, s32, s32, s32);
void fn_80097E48(s32, s32, s32, s32, s32, s32);

void fn_80093820(Unk_E6EE0C94 *arg0, s32 arg1) {
    register s32 a1 __asm__("r24");
    struct {
        f32 sp8[12];
        f32 sp38[12];
        s32 sp68;
        s32 pad0x6C;
        s32 sp70[48];
    } locals;
    f32 *sp8p;
    f32 t3, tB;
    register f32 t7 __asm__("fr0");
    register s32 sp38p_s __asm__("r30");
    f32 *sp38q;
    char *lbl_base;
    s32 var_r25;
    s32 var_r26;
    s32 var_r27;
    s32 temp_r30;
    s32 var_one;
    register s32 sp70_s __asm__("r29");
    s32 var_r3;
    s32 v6c;

    a1 = arg1;
    sp8p = locals.sp8;
    sp38p_s = (s32)locals.sp38;
    sp38q = locals.sp38;
    sp8p[0] = *(f32 *)((char *)arg0 + 8);
    sp8p[1] = *(f32 *)((char *)arg0 + 0x18);
    sp8p[2] = *(f32 *)((char *)arg0 + 0x28);
    sp8p[4] = *(f32 *)((char *)arg0 + 0xC);
    sp8p[5] = *(f32 *)((char *)arg0 + 0x1C);
    sp8p[6] = *(f32 *)((char *)arg0 + 0x2C);
    sp8p[8] = *(f32 *)((char *)arg0 + 0x10);
    sp8p[9] = *(f32 *)((char *)arg0 + 0x20);
    sp8p[10] = *(f32 *)((char *)arg0 + 0x30);
    sp8p[3] = *(f32 *)((char *)arg0 + 0x38);
    sp8p[7] = *(f32 *)((char *)arg0 + 0x3C);
    sp8p[11] = *(f32 *)((char *)arg0 + 0x40);
    PSMTX_Concat((void *)sp38p_s, (void *)lbl_8037B644, sp8p);
    fn_8001F738((void *)sp38p_s, 0);
    if (a1 & 0x10) {
        fn_8001FAA4(0, 0x3C, 0x3C, 0x3C, 0x3C);
    }
    if (arg0->unk0x60 != 0) {
        var_r3 = fn_80060DE4((Unk_C7387A53 *)arg0->unk0x60);
    } else {
        var_r3 = NULL;
    }
    if (var_r3 != NULL) {
        fn_8005B560((void *)var_r3, (char *)arg0 + 0x38, *(s32 *)var_r3);
    } else {
        fn_80059238();
    }
    PSMTXCopy(sp38q, lbl_8037B6E0);
    fn_8001D39C(lbl_8037B614, sp38q);
    lbl_base = lbl_8037B5E8;
    t3 = locals.sp38[3];
    t7 = locals.sp38[7];
    tB = locals.sp38[11];
    *(f32 *)(lbl_base + 0xEC) = t3;
    *(f32 *)(lbl_base + 0xF0) = t7;
    *(f32 *)(lbl_base + 0xF4) = tB;
    if (arg0->unk0x0 & 8) {
        *(s32 *)(lbl_base + 0x14C) = 1;
        *(u8 *)(lbl_base + 0x148) = arg0->unk0x5C;
        *(u8 *)(lbl_base + 0x149) = arg0->unk0x5D;
        *(u8 *)(lbl_base + 0x14A) = arg0->unk0x5E;
        *(u8 *)(lbl_base + 0x14B) = arg0->unk0x5F;
    }
    locals.sp68 = *(s32 *)(lbl_base + 0x150);
    fn_8001EF84(4, &locals.sp68);
    lbl_base += 0x178;
    var_r25 = 0;
    var_r26 = 0;
    var_one = 1;
    sp70_s = (s32)locals.sp70;
    var_r27 = 3;
    {
    register s32 sp68_s __asm__("r22");
    sp68_s = (s32)&locals.sp68;
    do {
        if (*(u8 *)(lbl_base - 0x24) + *(u8 *)(lbl_base - 0x23) + *(u8 *)(lbl_base - 0x22) != 0) {
            locals.sp68 = *(s32 *)(lbl_base - 0x24);
            temp_r30 = var_one << var_r26;
            var_r25 |= temp_r30;
            GX_InitLightColor((s32 *)sp70_s, (s32 *)sp68_s);
            var_r26 += 1;
            GX_InitLightPos((s32 *)sp70_s, *(f32 *)(lbl_base - 0x18), *(f32 *)(lbl_base - 0xC), *(f32 *)lbl_base);
            GX_LoadLightObjImm((s32 *)sp70_s, temp_r30);
            sp70_s += 0x40;
        }
        lbl_base += 4;
        var_r27 -= 1;
    } while (var_r27 != 0);
    }
    fn_8001E248(0, 1, 0, 1, var_r25, 2, 2);
    fn_8001E248(2, 0, 1, 1, 0, 0, 2);
    if ((arg0->unk0x48 != 0) && ((v6c = *(s32 *)((char *)arg0->unk0x54 + 0x6C)) == 0)) {
        fn_8001F83C(locals.sp8, 0);
        *(s32 *)lbl_8037B610 = v6c;
        fn_80098A54(arg0->unk0x54);
        GX_SetVtxAttrFmt(2, 9, 1, 3, 6);
        GX_SetVtxAttrFmt(3, 9, 1, 3, 6);
        GX_SetVtxAttrFmt(4, 9, 1, 3, 6);
        GX_SetVtxAttrFmt(5, 9, 1, 3, 6);
        GX_SetVtxAttrFmt(6, 9, 1, 3, 6);
        GX_SetVtxAttrFmt(7, 9, 1, 3, 6);
        fn_80097E48(arg0->unk0x54, arg0->unk0x68, a1 | 8, 0, NULL, 0);
        GX_SetVtxAttrFmt(2, 9, 1, 4, 0);
        GX_SetVtxAttrFmt(3, 9, 1, 4, 0);
        GX_SetVtxAttrFmt(4, 9, 1, 4, 0);
        GX_SetVtxAttrFmt(5, 9, 1, 4, 0);
        GX_SetVtxAttrFmt(6, 9, 1, 4, 0);
        GX_SetVtxAttrFmt(7, 9, 1, 4, 0);
    } else {
        if (!(arg0->unk0x0 & 4)) {
            a1 |= 0x400;
        }
        fn_8001F83C(sp38q, 0);
        if ((*(s32 *)((char *)arg0->unk0x54 + 0x6C) != 0) && (arg0->unk0x48 != 0)) {
            *(s32 *)lbl_8037B610 = 1;
            fn_80098A54(arg0->unk0x54);
            fn_80097E48(arg0->unk0x54, 0, a1 | 8, arg0->unk0x48, (char *)arg0 + 8, arg0->unk0x4C);
        } else {
            if (!(arg0->unk0x0 & 4)) {
                a1 |= 0x400;
            }
            *(s32 *)lbl_8037B610 = 0;
            fn_80098A54(arg0->unk0x54);
            fn_80097E48(arg0->unk0x54, 0, a1, 0, NULL, 0);
        }
    }
    if (arg0->unk0x0 & 8) {
        *(s32 *)lbl_8037B734 = 0;
    }
}
