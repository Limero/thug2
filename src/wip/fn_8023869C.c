// BATCH-68 PARK (72.4%, 16 words): collision-node insert helper. Residual:
// retail schedules addi r5,r1,0x10 BEFORE sth r9,4(r29), and re-loads
// p[1] (lbz) before p+4 (lhz); ngccc order differs + r27 shifted to r26 in
// the arg chain. Swapped source load order regresses to 69%. Doc-15 coin.
// PARKED: mwcc scheduling (42/58). Frame/sp10 alignment fixed via 8-aligned
// struct (sp10 at 0x10); remaining 16 diffs are pure instruction scheduling:
// mwcc hoists &sp10 (addi r5,r1,0x10) and the arg1[1] lbz/extsb into the
// 6-byte copy load group, and interleaves cmpwi arg2/li r7 before the branch;
// GCC schedules the copy atomically and emits lbz r5,1(r31)+extsb late.
// Call graph (fn_8023821C 3-arg, fn_802384F8 6-arg with (s8)arg1[1]/sp10^1,
// fn_802361E8, fn_802394F8, fn_8023862C) verified against the DOL.
//
// UPDATED 2026-09-20 — DRIFT REPAIR. The working-tree body had been replaced
// by a later commit with a 10.3% (6/58) variant (typed prototypes, missing
// 8-aligned sp10), while this note still described 72.4%. The 72.4% body was
// recovered from git history (`git show 734a97b7e:thug2/src/wip/fn_8023869C.c`)
// and is what is in this file now; re-verified at 42/58 = 72.4% against the
// current headers. Two lessons:
//   (a) bodies in this pool can regress across commits while their notes stay
//       put — before parking, cross-check the file's own claimed % against
//       tools/score_addrs.py, and search git history if it is lower;
//   (b) the two prototype styles are NOT equivalent here: with `void *`
//       everything + `s32 arg0` the body scores 72.4%, while the typed form
//       (`Unk_C8FEE62D *arg0`, `Unk_5D1D68CC *`, `Unk_673C6403 *`) with the
//       SAME statements scores 43.1% (25/58). tools/lead_arg_scan.py suggested
//       a 4-arg `fn_8023821C(..., arg1, ...)` on top of the typed form
//       (43.1%) but that same 4-arg change on the recovered body drops it to
//       22.0% (13/59) — the 3-arg shape is correct.
// family=m2c range=0x8023869C-0x80238784 size=232B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "structs.h"
s32 fn_8023821C(void *, void *, void *);
s32 fn_802384F8(void *, void *, s32, s32, s32, s32);
s32 fn_802361E8(void *, void *, s32);
void fn_802394F8(void *, s32, s32);
void fn_8023862C(void *);

s32 fn_8023869C(s32 arg0, Unk_8C3FE072 *arg1, s32 arg2) {
    s32 sp8;
    struct { s32 a; u16 b; } __attribute__((aligned(8))) sp10;
    s32 var_r7;
    s32 temp_r3;
    s32 var_r27 = 0;

    *(s32 *)&sp8 = *(s32 *)arg1;
    ((Unk_638CF717 *)&sp8)->unk0x4 = arg1->unk0x4;
    temp_r3 = fn_8023821C((void *)arg0, &sp8, &sp10.a);
    *(s32 *)&sp8 = *(s32 *)arg1;
    ((Unk_638CF717 *)&sp8)->unk0x4 = arg1->unk0x4;
    var_r7 = 1;
    if (arg2 <= 0) {
        var_r7 = 0;
    }
    if (fn_802384F8((void *)arg0, &sp8, (s8)*((s8 *)&((Unk_ECD1B899 *)arg1)->unk0x1), temp_r3, var_r7, sp10.a ^ 1) != 0) {
        if (fn_802361E8((void *)arg0, arg1, 1) != 0) {
            fn_802394F8((void *)arg0, 0, 0);
            var_r27 = 1;
        } else {
            fn_8023862C((void *)arg0);
            fn_802361E8((void *)arg0, arg1, 0);
        }
    }
    return var_r27;
}
// 2026-10-22: 77.6% (was 72.4%): `fn_802394F8` above `var_r27 = 1`.
