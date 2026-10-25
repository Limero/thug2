// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80192C8C-0x80192CD0 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void fn_8018CAD0(Unk_C7387A53 *);
bool fn_80192C8C(Unk_C7387A53 *arg0) {
    if (((arg0->unk0x70 & 0x80000) == 0) && (arg0->unk0x54 <= 0)) {
        fn_8018CAD0((s32)arg0);
        return true;
    }
    return false;
}
