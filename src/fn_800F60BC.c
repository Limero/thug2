// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F60BC-0x800F615C (160B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void fn_800F3708(Unk_C7387A53 *);
extern void fn_8005D734(CStruct *);
extern void Mem_Free_3(s32);
void fn_800F60BC(Unk_C7387A53 *arg0) {
    Unk_07FDFB02 *temp_r9;

    temp_r9 = *((void * *)&arg0->unk0x50);
    if (temp_r9->unk0x14((char *)arg0 + temp_r9->unk0x10) != 0) {
        temp_r9 = *((void * *)&arg0->unk0x50);
        fn_8005D734((void *)temp_r9->unk0x14((char *)arg0 + temp_r9->unk0x10));
        if (arg0->unk0x24 != 0) {
            Mem_Free_3(arg0->unk0x24);
            arg0->unk0x24 = 0;
        }
        temp_r9 = *((void * *)&arg0->unk0x50);
        ((s32 (*)(void *, s32))(*((void * *)&temp_r9->unk0x5C)))((char *)arg0 + temp_r9->unk0x58, 0);
    }
    fn_800F3708(arg0);
}
