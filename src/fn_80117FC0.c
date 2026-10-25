// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80117FC0-0x8011805C (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-expensive-optimizations
#include "types.h"
#include "structs.h"
// FLAG: -fno-expensive-optimizations
s32 fn_80128E34(s32, s32, s32, s32);
s32 fn_8000F2F8(Unk_9F352E7C *, void *);
extern char lbl_802FFE98[];
s32 fn_8000F68C(Unk_B0F19D72 *, s32);
bool ScriptMemPushContext(CStruct *, CScript *pScript);
s32 fn_80128C80(s32, s32, s32, s32);
bool ScriptMemPushContext(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;
    Unk_9994C3F5 *temp_r3;

    sp8 = 0;
    if (fn_80128C80((s32)pParams, 0, &sp8, 0) != 0) {
        if (sp8 == 0) {
            temp_r3 = *(void * *)&lbl_802FFE98;
            fn_8000F2F8(temp_r3, temp_r3->unk0x11C);
        }
    } else {
        fn_80128E34(pParams, 0, &spC, 1);
        fn_8000F2F8(*(s32 *)&lbl_802FFE98, fn_8000F68C(*(s32 *)&lbl_802FFE98, spC));
    }
    return true;
}
