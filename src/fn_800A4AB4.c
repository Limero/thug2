// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A4AB4-0x800A4B40 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// ID: ScriptNotifyEntryArray — iterates the 0x14-stride child array
// (arg0->0x0, count arg0->0x4) and calls fn_800A5B64(global lbl_80301A78,
// entry->0x0, arg1) for every live entry whose 0x4 flag is neither 0 nor
// 0xC377C572. Match recipe: for-form rotation (doc-47) with the single
// walker init'd in the for-init, count reloaded per evaluation, and the
// entry->0x0 test load kept in a named local so it rides into the call.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80301A78[];
void fn_800A5B64(CStruct *, s32, s32);
void fn_800A4AB4(CStruct *arg0, s32 arg1) {
    s32 i;
    CStruct *entry;

    for (i = 0, entry = (CStruct *)arg0->unk0x0; i < (s32) arg0->unk0x4;
         i++, entry = (CStruct *)((char *)entry + 0x14)) {
        s32 id;
        s32 flg;
        id = entry->unk0x0;
        if (id != 0) {
            flg = entry->unk0x4;
            if ((flg != 0) && (flg != -QB_UNKNOWN_0x3C883A8E)) {
                fn_800A5B64((CStruct *)*(s32 *)&lbl_80301A78, id, arg1);
            }
        }
    }
}
