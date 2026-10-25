// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80204250-0x80204294 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802AEF88[];
void fn_8009F558(void *arg0);

void fn_80204250(CScript *arg0) {
    s32 index = arg0->unk0x20;
    s32 base = arg0->unk0x1C;
    s32 *entry = (s32 *)((char *)base + index * 0x18);
    arg0->unk0x18 = (s32)lbl_802AEF88;
    entry[0x1EC / 4] = 0;
    fn_8009F558(arg0);
}
