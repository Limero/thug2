// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80151784-0x801517B4 (48B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_8016D1A8(void);
extern void fn_8016CA58(Unk_C7387A53 * arg0);
bool ScriptClearViewerObject(CStruct *pParams, CScript *pScript) {
    s32 temp_r3;

    temp_r3 = fn_8016D1A8();
    if (temp_r3 != 0) {
        fn_8016CA58(temp_r3);
    }
    return true;
}
