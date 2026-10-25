// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010EE18-0x8010EE68 (80B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 AddChecksum(CStruct *, s32, s32);

bool ScriptGetNodeName(void *arg0, Unk_EFC8CFAD *arg1) {
    CScript *temp_r5;

    temp_r5 = *((void * *)&arg1->unk0xBC);
    if ((temp_r5 != NULL) && (temp_r5->unk0x18 != 0)) {
        AddChecksum(arg1->unk0x18, QB_NODENAME, temp_r5->unk0x18);
        return true;
    }
    return false;
}
