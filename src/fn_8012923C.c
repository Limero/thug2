// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012923C-0x80129260 (36B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8012923C(CStruct *o, s32 i, s32 v) {
    if (o->unk0x4 == 1)
        o->unk0x8 = v;
    else
        ((s32 *)o->unk0x8)[i] = v;
}
