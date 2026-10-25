// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005DDBC-0x8005DDF4 (56B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern void *lbl_80300DFC;
extern char lbl_803C9E18[];

s32 fn_8005DDBC(s32 arg0)
{
    s32 temp_r0;

    temp_r0 = ((s32 *)lbl_80300DFC)[arg0];
    if (temp_r0 == -1) {
        return 0;
    }
    return *(s32 *)((char *)((s32 *)lbl_803C9E18)[temp_r0] + 0x18);
}
