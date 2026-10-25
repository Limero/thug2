// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80009264-0x800092B0 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_80009370(void);
extern s32 lbl_802FFA34;
void *fn_80009264(CStruct *arg0) {
    s32 id;
    arg0->unk0x8 = 0;
    fn_80009370();
    id = lbl_802FFA34;
    arg0->unk0x4 = id;
    lbl_802FFA34 = id + 1;
    return arg0;
}
