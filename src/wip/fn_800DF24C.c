// WIP DRAFT — hand-rebuilt 2026-10-12 from the DOL disassembly (was m2c husk at 13%).
// family=m2c range=0x800DF24C-0x800DF3F0 size=420B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// DECODE (from want disasm + callee audit):
//   - fn_800F0F84 is 2-arg (s32,s32): call1 = fn_800F0F84(arg2, 0) (NOT the
//     m2c 3-arg (arg0,arg2,0)); call2 = fn_800F0F84(arg4->unk0x18, 0) (NOT the
//     m2c 5-arg fold of surrounding code into sqrtf-style args).
//   - GetChecksum_2/GetStructure_2 are 4-arg; fn_8009F310 is 6-arg
//     (src/fn_8009F310.c). The m2c body left them unprototyped (spurious
//     crclr) and killed the tail with `(0 == 0) ||` (DCE deleted ~144B).
//   - Loop is countdown with peeled cmpwi/addi/beq preface (do/break shape).
//   - Bit loop is mtctr/bdnz over arg1[0..2]: `for (i = 3; i-- != 0;)`.
//   - Tail: spC==0 -> return 0; fn_80175450(lbl, var)!=0 -> return 0;
//     arg0->0x30 accumulates (1<<v); final 6-arg fn_8009F310; return 1.
//   - CLOSED: the cr4/`&spC` duplication came out of plain C by itself —
//     GCC duplicated both into the arms exactly like retail (jump threading
//     of the shared `if (arg4)` + `&spC` into the diamond arms). No lever.
//   - `for (i = 3; i-- != 0;)` fires mtctr/bdnz for the bit loop (transfer
//     from the fn_801AC9CC note); the `1 <<` li hoists out of the loop.
// PARKED: current official best is 77.14% (size-exact 420B). The remaining
// differences start with the parameter-home allocation (want arg0 in r27 and
// var_r31 in r31; got the reverse), then include the loop-test order, a call
// argument move order, and a tail reload. Callee signatures, fields and the
// high-level control flow have been checked against the instructions. Pinning
// the local to r31 collapsed the frame and worsened to 2.94%; keep the current
// unpinned body rather than introduce asm or unsupported casts.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305EAC[];
s32 fn_800F0F84(s32, s32);
s32 fn_80129528(CStruct *, s32);
s32 fn_800F0AFC(void);
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_80175450(s32, CStruct *);
s32 ContainsFlag(CStruct *, s32);
void *fn_8009F310(void *, s32, s32, s32, s32, s32);

s32 fn_800DF24C(Unk_C7387A53 *arg0, s32 *arg1, s32 arg2, CStruct *arg3, CScript *arg4) {
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 idx;
    s32 var_r31;
    s32 temp_r3;
    s32 temp2;
    s32 temp_net;
    s32 i;
    s32 *p;
    s32 v;

    var_r31 = 0;
    if (arg3 == NULL) {
        var_r31 = fn_800F0F84(arg2, 0);
    } else {
        idx = arg3->unk0x4;
        do {
            if (idx == 0)
                break;
            idx -= 1;
            var_r31 = fn_80129528(arg3, idx);
        } while (fn_800F0AFC() != arg2);
    }
    sp8 = 0;
    if (arg4 != 0) {
        temp_r3 = fn_800F0F84(arg4->unk0x18, 0);
        if (temp_r3 != 0)
            GetStructure_2((CStruct *)temp_r3, QB_MODELTRIGGERSCRIPTPARAMS, &sp8, 0);
    }
    spC = 0;
    GetChecksum_2((CStruct *)var_r31, QB_TRIGGERSCRIPT, &spC, 0);
    if (spC == 0)
        return 0;
    temp2 = fn_80175450(*(s32 *)lbl_80305EAC, (CStruct *)var_r31);
    if (temp2 != 0)
        return 0;
    arg0->unk0x30 = temp2;
    p = arg1;
    for (i = 3; i-- != 0;) {
        v = *p++;
        if (v != 0)
            arg0->unk0x30 += 1 << v;
    }
    temp_net = ContainsFlag((CStruct *)var_r31, QB_NETENABLED);
    fn_8009F310((void *)arg0->unk0xC, spC, arg2, temp_net,
                ContainsFlag((CStruct *)var_r31, QB_PERMANENT), sp8);
    return 1;
}
