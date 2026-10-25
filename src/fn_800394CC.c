// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800394CC-0x8003951C (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_800394CC(CStruct *arg0, f32 farg0) {
    if (arg0->unk0x8 != 0) {
        char *p0 = *((char * *)&arg0->unk0x8);
        u32 count = *((u32 *)&arg0->unk0x10);
        u32 i;
        for (i = 0; i <= count; i++) {
            f32 *arr = (f32 *)(p0 + 0x508);
            if (farg0 < arr[i]) {
                arg0->unk0xC = i;
                return;
            }
        }
    }
    arg0->unk0xC = arg0->unk0x10;
}
