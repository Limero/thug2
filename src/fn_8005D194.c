// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005D194-0x8005D1F8 (100B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_8005D0F8(void);
void fn_8005D194(CStruct *arg0, s32 arg1) {
    if ((s32) arg0->unk0x4 != 0) {
        fn_8005D0F8();
        if ((s32) arg0->unk0x4 != 0) {
            Mem_Free2(*((void * *)&arg0->unk0x4));
        }
        arg0->unk0x4 = 0;
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
