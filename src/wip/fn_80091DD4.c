// family=m2c range=0x80091DD4-0x80091E98 size=196B
// PARKED 2026-10-30: 89.80% (baseline 48.98%). Rebuilt from the
// decoded want: guard/reload of the count global (lbl_803017F4, read through a
// 0x80300000 page anchor that stays live across fn_80091D98), the 0x60-stride
// record walk over 0x803792D8 (+0x58 = data head), the two-s32 sum, and the
// write-index global lbl_803017F0. Object is now LENGTH-EXACT (196B) and 44 of
// 49 instructions are byte-identical; the 3 register pins (base r31, data r5,
// walk r4) plus the walk copy reproduce every shape except one 3-register cycle.
//
// RESIDUAL (5 of 49 words, a clean {base,walk} transposition). The want forms
// its page anchor high half in r9, derives the record base in r4 with a
// negative displacement there, derives the data pointer in r5 0x58 past that
// base, and copies it to r12. The current output forms the same anchor in r9
// but derives the base in r31 with a zero displacement, derives the data
// pointer in r5 0x58 past that, and copies it to r4 instead.
// i.e. want homes base in r4 and the data COPY in r12; we get base r31 / copy r4.
// Every OTHER web already matches: count r10, idx r8, latch r7, remaining r6,
// inner r11, offset r10, sum r8, write-index*4 r3, zero r31, ptr r9, data r5.
//
// WHY THIS IS A WALL (not a missing lever):
//  - cc1 -dr (post-reload RTL) is ALREADY correct in shape: `high:SI` (the
//    anchor) and `lo_sum` (the base address) are SEPARATE pseudos, and
//    data = base + 0x58 derives from the base pseudo, not the anchor. The
//    blocker is purely local_alloc register COLOUR (AGENTS 6fg-2 / doc 73:
//    "if the post-reload RTL already matches and the only diff is which hard
//    reg a pseudo gets, the blocker is local-alloc - park it").
//  - Pinning base to its WANT colour r4 is self-defeating: the pin binds the
//    lo_sum pseudo, then reg_alloc coalesces the high: anchor into the SAME
//    register and emits the degenerate `lis r4 ; addi r4,r4,0` (7 diffs, and
//    the count web is pushed out of r10 as well). Verified with a second name
//    for base and with "+r" / volatile / "=r" opacity barriers on it (7 forms,
//    all 7-12 diffs, none exact).
//  - The only route that DOES produce the un-coalesced `lis r9 ; addi r4,r9,off`
//    is an explicit `lis %0,%1@ha` asm anchor (AGENTS 6br / doc 73) pinned to
//    r9. That gets the base EXACT but costs 8 words: the anchor consumes the
//    HI16 slot the count's page anchor wanted, and the count reload then lands
//    in r0 instead of r10. 13 diffs best case; the count register is itself an
//    unpinnable local_alloc choice (11 registers x pin/opaque/volatile forms,
//    ALL 13 diffs - a pin cannot bind a plain load's reg_alloc pseudo, AGENTS
//    6bg-7).
//  - Closed and inert: declaration order (500 permutations of the 10 local
//    decls, all byte-identical 25 diffs on the unpinned base - local_alloc
//    orders by live-range size, not DECL_UID), 1- and 2-name splits of base and
//    data, 11x11 single-pin sweeps, nested-scope pins, and the asm-anchor
//    position/wording sweep. NOT tried: a >30%-asm whole-window transcription,
//    which is out of scope for this round.
//
// INLINE ASM: 0 emitted instructions (one zero-code `__asm__("" : "+r"(walk))`
// barrier, load-bearing: without it the object is 192B and the `mr r4,r5` copy
// is coalesced away). 3 `register ... __asm__("rN")` declaration attributes.

#include "types.h"
void fn_80091D98(void);
extern char lbl_803792D8[];
extern s32 lbl_803017F0;
extern s32 lbl_803017F4;

void fn_80091DD4(void) {
    s32 *page;
    s32 temp_r0;
    s32 temp_r10;
    s32 var_r3;
    s32 var_r6;
    s32 var_r7;
    s32 var_r8_2;
    s32 var_r10;
    s32 zero;
    u32 var_r11;
    s32 *var_r9;
    register char *base __asm__("r31");
    register char *data __asm__("r5");
    register char *walk __asm__("r4");
    s32 off;

    page = (s32 *)0x80300000;
    if (page[0x5FD] != 0) {
        fn_80091D98();
        temp_r10 = page[0x5FD];
        var_r7 = temp_r10 - 1;
        if (var_r7 >= 0) {
            var_r6 = temp_r10;
            base = lbl_803792D8;
            data = base + 0x58;
            walk = data;
            __asm__("" : "+r"(walk));
            var_r3 = *(s32 *)&lbl_803017F0 * 4;
            zero = 0;
            do {
                var_r10 = var_r7 * 0x60;
                var_r8_2 = 0;
                var_r11 = 0U;
                var_r9 = (s32 *)((char *)var_r10 + (s32)walk);
                do {
                    temp_r0 = var_r9[0];
                    var_r11 += 1;
                    var_r9 += 1;
                    var_r8_2 += temp_r0;
                } while (var_r11 <= 1U);
                if (var_r8_2 == 0) {
                    var_r9 = *(s32 **)(base + var_r10);
                    var_r6 -= 1;
                    *var_r9 = var_r8_2;
                } else {
                    off = var_r3 + var_r10;
                    *(s32 *)((char *)data + off) = zero;
                }
                var_r7 -= 1;
            } while (var_r7 >= 0);
            *(s32 *)&lbl_803017F4 = var_r6;
        }
    }
}
