// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80018570-0x8001867C (268B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_80300144[];
extern char lbl_80302E84[];
extern char lbl_80302EA4[];
extern char lbl_80302EC4[];
extern char DefaultTexData[];
extern char lbl_8031FB28[];
extern char lbl_80300150[];
extern u8 lbl_8031E7D9;
extern u8 lbl_8031E7DA;
void OSResumeThread(s32);
// VIPostCallback @ 0x80018570
void VIPostCallback(void) {
    s32 (*temp_r0)();
    s32 temp_r9;
    s32 var_r29;
    void *var_r31;

    if (((s32) lbl_8031E7D9 != 0) && ((s32) lbl_8031E7DA != 0)) {
        SetNextBreakPt();
        lbl_8031E7D9 = 0;
        lbl_8031E7DA = 0;
    }
    hwPadRead();
    if (((s32) *(s32 *)&lbl_80300150 == 1) && (OSGetResetButtonState() == 0)) {
        *(s32 *)&lbl_80300150 = 2;
    }
    temp_r0 = *(s32 (**)())lbl_80300144;
    if (temp_r0 != NULL) {
        ((s32 (*)())temp_r0)();
    }
    Tmr_IncrementVblankCounters();
    var_r31 = NULL;
    OSResumeThread((s32)lbl_8031FB28);
    var_r29 = 8;
    do {
        if (*(s32 *)((char *)var_r31 + (s32)DefaultTexData) == 0) {
            ((s32 (*)(void *, void *))*(s32 *)((char *)var_r31 + (s32)lbl_80302E84))(*(s32 *)((char *)var_r31 + (s32)lbl_80302EA4), *(s32 *)((char *)var_r31 + (s32)lbl_80302EC4));
        }
        temp_r9 = *(s32 *)((char *)var_r31 + (s32)DefaultTexData);
        if (temp_r9 >= 0) {
            *(s32 *)((char *)var_r31 + (s32)DefaultTexData) = (s32) (temp_r9 - 1);
        }
        var_r31 += 4;
        var_r29 -= 1;
    } while (var_r29 != 0);
}
