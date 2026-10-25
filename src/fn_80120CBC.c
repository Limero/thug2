// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80120CBC-0x80120D14 (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 lbl_80302F10;
typedef struct S0CBC { char pad0x0[8]; s32 unk0x8; } S0CBC;
S0CBC *fn_800153C4(s32, s32);
s32 fn_80120CBC(s32 arg0, s32 arg1) {
    S0CBC *r;

    if (arg1 != 0) {
        return 0;
    }
    if (lbl_80302F10 == 0) {
        return 0;
    }
    r = fn_800153C4(arg0, lbl_80302F10);
    if (r != 0) {
        return r->unk0x8;
    }
    return 0;
}
