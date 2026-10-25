// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D94E4-0x800D955C (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_800086B0(Unk_C7387A53 *, Unk_DB0E2BAB *, f32);
void fn_800D94E4(Unk_1536F9AE *arg0) {
    f32 temp_f11;
    f32 temp_f1;
    f32 var_f1;
    temp_f11 = *((f32 *)&arg0->unk0x1DC);
    temp_f1 = arg0->unk0x1E0 + arg0->unk0x1F8;
    arg0->unk0x1E0 = temp_f1;
    if (temp_f11 == 0.0f || temp_f1 >= temp_f11) {
        var_f1 = 1.0f;
        arg0->unk0x1C &= ~0x20;
    } else {
        var_f1 = temp_f1 / temp_f11;
    }
    fn_800086B0(*((void * *)&arg0->unk0x1E4), (void *)(arg0->unk0xC + 0x78), var_f1);
}
