// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A9BB8-0x801A9C1C (100B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern void fn_801A9B1C(void);
void fn_801A9BB8(CStruct *arg0, s32 arg1) {
    if (arg0->unk0x4 != 0) {
        fn_801A9B1C();
        if (arg0->unk0x4 != 0) {
            Mem_Free2(*((void * *)&arg0->unk0x4));
        }
        arg0->unk0x4 = 0;
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
