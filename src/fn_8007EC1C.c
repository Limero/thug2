// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007EC1C-0x8007EC7C (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void *fn_8007DF14(void *);
void fn_8009950C(void *, s32, s32);
void fn_800994C8(void *, s32, s32);
bool fn_8007EC1C(CScript *arg0, s32 arg1) {
    if (arg1 != 0) {
        fn_8009950C(fn_8007DF14((void *)arg0->unk0x18), arg0->unk0x24, arg0->unk0x20);
    } else {
        fn_800994C8(fn_8007DF14((void *)arg0->unk0x18), arg0->unk0x24, arg0->unk0x20);
    }
    return true;
}
