// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004C9C0-0x8004CA68 (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8004ADC8(s32, s32, s32, s32, s32);
s32 fn_80128A90(CStruct *, void *);
s32 ResolveComplexID(Unk_C7387A53 *, CStruct *, void *, void *);
// IMPROVED 2026-08-31 51.2% -> 55.8%: the two rodata2 string addresses
// (0x80292928/0x80292938) now reference extern lbl_ symbols -> lis+addi. The
// remaining 18 diffs are regalloc/ordering around the `temp_r30 = ... ^ 1`
// boolean and the fn_80128A90 call setup (want materializes r30=0 after the
// bl; got hoists it). Parked; retry after a regalloc discovery.
extern char lbl_80300434[];
extern char lbl_80292928[];
extern char lbl_80292938[];
bool ScriptDestroyScreenElement(CStruct *arg0, s32 arg1) {
    s32 sp8;
    s32 temp_r29;
    s32 temp_r30;
    s32 temp_r6;

    temp_r29 = *(s32 *)&lbl_80300434;
    if (ResolveComplexID(temp_r29, arg0, QB_ID, &sp8) == 0) {
        return false;
    }
    temp_r30 = fn_80128A90(arg0, (s32)lbl_80292928) ^ 1;
    temp_r6 = fn_80128A90(arg0, (s32)lbl_80292938);
    if ((temp_r30 != 0) || (temp_r6 == 0)) {
        fn_8004ADC8(temp_r29, sp8, temp_r30, temp_r6, arg1);
    }
    return true;
}
