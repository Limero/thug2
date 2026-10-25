// PARKED 2026-10-03 (a17): DIFF 45.2% masked (baseline DIFF 32.1%).
// reproduce: LEAF_TMPDIR=<scratch> tools/venv/bin/python \
//              tools/test_wip_drafts.py --addr 0x8019B84C
//   GOT 540B vs WANT 536B — the body is now *instruction-for-instruction*
//   identical to the original except for TWO register-allocation artifacts;
//   the single extra instruction shifts the whole tail by 4 bytes, which is
//   what keeps the masked score at 45% instead of ~98%.
//   (1) `addi r28, r1, 8` (hoisted `&s.v` into callee-saved r28 at the top of
//       the else-block) + `stmw r28, 0x10(r1)`/`lmw r28` instead of the
//       original's late `addi r6, r1, 8` at the sprintf call site and
//       `stmw r29, 0x14(r1)`.
//   (2) counter ++ address: want `lwzx/stwx r9, r30, r11` (base=r30=arg0+0x410,
//       index=r11=i*4); got `lwzx/stwx r9, r11, r30` — base/index swapped.
//   RULED OUT: plain s16/u16 scalar local (gives lha/srwi or lhz/srwi instead of
//   `lbz 9(r1)`; the byte read at sp+9 requires a *byte lvalue*, i.e. a union
//   member / array element); `s.b` and `u8 s[2]` + `*(s16*)s` array forms
//   (identical codegen, hoist still happens); declaring sprintf/strcpy
//   prototypes (no change); inlining the `cnt` pointer or the `c` load
//   (no change / worse); `(u16)` cast on the mask to force mb=0x10 — needed
//   `unsigned short v` + `(s16)` casts in the shifts, which is what is there.
//   NEXT IDEA: the hoist is regalloc pressure, not C shape — find the original
//   declaration that leaves r28 unused (the original only ever touches
//   r29/r30/r31). Possibly the sprintf 6th arg is not `&<local>` at all but a
//   pointer-typed local whose value happens to be r1+8, or the letter buffer is
//   reached via a `char *` that GCC folds to the frame address at the call.
// WIP DRAFT (non-matching) — C body from tools/fill_wip_drafts.py, hand-fixed by a17
// family=m2c range=0x8019B84C-0x8019BA64 size=536B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// UPDATED 2026-09-15 (e): 18.1% -> 32.1% via the widened
// doc-52 phantom-argument sweep (bare `0x80xxxxxx` literal in ANY
// argument position, not just trailing). tools/drop_phantom_arg.py.
// a17 2026-10-03: rewrote the body from the disassembly:
//   * .data score-globals are at 0x802F5Exx (lis r9,0x802F), not 0x80305Exx
//   * format strings recovered from .rodata: "unknown", "%s %s", "You are a %s!"
//   * sprintf dest is always arg0+0x210 (m2c had passed arg0 / the buf as fmt)
//   * fn_8019BB20/fn_8019C0C0 get real prototypes, strcpy branch targets fixed
//   * the letter block is a 16-bit local at sp+8 written with sth/lhz
#include "qb_constants.h"
#include "structs.h"

s32 fn_8019BD0C(s32, s32);
void fn_8019C0C0(void *);
s32 fn_8019BB20(void *);
char *fn_8012591C(s32, s32);
char *PrintThousands(s32, char);

extern s32 lbl_802F5EC8;
extern s32 lbl_802F5ECC;
extern s32 lbl_802F5ED0;
extern s32 lbl_802F5ED4;
extern s32 lbl_802F5EDC;

void fn_8019B84C(Unk_D4C58817 *arg0) {
    char *buf;
    s32 *cnt;
    s32 score;
    s32 target;
    s32 res;
    union {
        unsigned short v;
        u8 b[2];
    } s;
    u8 c;

    buf = (char *)arg0 + 0x210;
    sprintf(buf, "unknown");
    target = arg0->unk0x8;
    arg0->unk0xC = target;
    score = fn_8019BD0C(arg0, target);
    target = arg0->unk0x4;
    if (score > target) {
        arg0->unk0x4 = score;
        sprintf(buf, "%s %s", fn_8012591C(QB_HORSE_STR_SETSCOREIS, 0),
                PrintThousands(arg0->unk0x4, ','));
        res = lbl_802F5ED0;
    } else if (score < target) {
        cnt = (s32 *)((char *)arg0 + 0x410);
        arg0->unk0x4 = 0;
        *(cnt + arg0->unk0x8) = *(cnt + arg0->unk0x8) + 1;
        fn_8019C0C0(arg0);
        if (fn_8019BB20(arg0) != 0) {
            sprintf(buf, "You are a %s!", (char *)arg0 + 0x10);
            res = lbl_802F5ED4;
        } else {
            c = ((u8 *)arg0)[*(cnt + arg0->unk0x8) + 0xF];
            s.v = s.b[1] | (c << 8);
            if ((u8)(((s16)s.v >> 8) - 'a') <= 25) {
                s.v = (s.v & 0xFF) | ((u8)(((s16)s.v >> 8) - 'a') << 8);
                s.v = (s.v & 0xFF) | ((u8)(((s16)s.v >> 8) + 'A') << 8);
            }
            s.v &= 0xFF00;
            sprintf(buf, "%s %s", fn_8012591C(QB_HORSE_STR_GETSTHELETTER, 0),
                    &s.v);
            res = lbl_802F5EC8;
        }
    } else if (score == 0) {
        strcpy(buf, fn_8012591C(QB_HORSE_STR_NOSCORESET, 0));
        res = lbl_802F5EDC;
    } else {
        strcpy(buf, fn_8012591C(QB_HORSE_STR_YOUTIEDTHETARGETSCORE, 0));
        res = lbl_802F5ECC;
    }
    arg0->unk0x438 = res;
}