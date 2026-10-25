// WIP DRAFT (non-matching) — hand-edited from disasm
// family=m2c range=0x80181300-0x801813F0 size=240B
// PARKED: 58/60 = 96.7%. Only diff: the shared GCSE page anchor for
// lbl_80305EC0 (lis r30) is inserted at slot 0x1C (before the fn_8017471C
// call) in WANT, but ngccc always places it after the `beq` guard (start of
// the use block), swapping it with the `lwz r3, 0x5eac(r9)` EAC load.
// Exhausted: direct refs (GCSE shares anchor but late), char[]-deref form,
// inline-asm "@ha" anchor (right insn, wrong slot), statement-expression
// ordering, dual pinned anchors (r30+r9 — "inconsistent operand constraint"),
// pure-C page constant (code bloat), early-return guard form, volatile casts,
// named eacv/id temps in every permutation (6 statement orders), and flags:
// -fno-schedule-insns / insns2 / both / -fno-sched-spec / -interblock /
// -fno-gcse / -O1 / all ProDG 3.5–3.9.3 (identical). The swap survives even
// -fno-schedule-insns, i.e. it is an RTL/GCSE insertion-point artifact, not a
// scheduling tie-break. Semantically correct otherwise; doc-15 family.
// 2026-08-31 re-triage (still parked, now confirmed structural): the anchor
// swap is exactly `lis r9` (eacv page) before stw + `lis r30` (ec0 page)
// between stw and the eacv lwz. Two-asn dual anchors are IMPOSSIBLE in this
// SN build — a second `"s"`-constraint asm in one function dies in reload
// ("inconsistent operand constraints", with or without the r30 pin); the
// pin+r30-only single-asm form (current draft) is the best expressible
// shape at 58/60. All statement orders of {stw, r30-asm, eacv-load, lha}
// place either the lwz or the r30 lis one slot off; flags neutral.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// 2026-10-21: the @ha-only anchor cannot be replaced by plain C — assigning
// the symbol address to a char pointer emits lis+addi (244B, 13.1%) — so the
// asm anchor stays. Moving the anchor above the EAC load, moving it after the
// argument store, and a memory-clobber barrier between anchor and load all
// reorder the surrounding loads (best 91.7%); the current statement order is
// the only one that keeps the 3-word residual at 95.0%.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
extern char lbl_80305EC0[];
extern char lbl_802A93D0[];
extern char lbl_802A93D8[];

void *fn_8017471C(s32, s16);
s32 fn_80198F7C(s32);
s32 sprintf(s32, ...);
s32 fn_80141FA4(Unk_5FCDF30E *);
void fn_8004CE30(Unk_E80761A5 *, s32);

void fn_80181300(Unk_F515CE8D *arg0, s32 arg1) {
    char sp8[0x40];
    Unk_FFAD6788 *temp_r29;
    s32 eacv;
    s16 id;
    register s32 ec0a __asm__("r30");

    arg0->unk0x10 = arg1;
    eacv = lbl_80305EAC;
    __asm__ volatile("lis %0,%1@ha" : "=r"(ec0a) : "s"(lbl_80305EC0));
    id = arg0->unk0xC;
    temp_r29 = fn_8017471C(eacv, id);
    if (temp_r29->unk0xC8 != 0) {
        if ((fn_80198F7C(((Unk_2BEE97BE *)ec0a)->unk0x5EC0) == QB_NETKING) || (fn_80198F7C(((Unk_2BEE97BE *)ec0a)->unk0x5EC0) == QB_KING)) {
            u32 t = arg0->unk0x10;
            u32 secs = t / 1000U;
            sprintf((s32)&sp8, (s32)lbl_802A93D0, secs / 60U, secs % 60U);
        } else {
            sprintf((s32)&sp8, (s32)lbl_802A93D8, arg0->unk0x10);
        }
        fn_8004CE30((s32)&sp8, fn_80141FA4((s32)temp_r29));
    }
}
