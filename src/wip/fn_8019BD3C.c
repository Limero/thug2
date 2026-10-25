#include "types.h"
#include "qb_constants.h"
#include "structs.h"
// WIP DRAFT (non-matching) — hand-shaped from disasm toward byte-exact
// family=script range=0x8019BD3C-0x8019C090 size=852B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// UPDATED 2026-08-29: WA-split applied (f78c call-spec pattern) — best now
// 80.4% (172/214 masked, tools/diff_near.py).
// PARKED: best masked match 78.9% (848B vs 852B). Semantics + block layout +
// case-tree (u32 dispatch, root 0x5078BC7C, cmpw+cmplw idiom) all match; the
// residual is allocator/scheduler artifacts:
//  1. entry-block scheduling window — the four independent setups
//     [out-home, rodata anchor, mgr load, sp8[1]-value load] group together in
//     GOT where WANT interleaves them with `mr r31,r4` (arg1 home) and spreads
//     store-B to the slot right before bl. Statement-order permutations are
//     normalized by the scheduler (6 tried); -fno-schedule-insns makes the
//     whole function far worse (19%).
//  2. case 0x2523853D tail — WANT materializes the out-copy as
//     `ori r5; mr r28,r30; bl` (copy between arg-setup and bl); GOT sinks the
//     copy after the bl (out's next use is fn_800092B0 at the tail). Comma-in-
//     args placement and opaque-use wedges both reshape webs wrongly.
//  3. one word: WANT `li r4,0` vs GOT `mr r4,r29` on the else arm — GCC
//     propagates the known-zero flag register into the literal arg (blocked
//     with a pinned asm-li for that one site).
// Levers that got here: u32 cmdp pin -> r30 (fixes the arg1/arg2/mgr role
// rotation: arg1=r31 arg2=r30 mgr=r29), mgr-var reuse for the vowel flag
// (register recycling into r29), temp_r30 second r30 pin (non-overlapping
// lives — cc1 allows it) for addi-r30+mr-r28,r30 two-step, "+r" barrier on
// temp_r11 (keeps clrlwi + unfolded addi 0x41), var_r9 r9-pin + ch temp
// (lbz/extsb via r0), nested fn_8012591C call in case5078 else (arg-move
// order), pinned asm-li zero. All ProDG versions identical; C++ frontend no
// change. Do not re-grind without a new idea for expand_call slot assignment.
s32 fn_8017471C(void *, s32);
s32 fn_8014510C(Unk_EE36B018 *);
s32 fn_8012591C(s32, s32);
char* PrintThousands(s32 arg0, char arg1);
void strcpy(void *, void *);
void fn_8019BBE4(void *, void *, s32);
void *fn_800093A4(Unk_9994C3F5 *);
void fn_800092B0(Unk_9994C3F5 *, s32);
void *fn_8019BC64(void *);
void fn_80009218(s32, void *);
extern s32 lbl_802AABA8;
extern s32 lbl_80305EAC;
extern char lbl_802AAB84[];
extern char lbl_802AABB0[];
extern char lbl_802AABB4[];
s32 fn_8019BD3C(CStruct *arg0, CStruct *arg1, u32 arg2) {
s32 fs_t;
    s32 sp8[64];
    s32 sp108[4];
    Unk_4C649A8C *out;
    register s32 mgr __asm__("r29");
    register u32 cmdp __asm__("r30");
    CScript *temp_r3;
    s32 temp_r29;
    register s32 temp_r30 __asm__("r30");
    s32 temp_r31;
    s32 temp_r6;
    register s32 var_r9 __asm__("r9");
    s32 ch;
    s32 temp_r11;

    cmdp = (u32)arg2;
    out = (char *)sp8;
    mgr = lbl_80305EAC;
    sp8[0] = lbl_802AABA8;
    out->unk0x4 = ((Unk_59AB5482 *)&lbl_802AABA8)->unk0x4;
    temp_r3 = (void *)fn_8017471C((void *)mgr, arg1->unk0x8);
    switch (cmdp) {
    case QB_PLAYERNAME:
        sprintf(out, lbl_802AABB0,
                    fn_8014510C(fn_8017471C((void *)mgr, temp_r3->unk0x18)));
        break;
    case QB_HORSEPRERUN:
        if (arg1->unk0x4 > 0) {
            temp_r30 = fn_8012591C(QB_HORSE_STR_SCORETOBEAT, 0);
            temp_r6 = PrintThousands(arg1->unk0x4, ',');
            sprintf(out, lbl_802AAB84, temp_r30, temp_r6);
        } else {
            __asm__("" : "+r"(mgr));
            sprintf(out, fn_8012591C(QB_HORSE_STR_SETSCORE, 0));
        }
        break;
    case QB_HORSEPOSTRUN:
        strcpy(out, (char *)arg1 + 0x210);
        break;
    case QB_PANELSTRING1:
        temp_r29 = (s32)fn_8014510C(fn_8017471C((void *)mgr, 0));
        temp_r30 = (s32)sp108;
        fn_8019BBE4(sp108, arg1, 0);
        temp_r6 = (s32)fn_800093A4(sp108);
        sprintf(out, lbl_802AABB4, temp_r29, temp_r6);
        fn_800092B0(sp108, 2);
        break;
    case QB_PANELSTRING2:
        temp_r29 = (s32)fn_8014510C(fn_8017471C((void *)mgr, 1));
        temp_r30 = (s32)sp108;
        fn_8019BBE4(sp108, arg1, 1);
        temp_r6 = (s32)fn_800093A4(sp108);
        sprintf(out, lbl_802AABB4, temp_r29, temp_r6);
        fn_800092B0(sp108, 2);
        break;
    case QB_YOUAREA:
        mgr = 0;
        ch = *(u8 *)fn_8019BC64(arg1);
        var_r9 = (s8)ch;
        temp_r11 = var_r9 - 0x61;
        __asm__("" : "+r"(temp_r11));
        if ((u8)temp_r11 <= 0x19U) {
            ch = temp_r11 + 0x41;
            var_r9 = (s8)ch;
        }
        if ((var_r9 == 0x41) || (var_r9 == 0x45) || (var_r9 == 0x49) || (var_r9 == 0x4F) ||
            (var_r9 == 0x55)) {
            mgr = 1;
        }
        __asm__("" : "+r"(mgr));
        temp_r30 = (s32)sp108;
        fn_8019BD3C(temp_r30, arg1, QB_PLAYERNAME);
        out = (char *)temp_r30;
        temp_r31 = (s32)fn_800093A4(sp108);
        if (mgr != 0) {
            temp_r6 = fn_8012591C(QB_HORSE_STR_ISAN, 0);
        } else {
            register s32 z __asm__("r4");
            __asm__("li %0,0" : "=r"(z));
            fs_t = fn_8012591C(QB_HORSE_STR_ISA, z);
        }
            temp_r6 = fs_t;
        sprintf(sp8, lbl_802AAB84, temp_r31, temp_r6);
        fn_800092B0(out, 2);
        break;
    case QB_FINALWORD:
        sprintf(out, lbl_802AABB0, fn_8019BC64(arg1));
        break;
    }
    fn_80009218(arg0, sp8);
    return arg0;
}
