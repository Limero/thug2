// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012E65C-0x8012E710 (180B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern s32 lbl_803032A4;
extern CStruct *lbl_80303294[];
s32 fn_800120EC(CStruct *, void *);
void CompactPool_Free(CStruct *, void *);
void fn_8012E65C(void *arg0) {
    CStruct *e;
    e = lbl_80303294[lbl_803032A4];
    if (e != 0 && fn_800120EC(e, arg0) != 0) {
        CompactPool_Free(e, arg0);
        return;
    }
    e = lbl_80303294[lbl_803032A4 ^ 1];
    if (e != 0 && fn_800120EC(e, arg0) != 0) {
        CompactPool_Free(e, arg0);
        return;
    }
    if (arg0 != 0) {
        Mem_Free2(arg0);
    }
}
