// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021A18C-0x8021A290 (260B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EC0;
s32 fn_80220484(Unk_C7387A53 * arg0);
s32 fn_80198F7C(s32 arg0);
s32 ScriptInSplitScreenGame(s32 arg0, s32 arg1);
s32 fn_80140068(s32 arg0, void * arg1, void * arg2);
bool fn_8021A18C(Unk_C7387A53 *arg0) {
    if ((fn_80220484(arg0) == 0) && (fn_80198F7C(lbl_80305EC0) != QB_FREESKATE) && (fn_80198F7C(lbl_80305EC0) != QB_HORSE)) {
        ;
    } else if (fn_80198F7C(lbl_80305EC0) != QB_NETLOBBY) {
        return false;
    }
    if (ScriptInSplitScreenGame(0, 0) != 0) {
        return true;
    }
    if (fn_80140068((char *)arg0 + 0x110, QB_PLAYER_COLLISION, QB_CHECKSUM) == QB_BOOLEAN_TRUE) {
        return true;
    }
    if (fn_80198F7C(lbl_80305EC0) == QB_NETSLAP) {
        return true;
    }
    if (fn_80198F7C(lbl_80305EC0) != QB_SLAP) {
        return false;
    }
    __asm__ __volatile__("");
    return true;
}
