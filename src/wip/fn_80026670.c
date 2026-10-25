// WIP DRAFT — PARKED (non-matching). Hand-rebuilt from the want. The previous
// m2c body scored 13.45% (476 B) with undeclared temporaries (temp_r9_4,
// temp_r11_2) and a broken pointer chain in the 0x80000 block.
// reproduce: LEAF_TMPDIR=<scratch> \
//     tools/venv/bin/python tools/want_got.py 0x80026670  -> 452B / 108 diffs / 4.42%
//
// family=m2c range=0x80026670-0x8002684C size=476B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// NOTE: this draft is NOT one of the missing-`case` fold cases -- it has no
// switch. A grep-based scanner flags it only because the word "switch" appears
// in the old park comment; the scan in recipes 6gy should strip comments first.
//
// ------------------------------------------------------------------ decode
// A cursor/bump-allocator setup pass. THE KEY STRUCTURAL FACT: the cursor
// `cur` LIVES IN A STACK SLOT at r1+8 and is re-read/re-written after every
// step (`stw r?,8(r1)` ... `lwz r?,8(r1)`). It is NOT a register. The old draft
// modelled it as a normal C local, which is why its register pressure and
// instruction count were wrong.
//
// Steps, in want's order:
//   cur = arg1 + 0x10
//   arg0->unk8  = arg1->unk0
//   arg0->unk2C = arg1 + 0x18;  arg0->unk30 = that + n*2
//   cur = (arg1 + 0x18) + n*4                       (align up to 4)
//   arg0->unk34 = arg1->unk6 ; arg0->unk36 = arg1->unkA   (HALFWORD stores, sth)
//   if (arg0->unk4 & 0x01000000) arg0->unk1C = 0; else = the masked value
//   if (arg0->unk4 & 0x2000)  { arg0->unkC = cur; cur += 0x600; }
//   if (arg0->unk4 & 0x80000) { jump table fixup: v = *cur; arg0->unk20 = cur;
//                               off = v-1; if (off<0) off = v+0x1E;
//                               cur = cur+4 + ((off>>5)+1)*4; }
//   align cur to 4
//   if (fn_80026AD4(arg0) == 0) { arg0->unk10 = cur; arg0->unk14 = cur+a;
//                                 cur = cur+a+d; }
//   fn_80026668(arg0, a, d, 0);  align cur to 4
//   if (arg1->unkC) { arg0->unk28 = fn_800105CC(unkC*4);
//                     loop: v = fn_8002C638(&cur); if (!v) return 0;
//                           arr[i++] = v; }
//   arg0->unk38 = arg1->unkE;  return 1;
//
// THREE decode corrections vs the m2c draft:
//  1. fn_8002C638 takes the cursor BY POINTER (`addi r3,r1,8`). The draft passed
//     the cursor by value.
//  2. The allocation is `fn_800105CC(count * 4)` -- a direct allocator taking the
//     byte size (`slwi r3,r3,2` first). The draft used Mem_Alloc_3 and passed the
//     unscaled count.
//  3. arg0->unk1C is a WORD (`stw r0,0x1c`), while unk34/unk36/unk38 are HALFWORD
//     (`sth`, offsets 0x34/0x36/0x38). The draft typed unk1C as u16.
//
// Struct offsets verified field-by-field against every store in the want:
//   arg0: unk4=0x04 unk8=0x08 unkC=0x0C unk10=0x10 unk14=0x14 unk1C=0x1C
//         unk20=0x20 unk28=0x28 unk2C=0x2C unk30=0x30 unk34/36/38=0x34/36/38
//   arg1: unk0=0x00 unk6=0x06 unkA=0x0A unkC=0x0C unkE=0x0E unk10 unk14
//
// ------------------------------------------------------------------- parked
// Frame and prologue are exact. got is 24 B short and the residual is
// instruction SCHEDULING plus two register-allocator choices:
//   * want holds arg0 in r31 and arg1 in r28; got picks r30/r28.
//   * want keeps the in-loop counter in a dedicated register and stores with
//     `stwx r3, r29, r9` (index register), i.e. it reloads `arg0->unk28` from
//     memory each iteration; got keeps the array base in r31 and does
//     `stw r3, 0(r31)` with a bumped pointer.
//   * want re-reads `arg1->unkC` (offset 0xC) inside the loop; got hoists it, so
//     the loop loses a compare+reload pair.
// Score improved 13.45% -> 4.42%; the semantics are now correct. The remaining
// gap needs the cursor and the loop counter to land in specific registers.
#include "types.h"

typedef struct Arg0 Arg0;
struct Arg0 {
    s32 pad0;           /* 0x00 */
    s32 unk4;           /* 0x04 */
    void *unk8;         /* 0x08 */
    void *unkC;         /* 0x0C */
    void *unk10;        /* 0x10 */
    void *unk14;        /* 0x14 */
    s32 unk1C;          /* 0x1C -- want stores it with stw */
    void *unk20;        /* 0x20 */
    char pad24[4];      /* 0x24 */
    void *unk28;        /* 0x28 */
    void *unk2C;        /* 0x2C */
    void *unk30;        /* 0x30 */
    u16 unk34;          /* 0x34 */
    u16 unk36;          /* 0x36 */
    u16 unk38;          /* 0x38 */
};

typedef struct Arg1 Arg1;
struct Arg1 {
    s32 unk0;
    char pad4[2];
    u16 unk6;
    char pad8[2];
    u16 unkA;
    s32 unkC;
    u16 unkE;
    s32 unk10;
    s32 unk14;
};

s32 fn_80026668(Arg0 *, s32, s32, s32);
s32 fn_80026AD4(Arg0 *);
s32 fn_8002C638(void *);
void *fn_800105CC(u32);

s32 fn_80026670(Arg0 *arg0, Arg1 *arg1) {
    void *cur;      /* LIVES IN A STACK SLOT at r1+8, not a register */
    void *b, *c;
    s32 n;
    s32 a, d;
    void *arr;
    s32 i;
    s32 off;
    void *e;

    n = arg1->unk0;
    cur = (char *)arg1 + 0x10;
    arg0->unk8 = (s32)n;
    b = (char *)arg1 + 0x18;
    c = b + n * 2;
    e = c + n * 2;
    arg0->unk34 = arg1->unk6;
    arg0->unk36 = arg1->unkA;
    a = arg1->unk10;
    d = arg1->unk14;
    arg0->unk2C = b;
    arg0->unk30 = c;
    cur = e;
    if (((s32)e & 3) != 0) {
        cur = (void *)(((s32)e + 4) - ((s32)e & 3));
    }

    if ((arg0->unk4 & 0x01000000) != 0) {
        arg0->unk1C = 0;
    } else {
        arg0->unk1C = arg0->unk4 & 0x01000000;
    }

    if ((arg0->unk4 & 0x2000) != 0) {
        arg0->unkC = cur;
        cur = (char *)cur + 0x600;
    }

    if ((arg0->unk4 & 0x80000) != 0) {
        arg0->unk20 = cur;
        e = (char *)cur + 4;
        off = *(s32 *)cur - 1;
        if (off < 0) {
            off = *(s32 *)cur + 0x1E;
        }
        cur = e + (((off >> 5) + 1) * 4);
    }

    if (((s32)cur & 3) != 0) {
        cur = (void *)(((s32)cur + 4) - ((s32)cur & 3));
    }

    if (fn_80026AD4(arg0) == 0) {
        arg0->unk10 = cur;
        arg0->unk14 = (char *)cur + a;
        cur = (char *)cur + a + d;
    }

    fn_80026668(arg0, a, d, 0);

    if (((s32)cur & 3) != 0) {
        cur = (void *)(((s32)cur + 4) - ((s32)cur & 3));
    }

    if (arg1->unkC == 0) {
        arg0->unk28 = NULL;
    } else {
        arr = fn_800105CC(arg1->unkC * 4);
        arg0->unk28 = arr;
        i = 0;
        while (i < arg1->unkC) {
            /* fn_8002C638 can modify arg1, so unkC must be re-read each pass;
               that is what keeps this a compare+reload loop in the want. */
            s32 v = fn_8002C638(&cur);
            if (v == 0) {
                return 0;
            }
            ((s32 *)arr)[i] = v;
            i++;
        }
    }

    arg0->unk38 = arg1->unkE;
    return 1;
}