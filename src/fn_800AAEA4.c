// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AAEA4-0x800AAF30 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "types.h"
void fn_800AACC0(void *, void *);
void fn_800AAF30(void *, void *);
void Script_RunScript(void *, void *, void *, void *, void *);
#include "qb_constants.h"
#include "structs.h"
s32 fn_8009FCD8(s32, s32);
extern char lbl_80301A38[];
s32 fn_800A1A84(Unk_C7387A53 *);
s32 ContainsFlag(CStruct *, s32);
void fn_800AAEA4(CStruct *arg0) {
    s32 temp_r30;

    if (ContainsFlag(arg0, QB_BOUNCY) != 0) {
        temp_r30 = fn_800A1A84(*(s32 *)&lbl_80301A38);
        fn_8009FCD8(temp_r30, arg0);
        Script_RunScript(QB_BOUNCYOBJ_ADD_COMPONENTS, arg0, temp_r30, 0, 0);
        fn_800AAF30(temp_r30, arg0);
        return;
    }
    fn_800AACC0(arg0, 1);
}