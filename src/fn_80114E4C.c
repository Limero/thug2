// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80114E4C-0x80114F40 (244B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Identification: ScriptGetArraySize — resolves an array property through the
// script getters and writes its size to the array-size callback.
// Suggested rename: keep ScriptGetArraySize.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 AddInteger(CStruct *, void *, void *);
s32 GetInteger(CStruct *, void *, s32 *, void *);
s32 GetArray(CStruct *, void *, s32 *, void *);
s32 fn_8012954C(CStruct *, void *);

bool ScriptGetArraySize(CStruct *pParams, CScript *pScript) {
    s32 spC;
    void *sp8;

    GetArray(pParams, 0, &sp8, 1);
    spC = 0;
    if (GetInteger(pParams, QB_INDEX1, &spC, 0) != 0) {
        sp8 = fn_8012954C(sp8, spC);
        if (GetInteger(pParams, QB_INDEX2, &spC, 0) != 0) {
            sp8 = fn_8012954C(sp8, spC);
            if (GetInteger(pParams, QB_INDEX3, &spC, 0) != 0) {
                sp8 = fn_8012954C(sp8, spC);
            }
        }
    }
    AddInteger(pScript->unk0x18, QB_ARRAY_SIZE, ((CStruct *)sp8)->unk0x4);
    return true;
}
