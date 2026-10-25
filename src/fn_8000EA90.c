// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000EA90-0x8000EAF4 (100B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_8000E9F4(void);
void fn_8000EA90(CStruct *arg0, s32 arg1) {
    if ((s32) arg0->unk0x4 != 0) {
        fn_8000E9F4();
        if ((s32) arg0->unk0x4 != 0) {
            Mem_Free2(*((void * *)&arg0->unk0x4));
        }
        arg0->unk0x4 = 0;
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
