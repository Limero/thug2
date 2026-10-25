// PARKED 2026-10-03 (b74): NEAR 53.5% (baseline was DIFF 7.0% — pct went UP).
// Reproduce: LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x800151F4
//
// Body is semantically correct and instruction-for-instruction identical to the
// want over ~57 of 71 words; .text is 280B vs the want's 284B (1 word short).
// Prologue (stwu/mflr/mfcr/stmw/r29-r25/li/addi r30,r28,r27), the '/'→'\\' copy
// loop (lbzx/extsb/stbx/cmpwi/bne/li/stbx/addi), the rotated test
// (mr r3,r29/bl strlen/`cmplw r31,r3`/`ble`), the rotated backslash scan, both
// strcpy arg setups incl. `addi r4,r31,1` + `add r4,r30,r4` + hoisted `li r29,0`,
// the epilogue and the CR mask (mtcrf 0x18) all match exactly.
//
// TWO remaining diffs, both compiler coin-flips I could not reach from C:
//
// 1. +0x6c..+0x7c — hoisted if-guard compares split around the call. The want
//    builds r3 from r1 plus 8, calls strlen, derives r31 as r3 minus 1, and
//    only then emits the cr4 compare of r26 and the cr3 compare of r25 before
//    the branch; this build interleaves the cr4 compare before the call and
//    the r31 derivation after the cr3 compare.
//    Both are the jump-threading/CSE-hoisted guards of `if (dir_crc)`/`if (file_crc)`;
//    the want keeps them in source order at the block end. Identical in got for
//    every source variant tried (see below), so this is thread-jumps +
//    reload block-split order, not something the C order controls.
//
// 2. +0xb4.. — extension-strip block: 11 want words vs 10 got words. The
//    want copies r28 into r30, copies r30 into r3, calls strlen, derives r3
//    as r3 minus 4, loads byte r0 indexed by base r30 plus index r3,
//    compares, branches on nonzero, then repeats the r3 copy and strlen call,
//    derives r3 minus 4 again, and stores r29 indexed by base r30 plus index
//    r3; this build instead copies r28 straight into r3, calls strlen, folds
//    the minus-4 into an indexed add of r3 and r28, loads r0 from the -4
//    displacement of r3, and stores r29 to the -4 displacement of r3 on both
//    halves.
//    (a) the want's `&file` value lives in TWO registers (r28 in the prologue and
//        r30 here) — a split web; GCC folds every `name = file` I could write.
//    (b) the want keeps the `- 4` as a separate `addi` (variable index) instead of
//        folding it into the load displacement (`add`+disp).
//
// RULED OUT (each measured, all reverted):
//  * `u32 i` for the loop counter -> `cmplw r31,r3` + `ble` (want's unsigned
//    compare with a signed branch — GCC 2.95 `ble` pattern quirk). KEPT.
//  * `strcpy(file, &buf[i+1])` (not `buf+i+1`) -> `addi r4,r31,1` + `add r4,r30,r4`
//    in that order. KEPT.
//  * `char *name = file` / `register char *name` / struct field wrapper: all three
//    get CSE'd back to r28 (ngccc promotes the struct field to a reg, then folds).
//  * `register char *name __asm__("r30")` -> RA moves &buf to r29 and spills r24,
//    frame 0x1a0->0x1b0: destroys the matching prologue. Pinning a local in r30 is
//    impossible while &buf (a different web) also lives in r30 from the prologue.
//  * `__asm__("" : "+r"(name))` barrier after `name = file` -> same RA breakage
//    (frame 0x1b0, r24 saved, all three frame bases shifted).
//  * `(u32)strlen(name)-4`, `strlen(name)-4u`, `u32 strlen()` decl, `s32 strlen(s32)`
//    (m2c's decl) -> identical `add`+disp form; the A+(B-C) reassociation is not
//    signedness-blockable.
//  * a local `k = strlen(name)-4` index DOES give the want's `addi`+`lbzx` form, but
//    then only one strlen call survives, so the block is 4 words short of the want.
//  * loop-2 as empty `for`, loop-1 as `while`, `i = strlen(buf); i -= 1;`,
//    conditions hoisted into locals -> compare placement (diff 1) unchanged; the
//    `for`-loop2 variant even breaks the loop shape.
//
// MOST PROMISING NEXT IDEA: diff 1 (compare placement) is worth 4 words and diff 2
// only the last 11; solve 2 first only if a split web for `&file` can be forced
// without a register pin — e.g. finding the original's expression shape (the want
// calls `strlen` TWICE on the same buffer *and* keeps both `-4`s in registers, which
// no single-expression C form produces; two index variables each holding
// `strlen(name)-4` would give 11 words with r28 as base).
#include "types.h"
void strcpy(char *, const char *);
s32 strlen(const char *);
s32 Script_GenerateCRC(char *);
void fn_800151F4(char *path, s32 *dir_crc, s32 *file_crc) {
    char buf[128];
    char dir[128];
    char file[128];
    char *name;
    u32 i;

    for (i = 0; i <= strlen(path); i++) {
        buf[i] = path[i];
        if (buf[i] == '/') {
            buf[i] = '\\';
        }
    }
    i = strlen(buf) - 1;
    while (buf[i] != '\\') {
        i -= 1;
    }
    strcpy(file, &buf[i + 1]);
    buf[i] = 0;
    strcpy(dir, buf);
    name = file;
    if (name[strlen(name) - 4] == '.') {
        name[strlen(name) - 4] = 0;
    }
    if (dir_crc) {
        *dir_crc = Script_GenerateCRC(dir);
    }
    if (file_crc) {
        *file_crc = Script_GenerateCRC(file);
    }
}
// family=m2c range=0x800151F4-0x80015310 size=284B