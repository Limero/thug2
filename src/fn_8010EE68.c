// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010EE68-0x8010EEA8 (64B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 AddChecksum(CStruct *, s32, s32);

bool ScriptGetTriggerNodeName(void *arg0, Unk_9F352E7C *arg1) {
    s32 temp_r5;

    temp_r5 = arg1->unk0xB8;
    if (temp_r5 != 0) {
        AddChecksum(arg1->unk0x18, QB_NODENAME, temp_r5);
        return true;
    }
    return false;
}
