// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80167F80-0x8016803C (188B). Byte-identical.
// extra_cflags: -fno-schedule-insns2
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_80015A58(void *, void *, void *);
s32 fn_80015DE4(CScript *);
s32 fn_800161C4(void *);
s32 AddInteger(CStruct *, void *, void *);
extern char lbl_802FFF6C[];
bool ScriptGetMemCardSpaceAvailable(void *arg0, CScript *arg1) {
    s32 temp_r3;
    s32 temp_r30;
    s32 temp_r30_2;

    AddInteger(arg1->unk0x18, QB_SPACEAVAILABLE, 0);
    AddInteger(arg1->unk0x18, QB_FILESLEFT, 0xF4240);
    temp_r3 = fn_80015A58(*(s32 *)&lbl_802FFF6C, 0, 0);
    if (temp_r3 != 0) {
        temp_r30 = arg1->unk0x18;
        AddInteger(temp_r30, QB_SPACEAVAILABLE, fn_80015DE4(temp_r3));
        temp_r30_2 = arg1->unk0x18;
        AddInteger(temp_r30_2, QB_FILESLEFT, fn_800161C4(temp_r3));
        return true;
    }
    return false;
}
