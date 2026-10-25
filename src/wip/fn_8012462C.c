// PARKED 2026-09-15 (m): NOT A FUNCTION BOUNDARY — needs a split first.
//
// 0x8012462C is owned by no report.json unit; it sits strictly inside
// fn_80124478 (1820B).  `_want_sizes().get(addr)` therefore misses and
// test_one falls back to want=len(got): the draft is compared against a *slice of
// the neighbour*, so a body can score 100 as a prefix of another function while a
// promotion has no symbol to attach to (check_markers blocks).  This is a
// harness/split problem, not a matching one — do not re-pick (WIP.md (m)).
// WIP DRAFT (UNTESTABLE) — ; no boundary in report.json; function embedded in auto-generated asm range — needs split/config first
// Status: UNTESTABLE — no boundary in report.json; function embedded in auto-generated asm range — needs split/config first
// FRAGMENT: address lies inside fn_80124478 (0x71cB) — not an independent function; no range marker.
#include "types.h"
extern void fn_80121D80(s32,s32,s32,s32,s32,s32);
extern void fn_80121798(s32,s32,s32,s32,s32,s32);
extern void fn_80121CD0(s32,s32,s32,s32,s32,s32);
extern void fn_8012227C(s32,s32,s32,s32,s32,s32);
extern void fn_80121900(s32,s32,s32,s32,s32,s32);
s32 fn_8012462C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    // 40B function, 50 instructions
    fn_80121D80(arg0, arg1, arg2, arg3, arg4, arg5);
    fn_80121798(arg0, arg1, arg2, arg3, arg4, arg5);
    fn_80121CD0(arg0, arg1, arg2, arg3, arg4, arg5);
    fn_8012227C(arg0, arg1, arg2, arg3, arg4, arg5);
    fn_80121900(arg0, arg1, arg2, arg3, arg4, arg5);
    return 0;}
