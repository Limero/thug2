// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A871C-0x801A8794 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_802AB998[];
extern char lbl_802FFE98[];
s32 fn_801A9AA0(void *, s32);
void fn_8000F2F8(void *, s32);
void CStruct_new(s32);
s32 CStruct_ctor(void);
void fn_8000F320(void *);
void *fn_801A871C(Unk_C7387A53 *arg0) {
    Unk_C7387A53 *temp_r3;

    arg0->unk0x3C = (s32)lbl_802AB998;
    fn_801A9AA0((char *)arg0 + 8, 8);
    fn_801A9AA0((char *)arg0 + 0x20, 8);
    temp_r3 = *(Unk_C7387A53 **)&lbl_802FFE98;
    fn_8000F2F8(temp_r3, temp_r3->unk0x12C);
    CStruct_new(8);
    arg0->unk0x38 = CStruct_ctor();
    fn_8000F320(*(void **)&lbl_802FFE98);
    return arg0;
}
