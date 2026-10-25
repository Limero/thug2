// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021FCF8-0x8021FDF0 (248B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

// zone arity audit (prologue-read): fn_8019880C/fn_80198854/fn_80198F7C/fn_8019849C all 1-arg;
// fn_80198F7C = getter *(r3+0x1f0). Own sig takes a DEAD s32 (§6t-3 dead-arg proto):
// callers elsewhere set r3 before bl; body never reads arg0.
extern s32 lbl_80305EC0;
extern s32 fn_8019880C(s32);
extern s32 fn_80198854(CStruct *);
extern s32 fn_80198F7C(s32);
extern s32 fn_8019849C(s32);

bool fn_8021FCF8(s32 arg0) {
    s32 mgr = lbl_80305EC0;

    if (!((fn_8019880C(mgr) != 0) || (fn_80198854(mgr) != 0) ||
          (fn_80198F7C(mgr) == QB_NETFIREFIGHT) || (fn_80198F7C(mgr) == QB_NETGOALATTACK) ||
          (fn_80198F7C(mgr) == QB_NETCTF) || (fn_80198F7C(mgr) == QB_NETSCAVENGERHUNT))) {
        return false;
    }
    if (!((fn_8019849C(mgr) == 0) || (fn_80198F7C(mgr) == QB_NETFIREFIGHT) ||
          (fn_80198F7C(mgr) == QB_NETELIMISKATE))) {
        return false;
    }
    return true;
}
