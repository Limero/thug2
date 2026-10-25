// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80014F70-0x80014FCC (92B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_800132A4(void);
void fn_80014F70(Unk_C7387A53 *arg0, s32 arg1) {
    void *temp_r29;
    void *temp_r30;
    CStruct *temp_r30_2;

    temp_r30 = *((void * *)&arg0->unk0x3C);
    temp_r30_2 = temp_r30 + 0x78;
    temp_r29 = (char *)arg0 + *((s16 *)&((Unk_E1102E39 *)temp_r30)->unk0x78);
    ((void (*)(void *, s32, s32, s32))*((void * *)&temp_r30_2->unk0x4))(temp_r29, arg1, 1, fn_800132A4());
}
