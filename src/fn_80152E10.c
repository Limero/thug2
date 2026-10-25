// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80152E10-0x80152E84 (116B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80305EAC[];
extern s32 fn_80128C80(CStruct * arg0, void * arg1, void *arg2, s32 arg3);
extern void *fn_801746A4(Unk_C7387A53 * arg0, s32 arg1);
extern void fn_8009F9AC(Unk_6A70655D * arg0, s32 arg1);
bool ScriptUnPauseSkater(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    void *temp_r31;
    Unk_2C7D9FAD *vt;

    fn_80128C80(pParams, 0, &sp8, 1);
    temp_r31 = fn_801746A4(*(s32 *)&lbl_80305EAC, sp8);
    if (temp_r31 != NULL) {
        vt = *((void * *)&((Unk_9994C3F5 *)temp_r31)->unk0x8);
        ((void (*)(void *))vt->unk0x6C)(
            temp_r31 + vt->unk0x68);
        fn_8009F9AC(temp_r31, 0);
    }
    return true;
}
