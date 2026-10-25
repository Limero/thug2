// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F55D8-0x800F567C (164B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void fn_800F3708(Unk_C7387A53 *);
extern void fn_8005546C(void *, s32);
void fn_800F55D8(Unk_C7387A53 *arg0) {
    Unk_07FDFB02 *temp_r9;

    temp_r9 = *((void * *)&arg0->unk0x50);
    if (temp_r9->unk0x14((char *)arg0 + temp_r9->unk0x10) != 0) {
        temp_r9 = *((void * *)&arg0->unk0x50);
        fn_8005546C(temp_r9->unk0x14((char *)arg0 + temp_r9->unk0x10), 0);
        temp_r9 = *((void * *)&arg0->unk0x50);
        ((s32 (*)(void *, s32))(*((void * *)&temp_r9->unk0x5C)))((char *)arg0 + temp_r9->unk0x58, 0);
    }
    temp_r9 = *((void * *)&arg0->unk0x50);
    ((void (*)(void *))(temp_r9->unk0x84))((char *)arg0 + temp_r9->unk0x80);
    fn_800F3708(arg0);
}
