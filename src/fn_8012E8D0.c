// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012E8D0-0x8012E928 (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8012E88C(s32);
extern char lbl_803032BC[];
extern char lbl_8039C530[];
void fn_8012E8D0(Unk_5AA7B5D7 *arg0, s32 arg1) {
    s32 idx;
    char *p;
    char *q;

    idx = *(s32 *)lbl_803032BC;
    p = lbl_8039C530;
    q = p + 4;
    *(void **)(p + (idx << 3)) = arg0;
    *(s32 *)(q + (idx << 3)) = (arg1 != 0);
    *(s32 *)lbl_803032BC = idx + 1;
    fn_8012E88C((s32)arg0);
}
