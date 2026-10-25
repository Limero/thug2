// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002D108-0x8002D14C (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void *fn_8002D108(Unk_FFAD6788 *arg0) {
    char *var_r9;
    s32 var_ctr;

    var_ctr = 0x32;
    var_r9 = (char *)arg0 + 0xC8;
    do {
        *(s32 *)var_r9 = 0;
        var_r9 -= 4;
        var_ctr -= 1;
    } while (var_ctr != 0);
    arg0->unk0xD0 = 0;
    arg0->unk0xD4 = 0;
    arg0->unk0xD8 = 0;
    arg0->unk0xDC = 0;
    arg0->unk0xCC = 0;
    arg0->unk0xE0 = 0;
    return arg0;
}
