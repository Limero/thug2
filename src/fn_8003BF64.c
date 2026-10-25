// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003BF64-0x8003BF90 (44B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// Identification: 3-arg wrapper (0,0) around fn_80060B74 on the gfx-node
// registry at lbl_803003E8 (same node as fn_8003D318). Suggested rename:
// CineractorAttachDefaults (pending node ident).
#include "types.h"
#include "structs.h"
s32 fn_80060B74(CStruct *);
extern void* lbl_803003E8;
bool fn_8003BF64(void) {
    fn_80060B74(lbl_803003E8);
    return true;
}
