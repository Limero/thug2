// PARKED 2026-09-25: this is a real discrete CRT/linker-runtime function,
// not a merged blob.  __start calls it at 0x800031A4, and fn_800032C0 starts
// exactly at its final return.  The interior return is the shared zero-result path.
// SEMANTIC BEST: recover argc/argv from the loader metadata at 0x800000F4.
// table[0] is argc; table[1..argc] are relocated by adding the metadata base;
// table+1 is rounded down to 32 and written to 0x80000034; argc and argv are
// returned in the two result registers and later passed to fn_80145C14 by __start.
// BLOCKER: retail uses a frameless custom two-register return and hand-linker
// loop shape with a counter-driven loop.  A normal argc/argv struct returns
// through a hidden pointer with
// both ngccc and mwcc (140B/156B).  The typed u64/union candidate below is the
// best ABI match under ngccc, but is 124B versus 108B and 0/27 relocation-masked
// words: it folds the header addresses, uses a pointer-compare loop instead of
// a counter-driven loop, and still cannot express the custom argc/argv return cleanly.
// Do not replace this with whole-function asm or cast/permutation searches.
// WIP DRAFT (non-matching) — semantic reconstruction
// 2026-10-17: u64-return + pins + barriers rebuild reaches 51.85% (14/27,
// size-exact 108B): `u64` return explains li r3,0/li r4,0 exits and the
// (n, t+1) live-out; pins h=r5/n=r3/p=r4/x=r6 fix homes; zero-code "+r"
// barriers block combine's lwzux/lwzu fusions (volatile alone fails, frame).
// Residual: prologue addr-tmp r9 vs r6 (pin reservation), mtctr/addi order,
// loop temp r0 vs r7, u64-pack tail moves.
// family=m2c range=0x80003254-0x800032C0 size=108B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
// Stub (range 0x80003254-0x800032C0, 108B): original bytes in DOL, not reproduced here per repo policy.
u64 fn_80003254(void) {
    s32 base = *(s32 *)0x800000F4;
    union {
        u64 packed;
        struct {
            s32 argc;
            char **argv;
        } args;
    } result;
    s32 offset;
    s32 *table;
    s32 *cursor;
    s32 *end;

    if (base != 0) {
        offset = *(s32 *)((char *)base + 8);
        if (offset != 0) {
            table = (s32 *)((char *)base + offset);
            result.args.argc = table[0];
            if (result.args.argc != 0) {
                cursor = table;
                result.args.argv = (char **)(table + 1);
                end = table + result.args.argc;
                while (cursor != end) {
                    cursor++;
                    *cursor += base;
                }
                *(s32 *)0x80000034 = (s32)result.args.argv & ~31;
                return result.packed;
            }
        }
    }

    result.args.argc = 0;
    result.args.argv = 0;
    return result.packed;
}
