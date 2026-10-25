// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003E554-0x8003E5AC (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern char lbl_802921CC[];

s32 GetStructure_3(CStruct *, char *, s32 *, s32);
s32 GetFacePointsStruct(Unk_DB0E2BAB *, CStruct *);
void fn_8003DAA0(void *);

bool ScriptSetModelFaceTexturePoints(CStruct *arg0) {
    char buf[0x38];
    s32 sp40 = 0;

    GetStructure_3(arg0, lbl_802921CC, &sp40, 0);
    if (sp40 != 0) {
        GetFacePointsStruct((Unk_DB0E2BAB *)buf, (CStruct *)sp40);
        fn_8003DAA0(buf);
    }
    return true;
}
