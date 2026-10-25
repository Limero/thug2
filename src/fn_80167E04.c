// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80167E04-0x80167F80 (380B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 lbl_802FFE50;
extern char lbl_802A8730[];
extern char lbl_802A8740[];
extern char lbl_802A874C[];
extern char lbl_802A8758[];
void fn_80127138(CStruct *, void *);
s32 GetArray(CStruct *, s32, s32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_80129528(CStruct *, s32);
s32 GetChecksum_4(CStruct *, void *, void *, s32);
s32 fn_80128A90(CStruct *, void *);
s32 s_first_date_is_more_recent(CStruct *, CStruct *);
void fn_80127C90(CStruct *, void *, CStruct *);
// RESOLVED 2026-10-05 (was "PARKED 97.9%"): the note below described the SECOND
// half of the same wall and is now fixed by the zero-code memory fence below.
// Kept because it names the levers that were already spent, so a future session
// does not re-try them:
//   last 2 diffs were a li/load interleave at the rotated-loop guard — want
//   emits `li r29,0` (i=0) BETWEEN the second bl and the count loads
//   (`lwz r9,8(r1); lwz r0,4(r9); cmplw r30,r0` compares best!), got hoists the
//   sp8 address-load above the li. Resisted: plain/if-do-while/goto forms,
//   assignment-in-condition, comma-chains, "+r" opaque barrier on best (which
//   DID fix cmplw-r30-vs-fold), reg pins i/best, and flags
//   -fno-schedule-insns/-insns2/-sched-spec/-sched-interblock/-gcse (each
//   breaks something else, e.g. prologue mr order).
//   The fix was NOT a barrier on a value but `__asm__ volatile("" ::: "memory")`
//   after the guarded-do-while rewrite — see the header at the top of the file.
bool ScriptGetMostRecentSave(CStruct *arg0, CScript *arg1) {
    void * volatile sp8;
    s32 spC;
    s32 sp10;
    register s32 i __asm__("r29");
    register s32 best __asm__("r30");
    s32 entry;

    fn_80127138(arg1->unk0x18, (s32)lbl_802A8730);
    sp8 = NULL;
    GetArray(arg0, 0, &sp8, 0);
    if (sp8 == NULL) {
        return false;
    }
    spC = 0;
    best = 0;
    __asm__("" : "+r"(best));
    GetChecksum_2(arg0, 0, &spC, 0);
    i = 0;
    __asm__ volatile("" ::: "memory");
    if ((u32)best < *((u32 *)&((CStruct *)sp8)->unk0x4)) {
    do {
        entry = fn_80129528((s32)sp8, i);
        sp10 = 0;
        GetChecksum_4(entry, (s32)lbl_802A8740, &sp10, 0);
        if ((spC == 0 || spC == sp10) &&
            ((fn_80128A90(entry, (s32)lbl_802A874C) == 0 &&
              fn_80128A90(entry, (s32)lbl_802A8758) == 0) ||
             lbl_802FFE50 == 4 || lbl_802FFE50 == 5)) {
            if (best == 0 || s_first_date_is_more_recent(entry, best) != 0) {
                best = entry;
            }
        }
        i += 1;
    } while ((u32)i < *((u32 *)&((CStruct *)sp8)->unk0x4));
    }
    if (best != 0) {
        fn_80127C90(arg1->unk0x18, (s32)lbl_802A8730, best);
        return true;
    }
    return false;
}
