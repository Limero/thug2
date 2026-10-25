// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A807C-0x800A80D8 (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_800A7DBC(CStruct *);
void fn_800A807C(CStruct *arg0) {
    s32 i;
    for (i = 0; i < (s32) arg0->unk0xC; i++) {
        fn_800A7DBC((CStruct *)(arg0->unk0x0 + i * 8));
    }
}
