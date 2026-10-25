// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D6514-0x800D6544 (48B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_800D6514(CScript *arg0) {
    Unk_31DE137E *p;
    if (!(arg0->unk0x1C & 0x10))
        return 0;
    p = *((s32 * *)&arg0->unk0x204);
    if (p == NULL)
        return 0;
    return p->unk0x60;
}
