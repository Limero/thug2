// PARKED 2026-09-15 (m): NOT A FUNCTION BOUNDARY — needs a split first.
//
// 0x80124E74 is owned by no report.json unit; it sits strictly inside
// fn_80124E70 (84B).  `_want_sizes().get(addr)` therefore misses and
// test_one falls back to want=len(got): the draft is compared against a *slice of
// the neighbour*, so a body can score 100 as a prefix of another function while a
// promotion has no symbol to attach to (check_markers blocks).  This is a
// harness/split problem, not a matching one — do not re-pick (WIP.md (m)).
// WIP DRAFT (UNTESTABLE) — ; no boundary in report.json; function embedded in auto-generated asm range — needs split/config first
// Status: UNTESTABLE — no boundary in report.json; function embedded in auto-generated asm range — needs split/config first
// FRAGMENT: address lies inside fn_80124E70 (0x54B) — not an independent function; no range marker.
// VOID-ARITY FIX 2026-09-11 (tools/fix_void_calls.py): callee is `(void)` in src/ -- phantom argument removed; 0.0% -> 2.6%.
#include "types.h"
extern void fn_80124F00(s32,s32,s32,s32,s32,s32);
extern void fn_800144D4(void);
extern void fn_80124F00(s32,s32,s32,s32,s32,s32);
extern void fn_800144E0(s32,s32,s32,s32,s32,s32);
extern void Tmr_GetTime(s32,s32,s32,s32,s32,s32);
s32 fn_80124E74(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    // 40B function, 50 instructions
    fn_80124F00(arg0, arg1, arg2, arg3, arg4, arg5);
    fn_800144D4();
    fn_80124F00(arg0, arg1, arg2, arg3, arg4, arg5);
    fn_800144E0(arg0, arg1, arg2, arg3, arg4, arg5);
    Tmr_GetTime(arg0, arg1, arg2, arg3, arg4, arg5);
    return 0;}
