// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80173C5C-0x80173CFC (160B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_803A2E34[];
s32 fn_80131154(s32, CStruct *, Unk_9994C3F5 *, s32);
s32 fn_80173C5C(s32 arg0, s32 arg1, f32 farg0, f32 farg1, f32 farg2) {
    volatile double _dummy;
    f32 *curp;
    f32 cur;
    f32 mn;
    f32 step;
    f32 scale;
    f32 maxv;
    s32 ret;

    ret = arg1;
    scale = farg2;
    maxv = 0.01f;
    if (farg0 > maxv && farg0 <= farg1) {
        curp = (f32 *)&lbl_803A2E34;
        if (farg0 < *curp) {
            ret = fn_80131154(arg1, 0, 0, 0);
            cur = *curp;
            mn = 0.2f;
            step = cur / scale;
            if (step < mn) {
                step = mn;
            }
            *curp = cur - step;
        }
    } else {
        *(f32 *)&lbl_803A2E34 = farg1;
    }
    return ret;
}
