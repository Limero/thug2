// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022B1B0-0x8022B214 (100B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 lbl_80305F9C;
extern void AddInteger(CStruct * arg0, u32 arg1, s32 arg2);

bool ScriptNumServersInLobby(s32 arg0, CScript *arg1) {
    s32 v;
    Unk_B5F1D693 *tbl;
    s32 count;
    CStruct *node;

    v = arg1->unk0x18;
    tbl = lbl_80305F9C;
    count = 0;
    node = tbl->unk0x184;
    goto check;
    do {
        count++;
        node = *((void * *)&node->unk0xC);
check:
        if (node->unk0x4 == -1) {
            node = NULL;
        }
    } while (node != NULL);
    AddInteger(v, QB_NUM_SERVERS, count);
    return true;
}
