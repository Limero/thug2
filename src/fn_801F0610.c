// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F0610-0x801F0734 (292B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct T_801F0610 {
    char pad0x00[0xC];
    CScript *unk0xC;
    char pad0x10[0xC];
    s32 unk0x1C;
    char pad0x20[0x4];
    CStruct *unk0x24;
} T_801F0610;

extern f32 lbl_802ADE90;
CStruct *GetStructure(s32, s32);
void fn_80141834(CScript *, s32, CStruct *);

f32 fn_801F0610(T_801F0610 *arg0, s32 arg1) {
    if (arg0->unk0x24 != NULL) {
        fn_80141834(arg0->unk0xC, arg1, arg0->unk0x24);
    } else {
        switch ((u32)arg0->unk0x1C) {
        case QB_MANUAL:
        case QB_NOSEMANUAL:
            fn_80141834(arg0->unk0xC, arg1, GetStructure(QB_MANUALPARAMS, 0));
            break;
        case QB_GRIND:
        case QB_SLIDE:
            fn_80141834(arg0->unk0xC, arg1, GetStructure(QB_GRINDPARAMS, 0));
            break;
        case QB_LIP:
            fn_80141834(arg0->unk0xC, arg1, GetStructure(QB_LIPPARAMS, 0));
            break;
        case QB_SKITCH:
            fn_80141834(arg0->unk0xC, arg1, GetStructure(QB_SKITCHPARAMS, 0));
            break;
        default:
            return lbl_802ADE90;
        }
    }
}
