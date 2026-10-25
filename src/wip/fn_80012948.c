// family=m2c range=0x80012948-0x80012A10 size=200B
// INERT: not registered in splits.txt/configure.py - never compiled, not
// counted in objdiff progress.  activate via tools/wip.py.
// PARKED at 68.0% (16/50 words), exact 200B size (0x80012948 + 0xC8).
//
// WHAT THIS FUNCTION IS (fully re-derived from the DOL; the m2c draft's
// comment was wrong about the layout).
// lbl_8031362C (.bss:0x8031362C, size 0xC84) is a 200-entry table of 16-byte
// records:
//     +0x00 s32 *resource   (freed via Mem_Free_3, then zeroed)
//     +0x04 s32  owner      (compared with arg0, then zeroed)
//     +0x08 s32  value      (only ever zeroed here)
//     +0x0C s32  refcount   (decremented, then zeroed)
// 200 * 16 = 0xC80, so the last record starts at table+0xC70 and the loop's
// `cursor <= limit` test (cursor = table+0xC70 on the final pass) covers
// exactly 200 records; 0xC84-0xC80 = 4 trailing bytes.
//
// The retail loop walks the table with TWO cursors that advance in lockstep
// by 0x10: a record pointer (lwz/stw at +0 and +8, i.e. displacement form)
// and a byte offset used as the INDEX of the two parallel columns (owner at
// table+4, refcount at table+0xC, both reached through lwzx/stwx). That
// asymmetry is real, not an m2c artifact: the sibling scan loop in
// fn_800127E4 (0x800128B4-0x80012904) uses the same column idiom against the
// same table - `lis r9,-0x7fcf; slwi r11,r10,4; addi r9,r9,0x362c;
// lwzx r0,r9,r11` for the owner column and `addi r11,r9,0xC; lwzx r9,r11,r8;
// addi r9,r9,1; stwx r9,r11,r8` for the refcount (there the byte index is
// scaled from a record counter instead of being carried as a literal += 0x10
// cursor, and its owner/refcount tests are the same two 0..199 record scan).
//
// Body reconstructed as: release when the refcount is ALREADY zero or the
// decrement reaches zero, clearing all four words either way; then
// decrement the u16 at +0xA of fn_80012754(arg0) if it is non-zero. Both
// callee signatures are confirmed from their prologues: Mem_Free_3 at
// 0x800106A8 (scope:global) copies r3 into r4, i.e. it takes one argument
// and returns void; fn_80012754 at 0x80012754 keeps its argument in r28 and
// returns the pointer the caller null-tests with a record-form OR.
//
// WHY IT IS STILL PARKED - the blocker is now PURELY an 8-way callee-saved
// register assignment.  Every opcode, immediate, branch extent, condition
// register and (relocation-resolved) address in this body matches want; the
// only residue is that ngccc hands out the same register SET with two
// transpositions: this body assigns the constant to r25, the end to r24, the
// argument to r26, zero to r27, the owner to r28, the offset to r29, the
// cursor to r30 and the refcount to r31, while the want assigns the constant
// to r25, the end to r24, the argument to r26, the owner to r27, zero to r28,
// the offset to r29, the refcount to r30 and the cursor to r31 — i.e. the
// zero/owner pair and the cursor/refcount pair are each swapped.
//
// MEASURED AND REJECTED (all at 200B, none beat 16/50):
//   * 9 per-object flags: -fno-schedule-insns (19), -fno-schedule-insns2,
//     -fno-sched-spec, -fno-gcse, -fno-expensive-optimizations,
//     -fno-strength-reduce (all 18); -fno-crossjumping / -fno-if-conversion
//     / -fno-tree-pre do not exist in ProDG cc1.
//   * 9 declaration/birth orders of {z, base, off, end, cursor}: 16 is the
//     floor; every one that keeps the cursor copy emits it LAST
//     ([zero][end][off][mr]) while want emits it second ([zero][mr][off][end]).
//   * cursor typed s32* / Rec* / char* / s32: the s32 form is required for
//     `cmpw` (pointer forms give `cmplw`); all four otherwise identical.
//   * increment order: `p += 0x10; off += 0x10;` is mandatory - swapping
//     them grows the object to 208B.
//   * 5 store-run permutations: no effect at all on the allocation.
//   * register-var pins: pinning owner->r27 or refcount->r30 is a NO-OP
//     (the alias is coalesced away, so the pin never reaches RTL); pinning
//     the cursor to r31 REGRESSES to 18 and cascades (arg0->r27, const->r26,
//     end->r25, r24 freed, `stmw r25,0xc`) - the documented pin-leak /
//     post-death-reuse-loss behaviour (AGENTS.md 74-161c, 6ay-162).
// Per AGENTS.md doc-15 / 6ay-162 this is a brittle-allocator park; do not
// re-grind pins or permutations without a new lever.
//
// NOTE ON THE PREVIOUS BODY (14/50 = 72.0%, kept in git history): it scored
// 2 words higher but was structurally further from want - it referenced the
// symbol inline per column site, so ngccc re-materialized the table's PAGE a
// second time (`lis r25`) instead of sharing the one table address, omitted
// want's `mr r31,r25` cursor copy, chained the refcount base off the owner
// base (`addi r30,r28,8` vs want's `addi r30,r25,0xC`), and emitted all five
// lwzx/stwx with the INDEX in rA instead of the column base. Its higher word
// count was an artifact of that wrong operand order coinciding with ngccc's
// role assignment. Closing this body needs ONE thing (the two register
// transpositions); the 14/50 body needed three structural changes plus five
// operand-order flips on top of them.  The relocation addends in both forms
// were checked by hand and resolve to the correct 0x80313630/0x80313638
// column addresses, so neither body is semantically wrong.
#include "types.h"
extern char lbl_8031362C[];
void Mem_Free_3(s32);
void *fn_80012754(s32);
void fn_80012948(s32 arg0) {
    s32 z = 0;
    char *base = lbl_8031362C;
    s32 off = 0;
    s32 end = (s32)base + 0xC70;
    s32 p = (s32)base;
    do {
        if (*((s32 *)p) != 0) {
            s32 *ob = (s32 *)(base + 4);
            if (*(s32 *)((char *)ob + off) == arg0) {
                s32 *rb = (s32 *)(base + 0xC);
                s32 c = *(s32 *)((char *)rb + off);
                s32 d;
                if (c == 0 || (d = c - 1, *(s32 *)((char *)rb + off) = d, d == 0)) {
                    Mem_Free_3(*((s32 *)p));
                    *((s32 *)p) = z;
                    *((s32 *)((char *)p + 8)) = z;
                    *(s32 *)((char *)ob + off) = z;
                    *(s32 *)((char *)rb + off) = z;
                }
            }
        }
        p += 0x10;
        off += 0x10;
    } while (p <= end);
    {
        void *q = fn_80012754(arg0);
        if (q != NULL) {
            u16 v = *(u16 *)((char *)q + 0xA);
            if (v != 0) {
                *(u16 *)((char *)q + 0xA) = v - 1;
            }
        }
    }
}
