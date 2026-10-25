// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801321B8-0x801321F4 (60B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8012F8E8(Unk_FFAD6788 *, s32, CStruct *);
void fn_801321B8(Unk_FFAD6788 *arg0) {
    s32 field;

    field = arg0->unk0xE8;
    if (field != 0) {
        arg0->unk0xE8 = 0;
        fn_8012F8E8(arg0, field, 0);
    }
}
