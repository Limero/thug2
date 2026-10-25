// PARKED 2026-09-15 (m): NOT A FUNCTION BOUNDARY — needs a split first.
//
// 0x80125B0C is owned by no report.json unit; it sits strictly inside
// Script_AllocatePools (388B).  `_want_sizes().get(addr)` therefore misses and
// test_one falls back to want=len(got): the draft is compared against a *slice of
// the neighbour*, so a body can score 100 as a prefix of another function while a
// promotion has no symbol to attach to (check_markers blocks).  This is a
// harness/split problem, not a matching one — do not re-pick (WIP.md (m)).
// WIP DRAFT (UNTESTABLE) — ; no boundary in report.json; function embedded in auto-generated asm range — needs split/config first
// Status: UNTESTABLE — no boundary in report.json; function embedded in auto-generated asm range — needs split/config first
// FRAGMENT: address lies inside Script_AllocatePools (0x184B) — not an independent function; no range marker.
#include "types.h"
#include "structs.h"
extern void fn_8001075C(s32,s32,s32,s32,s32,s32);
extern void AllocateChecksumNameLookupTables(s32,s32,s32,s32,s32,s32);
extern void fn_80010760(s32,s32,s32,s32,s32,s32);
extern void fn_8000F2F8(s32,s32,s32,s32,s32,s32);
extern void fn_8001BC9C(s32,s32,s32,s32,s32,s32);
s32 fn_80125B0C(Unk_9F352E7C *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    // 40B function, 50 instructions
    fn_8001075C(arg0, arg1, arg2, arg3, arg4, arg5);
    AllocateChecksumNameLookupTables(arg0, arg1, arg2, arg3, arg4, arg5);
    fn_80010760(arg0, arg1, arg2, arg3, arg4, arg5);
    fn_8000F2F8(arg0, arg1, arg2, arg3, arg4, arg5);
    fn_8001BC9C(arg0, arg1, arg2, arg3, arg4, arg5);
    return 0;}
