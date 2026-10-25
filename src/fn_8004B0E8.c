// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004B0E8-0x8004B15C (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 ResolveComplexID(Unk_C7387A53 *, CStruct *, void *, void *);
void GetElement_2(CStruct *, Unk_C7387A53 *, s32, s32);
// GetElement @ 0x8004B0E8
void *GetElement(CStruct *arg0, Unk_C7387A53 *arg1, CStruct *arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 sp8;
    s32 temp_r3;
    temp_r3 = ResolveComplexID(arg1, arg2, arg3, &sp8);
    if (temp_r3 != 0) {
        GetElement_2(arg0, arg1, sp8, arg4);
    } else {
        arg0->unk0x4 = temp_r3;
        arg0->unk0x8 = temp_r3;
        arg0->unk0x0 = temp_r3;
    }
    return arg0;
}
