// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80153BB0-0x80153C3C (140B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EAC;
extern s32 lbl_80305F9C;
s32 ScriptIsObserving(s32, s32);

bool ScriptSkatersAreReady(CStruct *pParams, CScript *pScript) {
    Unk_C7387A53 *var_r10;
    Unk_C7387A53 *var_r9;
    CStruct *p;
    s32 n;

    var_r10 = (void *)lbl_80305F9C;
    var_r9 = (void *)lbl_80305EAC;
    if (var_r10->unk0x1B4 != 0) {
        p = (void *)var_r9->unk0x38;
        n = 0;
        goto check;
        do {
            p = (void *)p->unk0xC;
            n += 1;
        check:;
            if (p->unk0x4 == -1) {
                p = NULL;
            }
        } while (p != NULL);
        if ((n != 0) || (ScriptIsObserving(0, 0) != 0)) {
            return true;
        }
    }
    return false;
}
