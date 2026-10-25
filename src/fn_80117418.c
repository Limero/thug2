// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80117418-0x80117470 (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

void *fn_80125480(s32);
void GetChecksum_2(CStruct *, s32, s32 *, s32);

typedef struct Node { char pad0[2]; u8 unk2; } Node;

bool ScriptExists(CStruct *pParams, CScript *pScript) {
    s32 sp8 = 0;
    Node *n;

    GetChecksum_2(pParams, 0, &sp8, 0);
    n = fn_80125480(sp8);
    if (n != NULL && n->unk2 == 7) {
        return true;
    }
    return false;
}
