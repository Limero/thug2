// WIP DRAFT (non-matching) — hand-rebuilt from want; PARKED at NEAR 72.8%.
// family=m2c range=0x800200D8-0x800203D4 size=764B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// ---------------------------------------------------------------------------
// STATUS 2026-10-04: m2c 2.2% -> **NEAR 72.8%, object SIZE-EXACT (764B/191
// insns, delta 0)**, 0 emitted asm, 0 flags, 2 register-var pins, 1 frame pad.
// Every one of the 19 branches is at want's address with want's mnemonic, and
// every relocation addend resolves to want's target (checked via .rela.text
// section-relative addends: 0x800203a8 / 0x80020394 / 0x8002018c / 0x80020190
// / 0x800202b8 x2 / 0x80020394 x2 / 0x80020134 + 9x DCFlushRange).
//
// WHAT THE FUNCTION IS (fully recovered):
//   void fn(Hdr *hdr, Elem *arr, s32 n) — walks `n` 0x20-byte elements and
//   patches per-vertex data in a CPU-side vertex buffer, flushing each patch
//   with DCFlushRange.  Hdr = {u32 size; u8 *base; s16 idx1[]; s16 idx2[]};
//   Elem = {Obj *o; ...; u32 colA; u32 colB;};  Obj = {..; u8 log2w; u8 log2h;
//   u8 lvl; ..; u32 colA; u32 colB;}.  Two colour sub-blocks (0x10 / 0x14),
//   five patches each: 3-byte colour, 2 bytes (alpha, 0), a 3-byte
//   0xE0<<16|(h<<10)|w word, then two srawi-shifted 16-bit halves.
//
// SEMANTIC FIXES THAT MATTERED (each was worth points, in order):
//  1. Struct offsets/sizes (m2c's names lie about layout): Obj needs u8 at
//     +6/+7/+8 and u32 at +0x10/+0x14; Elem must be EXACTLY 0x20 bytes
//     (m2c's merged struct gave stride 0x1C) — that fixed the `lwzx r9,r24,r25`
//     base and every field offset.
//  2. `arg1[i].unk0` re-read at all five use points (no local for it).  The
//     char-pointer stores below force the reload; caching it in a local kills
//     4 of want's 5 `lwzx` pairs.  Same for `arg0->idx1[i]` (5 reads) and
//     `arg0->unk4` (8 reads) — they must stay EXPRESSIONS, not locals.
//  3. Loop form: plain `for (i = 0; i < arg2; i++)`.  The do-while form gives
//     `or. r20,r5,r5; ble` + `add r27,r23,r23; slwi r26,r23,5` and lands 4B
//     short; the `for` form emits want's `li r22,0 / cmpw / bge` entry guard
//     AND `li r23,1 / li r27,0 / li r24,0` + two byte-offset induction vars.
//  4. Address grouping: `base + (idx + 0x19)`, NOT `base + idx + 0x19`.  Only
//     the parenthesised tree yields `addi rX,rX,0x19; add r8,base,rX` (recipes
//     140 / 6fz); the flat form yields `add rX,base,idx; addi rY,rX,0x19`.
//     Worth ~12 points across the 8 patch sites.
//  5. `t = (w | (h << 10)) | 0xE00000` — ngccc keeps the `or` operand order,
//     so want's `or r0,r30,r0` needs the SOURCE to be `w | (h<<10)`; and the
//     0xE00000 must be the OUTER or, or GCC folds it into `w` first
//     (`oris r9,r30,0xe0`).  Worth 7 points (2 sites).
//  6. Float constants as LITERALS `1.0f` / `16.0f`, not `extern f32 lbl_...`
//     (see FINDING below).  This is also why the source really used literals:
//     want's pool holds magic,1.0f,16.0f,0.5f,1.0f,... adjacently and in that
//     order (recipes 6fy-4 / doc-14).  Worth ~13 points + the 3-FPR prologue.
//  7. 24-byte frame pad: want's stmw sits at 0x34 and lr at 0x84, i.e. 24B more
//     local area than the body produces; `u8 pad[24]` reproduces BOTH exactly
//     (and puts the fix-dance slots at want's 0x28/0x2c).  Unused *extra
//     parameters* do NOT grow the frame (measured), so this is locals, not a
//     wider prototype — the function has no static callers to check arity from.
//
// FINDING (recipe-worthy): GCC 2.95/ngccc's loop-invariant motion hoists the
// `(f32)(f64)(s32)` cast's SYNTHESIZED pool load (magic 0x4330000080000000,
// f31) and its `lis 0x4330` out of a conditional block into the loop
// preheader — but it does NOT hoist an extern-symbol `lfs`.  Only a *literal*
// constant load gets hoisted.  So the same C spelled with `extern f32
// lbl_802911E8` recompiles 4 words short with ONE saved FPR and the loads
// re-issued inside the loop; spelled `1.0f` it produces want's exact preheader
// (3x lis + lfd f31 + lfs f29 + lis 0x4330 + lfs f30) and stfd f29/f30/f31.
// Same rule should be assumed for any want that keeps >=2 loop-invariant
// float constants in callee-saved FPRs.
//
// WHY IT IS STILL PARKED (the blocker):
// pure GCC-2.95 global register allocation, on an otherwise byte-identical
// instruction stream.  Two short-lived pseudo families land one slot off:
//   (a) the per-site index `idx + off` — want uses r9 (and r11 at the third
//       patch), got coalesces it into `p` = r8 at all 8 sites;
//   (b) the colour: want `lwz r10,0x10(r9)` + shift temps r10/r9/r0, got
//       `lwz r9,0x10(r9)` + temps r11/r10/r0;
// plus the 3-byte-colour STORE order (want [+3],[+2],[+4], got [+3],[+4],[+2])
// and two 2-instruction `slw`/`clrlwi` swaps.  NEGATIVE RESULTS (measured):
//   - the 3 colour-store orderings ([2][3][4], [3][2][4], [3][4][2], [4][2][3])
//     all score IDENTICALLY -> the store order is scheduler-controlled, NOT
//     source-controlled; do not bother permuting it;
//   - `or`-association and address-grouping ARE source-controlled (see 4, 5);
//   - hoisting the declarations (p/c/h/w/t) to the null-block changes nothing;
//   - an `s16 idx` local kills the 5 reloads and drops the object to 736B;
//   - flags: only `-fno-expensive-optimizations` moves anything (72.8 -> 73.8,
//     and only by shuffling two adjacent `stb`s), which is a de-optimising
//     flag chasing scheduler noise — NOT load-bearing, deliberately not kept;
//     `-fno-gcse`, `-fno-caller-saves`, `-fno-inline` are all exactly neutral.
// The two `register ... __asm__("rN")` pins are allocator hints only (they
// change no semantics and are deterministic), kept because they are worth
// +4.2 points; with them removed the same body measures 68.6%.
//
// ---------------------------------------------------------------------------
typedef struct Unk_800200D8_Obj {
    s32 unk0;
    s16 unk4;
    u8 unk6;
    u8 unk7;
    u8 unk8;
    u8 unkA[7];
    u32 unk10;
    u32 unk14;
} Unk_800200D8_Obj;

typedef struct Unk_800200D8_Elem {
    Unk_800200D8_Obj *unk0;
    u8 unk4[0xC];
    u32 unk10;
    u32 unk14;
    u32 unk18;
    u32 unk1C;
} Unk_800200D8_Elem;

typedef struct Unk_800200D8_Hdr {
    u32 unk0;
    u8 *unk4;
    s16 idx1[4];
    s16 idx2[4];
} Unk_800200D8_Hdr;

void DCFlushRange(void *, u32);

void fn_800200D8(Unk_800200D8_Hdr *arg0, Unk_800200D8_Elem *arg1, s32 arg2) {
    s32 i;
    u8 pad[24];
    register u32 col __asm__("r10");
    register u8 *p __asm__("r8");

    for (i = 0; i < arg2; i++) {
        u8 zero;
        u8 alpha;

        if (arg1[i].unk0 != NULL) {
            zero = 0;
            if (arg1[i].unk0->unk8 > 1U) {
                alpha = (u8) (s32) (((f32) (f64) (s32) arg1[i].unk0->unk8 - 1.0f) * 16.0f);
            } else {
                alpha = 0;
            }

            col = arg1[i].unk0->unk10;
            if (col != 0) {
                if (arg0->idx1[i] != -1) {
                    u32 c;
                    s32 h;
                    s32 w;
                    u32 t;

                    c = col + 0x80000000;
                    p = arg0->unk4 + (arg0->idx1[i] + 0x19);
                    p[2] = (u8) (c >> 0x15U);
                    p[3] = (u8) (c >> 0xDU);
                    p[4] = (u8) (c >> 5U);
                    DCFlushRange(p + 2, 3);
                    p = arg0->unk4 + (arg0->idx1[i] + 5);
                    p[3] = alpha;
                    p[4] = zero;
                    DCFlushRange(p + 2, 3);
                    w = (u16) (1 << arg1[i].unk0->unk6) - 1;
                    h = (u16) (1 << arg1[i].unk0->unk7) - 1;
                    t = (w | (h << 0xA)) | 0xE00000;
                    p = arg0->unk4 + (arg0->idx1[i] + 0xA);
                    p[2] = (u8) (t >> 0x10U);
                    p[3] = (u8) (t >> 8U);
                    p[4] = (u8) t;
                    DCFlushRange(p + 2, 3);
                    p = arg0->unk4 + (arg0->idx1[i] + 0x1E);
                    p[3] = (u8) (w >> 8);
                    p[4] = (u8) w;
                    DCFlushRange(p + 3, 2);
                    p = arg0->unk4 + (arg0->idx1[i] + 0x23);
                    p[3] = (u8) (h >> 8);
                    p[4] = (u8) h;
                    DCFlushRange(p + 3, 2);
                }
            }

            if (arg1[i].unk0->unk14 != 0) {
                if (arg0->idx2[i] != -1) {
                    u32 c;
                    s32 h;
                    s32 w;
                    u32 t;

                    c = arg1[i].unk0->unk14 + 0x80000000;
                    p = arg0->unk4 + (arg0->idx2[i] + 0x19);
                    p[2] = (u8) (c >> 0x15U);
                    p[3] = (u8) (c >> 0xDU);
                    p[4] = (u8) (c >> 5U);
                    DCFlushRange(p + 2, 3);
                    p = arg0->unk4 + (arg0->idx2[i] + 5);
                    p[3] = alpha;
                    p[4] = zero;
                    DCFlushRange(p + 3, 2);
                    w = (u16) (1 << arg1[i].unk0->unk6) - 1;
                    h = (u16) (1 << arg1[i].unk0->unk7) - 1;
                    t = (w | (h << 0xA)) | 0xE00000;
                    p = arg0->unk4 + (arg0->idx1[i] + 0xA);
                    p[2] = (u8) (t >> 0x10U);
                    p[3] = (u8) (t >> 8U);
                    p[4] = (u8) t;
                    DCFlushRange(p + 2, 3);
                }
            }
        }
    }
    DCFlushRange(arg0->unk4, arg0->unk0);
}
// 2026-10-22: 75.9% (was 72.8%): `w` computed before `h` at both 1<<unk6/unk7 sites.
