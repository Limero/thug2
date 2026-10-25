// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A2F2C-0x801A2FE4 (184B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void *fn_801A275C(Unk_31DE137E * arg0, s32 arg1);
extern void *fn_801A26E0(Unk_31DE137E * arg0, s32 arg1);
extern s32 fn_801A2C10(Unk_31DE137E * arg0, s32 arg1);
bool fn_801A2F2C(Unk_31DE137E *arg0, s32 arg1) {
    void *temp_r31;
    Unk_F5317C5D *temp_r9;

    temp_r31 = fn_801A275C(arg0, arg1);
    if (temp_r31 != NULL) {
        if (temp_r31 == fn_801A26E0(arg0, 0)) {
            fn_801A2C10(arg0, 0);
            return true;
        }
        *(s32 *)(((Unk_C8FEE62D *)temp_r31)->unk0x10 + (s32)0xC) = ((Unk_C8FEE62D *)temp_r31)->unk0xC;
        *(s32 *)(((Unk_C8FEE62D *)temp_r31)->unk0xC + (s32)0x10) = ((Unk_C8FEE62D *)temp_r31)->unk0x10;
        ((Unk_C8FEE62D *)temp_r31)->unk0xC = (s32)temp_r31;
        ((Unk_C8FEE62D *)temp_r31)->unk0x10 = (s32)temp_r31;
        if (temp_r31 != NULL) {
            temp_r9 = ((Unk_C8FEE62D *)temp_r31)->unk0x14;
            ((s32 (*)(void *, s32))temp_r9->unk0xC)(temp_r31 + temp_r9->unk0x8, 3);
        }
        return true;
    }
    return false;
}
