// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007BDC8-0x8007BE24 (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern void * lbl_803009EC;
void *fn_8007BCCC(void *, s32, s32, s32, s32);
void fn_8007BDC8(void) {
    s32 i;
    Unk_C8FEE62D *temp_r3;

    for (i = 0; i < 0xA; i++) {
        temp_r3 = (Unk_C8FEE62D *)Mem_Alloc2(0x1C);
        temp_r3 = (Unk_C8FEE62D *)fn_8007BCCC(temp_r3, 0, 0, 0x280, 0x1C0);
        temp_r3->unk0x10 =  (s32) lbl_803009EC;
        lbl_803009EC = temp_r3;
    }
}
