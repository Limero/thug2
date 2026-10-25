// range 0x8005EE50-0x8005EE70 (0x20). Byte-identical.
// Identification: float-vector zero-init — stores the shared 0.0f pool
// constant (lbl_80293C74) into +0x0/+0x4/+0x8/+0xc, returning the object.
//
// Matching key: `return self` for the mr r11,r3 base copy, and the float
// store order is the recipe-249 rotation — source [0,4,8,0xc] emits want's
// [0xc,0,4,8] (brute-forced among the 4! float-store orders).
#include "types.h"
#include "structs.h"
void *fn_8005EE50(CStruct *r) {
    *((f32 *)&r->unk0x0) = 0.0f;
    *((f32 *)&r->unk0x4) = 0.0f;
    *((f32 *)&r->unk0x8) = 0.0f;
    *((f32 *)&r->unk0xC) = 0.0f;
    return r;
}