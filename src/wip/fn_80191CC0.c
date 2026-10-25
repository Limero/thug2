// PARKED 2026-10-13: 18.3% -> 93.65% (59/63 words),
// size-exact 252B. Rebuilt from full hand-decode; best version kept.
// LEVERS THAT LANDED (all verified by delta):
//  - frame struct {b1,b2,b3 @+8/+0x88/+0x108, w @+0x188} (old _pad hack out).
//  - fmt args as `extern char lbl_[]` ADDRESSES, not raw hex: raw 0x802A97E4
//    expands lis+ori, label addresses expand lis+addi (matches want).
//    GetString hash stays a raw literal (want uses ori there too).
//  - `register s32 sel __asm__("r30")` pin: unpinned, arg1 takes r30 and sel
//    r31 (whole-function swap); the pin seats arg1->r31, sel->r30.
//  - TWO textual Script_GenerateCRC calls (b1-path + shared crc label):
//    ngccc cross-jump-merges the [bl; mr r30] tails into ONE bl, reproducing
//    want's `addi r3=b1; b shared-bl` (no mr on the b1 path).
//  - third sprintf is 3-arg (buf, fmt, arg1); varargs sprintf proto (crclr),
//    fixed 2-arg fn_80125A08 + 4-arg GetString protos (no crclr in want).
// RESIDUAL (4 words, both pure sched order-ties at the b3 site):
//  - 0xD78/0xD7C: want [mr r5,r31][addi r4,lo], got [addi][mr r5].
//  - 0xD8C/0xD90: want [li r4,0][mr r3,r30], got [mr r3][li r4].
//  All six insns pairwise match; only emission order differs, and the orders
//  are mutually inconsistent with any single expand-order rule (b1/b2 sites
//  want the opposite relative order with the same insn classes), so no
//  source reordering can fix both. TRIED: -fno-schedule-insns2 (88.9%),
//  a1-pin instead of sel-pin (frame break, SHORT), z3 zero-var (neutral),
//  t1+ternary CRC arg (t1 homes r28, frame break).
// family=m2c range=0x80191CC0-0x80191DBC size=252B
// INERT: not registered in splits.txt/configure.py — never compiled.
// Decode notes:
//  - frame 0x1A0, stmw r29: r29=arg0, r31=arg1, r30=sel/ret.
//  - three 0x80-byte buffers at r1+8/+0x88/+0x108, s32 slot at +0x188
//    (frame struct below reproduces exactly; old _pad[0x178] hack dropped).
//  - GetString site (0x801280e0) has NO crclr -> fixed 4-arg.
//  - sprintf sites (0x80269F4C) HAVE crclr -> varargs.
//  - fn_80125A08 sites have NO crclr -> fixed 2-arg.
//  - THIRD sprintf is 3-arg (buf, fmt, arg1): no r6 setup in want; the old
//    draft passed a 4th 0 arg (extra li word). r6 keeps stale arg1.
//  - sel (r30): 0 -> &b1 -> &b2 -> &b3 -> CRC result, single s32 var.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802A97E4[];
extern char lbl_802A9880[];
extern char lbl_802A988C[];
s32 fn_80191FD4(void *);
s32 GetString(s32, s32, s32 *, s32);
s32 sprintf(s32, s32, ...);
s32 fn_80125A08(s32, s32);
s32 fn_80190974(void *);
s32 Script_GenerateCRC(s32);
s32 fn_80191CC0(void *arg0, s32 arg1) {
    register s32 sel __asm__("r30") = 0;
    struct { char b1[0x80]; char b2[0x80]; char b3[0x80]; s32 w; } fr;

    GetString(fn_80191FD4(arg0), 0xBFECC45B, &fr.w, 1);
    sprintf((s32)&fr.b1, (s32)lbl_802A97E4, fr.w, arg1);
    if (fn_80125A08((s32)&fr.b1, 0) != 0) {
        sel = Script_GenerateCRC((s32)&fr.b1);
        goto end;
    }
    if (arg1 == 0) {
        goto end;
    }
    sel = (s32)&fr.b2;
    sprintf((s32)&fr.b2, (s32)lbl_802A9880, fn_80190974(arg0), arg1);
    if (fn_80125A08((s32)&fr.b2, 0) != 0) {
        goto crc;
    }
    sel = (s32)&fr.b3;
    sprintf((s32)&fr.b3, (s32)lbl_802A988C, arg1);
    fn_80125A08((s32)&fr.b3, 0);
crc:
    sel = Script_GenerateCRC(sel);
end:
    return sel;
}
