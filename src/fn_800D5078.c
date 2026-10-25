// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D5078-0x800D512C (180B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern const f32 lbl_80299B14;
extern const f32 lbl_80299B18;
extern const f32 lbl_80299B1C;
s32 GetFloat(CStruct * arg0, s32 arg1, f32 * arg2, s32 arg3);
s32 ContainsFlag(CStruct * arg0, s32 arg1);
void fn_800D5078(CStruct *arg0, f32 *arg1) {
    if (GetFloat(arg0, 0, (void *)arg1, 0) != 0) {
        if (ContainsFlag(arg0, -QB_UNKNOWN_0x552837F1) != 0) {
            *arg1 *= lbl_80299B14;
        } else if (ContainsFlag(arg0, QB_IPS) == 0) {
            *arg1 = *arg1 * lbl_80299B18 * lbl_80299B14 / lbl_80299B1C;
        }
    }
}
