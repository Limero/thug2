// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8014F1FC-0x8014F338 (316B). Byte-identical.
#include "types.h"
#include "structs.h"
extern f32 lbl_802A7C34;
extern f32 lbl_802A7C38;
extern f32 lbl_802A7C3C;
extern f32 lbl_802A7C40;
extern char lbl_802A7C1C[];
extern char lbl_802A7C24[];
extern char lbl_802A7C28[];
extern char lbl_802A7C2C[];
extern char lbl_802A7C30[];
extern s32 lbl_80305E98;
s32 fn_8012834C(CStruct *, void *, void *, s32);
void *fn_80054EE8(void);
s32 GetChecksum_4(CStruct *, void *, void *, s32);
s32 fn_8014E440(void *, f32, f32, f32, f32, s32);

bool ScriptCenterCamera(CStruct *pParams, CScript *pScript) {
    s32 sp18;
    f32 sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    s32 temp_r0;
    register void *temp_r9 __asm__("r9");
    void *var_r31;
    CStruct *var_r3;

    if (lbl_80305E98 == 0) {
        return false;
    }
    sp8 = lbl_802A7C34;
    fn_8012834C(pParams, (void *)lbl_802A7C1C, &sp8, 0);
    spC = lbl_802A7C38;
    fn_8012834C(pParams, (void *)lbl_802A7C24, &spC, 0);
    sp10 = lbl_802A7C3C;
    fn_8012834C(pParams, (void *)lbl_802A7C28, &sp10, 0);
    sp14 = lbl_802A7C40;
    fn_8012834C(pParams, (void *)lbl_802A7C2C, &sp14, 0);
    sp18 = 0;
    GetChecksum_4(pParams, (s32)lbl_802A7C30, &sp18, 0);
    var_r3 = fn_80054EE8();
    if (var_r3 != NULL) {
        do {
            temp_r9 = *((void * *)&var_r3->unk0xC);
            temp_r0 = ((CStruct *)temp_r9)->unk0x4;
            var_r31 = temp_r9;
            __asm__("" : "+r"(temp_r9));
            if (temp_r0 == -1) {
                var_r31 = NULL;
            }
            fn_8014E440(var_r3->unk0x4, sp8, spC, sp10, sp14, sp18);
            var_r3 = var_r31;
        } while (var_r3 != NULL);
    }
    return true;
}
