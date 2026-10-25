// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A6E0C-0x801A6E64 (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct Ent { s32 unk0; s32 unk4; char pad[0x18]; } Ent;
typedef struct Outer { char pad[4]; Ent e[1]; } Outer;
#include "structs.h"
s32 fn_801A6820(s32);
s32 fn_801A6E0C(Unk_93C2DF4D *arg0, s32 arg1) {
    s32 temp_r29;
    s32 var_r4;

    var_r4 = arg1;
    if (var_r4 == -1) {
        var_r4 = arg0->unk0x630;
    }
    temp_r29 = fn_801A6820(((Outer *)arg0)->e[var_r4].unk0);
    return temp_r29 + fn_801A6820(((Outer *)arg0)->e[var_r4].unk4);
}
