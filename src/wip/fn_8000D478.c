// WIP DRAFT (non-matching) — hand-reconstructed from want disassembly.
// family=m2c range=0x8000D478-0x8000D984 size=1292B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// === REWRITE 2026-10-07 (raw m2c dump was 11.8%) ===
// fn_8000D478 is pure INTEGER code (323 insns, 46 calls) — a "load a script/
// sprite sheets by filename" dispatcher.  The raw m2c draft was structurally
// hopeless because m2c modelled the two stack buffers as `s32 sp8; s32 sp88;`
// (4 bytes each): the want frame is 0x1b0 with two real buffers, so every
// r1-relative access, the save area AND the whole register allocation were off.
//
// WANT frame (verified word-by-word): the prologue adjusts the stack by
// 0x1b0, saves the link register and the condition register, saves r24
// onward at 0x190, and spills the link value at 0x1b4 and the CR value at
// 0x18c.
//   locals start at r1+8: sp8[0x80] at r1+8 (sprintf/OSVReport buffer),
//   sp88[0x100] at r1+0x88 (the filename buffer, indexed as `lbzx r29,r9`).
//   Locals end at 0x188, CR save at 0x18c, GPR save r24..r31 at 0x190,
//   LR at 0x1b4.  Epilogue: lwz r0,0x1b4 / lwz r12,0x18c / mtlr r0 /
//   lmw r24,0x190 / mtcrf 8,r12 / addi r1,r1,0x1b0 / blr.
//   MEASURED: sp88 must be **0x100**; 0x104 gives frame 0x1b8 (the prologue and
//   save area are then 8 bytes high).  0xfc and 0x100 both give 0x1b0.
//   The mfcr/mtcrf pair exists because one comparison result lives in **cr4**
//   across calls (CR2..CR4 are non-volatile in the EABI): the C tests
//   `arg2 != 0` twice and `arg4 != 0` twice with calls in between.
//
// arg0 layout (all offsets verified):
//   0x14  void *f14      (first arg of fn_8000EC94)
//   0x18  s32  f18       (flag stored before the early-outs)
//   0x1C  Ent  ent[8]    (stride 0x44: f00 = payload, name[0x40] = string)
//   0x23C s32  f23C      (entry count; (0x23C-0x1C)/0x44 == 8)
//
// Reconstruction notes:
//  * The two stack buffers must be INDEXED through the array, not through a
//    pointer: `sp88[n-4]` gives want's `addi r0,r3,-4` + `lbzx r9,r29,r0`,
//    whereas `p[n-4]` with a pointer makes ngccc fold the offset into a
//    displacement (`lbz r0,-4(r11)`) and the whole check diverges.
//  * The filename check walks the tail backwards: 'e','r','p','.','s','t','p',
//    'i','r','c','s' == "scripts.pre" read forward.  The n-1 character is
//    loaded once into an int and reused as the "keep" value of the switch.
//  * `switch (lbl_802FFE48)` picks the replacement for the last character:
//    3 -> 'f', 5 -> 'd', 6 -> the char at [n-8] (want reuses the extsb'd load
//    in r10), 4 -> the unchanged char, default -> 'e'.
//  * fn_800099AC's return feeds fn_8000CB0C as its first argument — the want
//    leaves r3 untouched between the two bls, so the calls are nested.
//    arg4 selects `lbl_802FFE98->f11C` vs `->f118` and `1` vs `0`.
//  * fn_8011D0AC / fn_800136FC / fn_80010760 / fn_800132A4 take no arguments
//    at the want's call sites.
//
// FIX 2026-10-07: the three `arg4 == 0` arms of
// fn_8000F10C read `lbl_802FFE98->f168` (want `lwz r6, 0x168(r3)` at
// 0xD75C/0xD818/0xD8BC), not `->f118` — a real field-offset bug worth 3
// words.  The final `fn_800099AC(0x1C, lbl_802FFE98->f118, 1)` calls
// genuinely do use 0x118 (want 0xD944), so `Glo` now carries both.
//
// RESIDUAL (68.4% positional, .text size exact at 323 words — sweep NEAR):
//  * every callee-saved register in the first half is one HIGHER than the want
//    (arg0 r28 vs r27, arg1 r27 vs r26, arg4 r26 vs r25) — one extra live
//    value in the prologue that has not been identified yet; the string
//    pointer ends up in r25 instead of the want's r29/r30 pair.
//  * the extra `mr r8,r30` before `cmpwi r3,0xb` (dead copy of the address).
//  * case 6 of the switch folds to `li …,0x69` here (ngccc records the
//    register's value from the `== 'i'` compare and substitutes the constant)
//    while the want reuses r10.
//  * `t = (fn_80125A6C(...) != 0) ? 1 : 0` must stay a ternary; an if/else
//    flips the branch (`beq` first) and loses `li r0,1`.
// Not hand-verified: every branch addend, and the exact expression order of the
// second half (the two `beq cr4` arms share a tail).
//
// PARKED 2026-10-07: the residual is dominated by a single
// callee-saved ROLE ROTATION, not by any expression mismatch.  want homes
// arg0->r27, arg1->r26, arg4->r25, the fn_8001371C result->r28 and the sp88
// walk pointer->r29; got homes them r28/r27/r26/r29/r25 — every middle slot one
// higher, while arg2 (r31) and arg3 (r24), the two ENDS of the r24..r31 save
// set, are identical.  That is exactly `allocno` priority/creation-order driven
// (doc 32 flavour A): the same eight registers are live in both, so no source
// edit that merely removes a value can move it.  Concrete sub-symptoms that all
// follow from the same rotation (do NOT chase them individually):
//   * `mr r8, r30` (got 0xD588) is the hoisted definition of the base register
//     the `sp88[n-1] = t` store lands on; want stores through the walk pointer
//     r29 directly (want 0xD69C `stbx r10, r29, r11`).
//   * the ternary result lives in r11 in got but r0 in want (want 0xD524
//     `li r0,1`); `t` is currently ONE variable shared by the ternary and the
//     filename switch, which extends its live range — splitting it into a
//     separate switch value is the untried lever (it cannot change semantics,
//     only the live range, so it is safe to measure).
//   * case 6 folds to `li r11, 0x69` in got vs want's `stbx r10, r29, r11`
//     reuse: want sign-extends the [n-8] byte (`extsb r10, r9`, want 0xD60C)
//     while got keeps it unsigned, so cc1 rematerialises the known constant.
//     Making just those two comparisons ([n-8] and [n-11], want 0xD640) go
//     through a `s8`-typed load is the other untried lever — but a blanket
//     `s8` array would add extsb to all eleven comparisons, so it needs care.
// Both levers change live ranges only, so measure each against this body.
//
// LEVER TRIED 2026-10-07 (re-entry): lever (a).
// The ternary result and the filename switch's replacement value are now TWO
// variables — `t` stays the ternary (`t = (fn_80125A6C(...) != 0) ? 1 : 0;`,
// `arg0->f18 = t;`, `if (t != 0) return;`) and `sw` carries only the switch.
// Justification: want keeps the ternary in **r0** (`li r0,1` / `li r0,0` /
// `cmpwi r0,0` / `stw r0,0x18(r27)` at want 0xAC..0xBC) while we keep it in
// r11, and one shared pseudo is exactly what ties `t`'s live range to the
// switch, which is the one thing that can move its allocno up the priority
// order.  `sw` is dead until `sw = sp88[n-1]`, so this is semantics-neutral
// and can only change live ranges.
//
// Lever (b), the `extsb` on the [n-8]/[n-11] comparisons, is MEASURED
// NEGATIVE: reading those two elements through an `s8` cast gives 67.8% when
// the case-6 store uses the same cast and 25.2% when only the comparisons do
// (from 70.3%). Routing the array indexing through the `r29` copy instead of
// the array name collapses the body to 22.9%. The tail comparisons stay
// unsigned.
//
// NEW FINDING (this pass) — where the rotation actually shows: want indexes
// the buffer through the SAME register it hands to the four path calls.  want
// 0x11C `lbzx r0, r29, r9` / 0x218 `stbx r10, r29, r11` use r29, and want's
// `mr r3, r29` (0x230/0x364/0x3B8/0x3CC) pass that same r29 — i.e. in want the
// `r29 = r30` copy is the ONE live path web (indexing + every call argument:
// many refs over a very long range), while the original r30 is dead after the
// copy.  We instead split those refs over TWO webs: r30 (the original) serves
// the array indexing and r25 (the copy) serves the calls, so both webs have
// few refs and a shorter range and therefore rank HIGHER in allocno priority
// (GCC 2.95 orders by floor_log2(n_refs)*n_refs/live_length and hands the
// lowest free register out first).  That is the most plausible single cause of
// the whole r25..r29 rotation: the copy web's priority is what decides whether
// r25 goes to arg4 or to the path pointer.  Next round should make the array
// accesses go through the same variable that is passed to the four calls
// (keep the `r30 = sp88; r29 = r30;` pair so want's `mr r29,r30` at 0xFC is
// preserved, but reach the buffer through the copy) and re-measure; do not
// chase the `mr r8,r30` extra word separately — it is the same symptom.
#include "types.h"

extern char lbl_802902D4[];
extern char lbl_802902E0[];
extern char lbl_802902E8[];
extern char lbl_802902FC[];
extern char lbl_80290310[];
extern char lbl_80290324[];
extern char lbl_8029032C[];
extern char lbl_8029033C[];
extern s32 lbl_802FFE48;
extern bool lbl_802FFE58;

/* 0x802FFE98 holds a pointer to the engine context.
   0x118 is used by fn_800099AC, 0x11C by fn_8000F10C/fn_800099AC, and the
   second arm of every fn_8000F10C call reads 0x168 (want 0xD75C/0xD818/
   0xD8BC: `lwz r6, 0x168(r3)`) — NOT 0x118 as the first draft assumed. */
typedef struct Glo {
    u8 pad00[0x118];
    u32 f118;
    u32 f11C;
    u8 pad120[0x48];
    u32 f168;
} Glo;
extern Glo *lbl_802FFE98;

char *strstr(char *s, char *pat);
u32 strlen(char *s);
s32 sprintf(char *buf, char *fmt, ...);
char *strcpy(char *dst, char *src);

void OSVReport(s32 a, s32 b);
s32 fn_80125A6C(s32 a, s32 b);
s32 fn_800136FC(void);
s32 fn_8011D0AC(void);
s32 fn_8001371C(s32 a, s32 b, s32 c);
s32 fn_800132A4(void);
void fn_8001075C(s32 a);
void fn_8001BC9C(s32 a);
s32 fn_8000F10C(s32 a, s32 b, s32 c, s32 d);
void fn_80010760(void);
void fn_80013294(s32 a, s32 b, s32 c, s32 d);
void fn_800132F8(s32 a, s32 b, s32 c, s32 d);
s32 fn_8001475C(s32 a);
void fn_80014764(s32 a, s32 b);
s32 fn_800147E8(s32 a, s32 b);
s32 fn_800146E0(s32 a);
void fn_80014904(s32 a, s32 b, s32 c, s32 d);
void fn_80014898(s32 a);
s32 fn_800099AC(s32 a, s32 b, s32 c);
s32 fn_8000CB0C(s32 a, s32 b, s32 c);
void fn_8000EC94(s32 a, s32 b, s32 c);
extern void fn_8000DAB8(void);

/* entry: f00 = payload, name = the 0x40-byte string built by strcpy */
typedef struct Ent {
    s32 f00;
    char name[0x40];
} Ent;

typedef struct Ctx {
    u8 pad00[0x14];
    void *f14;
    s32 f18;
    Ent ent[8];
    s32 f23C;
} Ctx;

void fn_8000D478(Ctx *arg0, char *arg1, s32 arg2, s32 arg3, s32 arg4) {
    char sp8[0x80];
    char sp88[0x100];
    char *r29;
    char *r30;
    s32 n;
    s32 r28;
    s32 r31;
    s32 t;
    s32 sw;

    if ((arg4 == 0) && (strstr(arg1, lbl_802902D4) != NULL)
        && (strstr(arg1, lbl_802902E0) == NULL)) {
        OSVReport((s32)lbl_802902E8, 0);
        return;
    }
    sprintf(sp8, lbl_802902FC, arg1);
    OSVReport((s32)sp8, 0);

    t = (fn_80125A6C((s32)lbl_80290310, 0) != 0) ? 1 : 0;
    arg0->f18 = t;
    if (t != 0) {
        return;
    }

    if (fn_800136FC() == 0) {
        arg2 = 0;
    }
    if (arg2 == 0) {
        if (fn_8011D0AC() != 0) {
            return;
        }
    }

    r30 = sp88;
    r29 = r30;
    sprintf(sp88, lbl_80290324, arg1);
    n = strlen(sp88);
    if (n > 0xb) {
        if ((sp88[n - 1] == 'e') && (sp88[n - 2] == 'r') && (sp88[n - 3] == 'p')
            && (sp88[n - 4] == '.') && (sp88[n - 5] == 's') && (sp88[n - 6] == 't')
            && (sp88[n - 7] == 'p') && (sp88[n - 8] == 'i') && (sp88[n - 9] == 'r')
            && (sp88[n - 10] == 'c') && (sp88[n - 11] == 's')) {
            sw = sp88[n - 1];
            switch (lbl_802FFE48) {
            case 3:
                sw = 'f';
                break;
            case 5:
                sw = 'd';
                break;
            case 6:
                sw = sp88[n - 8];
                break;
            case 4:
                break;
            default:
                sw = 'e';
                break;
            }
            sp88[n - 1] = sw;
        }
    }

    if (arg2 != 0) {
        r28 = fn_8001371C((s32)r29, arg2 ^ 1, 0x64);
        if (r28 != 0) {
            strcpy(arg0->ent[arg0->f23C].name, arg1);
            arg0->ent[arg0->f23C].f00 = r28;
            arg0->f23C++;
            r30 = (char *)fn_800132A4();
            sprintf(sp8, lbl_8029032C, r30);
            OSVReport((s32)sp8, 0);
            fn_8001075C((s32)r29);
            fn_8001BC9C(2);
            if (arg4 != 0) {
                r31 = fn_8000F10C((s32)lbl_802FFE98, (s32)r30, 1, (s32)lbl_802FFE98->f11C);
            } else {
                r31 = fn_8000F10C((s32)lbl_802FFE98, (s32)r30, 1, (s32)lbl_802FFE98->f168);
            }
            fn_8001BC9C(3);
            fn_80010760();
            fn_80013294(r28, (s32)fn_8000DAB8, (s32)arg0, r31);
            fn_800132F8(r28, r31, 1, (s32)r30);
            return;
        }
    }

    r30 = (char *)fn_8001475C((s32)r29);
    if (r30 != 0) {
        sprintf(sp8, lbl_8029032C, r30);
        OSVReport((s32)sp8, 0);
        fn_8001075C((s32)r29);
        fn_8001BC9C(2);
        if (arg4 != 0) {
            r31 = fn_8000F10C((s32)lbl_802FFE98, (s32)r30, 1, (s32)lbl_802FFE98->f11C);
        } else {
            r31 = fn_8000F10C((s32)lbl_802FFE98, (s32)r30, 1, (s32)lbl_802FFE98->f168);
        }
        fn_8001BC9C(3);
        fn_80010760();
        fn_80014764((s32)r29, r31);
    } else {
        r28 = fn_800147E8((s32)r29, (s32)lbl_8029033C);
        if (r28 == 0) {
            if (arg3 != 0) {
                return;
            }
            if (lbl_802FFE58 != 0) {
                return;
            }
        }
        r30 = (char *)fn_800146E0(r28);
        fn_8001075C((s32)r29);
        fn_8001BC9C(2);
        if (arg4 != 0) {
            r31 = fn_8000F10C((s32)lbl_802FFE98, (s32)r30, 1, (s32)lbl_802FFE98->f11C);
        } else {
            r31 = fn_8000F10C((s32)lbl_802FFE98, (s32)r30, 1, (s32)lbl_802FFE98->f168);
        }
        fn_8001BC9C(3);
        fn_80010760();
        fn_80014904(r31, 1, (s32)r30, r28);
        fn_80014898(r28);
    }

    if (arg4 != 0) {
        fn_8000EC94((s32)arg0->f14, (s32)arg1,
                    fn_8000CB0C(fn_800099AC(0x1C, (s32)lbl_802FFE98->f11C, 1), r31, arg4));
    } else {
        fn_8000EC94((s32)arg0->f14, (s32)arg1,
                    fn_8000CB0C(fn_800099AC(0x1C, (s32)lbl_802FFE98->f118, 1), r31, 0));
    }
}
