// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013229C-0x801322F8 (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_801252BC(Unk_5D1D68CC *);
void fn_801322F8(Unk_B1CD4D9E *);
void *fn_8013229C(CScript *arg0) {
    s32 i;
    void *p = (char *)arg0 + 4;
    i = 0x13;
    do {
        fn_801252BC(p);
        p = (char *)p + 0x10;
    } while (--i != -1);
    fn_801322F8(arg0);
    arg0->unk0x1F8 = 1;
    return arg0;
}
