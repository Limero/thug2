// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FB054-0x801FB15C (264B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_800AA068(Unk_C8FEE62D * arg0);
void Script_RunScript(s32, s32, s32, s32, s32);
void fn_801FB054(Unk_31DE137E *arg0) {
    char *base;
    s32 temp_r30;

    temp_r30 = arg0->unk0x1C;
    base = temp_r30 + 0x1FC;
    if (((Unk_1D62F22E_2 *)base)->unk0x14 != 0) {
        fn_800AA068(base);
        Script_RunScript(QB_RAILEDITORX, 0, arg0->unk0xC, 0, 0);
    }
    base = temp_r30 + 0x1B4;
    if (((Unk_1D62F22E_2 *)base)->unk0x14 != 0) {
        fn_800AA068(base);
        Script_RunScript(QB_RAILEDITORTRIANGLE, 0, arg0->unk0xC, 0, 0);
    }
    base = temp_r30 + 0x1D8;
    if (((Unk_1D62F22E_2 *)base)->unk0x14 != 0) {
        fn_800AA068(base);
        Script_RunScript(QB_RAILEDITORSQUARE, 0, arg0->unk0xC, 0, 0);
    }
    base = temp_r30 + 0x190;
    if (((Unk_1D62F22E_2 *)base)->unk0x14 != 0) {
        fn_800AA068(base);
        Script_RunScript(QB_RAILEDITORCIRCLE, 0, arg0->unk0xC, 0, 0);
    }
    Script_RunScript(QB_RAILEDITOREVERYFRAME, 0, arg0->unk0xC, 0, 0);
}
