// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80121218-0x80121250 (56B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct S1218 { char pad0x0[0x24]; s32 unk0x24; char pad0x28[0x1F0]; s32 unk0x218; } S1218;
extern S1218 lbl_8038F0C0[];
bool fn_80121218(s32 arg0) {
    if (lbl_8038F0C0[arg0].unk0x218 != 0 && lbl_8038F0C0[arg0].unk0x24 != 0) {
        return true;
    }
    return false;
}
