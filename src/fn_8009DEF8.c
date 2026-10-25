// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009DEF8-0x8009DF44 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
s32 CObject_ClearRefLinks();
extern char lbl_802979B0[];
extern char lbl_802979B0[];
// CObject_dtor @ 0x8009DEF8
void CObject_dtor(Unk_9994C3F5 *arg0, s32 arg1) {
    arg0->unk0x8 = (s32)lbl_802979B0;
    CObject_ClearRefLinks();
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}