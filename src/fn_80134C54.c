// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80134C54-0x80134CB8 (100B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern void fn_80134BB8(void);
void fn_80134C54(CStruct *arg0, s32 arg1) {
    if (arg0->unk0x4 != 0) {
        fn_80134BB8();
        if (arg0->unk0x4 != 0) {
            Mem_Free2(*((void * *)&arg0->unk0x4));
        }
        arg0->unk0x4 = 0;
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}