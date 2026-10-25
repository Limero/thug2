// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F56CC-0x800F573C (112B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void fn_80012948(s32);
extern void Mem_Free_3(s32);
void fn_800F56CC(Unk_A9157FE7 *arg0) {
    if (arg0->unk0x60 != 0) {
        Mem_Free_3(arg0->unk0x60);
        arg0->unk0x60 = 0;
    }
    if (arg0->unk0x54 != 0) {
        fn_80012948(arg0->unk0x54);
    } else if (arg0->unk0x24 != 0) {
        Mem_Free_3(arg0->unk0x24);
    }
    arg0->unk0x54 = 0;
    arg0->unk0x24 = 0;
}
