// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800241E8-0x80024250 (104B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void CObject_RemoveRefLink(CStruct *, CStruct *);
extern char lbl_802912B0[];
void fn_800241E8(Unk_C7387A53 *arg0, s32 arg1) {
    void *p18;
    void *pp;

    pp = (char *)arg0 + (s32)0x18;
    p18 = *(void **)pp;
    arg0->unk0x24 = (s32)lbl_802912B0;
    if (p18 != 0) {
        CObject_RemoveRefLink(p18, pp);
        *(s32 *)pp = 0;
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
