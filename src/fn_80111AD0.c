// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80111AD0-0x80111BE0 (272B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_8029D030;
extern f32 lbl_8029D034;
s32 fn_80128CE0(CStruct *, void *, void *, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void *fn_80054EE8(s32);
void *fn_80054E94(void);
void fn_801118C8(Unk_FFAD6788 *, f32, f32, s32);
bool ScriptCompressVC(CStruct *pParams, CScript *pScript) {
    struct {
        f32 sp8;
        f32 spC;
        s32 sp10;
        char pad[12];
    } loc;
    void *temp_r9;
    void *var_r30;
    CStruct *var_r3;
    Unk_FFAD6788 *var_r3b;
    f32 var_f31;

    var_f31 = lbl_8029D030;
    loc.sp8 = var_f31;
    fn_80128CE0(pParams, QB_TARGET, &loc.sp8, 1);
    loc.spC = var_f31;
    GetFloat(pParams, QB_PERCENT, &loc.spC, 0);
    loc.sp10 = 0;
    loc.spC = (lbl_8029D034 - loc.spC) / lbl_8029D034;
    var_r3 = fn_80054EE8(GetChecksum_2(pParams, QB_LIGHTGROUP, &loc.sp10, 0));
    if (var_r3 != NULL) {
        do {
            register void *temp_r9 __asm__("r9");
            s32 temp_r0;
            temp_r9 = *((void * *)&var_r3->unk0xC);
            temp_r0 = ((CStruct *)temp_r9)->unk0x4;
            var_r30 = temp_r9;
            if (temp_r0 == -1) {
                var_r30 = NULL;
            }
            var_r3b = *((void * *)&var_r3->unk0x4);
            if (var_r3b->unk0x8C == 0) {
                fn_801118C8(var_r3b, loc.sp8, loc.spC, loc.sp10);
            }
            var_r3 = var_r30;
        } while (var_r3 != NULL);
    }
    var_r3 = fn_80054E94();
    if (var_r3 != NULL) {
        fn_801118C8(var_r3, loc.sp8, loc.spC, loc.sp10);
    }
    return true;
}
