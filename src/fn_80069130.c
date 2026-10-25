// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80069130-0x80069178 (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_800071D4(s32);
s32 fn_80068F70(void *);
extern char lbl_80294980[];
void *fn_80069130(Unk_7A675EAB *arg0) {
    arg0->unk0x1B8 = (s32)lbl_80294980;
    fn_80068F70((char *)arg0 + 8);
    fn_800071D4((char *)arg0 + 0x188);
    return arg0;
}
