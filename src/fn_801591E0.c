// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801591E0-0x8015943C (604B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_802A8030[];
extern char lbl_802A83F8[];
extern s32 lbl_80305EC0;
extern s32 lbl_80305F9C;
s32 fn_80198B10(s32);
s32 fn_8021D454(s32, CStruct *, s32);
s32 fn_8021D4E8(s32, CStruct *, s32);
s32 fn_8021D578(s32, CStruct *);
s32 fn_801403CC(void *);
s32 fn_801813F0(CStruct *);
s32 fn_80219698(CStruct *);
s32 fn_80219638(Unk_C7387A53 *);

// SOLVED 2026-09-28: 94.7% -> 100% (byte-exact, 604B, zero inline asm).
// The 8-word residual was entirely in the entry block, and the cause was the
// PREVIOUS session's own two scaffolding lines, not scheduling:
//   (1) `register struct cmd_s *ps __asm__("r10")` — a hard pin on the &sp8
//       web.  It forced r10 to be live until `mr r27,r10`, which is exactly
//       why ngccc could not use r10 as the EC0 @ha reload register and picked
//       r8 in want.  Dropping the pin lets the allocator pick r10 by itself.
//   (2) `__asm__ volatile("" :: "r"(ps))` — a stale liveness barrier.  It
//       split the reload block and pulled the `mr r27,r10` home copy to the
//       TOP of the tail, ahead of `stw r9,0x20(r1)`, instead of after the
//       EC0/F9C `lis` pair as want has it (L5).
// Neither alone is enough — BOTH are required:
//   remove pin only        -> 94.0%   (barrier still hoists the mr)
//   remove barrier only    -> 94.7%   (pin still steals r10 for the EC0 anchor)
//   remove BOTH            -> 100.0%  <-- this file
// Dead ends recorded so they are not retried: promoting the call argument
// into a named local (`temp_ec0 = lbl_80305EC0;`) reaches the same 100% but
// adds nothing; the tail's 6-statement order is fully canonicalised by sched1
// (6 different hand orderings produced byte-identical objects, with and
// without the old barrier); reordering the head's `ps->unk4 = 0` is a no-op;
// M8.31 return-type flips are unsafe here (all 8 call sites are already
// byte-exact, and fn_8021D578/fn_80219698/fn_80219638 are all provably
// s32-returning from their own prologues).  ARITY audit: all 9 callee
// prototypes verified against their prologues — 80198B10/801403CC/801813F0/
// 80219698/80219638 read r3, 8021D454/8021D4E8 read r3+r4, 8021D578 reads
// r3+r4, memset correctly left unprototyped (want keeps `crclr cr1eq`).
// No .rodata is emitted; the only unresolved reloc is `memset` (R_PPC_REL24),
// resolved by the CRT at link.
bool ScriptOnlyOneSkaterLeft(void) {
    struct cmd_s {
        s32 unk0;
        s32 unk4;
        s32 unk8;
        s32 unkC;
    } sp8;
    struct cmd_s sp18;
    s32 sp28[4];
    struct cmd_s *ps;
    struct cmd_s *ps18;
    register struct cmd_s *pin_p8 __asm__("r27");
    register struct cmd_s *pin_p18 __asm__("r25");

    s32 temp_r0;
    s32 temp_r30;
    s32 temp_a8030;
    s32 temp_ec0;
    s32 temp_r3;
    s32 var_r28;
    s32 var_r29;
    CScript *var_r31;
    s32 *var_p;
    s32 var_ctr;

    ps = &sp8;
    ps->unk8 = (s32)lbl_802A83F8;
    temp_a8030 = (s32)lbl_802A8030;
    ps->unk4 = 0;
    sp18.unk8 = temp_a8030;
    ps18 = &sp18;
    ps18->unk4 = 0;
    pin_p8 = ps;
    pin_p18 = ps18;
    temp_r30 = lbl_80305F9C;
    var_r28 = 0;
    if (fn_80198B10(lbl_80305EC0) != 0) {
        memset(sp28, 0, 0x10);
        var_r31 = (void *)fn_8021D454(temp_r30, pin_p8, 0);
        if (var_r31 != NULL) {
            do {
                sp28[var_r31->unk0x34] +=
                    fn_801813F0(fn_801403CC(var_r31->unk0x18));
                var_r31 = (void *)fn_8021D4E8(temp_r30, &sp8, 0);
            } while (var_r31 != NULL);
        }
        var_p = sp28;
        var_ctr = 4;
        do {
            temp_r0 = *var_p;
            var_p += 1;
            if (temp_r0 > 0) {
                var_r28 += 1;
            }
            var_ctr -= 1;
        } while (var_ctr != 0);
        if (fn_8021D578(temp_r30, pin_p18) != 0) {
            pin_p8->unk8 = (s32)lbl_802A83F8;
            sp18.unk8 = (s32)lbl_802A8030;
            return false;
        }
    } else {
        var_r29 = 0;
        var_r31 = (void *)fn_8021D454(temp_r30, pin_p8, 0);
        if (var_r31 != NULL) {
            do {
                if (var_r31->unk0x18 != 0) {
                    temp_r3 = fn_801403CC(var_r31->unk0x18);
                    var_r29 += 1;
                    if (fn_801813F0(temp_r3) > 0) {
                        var_r28 += 1;
                    }
                }
                var_r31 = (void *)fn_8021D4E8(temp_r30, &sp8, 0);
            } while (var_r31 != NULL);
        }
        if (fn_8021D578(temp_r30, pin_p18) != 0) {
            pin_p8->unk8 = (s32)lbl_802A83F8;
            sp18.unk8 = (s32)lbl_802A8030;
            return false;
        }
        if (var_r29 == 1) {
            pin_p8->unk8 = (s32)lbl_802A83F8;
            sp18.unk8 = (s32)lbl_802A8030;
            return false;
        }
    }
    /* block_19 */
    if ((fn_80219698(temp_r30) != 0)
        && ((fn_80219638(temp_r30) == 1) || (fn_80219638(temp_r30) == 2))
        && (var_r28 == 0)) {
        pin_p8->unk8 = (s32)lbl_802A83F8;
        sp18.unk8 = (s32)lbl_802A8030;
        return true;
    }
    pin_p8->unk8 = (s32)lbl_802A83F8;
    sp18.unk8 = (s32)lbl_802A8030;
    return (var_r28 ^ 1) == 0;
}
