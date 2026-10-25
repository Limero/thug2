// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80011F20-0x80011F54 (52B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct { char _0[0x84]; void *unk0x84; } N11F20;
extern s32 lbl_80290628;
void *fn_80011F20(void *arg0) {
    N11F20 *o = (N11F20 *)arg0;
    void *n = o->unk0x84;
    if (n != 0) {
        s32 off = lbl_80290628;
        o->unk0x84 = *(void **)n;
        *(void **)n = o;
        return (char *)n + off;
    }
    return 0;
}
