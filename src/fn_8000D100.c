// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000D100-0x8000D150 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_8000EA90(CStruct *, s32);
void fn_8000D100(Unk_C8FEE62D *arg0, s32 arg1) {
    if ((s32) arg0->unk0x14 != 0) {
        fn_8000EA90(arg0->unk0x14, 3);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
