// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F69BC-0x800F6A14 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void fn_80012948(s32);
extern void Mem_Free_3(s32);
void fn_800F69BC(Unk_C7387A53 *arg0) {
    if (arg0->unk0x54 != 0) {
        fn_80012948(arg0->unk0x54);
    } else if (arg0->unk0x24 != 0) {
        Mem_Free_3(arg0->unk0x24);
    }
    arg0->unk0x54 = 0;
    arg0->unk0x24 = 0;
}
