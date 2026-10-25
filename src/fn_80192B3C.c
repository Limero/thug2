// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80192B3C-0x80192B9C (96B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_8018E24C(Unk_C7387A53 *);
bool fn_80192B3C(Unk_C7387A53 *arg0) {
    if ((fn_8018E24C(arg0) == QB_ELIMISKATE_INTERVAL) || (fn_8018E24C(arg0) == QB_SCAVENGER_INTERVAL)) {
        return false;
    }
    return true;
}
