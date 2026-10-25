// PARKED 2026-09-26 — redrafted from the DOL. 7.0% -> 46.3% (72/134 words),
// size 536B vs want 532B (1 insn over). The old "big-function regalloc
// divergence, wholesale colouring difference" assessment was wrong: the m2c body
// was semantically broken (see below), and fixing the semantics recovered the
// frame (0x30), the ctr loop, the arg homes (r29/r28/r12 — incl. arg1 living in
// the VOLATILE r12 across the call-free loop) and the whole tail structure.
// REMAINING BLOCKER (all one class, all measured):
//   (1) two extra callee-saved regs: want `stmw r26,0x18` (6) vs got
//       `stmw r24,0x10` (8). The extras are (a) the `&sp8` out-param ADDRESS,
//       which GCC homes in r24 while want rematerialises `addi r3/r4,r1,8` at
//       each of its 2 call sites, and (b) the `arg0+0x5DC` base, which want
//       keeps in r31 and then REUSES for the record pointer (`add r31,r30,r29`
//       overwrites the base) whereas ngccc gives it r25 and rec r30. Because
//       of (a)+(b) every following register NUMBER is off by one/two, so the
//       whole tail reads as diffs. Tries that did NOT fix it: volatile sp8
//       (volatile s32 / volatile void* both cost +8 frame), sp as a 1-element
//       array, a struct-typed out param, per-site temporaries, unprototyped
//       4th-arg forms, -fno-gcse/-fno-schedule-insns(2)/-fno-expensive-optimizations
//       (all neutral or worse), and register pins (collapse allocation).
//   (2) address FORM: want builds `arg0+0x5D4` / `arg0+0x5D8` in the post-loop
//       block and stores with `stwx base,index` (index = best*0x18 in r30);
//       ngccc CSEs both through the record pointer and emits
//       `stw rX,0x5D4(rec)` / `stw rX,0x5D8(rec)`. Named base pointers for the
//       stores force the stwx form but then add a saved reg and rotate every
//       home (doc-32) — 18-21%. Want's `lwzu r3,0x5c8(r31)` (record head read
//       folding +0x5C8 into r31) likewise not reproducible: expressing the
//       record as `+0x5C8+off` gives addi+add+add, expressing the head as a
//       0x5C8-offset member gives plain `lwz` (34%), the raw offset gives
//       `lwzx` (44%).
//   (3) one word: want passes r3 UNTOUCHED to AddChecksum in the `arg2>maxv`
//       arm (r3 still holds the ctor result); `AddChecksum(0,0,QB_HIDE)` emits
//       a spurious `li r3,0`. Passing `tmp` emits `mr r3,r31` instead (worse);
//       an uninitialised local (documented leftover-reg trick) is also worse.
// SEMANTIC FIXES vs the m2c draft (all verified against the DOL):
//   - m2c scaled the table index by 4: `*((s32*)arg0 + 0x5D8 + var_r7)` is
//     byte offset 4*(0x5D8+var_r7), the code wants 0x5D8 + var_r7 (var_r7 is a
//     BYTE offset, +0x18/iter). Same bug on the post-loop `0x5DC`/`0x5D4`
//     stores. This alone mis-compiled the whole body.
//   - the table is a 10 x 24-byte row array at arg0+0x5C8 (head/tail/count at
//     +0x00/+0x04/+0x08, id +0x0C, value +0x10, in-use +0x14) with the
//     `arg0+0x5C4` s32 in-use counter (sibling fn_8004C66C + promoted
//     fn_8004C2DC confirm: 0x5A4 ptr table, 0x5C4 counter, walk pointer at
//     +0x5D8, `lwzx` value re-read at +0x5D8+off).
//   - the row's +0x00 field IS the CObject link list header, so the
//     Add/RemoveRefLink 2nd argument is the row itself; the final
//     `CObject_RemoveRefLink()` had NO arguments in m2c but is called with
//     (sp8, &sp8) -> the local's head is unlinked and the slot cleared.
//   - fn_8004B03C is a 4-arg call at the call site (r3=&sp8, r4=arg0, r5=arg1,
//     r6=1) even though its own prologue only reads r3/r5 (doc-10/§6y-132:
//     arity comes from want's arg setup).
//   - CStruct_ctor(CStruct_new(8)) must be chained, not two statements.
//   - vcall: vtable at e+8, s16 offset at vtbl+0x10, fn at vtbl+0x14
//     (Unk_07FDFB02 is the exact shape; m2c used Unk_9994C3F5, which types
//     0x10 as s32 and loses the `lha`).
//   - the guard is `!found && (u32)arg2 < minv` (cmplw, both sides unsigned) and
//     the two loop trackers are u32 (`cmplw`), while `unk0x5C4 > 0` is signed.
//   - deleted m2c's file-scope `static s32 sp8;` (it shadowed the real local).
// Proven levers in this body (keep them): hoisting ONLY the `arg0+0x5DC` base
// into a live-across-the-loop variable (35->44%, it is what produces want's
// preheader `addi r31,r29,0x5dc`), and initialising `i` BEFORE the walk
// pointers so the preheader emits `li r10,0` before `addi r11`/`li r7`
// (44->46%). Hoisting the 0x5D4 base the same way costs 2 extra saved regs
// (10%) — do not.
// family=m2c range=0x8004C458-0x8004C66C size=532B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

void GetElement_2(void *out, void *self, s32 id, s32 flag);
void CObject_AddRefLink(Unk_C7387A53 *item, Unk_C7387A53 **head);
void CObject_RemoveRefLink(Unk_C7387A53 *item, Unk_C7387A53 **head);
s32 CStruct_new(s32 size);
s32 CStruct_ctor(s32 arg0);
s32 AddChecksum(s32 arg0, s32 arg1, s32 hash);
void CStruct_delete(s32 arg0, s32 arg1);

// One 24-byte row of the container's 10-entry table (base arg0+0x5C8).
typedef struct C458Row {
    void *unk0x00;  /* list head (CObject link list)  */
    void *unk0x04;  /* list tail                     */
    s32 unk0x08;    /* list count                    */
    s32 unk0x0C;    /* id  <- arg1                   */
    u32 unk0x10;    /* value <- arg2 (min/max track) */
    u32 unk0x14;    /* in-use flag                   */
} C458Row;

s32 fn_8004C458(void *arg0, s32 arg1, u32 arg2) {
    void *sp8;               /* r1+8: GetElement_2 out-param (list head) */
    Unk_C7387A53 *e;         /* the row's linked object                 */
    Unk_07FDFB02 *vt;        /* its vtable                              */
    C458Row *rec;            /* the chosen row                          */
    char *used_base;         /* arg0+0x5DC, hoisted across the loop     */
    s32 *p;                  /* walk pointer, arg0+0x5D8 (+0x18/iter)    */
    s32 off;                 /* walk byte offset, +0x18/iter            */
    s32 i;                   /* row index                               */
    s32 best;                /* first free row, else min-value row      */
    s32 found;               /* a free row was seen                     */
    s32 maxi;                /* row holding the largest value           */
    u32 maxv;                /* largest value seen                      */
    u32 minv;                /* smallest value seen                     */
    s32 tmp;                 /* scratch object                          */

    used_base = (char *)arg0 + 0x5DC;
    maxv = 0U;
    maxi = -1;
    minv = 0U;
    best = -1;
    found = 0;
    i = 0;
    p = (s32 *)((char *)arg0 + 0x5D8);
    off = 0;
    for (; i < 10; i++) {
        if (p[1] != 0) {                     /* p[1] = row->unk0x14 (in use) */
            if ((u32)p[0] < minv || minv == 0U) {
                minv = (u32)p[0];
                best = i;
            }
            if ((u32)*(u32 *)((char *)arg0 + 0x5D8 + off) > maxv) {
                maxv = *(u32 *)((char *)arg0 + 0x5D8 + off);
                maxi = i;
            }
        } else if (found == 0) {
            best = i;
            found = 1;
        }
        p += 6;                              /* +0x18 bytes */
        off += 0x18;
    }
    if (found == 0 && arg2 < minv) {
        return 0;
    }
    rec = (C458Row *)((char *)arg0 + best * 0x18);
    *(u32 *)(used_base + best * 0x18) = 1;
    *(s32 *)((char *)arg0 + 0x5D4 + best * 0x18) = arg1;
    GetElement_2(&sp8, arg0, arg1, 1);
    e = (Unk_C7387A53 *)rec->unk0x00;
    if (e != NULL) {
        CObject_RemoveRefLink(e, (Unk_C7387A53 **)rec);
        rec->unk0x00 = NULL;
    }
    rec->unk0x00 = sp8;
    if (sp8 != NULL) {
        CObject_AddRefLink((Unk_C7387A53 *)sp8, (Unk_C7387A53 **)rec);
    }
    *(u32 *)((char *)arg0 + 0x5D8 + best * 0x18) = arg2;
    if (((Unk_9E4B1D7B *)arg0)->unk0x5C4 > 0) {
        tmp = CStruct_ctor(CStruct_new(8));
        if (arg2 > maxv) {
            AddChecksum(0, 0, QB_HIDE);
            e = *(Unk_C7387A53 **)((char *)arg0 + maxi * 0x18 + 0x5C8);
            vt = *(Unk_07FDFB02 **)((char *)e + 8);
            ((s32 (*)(void *, void *))vt->unk0x14)((char *)e + vt->unk0x10,
                                                    (void *)tmp);
        } else {
            AddChecksum(tmp, 0, QB_HIDE);
            e = (Unk_C7387A53 *)sp8;
            vt = *(Unk_07FDFB02 **)((char *)e + 8);
            ((s32 (*)(void *, void *))vt->unk0x14)((char *)e + vt->unk0x10,
                                                    (void *)tmp);
        }
        if (tmp != 0) {
            CStruct_delete(tmp, 3);
        }
    }
    ((Unk_9E4B1D7B *)arg0)->unk0x5C4 = ((Unk_9E4B1D7B *)arg0)->unk0x5C4 + 1;
    if (sp8 != NULL) {
        CObject_RemoveRefLink((Unk_C7387A53 *)sp8, &sp8);
        sp8 = NULL;
    }
    return 1;
}
