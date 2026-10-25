// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A25A4-0x800A2684 (224B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct {
    s32 unk0;
    u32 unk4;
    f32 unk8;
} A25A4Obj;
void *fn_800A2430(void *);
f32 fn_800A21B8(void *);
s32 fn_800A25A4(A25A4Obj *arg0, void *arg1) {
    f32 value;

    value = fn_800A21B8(fn_800A2430(arg1));
    switch (arg0->unk4) {
    case 2:
        return value < arg0->unk8;
    case 10:
        return value <= arg0->unk8;
    case 8:
        return value == arg0->unk8;
    case 4:
        return value > arg0->unk8;
    case 12:
        return value >= arg0->unk8;
    default:
        return 0;
    }
}
