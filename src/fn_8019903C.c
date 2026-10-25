// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019903C-0x80199120 (228B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
s32 fn_8019903C(s32 arg0, s32 arg1) {
    register s32 v __asm__("r3");

    v = arg1;
    if (v == QB_NETTRICKATTACK) {
        return QB_TRICKATTACK;
    } else if (v == QB_NETGRAFFITI) {
        return QB_GRAFFITI;
    } else if (v == QB_NETCOMBOMAMBO) {
        return QB_COMBOMAMBO;
    } else if (v == QB_NETSLAP) {
        return QB_SLAP;
    } else if (v == QB_NETKING) {
        return QB_KING;
    } else if (v == QB_NETFIREFIGHT) {
        return QB_FIREFIGHT;
    } else if (v == QB_NETCTF) {
        return QB_CTF;
    } else if (v == QB_NETELIMISKATE) {
        return QB_ELIMISKATE;
    }
    return v;
}
