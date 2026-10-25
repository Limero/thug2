// WIP DRAFT (non-matching) — hand-rebuilt from the WANT disassembly.
// family=m2c range=0x8007FBEC-0x8007FE50 size=612B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// PARKED 2026-10-06. Five semantic defects were
// fixed off the WANT + the matched sibling src/fn_8007671C.c (same
// fn_8007DE80(Mem_Alloc2(0x290), 0xA) ctor idiom):
//   (1) ctor arg shape: WANT is `obj = fn_8007DE80(Mem_Alloc2(0x290), 0xA)`
//       (r4 = 0xA, r3 = the Mem_Alloc2 result). The old m2c body dropped the
//       alloc result and called `fn_8007DE80(0xA)` — one arg, 0xA in r3.
//   (2) the 0x5e element count is a u16 (`lhz`), not the m2c 32-bit read
//       (which emitted `lhz ...,0x60(r11)`, one field too high).
//   (3) the matrix fill read lbl_80296274 through the RAW literal 0x80296274
//       — that compiles to a load from address 0; now the registered symbol.
//   (4) the tail alloc is `Mem_Alloc2(0x70)` (single arg); the old body passed
//       arg0 as well, so r3 held the object and 0x70 landed in r4.
//   (5) the `obj != 0` vtable dispatch was emitted by m2c as `if (0)` (dead).
//       Restored from WANT: `lha r3,8(vt); lwz r0,0xC(vt); mtlr; add; blrl`.
// Residual after these fixes is UNMEASURED (this slice has no compiler). The
// two empty countdown spins at 0x8007FD1C / 0x8007FDA0 and the exact
// fn_80093E4C argument staging are still best-effort; WANT frame is 0x70 with
// stmw r24 (r24..r31) + mfcr, the old object was 0x80/stmw r23.
#include "types.h"
#include "structs.h"
extern char lbl_80296270[];
extern char lbl_80296274[];
void *Mem_Alloc(s32);
void *Mem_Alloc2(s32);
void *Mem_NewZero(s32);
void *fn_8007DE80(void *, s32);
void *fn_8007E8F8(void);
void *fn_8007ED94(void *);
s32 fn_800963F8(void *, s32);
void fn_8005F1F0(void *, s32);
s32 *fn_80093E4C(void *, void *, s32, void *);

typedef struct {
    char pad0x0[0x8];
    s16 unk0x8;
    char pad0xA[0x2];
    s32 (*unk0xC)(void *, s32);
} VTable_8007FBEC;

void *fn_8007FBEC(void *arg0, s32 arg1, CStruct *arg2) {
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    f32 sp14;
    f32 spC;
    Unk_59AB5482 sp8;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f13;
    f32 temp_f13_2;
    s32 *temp_r3_3;
    s32 temp_r30;
    s32 temp_r31_2;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_ctr_3;
    s32 var_r31;
    s32 var_r9;
    u16 temp_r31;
    u32 var_r30;
    void *temp_r28;
    Unk_DB0E2BAB *temp_r3;
    Unk_9D99273B *temp_r3_2;
    VTable_8007FBEC *temp_r9;
    void *var_r9_2;

    temp_r3_2 = fn_8007DE80(Mem_Alloc2(0x290), 0xA);
    temp_r3_2->unk0x288 = *(s32 *)(*(s32 *)((char *)arg0 + 0x30) + 0x54);
    Mem_NewZero(0x58);
    temp_r3 = fn_8007E8F8();
    temp_r3->unk0x18 = temp_r3_2;
    temp_r31 = *(u16 *)(*(s32 *)(*(s32 *)((char *)arg0 + 0x30) + 0x54) + 0x5E);
    if ((s32)temp_r31 != 0) {
        temp_r3->unk0x20 = Mem_Alloc((s32)temp_r31 * 4);
    } else {
        temp_r3->unk0x20 = (void *)temp_r31;
    }
    var_r30 = 0U;
    *((u32 *)&temp_r3->unk0x24) = (u32)temp_r31;
    if (temp_r31 > 0U) {
        var_r31 = 0;
        do {
            var_r30 += 1;
            *((s32 *)var_r31 + temp_r3->unk0x20) =
                fn_800963F8(
                    *((s32 *)var_r31 +
                      *(s32 *)(*(s32 *)((char *)*(s32 *)((char *)((char *)arg0) + 0x30) + 0x54) + 0x58)),
                    arg1);
            var_r31 += 4;
        } while (var_r30 < (u32)*((u32 *)&temp_r3->unk0x24));
    }
    temp_r31_2 = fn_8007ED94(temp_r3);
    temp_r3_2->unk0x288 = 0;
    if (temp_r3_2 != 0) {
        temp_r9 = (VTable_8007FBEC *)temp_r3_2->unk0x284;
        temp_r9->unk0xC((char *)temp_r3_2 + temp_r9->unk0x8, 3);
    }
    temp_r3->unk0x18 = 0;
    fn_8005F1F0(temp_r3, 1);
    temp_r30 = arg2->unk0x8;
    var_r9 = temp_r30 - 1;
    temp_r28 = Mem_Alloc(temp_r30 << 6);
    if (temp_r30 != 0) {
        do {
            var_ctr = 4;
loop_10:
            var_ctr -= 1;
            if (var_ctr != 0) {
                goto loop_10;
            }
            var_r9 -= 1;
        } while (var_r9 != -1);
    }
    if (temp_r30 > 0) {
        var_ctr_2 = temp_r30;
        temp_f13 = *(f32 *)lbl_80296270;
        temp_f0 = *(f32 *)lbl_80296274;
        var_r9_2 = temp_r28;
        do {
            ((Unk_DB0E2BAB *)var_r9_2)->unk0x0 = temp_f13;
            ((Unk_DB0E2BAB *)var_r9_2)->unk0x4 = temp_f0;
            ((Unk_DB0E2BAB *)var_r9_2)->unk0x8 = temp_f0;
            ((Unk_DB0E2BAB *)var_r9_2)->unk0xC = temp_f0;
            ((Unk_DB0E2BAB *)var_r9_2)->unk0x10 = temp_f0;
            ((Unk_DB0E2BAB *)var_r9_2)->unk0x14 = temp_f13;
            ((Unk_DB0E2BAB *)var_r9_2)->unk0x18 = temp_f0;
            ((Unk_DB0E2BAB *)var_r9_2)->unk0x1C = temp_f0;
            ((Unk_DB0E2BAB *)var_r9_2)->unk0x20 = temp_f0;
            ((Unk_DB0E2BAB *)var_r9_2)->unk0x24 = temp_f0;
            ((Unk_DB0E2BAB *)var_r9_2)->unk0x28 = temp_f13;
            ((Unk_DB0E2BAB *)var_r9_2)->unk0x2C = temp_f0;
            ((Unk_DB0E2BAB *)var_r9_2)->unk0x30 = temp_f0;
            ((Unk_DB0E2BAB *)var_r9_2)->unk0x34 = temp_f0;
            ((Unk_DB0E2BAB *)var_r9_2)->unk0x38 = temp_f0;
            ((Unk_DB0E2BAB *)var_r9_2)->unk0x3C = temp_f13;
            var_r9_2 += 0x40;
            var_ctr_2 -= 1;
        } while (var_ctr_2 != 0);
    }
    var_ctr_3 = 4;
    do {
        var_ctr_3 -= 1;
    } while (var_ctr_3 != 0);
    temp_f0_2 = *(f32 *)lbl_80296274;
    temp_f13_2 = *(f32 *)lbl_80296270;
    spC = temp_f0_2;
    *((f32 *)&sp8) = temp_f13_2;
    sp8.unk0x8 = temp_f0_2;
    sp40 = temp_f0_2;
    sp44 = temp_f13_2;
    sp14 = temp_f0_2;
    sp18 = temp_f0_2;
    sp1C = temp_f13_2;
    sp20 = temp_f0_2;
    sp24 = temp_f0_2;
    sp28 = temp_f0_2;
    sp2C = temp_f0_2;
    sp30 = temp_f13_2;
    sp34 = temp_f0_2;
    sp38 = temp_f0_2;
    sp3C = temp_f0_2;
    Mem_Alloc2(0x70);
    temp_r3_3 = fn_80093E4C((void *)temp_r31_2, &sp8, temp_r30, temp_r28);
    arg2->unk0x58 = (s32)temp_r3_3;
    *((s32 *)temp_r3_3) |= 1;
    temp_r3->unk0x30 = temp_r3_3;
    return temp_r3;
}

// NOTE (2026-10-06): unverified against the compiler. The four
// load-bearing WANT facts encoded here are the ctor call shape, the u16 0x5e
// count, the lbl_80296274 symbol (not the raw literal), and Mem_Alloc2(0x70).
// The `if (temp_r3_2 != 0)` vtable call matches WANT's `lha r3,8(vt)` (s16
// offset) + `lwz r0,0xC(vt)`; the old body had it as `if (0)`.
