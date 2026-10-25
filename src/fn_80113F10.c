// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80113F10-0x80114028 (280B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 lbl_80302C34;

void fn_80128E34(CStruct *arg0, void *arg1, void *arg2, s32 arg3);
f32 fn_8011D4EC(void);
f32 fn_8011A8FC(s32 arg0);
f32 fn_8011D57C(void);
void fn_80127E70(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

// ScriptGetValueFromVolume @ 0x80113F10
bool ScriptGetValueFromVolume(CStruct *pParams, CScript *pScript) {
    u32 sp8;

    fn_80128E34(pParams, 0, &sp8, 1);
    switch (sp8) {
    case QB_SFXVOL:
        fn_80127E70(pScript->unk0x18, QB_VALUE, 1, (s32)fn_8011A8FC(lbl_80302C34) / 10);
        break;
    case QB_CDVOL:
        fn_80127E70(pScript->unk0x18, QB_VALUE, 1, (s32)fn_8011D4EC() / 10);
        break;
    case QB_UNKNOWN_0xE32F3525:
        fn_80127E70(pScript->unk0x18, QB_VALUE, 1, (s32)fn_8011D57C() / 10);
        break;
    }
    return true;
}
