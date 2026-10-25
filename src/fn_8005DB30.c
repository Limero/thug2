// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005DB30-0x8005DB64 (52B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80293940[];
void fn_8005DB30(Unk_C8FEE62D *arg0, s32 arg1) {
    arg0->unk0x14 = (s32)lbl_80293940;
    if (arg1 & 1) {
        Mem_Free();
    }
}
