// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801136AC-0x8011372C (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 GetArray(CStruct *, s32, s32 *, s32);
void fn_8011A12C(s32, s32);
s32 fn_801293FC(CStruct *, s32);
extern s32 lbl_80302C34;
bool ScriptAddSoundBanks(CStruct *pParams, CScript *pScript) {
    void *volatile sp8;
    register CStruct *p __asm__("r9");
    s32 temp_r30;
    u32 var_r31;

    if (GetArray(pParams, 0, (s32 *)&sp8, 0) != 0) {
        p = (CStruct *)sp8;
        __asm__ volatile("" : "+r"(p));
        var_r31 = 0;
        temp_r30 = lbl_80302C34;
        goto bottom;
    loop_3:
        fn_8011A12C(temp_r30, fn_801293FC((CStruct *)sp8, var_r31++) << 0xA);
        p = (CStruct *)sp8;
    bottom:
        if (var_r31 < p->unk0x4) {
            goto loop_3;
        }
    }
    return true;
}
