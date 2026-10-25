// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A229C-0x800A234C (176B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_800A21C8(Unk_6A78CE27 *, s32);
s32 fn_800A15DC(void *, s32, s32);
s32 fn_800A21C0(Unk_6A78CE27 *);
void AddInteger(CStruct *, s32, s32);
s32 fn_800A229C(s32 arg0, s32 arg1, CStruct *arg2, CScript *arg3) {
    s32 sp8;
    s32 temp_r30;

    switch (arg1) {
    case QB_OBJ_GETPRIORITY:
        temp_r30 = arg3->unk0x18;
        AddInteger(temp_r30, QB_OBJPRIORITY, fn_800A21C0(arg0 + 0x120));
        break;
    case QB_OBJ_SETPRIORITY:
        sp8 = 0;
        GetInteger(arg2, 0, &sp8, 1);
        fn_800A21C8(arg0 + 0x120, *(u8 *) ((char *) &sp8 + 0x3));
        break;
    default:
        return fn_800A15DC(arg0, arg1, arg2);
    }
    return 1;
}

