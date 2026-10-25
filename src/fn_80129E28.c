// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80129E28-0x80129EA0 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 Mem_Alloc_3(s32);
s32 fn_80129C08(void *, void *, void *, void *, void *);
s32 fn_8000F2F8(Unk_9F352E7C *, void *);
extern char lbl_802FFE98[];
s32 fn_8000F320(s32);
s32 Mem_Free_3(s32);
s32 fn_80129E28(void *arg0, void *arg1) {
    s32 temp_r29;
    s32 temp_r3_2;
    Unk_9994C3F5 *temp_r3;

    temp_r3 = *(void * *)&lbl_802FFE98;
    fn_8000F2F8(temp_r3, temp_r3->unk0x118);
    temp_r3_2 = Mem_Alloc_3(arg1);
    temp_r29 = fn_80129C08(arg0, temp_r3_2, arg1, 1, 0);
    Mem_Free_3(temp_r3_2);
    fn_8000F320(*(void * *)&lbl_802FFE98);
    return temp_r29;
}
