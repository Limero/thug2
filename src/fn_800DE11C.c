// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DE11C-0x800DE1A4 (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(Unk_6A70655D *, void *);
void fn_800A7938(Unk_C7387A53 *, s32);
void *Mem_NewZero(s32);
void *fn_800A7910(Unk_C7387A53 *);
void fn_800A7A98(Unk_E7B97107 *, CStruct *);
void fn_800DE11C(Unk_31DE137E *arg0) {
    void *temp_r29;
    Unk_C7387A53 *temp_r9;
    void *temp_r3;

    temp_r29 = GetChecksum_3(arg0->unk0xC, QB_NODEARRAY);
    if ((s32) arg0->unk0x1C != 0) {
        fn_800A7938((Unk_C7387A53 *)arg0->unk0x1C, 3);
    }
    temp_r3 = fn_800A7910((Unk_C7387A53 *)Mem_NewZero(0x58));
    arg0->unk0x1C = (s32)temp_r3;
    temp_r9 = ((CScript *)temp_r29)->unk0x18;
    fn_800A7A98((Unk_E7B97107 *)temp_r3, ((s32 (*)(void *))temp_r9->unk0x74)(temp_r29 + *(s16 *)((char *)temp_r9 + 0x70)));
}
