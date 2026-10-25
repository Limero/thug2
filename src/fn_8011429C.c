// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011429C-0x801142E8 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
extern Unk_9994C3F5 * lbl_80366474;
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_8005CF80(Unk_9994C3F5 *, s32);
void fn_8009DBB0(void);

bool ScriptSetCaptureDestTexture(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    if (GetChecksum_2(pParams, 0, &sp8, 0) != 0) {
        fn_8005CF80(lbl_80366474, sp8);
        fn_8009DBB0();
    }
    return true;
}
