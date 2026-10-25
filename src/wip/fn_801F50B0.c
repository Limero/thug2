// WIP DRAFT (non-matching) — C body rebuilt from the m2c draft.
// family=m2c range=0x801F50B0-0x801F5188 size=216B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED at 96.3% (215/216 words, object 216 B == symbol size, no private
// .rodata). Everything matches except one slot in the entry block: the zero
// initialisation of the element counter `var_r27` belongs in the shadow of
// the fn_801F5A0C call, between that call and the result-save copy, while
// ngccc hoists it above the call.
//
// Why it is stuck: the constant has no dependence on the call, so sched2 may
// hoist it, and the result copy is placed immediately after the call by
// local_alloc. Any dependence that pulls the constant below the call also
// pulls the result copy ahead of it, because the only value available after
// the call is the result, which is homed for its later use by the second
// callee. Measured and rejected: r27/r28 register pins are load-bearing
// (removing them drops the body to 83%); callee prototypes and return-type
// flips on all five callees; zero-code barriers in every position; asm-birth
// `li` forms (volatile, non-volatile, call-result input, memory clobber);
// res-split copies around the barrier; statement and declaration order
// permutations; -fno-schedule-insns/-insns2/-sched-spec. Reordering the two
// counter inits only moves the failure to the second one.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 CStruct_new(s32);
void AddArrayPointer(CStruct *, s32, s32);
void fn_80129314(CStruct *, s32, s32);
void fn_801F2F58(Unk_5FCDF30E *, CStruct *);
s32 CStruct_ctor(s32);
void fn_80129068(Unk_5AA7B5D7 *, s32, s32);
s32 fn_8003E7CC(s32);
s32 fn_80128F94(Unk_9D4ED6AF *);
s32 fn_801F5A0C(s32);
void fn_801F50B0(s32 arg0, s32 arg1, CStruct *arg2) {
    s32 temp_r29;
    s32 temp_r30;
    s32 temp_r3;
    s32 temp_r4;
    s32 var_r9;
    void *var_r31;
    register s32 var_r27 __asm__("r27");
    register s32 var_r28 __asm__("r28");

    var_r31 = arg0 + 0x20;
    temp_r30 = fn_801F5A0C(arg0);
    var_r27 = 0;
    __asm__("" : "+r"(var_r27));
    var_r28 = 0x32;
    temp_r29 = fn_80128F94(fn_8003E7CC(0xC));
    fn_80129068(temp_r29, temp_r30, 0xA);
    do {
        var_r9 = 1;
        if ((s32) ((Unk_127FDB99 *)var_r31)->unk0x2BE == 0) {
            var_r9 = 0;
        }
        if ((var_r9 != 0) && ((s32) ((Unk_127FDB99 *)var_r31)->unk0x0 == arg1)) {
            temp_r3 = CStruct_ctor(CStruct_new(8));
            fn_801F2F58(var_r31, temp_r3);
            temp_r4 = var_r27;
            var_r27 += 1;
            fn_80129314(temp_r29, temp_r4, temp_r3);
        }
        var_r31 += 0x370;
        var_r28 -= 1;
    } while (var_r28 != 0);
    AddArrayPointer(arg2, QB_GOALS, temp_r29);
}