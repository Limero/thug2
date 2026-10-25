// WIP DRAFT (non-matching) — rebuilt from disasm (m2c husk was statics-DCE'd)
// PARKED 2026-08-25 at 33.5% masked (-mps-float). Structure fully recovered
// (bool head, setup calls, while-walk w/ fused or.-test, psq record copy,
// two unsigned int->float dances w/ shared cvt slot via split fctiwz asm,
// clamp chain, tail record-copy loop, final store run).
// BLOCKING REASONS (all recipe-catalog exhausted):
// 1. Want interleaves the K1/K2/magic rodata2 float loads INTO the psq
//    record-copy window ([st1][ld2][lfs K1][st2][ld3][lfs x0][st3][lfs K2]);
//    ngccc always hoists them above the window (or duplicates per-site when
//    referenced directly -- volatile asm blocks GCSE sharing). Staged locals
//    give correct sharing+FPR colors (f9/f10/f11) but wrong placement;
//    direct refs give neither. Comma-defs, volatile lvalues, all five sched
//    flags resist.
// 2. Want-only dead `mr r10,r9` inside dance 1 (want-extra-dead-insn class,
//    docs/parkings/33) and 1-2 slot shifts of [stw r0,0x14(r28)]/[lwz r30]
//    around the post-loop calls (doc-15 family).
// Sweep: test_wip_drafts.py --addr 0x8022D910 --extra-cflags "-mps-float"
// family=m2c range=0x8022D910-0x8022DBD4 size=708B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// NEEDS --extra-cflags "-mps-float" (psq record copy).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802B059C[];
extern char lbl_802B05A4[];
extern f32 lbl_802B05AC;
extern f32 lbl_802B05B0;
extern f64 lbl_802B05B8;
extern f32 lbl_802B05C0;
extern f32 lbl_802B05C4;
extern s32 lbl_802FFE98;
s32 fn_8022DBD4(CStruct *);
s32 fn_80054E1C(void *);
void fn_800577A0(CStruct *);
void *fn_800577B4(CStruct *, s32 *);
void fn_8000F2F8(Unk_9F352E7C *, s32);
s32 fn_8023FB40(void);
void *Mem_Alloc2(s32);
void *fn_80240DC0(Unk_DB0E2BAB *);
void fn_8000F320(Unk_F12C5E01 *);
s32 fn_80057C90(CStruct *);
void *fn_80057E2C(Unk_C8FEE62D *);
s32 fn_80054904(s32, s32, s32);
s32 fn_8007DF14(Unk_9D99273B *);
void fn_8022D3F4(Unk_C8FEE62D *);
void fn_80230BA4(void *);
typedef union {
    __ps_t ps[4];
    struct { f32 x0, y0, x2, y2, x4, y4, x6, y7; } f;
} rec_t;
void fn_8022D910(Unk_DB0E2BAB *arg0) {
    struct {
        rec_t rec;
        char _pad[8];
        union { u32 w[2]; f64 d; } cvt;
    } fr;
    s32 var_r9;
    s32 temp_r27;
    Unk_FFAD6788 *temp_r3;
    void *var_r31;
    void *temp_r30;
    Unk_DB0E2BAB *newnode;
    s32 var_r0;
    s32 var_r0_2;
    f32 temp_f13;
    s32 t;
    register void *temp_r29 __asm__("r29");
    register void *var_r10 __asm__("r10");
    register void *var_r11 __asm__("r11");
    register s32 var_r8 __asm__("r8");
    rec_t *srcp;
    f32 k1;
    f32 k2;
    f64 kmagic;

    var_r9 = 1;
    if (!(arg0->unk0x0 & 2)) {
        var_r9 = 0;
    }
    if (var_r9 != 0) {
        fn_8022DBD4(arg0);
    }
    arg0->unk0x1C = 0x20;
    arg0->unk0x0 |= 2;
    temp_r3 = (void *)fn_80054E1C((void *)lbl_802B059C);
    arg0->unk0x10 = (s32)temp_r3;
    temp_r27 = temp_r3->unk0xD0;
    fn_800577A0(temp_r27);
    while ((var_r31 = fn_800577B4(temp_r27, 0)) != NULL) {
        temp_r30 = (void *)lbl_802FFE98;
        fn_8000F2F8((s32)temp_r30, fn_8023FB40());
        newnode = fn_80240DC0(Mem_Alloc2(0x30));
        fn_8000F320(lbl_802FFE98);
        newnode->unk0x8 = arg0->unk0xC;
        arg0->unk0xC = (s32)newnode;
        newnode->unk0x0 = fn_80057C90(var_r31);
        srcp = (rec_t *)fn_80057E2C(var_r31);
        fr.rec.ps[0] = srcp->ps[0];
        fr.rec.ps[1] = srcp->ps[1];
        fr.rec.ps[2] = srcp->ps[2];
        fr.rec.ps[3] = srcp->ps[3];
        {
            f64 hold;
            __asm__ volatile("fctiwz %0, %1" : "=f"(hold) : "f"(((fr.rec.f.x4 - fr.rec.f.x0) + (k1 = lbl_802B05AC, k1)) / (k2 = lbl_802B05B0, k2)));
            fr.cvt.d = hold;
        }
        var_r0 = (s32)fr.cvt.w[1];
        if (var_r0 <= 0) {
            var_r0 = 1;
        }
        fr.cvt.w[1] = (u32)var_r0 ^ 0x80000000;
                fr.cvt.w[0] = QB_INT_TO_DOUBLE_BIAS;
        kmagic = lbl_802B05B8;
        *((f32 *)&newnode->unk0x10) = (f32)(fr.cvt.d - kmagic) * k2;
        {
            f64 hold2;
            __asm__ volatile("fctiwz %0, %1" : "=f"(hold2) : "f"(((fr.rec.f.x6 - fr.rec.f.x2) + k1) / k2));
            fr.cvt.d = hold2;
        }
        var_r0_2 = (s32)fr.cvt.w[1];
        if (var_r0_2 <= 0) {
            var_r0_2 = 1;
        }
        fr.cvt.w[1] = (u32)var_r0_2 ^ 0x80000000;
        fr.cvt.w[0] = QB_INT_TO_DOUBLE_BIAS;
        *((f32 *)&newnode->unk0x18) = (f32)(fr.cvt.d - kmagic) * k2;
        temp_f13 = fr.rec.f.y7 - fr.rec.f.y2;
        *((f32 *)&newnode->unk0x14) = temp_f13;
        if ((temp_f13 < lbl_802B05C0) && (temp_f13 > lbl_802B05C4)) {
            *((f32 *)&newnode->unk0x14) = lbl_802B05C0;
        }
    }
    t = fn_80054904((s32)lbl_802B05A4,
        ((Unk_C7387A53 *)arg0->unk0x10)->unk0x84, 1);
    arg0->unk0x14 = t;
    temp_r29 = (void *)fn_8007DF14(t);
    var_r10 = (void *)fn_8007DF14(arg0->unk0x10);
    var_r11 = temp_r29;
    var_r8 = 0x60;
    do {
        var_r8 -= 0x18;
        ((Unk_DB0E2BAB *)var_r11)->unk0x0 = ((CStruct *)var_r10)->unk0x0;
        ((Unk_DB0E2BAB *)var_r11)->unk0x4 = ((CStruct *)var_r10)->unk0x4;
        ((Unk_DB0E2BAB *)var_r11)->unk0x8 = ((CStruct *)var_r10)->unk0x8;
        ((Unk_DB0E2BAB *)var_r11)->unk0xC = ((CStruct *)var_r10)->unk0xC;
        ((Unk_DB0E2BAB *)var_r11)->unk0x10 = ((CStruct *)var_r10)->unk0x10;
        var_r10 = (char *)var_r10 + 0x18;
        ((Unk_DB0E2BAB *)var_r11)->unk0x14 = *(s32 *)((char *)var_r10 + -0x4);
        var_r11 = (char *)var_r11 + 0x18;
    } while (var_r8 != 0);
    ((Unk_DB0E2BAB *)var_r11)->unk0x0 = ((CStruct *)var_r10)->unk0x0;
    ((Unk_DB0E2BAB *)var_r11)->unk0x4 = ((CStruct *)var_r10)->unk0x4;
    ((Unk_DB0E2BAB *)var_r11)->unk0x8 = ((CStruct *)var_r10)->unk0x8;
    ((Unk_DB0E2BAB *)var_r11)->unk0xC = ((CStruct *)var_r10)->unk0xC;
    ((Unk_1C4D340C *)temp_r29)->unk0x4 = 0x400;
    ((Unk_1C4D340C *)temp_r29)->unk0x0 = var_r8;
    ((Unk_1C4D340C *)temp_r29)->unk0x5C = (u16)var_r8;
    ((Unk_1C4D340C *)temp_r29)->unk0x5E = (u16)var_r8;
    ((Unk_1C4D340C *)temp_r29)->unk0x58 = var_r8;
    ((Unk_1C4D340C *)temp_r29)->unk0x68 = var_r8;
    ((Unk_1C4D340C *)temp_r29)->unk0x6C = var_r8;
    fn_8022D3F4(arg0);
    fn_80230BA4(arg0);
}
