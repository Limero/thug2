// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011405C-0x80114114 (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
#include "mem.h"
extern f32 lbl_8029D11C;

s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 fn_801195DC(void);
s32 fn_8011C97C(s32, CStruct *, s32, f32);
s32 fn_80119640(void *, s32);

s32 ScriptStartPreLoadedStream(CStruct *pParams, CScript *pScript) {
    volatile s32 sp8;
    volatile f32 spC;
    volatile double _pad;
    f32 temp_f31;
    s32 temp_r31;
    CStruct *temp_r3;

    GetChecksum_2(pParams, QB_STREAMID, &sp8, 1);
    temp_f31 = lbl_8029D11C;
    spC = temp_f31;
    GetFloat(pParams, QB_VOLUME, &spC, 0);
    Mem_Alloc2(0x18);
    temp_r3 = (void *)fn_801195DC();
    *((f32 *)&temp_r3->unk0x0) = spC;
    *((f32 *)&temp_r3->unk0x4) = spC;
    temp_r31 = fn_8011C97C(sp8, temp_r3, 0, temp_f31);
    if (temp_r3 != NULL)
        fn_80119640(temp_r3, 3);
    return temp_r31;
}