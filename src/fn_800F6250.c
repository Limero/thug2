// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F6250-0x800F62D4 (132B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void fn_800F3708(Unk_C7387A53 *);
bool fn_800F6250(Unk_C7387A53 *arg0) {
    Unk_07FDFB02 *temp_r9;
    Unk_6849630D *temp_r3;

    temp_r9 = *((void * *)&arg0->unk0x50);
    temp_r3 = (void *)temp_r9->unk0x14((char *)arg0 + temp_r9->unk0x10);
    if (temp_r3 != NULL) {
        void *temp_r9_2 = temp_r3->unk0x34D8;
        ((s32 (*)(void *, s32))(*((void * *)&((Unk_F5317C5D *)temp_r9_2)->unk0xC)))((char *)temp_r3 + ((Unk_F5317C5D *)temp_r9_2)->unk0x8, 3);
        temp_r9 = *((void * *)&arg0->unk0x50);
        ((s32 (*)(void *, s32))(*((void * *)&temp_r9->unk0x5C)))((char *)arg0 + temp_r9->unk0x58, 0);
    }
    return false;
}
