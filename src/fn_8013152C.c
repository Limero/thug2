// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013152C-0x8013157C (80B). Byte-identical.
#include "types.h"
#include "structs.h"
void *fn_8012ED7C(CStruct *);
void *fn_8013152C(s32 arg0) {
    Unk_FFAD6788 *r;
    for (r = fn_8012ED7C(0); r != 0; r = fn_8012ED7C(r))
        if (r->unk0xB0 == arg0)
            return r;
    return 0;
}
