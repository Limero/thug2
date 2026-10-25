// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800121D8-0x80012224 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80012270(s32);
s32 *fn_80012110(Unk_C8FEE62D *);
extern s32 *lbl_802FFF08[];
void fn_800121D8(s32 arg0) {
    s32 *entry = lbl_802FFF08[arg0];
    if (entry == NULL) {
        fn_80012270(arg0);
        Mem_Alloc();
        return;
    }
    fn_80012110(entry);
}
