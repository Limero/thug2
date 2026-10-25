// Compare @ 0x8000978C
// PROMOTED 2026-08-31 — Compare (byte-identical, verified 35/35 masked)
// range=0x8000978C-0x80009818 size=140B (leaf). Registered + DOL byte-identical.
// Suggested rename: Fn_8000978C_Stricmp
//
// MATCHED 2026-08-31 (was parked at 82.4%): case-insensitive ASCII string
// compare (stricmp-style: lowercases A-Z, then < / > / == with end-of-string
// handling). The parked draft's null-check section emitted `cmpwi r11,0; beq`
// (then-block placed last); WANT needs the SHORT-CIRCUIT form:
// `if (c1 == 0 && c2c == 0) return 0;` emits `cmpwi r11,0; bne L1; cmpwi
// r0,0; bne L2; li r3,0; blr` with L1 = the c2c != 0 → loop check and L2 =
// the shared return -1 block, exactly WANT's block order (ret-0 inline, then
// c2_check, then ret-1 at the bottom). `if (c1 > c2c) return 1;` and the
// c2_check's `return 1` crossjump into one shared ret-1 block (0x9808).
// Suggested rename: `stricmp` / `caseInsensitiveCompare` (THUG2 runtime
// string helper; no symbol in this zone).
#include "types.h"
s32 Compare(char *s1, char *s2) {
    s8 c1, c2, c2c;
again:
    c1 = (s8)*s1++;
    c2 = (s8)*s2++;
    if ((u32)(c1 - 0x41) <= 0x19U) c1 += 0x20;
    if ((u32)(c2 - 0x41) <= 0x19U) c2c = c2 + 0x20;
    else c2c = c2;
    if (c1 < c2c) return -1;
    if (c1 > c2c) return 1;
    if (c1 == 0 && c2c == 0) return 0;
    if (c1 == 0) return -1;
    if (c2c != 0) goto again;
    return 1;
}
