// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A3C50-0x800A3CC4 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "structs.h"
#include "mem.h"
s32 fn_800A5B18(s32, s32);
extern s32 lbl_80301A78;
void CObject_RemoveRefLink(CStruct *, CStruct *);
extern char lbl_80298050[];
void fn_800A3C50(Unk_DB0E2BAB *arg0, s32 arg1) {
    arg0->unk0x18 = (s32)lbl_80298050;
    fn_800A5B18(lbl_80301A78, arg0);
    if ((s32) arg0->unk0x0 != 0) {
        CObject_RemoveRefLink(*(s32 *)((char *)arg0), arg0);
        arg0->unk0x0 = 0;
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
