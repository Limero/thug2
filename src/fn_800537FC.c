// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800537FC-0x80053834 (56B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern s8 lbl_803C9DF8[];
u32 DehexifyDigit(const char *);

s8 fn_800537FC(const char *arg0)
{
    s8 *p = lbl_803C9DF8;

    return p[DehexifyDigit(arg0)];
}
