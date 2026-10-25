// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801813F0-0x8018148C (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EC0;
extern s32 lbl_80305F1C;
extern s32 lbl_80305F9C;
s32 fn_80219698(CStruct *);
s32 Script_GetInteger(s32, s32);
s32 IsTrue(s32, s32);
s32 fn_801A95C0(s32, s32);
typedef struct {
    char _0[0xC];
    s16 unk0xC;
    s16 unk0xE;
    s32 unk0x10;
} S813F0;

s32 fn_801813F0(S813F0 *arg0) {
    register s32 t30 __asm__("r30");
    s32 v;

    if (fn_80219698((CStruct *)lbl_80305F9C) != 0) {
        t30 = lbl_80305EC0;
        v = Script_GetInteger(QB_DEBUG_GRAFFITI, 0) != 0;
        if ((v != 0) || (IsTrue(t30, QB_SHOULD_MODULATE_COLOR) != 0)) {
            return fn_801A95C0(lbl_80305F1C, arg0->unk0xC);
        }
    }
    return arg0->unk0x10;
}
