// WIP DRAFT (non-matching) — hand rebuild.
// family=m2c range=0x800DF164-0x800DF24C size=232B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Scans the element array at obj+0x30 (stride 0x68, count word at obj+0xD30)
// from the last element down; for every element whose byte flag at +0x64 is
// set, it looks forward for a later element carrying the same +0x60 key and,
// only when none exists, reports it through fn_800DF24C(arg0, arg1, key, 0, 0).
// The key is read as `e->key` at every use (never cached in a local): that is
// what keeps it in one register while the call site reloads it. The forward
// bound and the `i == count` test both re-read the count word rather than
// using a local — the original reloads it at both sites.
//
// PARKED 2026-10-20: 96.55% (56/58 words), object size exact.
//
// Shape notes that are load-bearing (keep them):
//  * The outer walk is a countdown guard plus an endless body whose bottom
//    test is `j == -1`. Writing it as `for (j = n - 1; j != -1; j--)` makes
//    ngccc fold the entry test onto the count in a *different* register and
//    emit the decrement before the compare (55/58 words). The guard-then-body
//    form below is the only one that puts the count and the index in the same
//    register, which is what the original does.
//  * `while (j-- != 0)` is not usable: ngccc copies the old count into a
//    scratch first (`mr r0, ...`) and every later word shifts.
//
// RESIDUAL: 2 words at the loop head — the original emits the decrement
// between the count compare and the taken branch (compare, decrement, branch),
// ngccc emits the branch first (compare, branch, decrement). Both orderings
// read the same register; every source spelling that changes it also changes
// the register assignment or duplicates the entry test. -fno-schedule-insns2
// and -fno-delayed-branch are byte-neutral here, -fno-expensive-optimizations
// is worse (91.4%), -fno-schedule-insns collapses the body (75.9%).
#include "types.h"
#include "structs.h"

void fn_800DF24C(Unk_C7387A53 *, void *, s32, s32, s32);

/* One element: +0x60 key (word), +0x64 flag (byte), stride 0x68. */
typedef struct DF164Ent {
    char pad0x0[0x60];
    s32 key;
    u8 flag;
} DF164Ent;

void fn_800DF164(Unk_C7387A53 *arg0, void *arg1, char *obj) {
    DF164Ent *e;
    s32 i;
    s32 j;

    j = *(s32 *)(obj + 0xD30);
    if (j != 0) {
        j -= 1;
        for (;;) {
            e = (DF164Ent *)(obj + 0x30 + j * 0x68);
            if (e->flag != 0) {
                for (i = j + 1; i < *(s32 *)(obj + 0xD30); i++) {
                    if (e->flag == 0) {
                        continue;
                    }
                    if (e->key == ((DF164Ent *)(obj + 0x30 + i * 0x68))->key) {
                        break;
                    }
                }
                if (i == *(s32 *)(obj + 0xD30)) {
                    fn_800DF24C(arg0, arg1, e->key, 0, 0);
                }
            }
            j -= 1;
            if (j == -1) {
                break;
            }
        }
    }
}
