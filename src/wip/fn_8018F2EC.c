// WIP DRAFT (non-matching) — redesigned from disassembly 2026-09-17.
// family=m2c range=0x8018F2EC-0x8018F428 size=316B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-09-17 at 27.8% (same score as the old draft, but the decode is
// now correct).  Trick-list refresh: reads the QB "should_remove_trick" flag,
// scans the 0xC-entry trick table via s_find_trick_in_mapping, and on a name match fills
// an entry (fn_801A7EB4 + two 0xF60C9090 "Unassigned" slots) and broadcasts
// the removal to the two key-combo scripts.
//
// Decode corrections made this pass (all score-neutral — the residual is
// pure STACK LAYOUT, see below):
// 1. The old draft had `static s32 spC;` — m2c turned a stack slot into a
//    file-scope static.  In want spC is a stack local at r1+0xc.
// 2. The scan is a plain `for (i = 0; i <= 0xB; i++)` with an early
//    `continue` when spC != sp2C — want's rotated form is
//    [i++][cmpwi 0xb][body] with the `bne` targeting the increment block,
//    which is what the for + continue spelling emits.  The old goto-CFG
//    spelling put the increment inside the else arm.
// 3. `fn_801A5D88` really returns the ctx used by every later call, and
//    `fn_801A54DC(ctx, i, &entry, 1)` takes 4 args.
//
// THE RESIDUAL — stack frame.  want is `stwu -0x48` with stmw r27 at 0x34
// and the three scratch groups at r1+8 (8B: sp8/spC), r1+0x18 (12B:
// sp18/sp1C/sp20) and r1+0x28 (8B: sp28/sp2C) — i.e. 16-byte spacing with
// gaps at 0x10..0x18 and 0x24..0x28.  Flat `s32` locals (any declaration
// order) pack them contiguously and give a 0x30 frame; declaring the three
// groups as `P8/P12/P8` structs gets the frame to 0x40-0x48 but moves every
// base (5.0%).  What is needed is the declaration shape that makes ngccc
// allocate three SEPARATE 16-byte-spaced scratch objects.  Not yet found;
// the m2c offsets (sp8/spC, sp18/sp1C/sp20, sp28/sp2C) are correct and
// should be preserved when re-probing.
#include "qb_constants.h"
#include "structs.h"
s32 fn_801A5D88(Unk_C7387A53 *);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 ContainsFlag(CStruct *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 s_find_trick_in_mapping(s32 *, s32, s32);
s32 fn_801A7EB4(s32 *);
s32 fn_801A54DC(s32, s32, s32 *, s32);
s32 AddInteger(CStruct *, s32, s32);
s32 fn_801A531C(s32, s32);
s32 fn_801270B4(CStruct *, s32);
extern char lbl_80305EFC[];
void fn_8018F2EC(Unk_C7387A53 *arg0) {
    s32 sp2C;
    s32 sp28;
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    s32 spC;
    s32 sp8;
    s32 temp_r27;
    s32 i;

    temp_r27 = fn_801A5D88(*(s32 *) &lbl_80305EFC);
    GetInteger(arg0->unk0x20, QB_SHOULD_REMOVE_TRICK, &sp28, 1);
    if (sp28 == 1) {
        if (ContainsFlag(arg0->unk0x20, QB_CREATE_A_TRICK) != 0) {
            sp2C = 0;
        } else {
            GetChecksum_2(arg0->unk0x20, QB_TRICK_NAME, &sp2C, 1);
        }
        for (i = 0; i <= 0xB; i++) {
            s_find_trick_in_mapping(&sp8, temp_r27, i);
            if (spC != sp2C) {
                continue;
            }
            fn_801A7EB4(&sp18);
            sp20 = QB_UNASSIGNED;
            sp1C = QB_UNASSIGNED;
            fn_801A54DC(temp_r27, i, &sp18, 1);
            AddInteger(arg0->unk0x20, QB_SHOULD_REMOVE_TRICK, 0);
        }
        fn_801A531C(temp_r27, -1);
    }
    fn_801270B4(arg0->unk0x20, QB_KEY_COMBOS);
    fn_801270B4(arg0->unk0x20, QB_KEY_COMBO_STRING);
}
// RE-TRIAGE 2026-10-12: parked 27.8% stands; needs decode work, out of round scope; no body change.
