// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80155430-0x801554C4 (148B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct { s32 unk0; f32 unk4; f32 unk8; } loddist_out;

s32 fn_8016D1A8(void);
void fn_80125000(Unk_C71E6DE1 *);
s32 GetPair(s32, u32, void *, s32);
s32 fn_8016CFDC(Unk_C7387A53 *);
s32 GetChecksum_3(Unk_6A70655D *, s32);
void fn_800B484C(Unk_9D191493 *, s32, f32);

bool ScriptSetViewerLODDist(CStruct *pParams, CScript *pScript) {
    loddist_out sp8;
    s32 var_r30;
    s32 temp_r3;

    var_r30 = fn_8016D1A8();
    if (var_r30 != 0) {
        fn_80125000(&sp8);
        if (GetPair(pParams, 0, &sp8, 0) == 0) {
            return false;
        }
        temp_r3 = fn_8016CFDC(var_r30);
        if (temp_r3 != 0) {
            fn_800B484C((void *)GetChecksum_3(temp_r3, QB_MODEL), (s32)sp8.unk4, sp8.unk8);
        }
    }
    return true;
}
