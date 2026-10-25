// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000DBFC-0x8000DC80 (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_802FFE98[];
void fn_8000F2F8(Unk_9F352E7C *, s32);
void fn_8000D478(void *, void *, s32, s32, void *);
void fn_8000F320(Unk_F12C5E01 *);
void fn_8000DBFC(void *arg0, void *arg1, s32 arg2, s32 arg3, Unk_9994C3F5 *arg4) {
    Unk_9994C3F5 *temp_r3;

    if (arg4 != 0) {
        temp_r3 = *(Unk_9994C3F5 **)&lbl_802FFE98;
        fn_8000F2F8((Unk_9F352E7C *)temp_r3, temp_r3->unk0x11C);
    } else {
        temp_r3 = *(Unk_9994C3F5 **)&lbl_802FFE98;
        fn_8000F2F8((Unk_9F352E7C *)temp_r3, temp_r3->unk0x118);
    }
    fn_8000D478(arg0, arg1, arg2, arg3, arg4);
    fn_8000F320((Unk_F12C5E01 *)(*(void **)&lbl_802FFE98));
}
