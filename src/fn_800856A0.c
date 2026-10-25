// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800856A0-0x8008573C (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8006F8C8(s32);
extern void* lbl_80301438;
s32 fn_8006F8DC(CStruct *arg0, s32 *arg1);
void fn_8006F998(CStruct *arg0, s32 *arg1);

void fn_800856A0(void) {
    void *sp8;
    void *temp_r30;
    CStruct *temp_r9;
    void *var_r31;
    s32 mgr_tmp;

    fn_8006F8C8(lbl_80301438);
    var_r31 = fn_8006F8DC(lbl_80301438, 0);
    if (var_r31 != NULL) {
        do {
            temp_r30 = var_r31;
            var_r31 = fn_8006F8DC(lbl_80301438, 0);
            mgr_tmp = lbl_80301438;
            sp8 = temp_r30;
            fn_8006F998(mgr_tmp, &sp8);
            if (temp_r30 != NULL) {
                temp_r9 = ((Unk_C7387A53 *)temp_r30)->unk0x28;
                ((s32 (*)(void *, s32))temp_r9->unk0xC)(temp_r30 + *(s16 *)((char *)temp_r9 + 8), 3);
            }
        } while (var_r31 != NULL);
    }
}
