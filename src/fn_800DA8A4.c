// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DA8A4-0x800DA908 (100B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800A738C(Unk_E7B099EB *);
void fn_800A74A8(Unk_A510FB62 *, Unk_C7387A53 *, Unk_DB0E2BAB *);
void fn_800DA8A4(Unk_FD25FE4D *arg0) {
    volatile double _dummy;
    f32 temp_f31;
    Unk_C7387A53 *temp_r4;
    fn_800A738C(*((void * *)&arg0->unk0x208));
    temp_r4 = arg0->unk0xC;
    temp_f31 = *((f32 *)&temp_r4->unk0x5C);
    fn_800A74A8(*((void * *)&arg0->unk0x208), (char *)temp_r4 + 0x58, (char *)temp_r4 + 0x78);
    if (arg0->unk0x20C != 0) {
        *(f32 *)((char *)arg0->unk0xC + 0x5C) = temp_f31;
    }
}
