// PARKED 2026-10-05. Semantically correct rebuild of the QB
// "create_a_trick" command; the m2c draft it replaces was structurally wrong
// (wrong frame, every chained call flattened, dead `if (0)` arms) and scored
// 3.5% DIFF.
//
// family=m2c range=0x8018EF54-0x8018F2EC size=920B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// BEST MEASURED STATE: 904B vs want 920B — exactly 4 words SHORT, and those 4
// words are the condition-register save/restore. Shift the got by +8B and the
// whole body lines up except register choices, so the semantics are right; the
// honest verdict is still DIFF because of the 4-word shortfall.
//
// THE ONE MISSING THING: the want opens `mfcr r12 ; stw r12,0x30(r1)` and closes
// `lwz r12,0x30(r1) ; mtcrf 8,r12` — ProDG allocated a NON-cr0 condition
// register and had to preserve it across calls. The tell is `cmpwi cr4,r31,0` at
// 0x8018EFE0 and `bne cr4` / `beq cr4` after the calls to 0x801a53c0 /
// 0x801a531c: ngccc reads the CR those calls left behind instead of emitting
// `cmpwi r3,0`. cralloc hands out cr0,cr1,... in allocation order, so landing on
// cr4 means the ORIGINAL source had ~3 more comparison expressions than this
// reconstruction — the dead `if (0)` / `if (0 && ...)` statements m2c left in
// the old draft are probably exactly those. Reconstructing them (or otherwise
// pushing the 5th live comparison onto cr4) is the remaining lever; it is a
// source-CONTENT question, not a shape or type question.
//
// SEMANTICS. QB "create_a_trick" script command. It resolves the trick name /
// premade-cat index (`sp20`) and the trick category (`sp18`), publishes the
// trick_string into the script's array, then resolves `var_r29` = the goal's
// special-trick structure for that category (0 unless the category is one of
// CAT/AIR/LIP/GRIND/MANUAL). It then linearly scans the premade-cat table
// looking for the entry whose name checksum equals `sp20`; on a hit it keeps
// that entry's index in `var_r26` and sets `found`. On a miss it either
// synthesises a temporary structure and runs QB_LOAD_PREMADE_CAT on it, or
// (when the map owns the entry) removes the entry and flags
// QB_SHOULD_REMOVE_TRICK. Finally it rebuilds QB_KEY_COMBOS and returns
// `!found`.
//
// REBUILD. The m2c draft was structurally wrong in five ways, all of
// which cost more than the load-width details:
//  * every `0;` / `if (0)` / `if (0 && ...)` statement is an m2c artefact for
//    an unresolved CR compare. The want tests the *return values*:
//    `bl 0x801a53c0 ; bne cr4` (find succeeded) and
//    `bl 0x801a531c ; beq cr4` (map insert failed). Dropping them restores the
//    two live arms of each if.
//  * the switch on `sp18` must SKIP the `GetStructure` call in the default
//    arm (`b 0x8018f124` goes past `bl 0x80125954`), which m2c's
//    unconditional `var_r29 = GetStructure(var_r3, 1)` cannot express. Use an
//    explicit `id` temp plus `if (id != 0)`; GCC then constant-propagates the
//    guard away and cross-jumps the five arms onto one call site.
//  * `fn_80128F94()` is called with NO argument (m2c passed `arg0`).
//  * the `sp8/spC/sp10` triple is one 16-byte object at r1+8 (fields +0/+4/+8,
//    plus a pad word), and `&sp8` is passed to `s_find_trick_in_mapping`,
//    `fn_801A7EB4` and `fn_801A54DC`. Declaring three separate `s32`s puts them
//    at the wrong offsets and gives the wrong `addi r3,r1,N`.
//  * the search loop is `for (i = 0; i < n; i++) { if (find(...) && c == s)
//    {...; break;} fn_8012720C(var_r29, sp10); }` — the call belongs to the
//    *not-found* fall-through, and the `addi i,i,1` sits in the same block as
//    the call (the want's loop-increment block at 0x8018F14C).
#include "types.h"

extern char lbl_80305EFC[];

typedef struct {
    s32 f0;    /* 0x0 */
    s32 f4;    /* 0x4 */
    s32 f8;    /* 0x8 */
    s32 pad;   /* 0xC */
} Unk_8018EF54Hit;

s32 ContainsFlag(s32, s32);
s32 GetChecksum_2(s32, s32, s32 *, s32);
s32 GetInteger(s32, s32, s32 *, s32);
s32 GetString(s32, s32, s32 *, s32);
s32 GetStructure(s32, s32);
s32 GetStructure_2(s32, s32, s32 *, s32);
s32 AddString(s32, s32, s32);
s32 AddInteger(s32, s32, s32);
s32 AddChecksum(s32, s32, s32);
s32 AddArrayPointer(s32, s32, s32);
s32 Script_RunScript(s32, s32, s32, s32, s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(void);
s32 CStruct_delete(s32, s32);
s32 s_find_trick_in_mapping(Unk_8018EF54Hit *, s32, s32);
s32 fn_801259C8(s32, s32);
s32 fn_80129528(s32, s32);
s32 fn_801281BC(s32, s32, s32 *, s32);
s32 fn_8012720C(s32, s32);
s32 fn_80127358(s32, s32);
s32 fn_80128F94(void);
s32 fn_80129068(s32, s32);
s32 fn_801292A8(s32, s32, s32);
s32 fn_801270B4(s32, s32);
s32 fn_8018FC80(s32);
s32 fn_8003E7CC(s32);
s32 fn_801A5D88(s32);
s32 fn_801A5388(void);
s32 fn_801A531C(s32, s32);
s32 fn_801A7EB4(Unk_8018EF54Hit *);
s32 fn_801A54DC(s32, s32, Unk_8018EF54Hit *, s32);

s32 fn_8018EF54(void *arg0) {
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    Unk_8018EF54Hit sp8;
    s32 var_r25;
    s32 var_r26;
    s32 var_r29;
    s32 var_r30;
    s32 var_r3;
    s32 temp_r28;
    s32 temp_r30;
    s32 temp_r31;
    s32 temp_r31_2;

    temp_r31 = ContainsFlag(*(s32 *)((char *)arg0 + 0x20), 0x8E6014F6);
    GetChecksum_2(*(s32 *)((char *)arg0 + 0x20), 0x3D929B66, &sp18, 1);
    if (temp_r31 != 0) {
        GetInteger(*(s32 *)((char *)arg0 + 0x20), 0x0B502200, &sp1C, 1);
        sp20 = sp1C;
    } else {
        GetChecksum_2(*(s32 *)((char *)arg0 + 0x20), 0xEF6FB249, &sp20, 1);
    }
    if (temp_r31 != 0) {
        GetString(fn_80129528(fn_801259C8(0xFFD7913F, 1), sp20), 0xA1DC81F9, &sp24, 1);
        AddString(*(s32 *)((char *)arg0 + 0x20), 0x3A54CC4B, sp24);
    } else {
        GetStructure_2(GetStructure(sp20, 1), 0x7031F10C, &sp28, 1);
        fn_801281BC(sp28, 0xA1DC81F9, &sp2C, 1);
        AddString(*(s32 *)((char *)arg0 + 0x20), 0x3A54CC4B, sp2C);
    }
    var_r3 = 0;
    switch (sp18) {
    case 0x61A1BC57:
    case 0x439F4704:
        var_r3 = 0x4764231D;
        break;
    case 0xA549B57B:
        var_r3 = 0xA1B2D162;
        break;
    case 0x255ED86F:
        var_r3 = 0xF481D0CD;
        break;
    case 0xEF24413B:
        var_r3 = 0xD72D5CF7;
        break;
    }
    var_r29 = 0;
    if (var_r3 != 0) {
        var_r29 = GetStructure(var_r3, 1);
    }
    var_r26 = 0;
    var_r25 = 0;
    var_r30 = 0;
    temp_r31_2 = fn_801A5D88(*(s32 *)&lbl_80305EFC);
    temp_r28 = fn_801A5388();
    for (; var_r30 < temp_r28; var_r30++) {
        if ((s_find_trick_in_mapping(&sp8, temp_r31_2, var_r30) != 0) &&
            (sp8.f4 == sp20)) {
            var_r26 = sp8.f8;
            var_r25 = 1;
            break;
        }
        fn_8012720C(var_r29, sp8.f8);
    }
    if (var_r25 == 0) {
        temp_r30 = *(s32 *)((s32 *)fn_80127358(var_r29, 0) + 0x8);
        var_r26 = temp_r30;
        if (fn_801A531C(temp_r31_2, 1) != 0) {
            s32 temp_r30_2;
            CStruct_new(8);
            temp_r30_2 = CStruct_ctor();

            AddChecksum(temp_r30_2, 0xA92A2280, var_r26);
            AddInteger(temp_r30_2, 0x7F8C98FE, sp20);
            AddInteger(temp_r30_2, 0x7F264BE9, temp_r28);
            Script_RunScript(0x466576C8, temp_r30_2, 0, 0, 0);
            if (temp_r30_2 != 0) {
                CStruct_delete(temp_r30_2, 3);
            }
        } else {
            fn_801A7EB4(&sp8);
            sp8.f8 = var_r26;
            sp8.f4 = sp20;
            fn_801A54DC(temp_r31_2, temp_r28, &sp8, 1);
        }
        AddInteger(*(s32 *)((char *)arg0 + 0x20), 0xBC678826, 1);
    }
    fn_801270B4(*(s32 *)((char *)arg0 + 0x20), 0x79704516);
    fn_8003E7CC(0xC);
    temp_r30 = fn_80128F94();
    fn_80129068(1, 0xD);
    fn_801292A8(temp_r30, 0, var_r26);
    AddArrayPointer(*(s32 *)((char *)arg0 + 0x20), 0x79704516, temp_r30);
    fn_8018FC80((s32)arg0);
    return var_r25 ^ 1;
}