// WIP DRAFT (non-matching) — C body re-derived from the want disasm
// family=m2c range=0x80044D98-0x80044EA4 size=268B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-02 (w75/0x80044D98): 94.0% (263/268 B, only 4 words wrong)
// 2026-10-21: swapping the second declared parameter of fn_80009818 to `u16`
// (or `u8`) drops the count 4 -> 1, but that declaration is `void **` and a
// narrow integer there is not admissible, so it is NOT applied -- it is only
// evidence that the residual sits in that call's argument window. No other
// prototype in the body responds, and no matched source defines fn_80009818 to
// copy a signature from.
// — the residual is a pure r26<->r27 colour swap of the two hoisted
// address pseudos for fn_800586CC's out-params: at 0x80044E10 the want
// builds r1 plus 0x6c into r26 and at 0x80044E14 it builds r1 plus 0x70 into
// r27, while this body colours those two hoisted addresses swapped (r27 for
// the first slot, r26 for the second), with the matching fifth- and sixth-
// argument copies at 0x80044E3C and 0x80044E40 swapped the same way.
//   (and the matching `mr r5,r26`/`mr r6,r27` at 0x80044E3C/0x80044E40).
// Everything else — frame 0x90, stmw r26/0x78, all slots (buffer 0x8,
// cursor 0x68, f32 0x6c, s32 0x70), the three GCSE-hoisted addis, the
// do/while->preheader shape, the fcmpu/fmuls/stfs order, both return
// paths and both Mem_Free sites — is byte-identical, so this is a
// local_alloc tie-break, not a scheduling or semantic error.
//
// ROOT CAUSE (verified with `ngccc -da` dumps): CSE hoists the three
// loop-invariant `r31+K` address births into the loop preheader as
// pseudos 112(0x68), 113(0x6c), 114(0x70) — in *materialisation* order,
// which is also the order `allocate_other_regs` gives the callee-saved
// regs (112->r30, 113->r27, 114->r26; r26 is otherwise unused, so it
// lands on the LAST pseudo).  The want's mapping (113->r26, 114->r27)
// requires the hoist order 0x68, 0x70, 0x6c — i.e. &sp70 born before
// &sp6C.  That is unreachable from C here because the stack-slot layout
// follows the *same* materialisation order, and the want's own
// `mr r5,r26`(0x6c)/`mr r6,r27`(0x70) pins arg3=&f32, arg4=&s32, so the
// only C spelling that yields the correct slots forces &sp6C to be born
// first.  Slots verified to follow first-address-taking-use, not
// declaration order (swapping the declarations does not move them).
//
// Tried (all 94.03% / 268 B unless noted): plain scalars; loop shape
// `while`, `do/while`, `for(;;)+continue/break`, and the call placed
// inside the loop (79.1% — arg0 falls to r26); strict-aliasing struct
// for {cursor,f32,s32}; per-cursor `s32`/pointer out-params;
// `volatile f32` out-param (88.1%); protos for fn_80009818
// `(s8*,void**)`/`(char*,char**)`/`(s8*,void*)` and for fn_800586CC
// `(s32,char*,f32*,s32*)`/`(void*,char*,void*,void*)`; call arg order
// swapped (moves the slots with it); pre-materialised pointer temporaries
// for the out-params (89.6%/92.5% — slot order moves); param-reassignment
// of the fn_80053790 result into arg1/arg2 (74.6%/76.1%); a named size
// local, `buf = strcat(buf,arg1)`, an `f32 scale` local, unused pad
// locals (none shift pseudos 112/113/114).  Flags: default is the only
// good one — `-fno-expensive-optimizations` 36.9%, `-fno-gcse` 34.4%
// (kills the preheader hoist), `-fno-gcse-lm`/`-fno-thread-jumps`/
// `-fno-cse-follow-jumps`/`-fno-crossjumping`/`-fno-caller-saves`/
// `-fomit-frame-pointer` no-ops, `-fno-schedule-insns2` 91.0% (6 words),
// `-fno-schedule-insns` 65.7%.  The m2c `// FLAG: -fno-expensive-
// optimizations` marker was therefore REMOVED (it costs 57 points).
// 2026-10-15: hard-pin attempts REVERTED (both DIFF): `register f32 *pf
// __asm__("r26")` + `register s32 *pi __asm__("r27")` steal the arg-home regs
// globally (prologue reshuffled from the first mr); single pf->r26 pin also
// DIFFs. Pins cannot fix a local_alloc tie-break when the pinned regs are
// live argument homes. Do not re-pin here.
// Applies to: any fn whose two symmetric &spN out-params are GCSE-hoisted
// into a loop preheader; the lever is CSE-table birth order, not C.
#include "types.h"

typedef struct Obj_80044D98 {
    char pad0x0[0x178];
    f32 unk0x178;      /* lfs f12,0x178(r28) */
    char pad0x17C[0x14];
    s32 unk0x190;      /* fn_80053790(arg0->unk0x190) */
    char pad0x194[0x20];
    f32 unk0x1B4;      /* lfs f13,0x1b4(r28) */
} Obj_80044D98;

extern char lbl_80292518[];             /* "/" separator, .rodata2 */
void *Mem_Alloc(s32);
void Mem_Free(void *);
char *strcat(char *, const char *);
int strcmp(const char *, const char *);
s32 fn_80044614(Obj_80044D98 *, char *, s32);
void fn_800445E8(Obj_80044D98 *, char *);
s32 fn_80053790(s32);
s32 fn_80009818(s8 *, void **);
void fn_800586CC(s32, char *, f32 *, s32 *);

s32 fn_80044D98(Obj_80044D98 *arg0, char *arg1, s32 arg2, s32 arg3) {
    char sp8[0x60];
    char *sp68;
    f32 sp6C;
    s32 sp70;
    char *buf;
    s32 temp_r3_2;
    f32 temp_f0;

    buf = (char *)Mem_Alloc(0x200);
    fn_80044614(arg0, buf, 0x200);
    strcat(buf, arg1);
    if (((arg2 != 0) && (strcmp(arg1, lbl_80292518) != 0)) || (arg3 != 0)) {
        temp_r3_2 = fn_80053790(arg0->unk0x190);
        sp68 = buf;
        while (fn_80009818((s8 *)sp8, (void **)&sp68) != 2) {
        }
        fn_800586CC(temp_r3_2, sp8, &sp6C, &sp70);
        temp_f0 = sp6C * arg0->unk0x1B4;
        sp6C = temp_f0;
        if (temp_f0 > arg0->unk0x178) {
            Mem_Free(buf);
            return 0;
        }
    }
    fn_800445E8(arg0, buf);
    Mem_Free(buf);
    return 1;
}
