// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A7978-0x800A79D4 (92B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_800A7978(CStruct *arg0) {
    void *temp_r30;
    CScript *temp_r9;

    if ( arg0->unk0x4 != NULL) {
        do {
            temp_r9 = arg0->unk0x4;
            temp_r30 = temp_r9->unk0x18;
            Mem_Free(temp_r9);
            arg0->unk0x4 = temp_r30;
        } while (temp_r30 != NULL);
    }
    arg0->unk0x8 = 0;
    arg0->unk0x50 = 0;
}
