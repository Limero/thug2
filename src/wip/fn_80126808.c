// WIP DRAFT - PARKED 2026-10-03 (b66): DIFF 15.2% (baseline DIFF 7.6%; went UP because
// the body is now semantically right and instruction-for-instruction correct in the
// prologue, all 7 case bodies, the byte-copy loop and the epilogue - 548B got vs 552B
// want, only 3 residual items, see below).
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x80126808
// WHAT IS ALREADY EXACT (do not re-derive):
//   * frame 0x18 + `stmw r29,0xc` + LR at old-sp+4, i.e. ZERO stack locals. The 8 free
//     words at +4/+8 are standard padding, not locals.
//   * prologue: `mr r31/r29/r30 = r3/r4/r5`, `lwz r0,8(r31); cmpwi; beq; bl 0x801266EC`
//     -> `fn_801266EC(arg0)` (1 arg = the object itself, NOT its payload).
//   * case 3/4 `CreateString(p)` = 0x801251B4 (1 arg); case 5 `fn_80125000(fn_80128EF4(0xC))`,
//     case 6 `fn_80124FDC(fn_80128F44(0x10))` (inits return their arg in r3); case 10
//     `fn_80126EAC(fn_80019D08(8))` then `fn_80126F40(o, src)`; case 12
//     `fn_80128F94(fn_8003E7CC(0xC))` then `fn_80126E28(o, src)` - BOTH take 2 args
//     (m2c dropped the 2nd). Declaring every callee is what killed the `crclr cr1eq`s.
//   * case 5/6 float copies: first store goes through the ctor-result local (`stfs f0,4(r3)`),
//     the rest re-read `arg0->unk0x8`/`arg1->unk0x8` each time. Payload is an object with
//     f32 at +4/+8/+0xC: `(f32*)`-style field access, NOT `(f32)*(s32*)` (m2c's form injects
//     int->double converts and ~200 bytes of junk).
//   * case 7 loop: plain `while (i < arg1->unk0x2)` (NO `if (n>0) do{}while`), u32 index +
//     u16 bound re-loaded every test, byte pointers post-incremented. Got == want
//     instruction-for-instruction (only the index register differs: r28 vs r11).
//   * case 7 head: `fn_8000F2F8(*(void**)0x802FFE98, ((...*)...)->unk0x12C)` - the global at
//     0x802FFE98 must be written as a literal address TWICE (want reloads it after the call).
//     `arg0->unk0x2 = arg1->unk0x2` (u16) and the order alloc/store/len/UNLOCK matches.
//   * shared `flags_copy` tail for cases 10/12 with arg2!=0: k=0x14 / k=0x15 then
//     `mr r0,r11; rlwimi; stw 0(r31); lwz/stw 8` - the same rotate-merge form as the
//     prologue store, so whatever fixes the prologue flags fixes this too.
// RESIDUAL DIFF (3 items):
//   1. FLAG MERGE, +1 insn. want `clrlwi r0,r0,0x19` (= x & ~0x7F) +
//      `rlwimi r11,r0,0x10,9,0xf` (dest bits 9..15 <- src bits 25..31). Because the source
//      is an `lhz`, that pair is semantically just "clear bits 9..15". Every C form I tried
//      folds to `rlwinm + rlwinm + or` (see Ruled out). The pair is the rs6000 `insn_ori`
//      pattern: RTL must be `(ior (and REG 0xFFFF01FF) (and (lshift REG 16) 0xFE00))`,
//      i.e. the value operand must be reduced to a PLAIN REGISTER and the 0xFE00 mask must
//      come from the DESTINATION mask only (an explicit `& 0x7F00` on the shifted operand
//      makes ProDG fold the whole thing to zero).
//   2. `stmw r28,8(r1)` + loop index in r28: one register more of pressure than the want
//      (which saves only r29-r31 and keeps the index in r11). Everything I moved into
//      per-case scopes did not change it - likely one more long-lived pseudo than the
//      original had.
//   3. Switch decision tree: same 10 `cmpwi` but a different shape. want splits
//      `cmpwi 6 / cmpwi 2 / cmpwi 1` on the low side; mine splits `cmpwi 4 / cmpwi 3 /
//      cmpwi 1`. GCC's balance_case_nodes depends on the case order in the source, so this
//      needs the original case order, not a rewrite.
// RULED OUT (measured, ProDG 3.9.3, -O2 -G0 -mcpu=750 -fno-common):
//   * `(t & ~0xFE00) | ((x & 0x7F) << 16)` and every variant with a destination mask of
//     0x7F00/0xFE00 -> always `rlwinm val,16,9,15` + `rlwinm dst` + `or` (3 insns), never
//     the 2-insn clrlwi+rlwimi. Same for `(x << 16) & 0xFE00` (folds to nothing), for
//     `<< 9` variants, for a variable `k`, and for `>> 7`/`>> 16` right-shifts.
//   * ProDG 3.9.3 BUG worth knowing: `(X << C) & M` where the shift and the mask overlap is
//     mis-compiled - the mask gets shifted by 8. `(f->w << 9) & 0x7F00` becomes
//     `rlwinm r,r,9,17,22` (mask 0x7E0000) instead of 0x7F00's bits 9..15. `<< 16` with an
//     overlapping mask folds to a constant. So `(X << 9) & 0x7F00` (semantically "type into
//     bits 9..15") is NOT expressible - which is exactly the mask the want's rlwimi uses.
//   * `__attribute__((packed))` is broken in ProDG (u16+s32+u32 gave offsets 0,4,6,10).
//     `-G0` struct layout puts a `u16` AFTER an `s32` at the next 4-byte boundary, so a
//     literal `{s32; u16; s32; ptr}` cannot give offsets 0/2/4/8 - the union
//     `{union {s32 a; struct {u16 lo,hi;};}; s32; void*;}` in this file does, exactly.
//   * `if (n > 0) do{...}while` for case 7 (m2c's shape) costs an extra cmp/branch; the
//     want is a plain rotated while.
// MOST PROMISING NEXT STEP: brute-force only the FLAG MERGE - compile ~20 one-line variants
//   of `(t & ~M) | ((V op C) op M2)` in this real function and grep the .s for
//   `rlwimi ...,16,9,15` + a preceding `clrlwi ...,25`; the value operand has to end up as a
//   plain register, so try casts (`(u16)`, `(s32)`), `*0` tricks and splitting the value into
//   its own `u16` local. Then fix the case order for the switch tree.
// family=m2c range=0x80126808-0x80126A30 size=552B
// INERT: not registered in splits.txt/configure.py - never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "structs.h"

/* arg0: s32 flags, u16 len, s32 unk4, ptr payload (unk0x2 is written only by case 7) */
typedef struct {
    union {
        s32 unk0x0;
        struct { u16 lo; u16 hi; } h;
    } u0;
    s32 unk0x4;
    void *unk0x8;
} B66D;

/* arg1: u16 type, u16 len, s32 unk4, ptr payload */
typedef struct {
    u16 unk0x0;
    u16 unk0x2;
    s32 unk0x4;
    void *unk0x8;
} B66S;

/* payload object: s32 tag then f32 fields at +4/+8/+0xC */
typedef struct {
    s32 unk0x0;
    f32 unk0x4;
    f32 unk0x8;
    f32 unk0xC;
} B66P;

/* the global at 0x802FFE98 */
typedef struct {
    char pad0x12C[0x12C];
    void *unk0x12C;
} B66G;

void fn_801266EC(B66D *);
void *fn_80128EF4(s32);
B66P *fn_80125000(B66P *);
B66P *fn_80128F44(s32);
B66P *fn_80124FDC(B66P *);
B66P *fn_80128F94(B66P *);
void *fn_80019D08(s32);
B66P *fn_80126EAC(B66P *);
void fn_80126F40(B66P *, void *);
void fn_80126E28(B66P *, void *);
char *CreateString(char *);
void *Mem_Alloc_3(s32);
void *fn_8003E7CC(s32);
void fn_8000F2F8(void *, void *);
void fn_8000F320(void *);

void fn_80126808(B66D *arg0, B66S *arg1, s32 arg2) {
    s32 t;
    s32 k;

    if (arg0->unk0x8 != NULL) {
        fn_801266EC(arg0);
    }
    t = arg0->u0.unk0x0;
    arg0->u0.unk0x0 = (t & ~0x7F00) | ((arg1->unk0x0 & 0x7F) << 16);
    arg0->unk0x4 = arg1->unk0x4;
    switch (arg1->unk0x0 & 0x7F) {
    case 1:
    case 2:
    case 13:
    case 20:
    case 21:
        arg0->unk0x8 = arg1->unk0x8;
        break;
    case 3:
    case 4:
        arg0->unk0x8 = CreateString((char *)arg1->unk0x8);
        break;
    case 5: {
        B66P *o = fn_80125000(fn_80128EF4(0xC));
        arg0->unk0x8 = o;
        ((B66P *)arg0->unk0x8)->unk0x4 = ((B66P *)arg1->unk0x8)->unk0x4;
        ((B66P *)arg0->unk0x8)->unk0x8 = ((B66P *)arg1->unk0x8)->unk0x8;
        break;
    }
    case 6: {
        B66P *o = fn_80124FDC(fn_80128F44(0x10));
        arg0->unk0x8 = o;
        ((B66P *)arg0->unk0x8)->unk0x4 = ((B66P *)arg1->unk0x8)->unk0x4;
        ((B66P *)arg0->unk0x8)->unk0x8 = ((B66P *)arg1->unk0x8)->unk0x8;
        ((B66P *)arg0->unk0x8)->unk0xC = ((B66P *)arg1->unk0x8)->unk0xC;
        break;
    }
    case 10:
        if (arg2 != 0) {
            k = 0x14;
            goto flags_copy;
        }
        {
            B66P *o = fn_80126EAC(fn_80019D08(8));
            arg0->unk0x8 = o;
            fn_80126F40(o, arg1->unk0x8);
        }
        break;
    case 12:
        if (arg2 != 0) {
            k = 0x15;
            goto flags_copy;
        }
        {
            B66P *o = fn_80128F94(fn_8003E7CC(0xC));
            arg0->unk0x8 = o;
            fn_80126E28(o, arg1->unk0x8);
        }
        break;
    case 7: {
        u8 *d;
        u8 *s;
        u32 i = 0;

        fn_8000F2F8(*(B66G **)0x802FFE98, ((B66G *)*(B66G **)0x802FFE98)->unk0x12C);
        arg0->unk0x8 = Mem_Alloc_3(arg1->unk0x2);
        arg0->u0.h.hi = arg1->unk0x2;
        fn_8000F320(*(void **)0x802FFE98);
        d = (u8 *)arg0->unk0x8;
        s = (u8 *)arg1->unk0x8;
        while (i < arg1->unk0x2) {
            *d = *s;
            i++;
            s++;
            d++;
        }
        break;
    }
    }
    return;
flags_copy:
    arg0->u0.unk0x0 = (t & ~0x7F00) | ((k & 0x7F) << 16);
    arg0->unk0x8 = arg1->unk0x8;
    return;
}
