// PARKED 2026-09-15 (m): NOT A FUNCTION BOUNDARY — needs a split first.
//
// 0x801260E0 is owned by no report.json unit; it sits strictly inside
// fn_801260D8 (116B).  `_want_sizes().get(addr)` therefore misses and
// test_one falls back to want=len(got): the draft is compared against a *slice of
// the neighbour*, so a body can score 100 as a prefix of another function while a
// promotion has no symbol to attach to (check_markers blocks).  This is a
// harness/split problem, not a matching one — do not re-pick (WIP.md (m)).
// WIP DRAFT (UNTESTABLE) — ; no boundary in report.json; function embedded in auto-generated asm range — needs split/config first
// Status: UNTESTABLE — no boundary in report.json; function embedded in auto-generated asm range — needs split/config first
// FRAGMENT: address lies inside fn_801260D8 (0x74B) — not an independent function; no range marker.
#include "types.h"
#include "structs.h"
extern void Mem_Alloc2(s32,s32,s32,s32,s32,s32);
extern void fn_80011F94(s32,s32,s32,s32,s32,s32);
extern void Mem_Alloc2(s32,s32,s32,s32,s32,s32);
extern void fn_80011F94(s32,s32,s32,s32,s32,s32);
s32 fn_801260E0(Unk_78674569 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    // 40B function, 50 instructions
    Mem_Alloc2(arg0, arg1, arg2, arg3, arg4, arg5);
    fn_80011F94(arg0, arg1, arg2, arg3, arg4, arg5);
    Mem_Alloc2(arg0, arg1, arg2, arg3, arg4, arg5);
    fn_80011F94(arg0, arg1, arg2, arg3, arg4, arg5);
    return 0;}
