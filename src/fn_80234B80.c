// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80234B80-0x80234BCC (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

s32 fn_8023C598(s32);
s32 fn_8023D780(void);
void fn_801275D4(s32, char *, s32);
extern char lbl_802B0928[];

bool ScriptGetEditedParkGapName(void *arg0, CScript *arg1) {
    s32 n = arg1->unk0x18;
    s32 x;

    fn_8023C598(1);
    x = fn_8023D780();
    fn_801275D4(n, lbl_802B0928, x);
    return true;
}
