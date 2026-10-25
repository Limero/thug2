// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021F6D4-0x8021F748 (116B). Byte-identical.
#include "types.h"
extern s32 lbl_80305EAC;
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_8009CF2C(CStruct * arg0);
extern s32 fn_8021E024(void * arg0);
extern s32 fn_8017480C(Unk_FFAD6788 * arg0);
extern s32 fn_8013FF5C(s32 arg0, s32 arg1);
extern s32 fn_80128E34(CStruct * arg0, void * arg1, void *arg2, s32 arg3);

s32 fn_8021F6D4(CStruct *arg0) {
    s32 sp8;
    s32 mgr;
    s32 t;

    mgr = lbl_80305EAC;
    if (fn_8009CF2C(arg0) != 0) {
        t = fn_8021E024(arg0);
    } else {
        t = fn_8017480C(mgr);
    }
    fn_80128E34(fn_8013FF5C(t, QB_GAME_TYPE), QB_CHECKSUM, &sp8, 1);
    return sp8;
}
