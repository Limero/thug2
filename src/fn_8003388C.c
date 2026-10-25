// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003388C-0x80033904 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
f32 fn_8002DB10(s32);
void fn_800331F8(void *, f32, f32);
s32 fn_8006FB50(s32, s32);
void fn_8003388C(Unk_C8FEE62D *arg0) {
    volatile double _dummy;
    f32 temp_f31;
    void *temp_r9;

    temp_r9 = *((void * *)&arg0->unk0x4);
    temp_f31 = *(f32 *)((char *)temp_r9 + 0x20);
    *(f32 *)((char *)*((void * *)&arg0->unk0x4) + 0x20) = fn_8002DB10((s32)temp_r9 + 4);
    fn_800331F8(*((void * *)&arg0->unk0x4), temp_f31, *(f32 *)((char *)*((void * *)&arg0->unk0x4) + 0x20));
    if (*(f32 *)((char *)*((void * *)&arg0->unk0x4) + 0x20) < temp_f31) {
        arg0->unk0x1C = fn_8006FB50(arg0->unk0x20, 0);
    }
}
