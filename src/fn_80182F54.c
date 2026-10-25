// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80182F54-0x80182F98 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void Mem_Free_3(s32);
void fn_80182F54(CStruct *arg0, s32 arg1) {
    Mem_Free_3(arg0->unk0x4);
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
