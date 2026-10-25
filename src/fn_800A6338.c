// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A6338-0x800A638C (84B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_800A5F38(Unk_727B8CF2 *, Unk_FFAD6788 *, void *);
s32 GetChecksum_2(CStruct *, void *, s32 *, void *);
extern char lbl_80301A78[];
bool ScriptWaitForEvent(CStruct *arg0, Unk_FFAD6788 *arg1) {
    s32 sp8;

    GetChecksum_2(arg0, QB_TYPE, &sp8, 0);
    fn_800A5F38(*(s32 *)&lbl_80301A78, arg1, sp8);
    return true;
}
