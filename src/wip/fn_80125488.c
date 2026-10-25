// PARKED 2026-09-15 (m): NOT A FUNCTION BOUNDARY — needs a split first.
//
// 0x80125488 is owned by no report.json unit; it sits strictly inside
// fn_80125480 (100B).  `_want_sizes().get(addr)` therefore misses and
// test_one falls back to want=len(got): the draft is compared against a *slice of
// the neighbour*, so a body can score 100 as a prefix of another function while a
// promotion has no symbol to attach to (check_markers blocks).  This is a
// harness/split problem, not a matching one — do not re-pick (WIP.md (m)).
// WIP DRAFT (UNTESTABLE) — ; no boundary in report.json; function embedded in auto-generated asm range — needs split/config first
// Status: UNTESTABLE — no boundary in report.json; function embedded in auto-generated asm range — needs split/config first
// FRAGMENT: address lies inside fn_80125480 (0x64B) — not an independent function; no range marker.
// MIS-SPLIT 2026-09-03: fragment missing its own prologue —
// starts with `stw r31,0xc(r1)` then `bl fn_8012543C`; the real function
// head is fn_80125480 (symbols.txt, size 0x64 = 100B covering 0x80125480-
// 0x801254E4). The m2c filler body (two same-arg calls + return 0) is
// fabricated. Needs a head-draft of fn_80125480 instead.
#include "types.h"
extern void fn_8012543C(s32,s32,s32,s32,s32,s32);
extern void fn_8012543C(s32,s32,s32,s32,s32,s32);
s32 fn_80125488(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    // 40B function, 50 instructions
    fn_8012543C(arg0, arg1, arg2, arg3, arg4, arg5);
    fn_8012543C(arg0, arg1, arg2, arg3, arg4, arg5);
    return 0;}
