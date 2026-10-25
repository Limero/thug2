// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801551EC-0x801552D4 (232B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802A7F6C[];
extern char lbl_802A7F74[];
extern bool lbl_80305DF0;
extern s32 lbl_80301914;
extern s32 lbl_80301A38;
s32 Mem_NewZero(s32);
s32 fn_8016CD30(Unk_9AA07378 *);
void fn_8009CCF8(void *, CStruct *);
void fn_8009CD44(Unk_C7387A53 *, CStruct *);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void fn_80127848(CStruct *, void *, s32);
s32 fn_80125A08(s32, s32);
s32 fn_800A1AE8(s32, s32, s32, s32);
void CStruct_delete(CStruct *, s32);

bool ScriptLaunchViewer(CStruct *pParams, CScript *pScript) {
    s32 guard;
    void *temp_r31;
    register s32 temp_r30 __asm__("r30");

    guard = lbl_80305DF0;
    temp_r31 = (void *)lbl_80301914;
    if (guard != 0) {
        return true;
    }
    temp_r30 = fn_8016CD30(Mem_NewZero(0x60));
        fn_8009CCF8(temp_r31, (void *)temp_r30);
        fn_8009CD44(temp_r31, (void *)temp_r30);
        lbl_80305DF0 = 1;
        temp_r31 = (void *)CStruct_ctor(CStruct_new(8));
        fn_80127848((s32)temp_r31, (s32)lbl_802A7F6C, QB_VIEWER_CAM);
        temp_r30 = lbl_80301A38;
        temp_r30 = fn_800A1AE8(temp_r30, fn_80125A08((s32)lbl_802A7F74, 0), temp_r31, 1);
        if ((s32)temp_r31 != 0) {
            CStruct_delete((s32)temp_r31, 3);
        }
        ((Unk_C7387A53 *)temp_r30)->unk0xC |= 2;
    return true;
}
