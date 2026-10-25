// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80034C70-0x80034D24 (180B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern s32 lbl_803003D4[];
extern s32 lbl_803003E4;
s32 fn_800120EC(s32, void *);
void CompactPool_Free(s32, void *);
void fn_80034C70(void *arg0) {
    s32 v;
    v = ((s32 *)lbl_803003D4)[lbl_803003E4];
    if (v != 0 && fn_800120EC(v, arg0) != 0) {
        CompactPool_Free(v, arg0);
        return;
    }
    v = ((s32 *)lbl_803003D4)[lbl_803003E4 ^ 1];
    if (v != 0 && fn_800120EC(v, arg0) != 0) {
        CompactPool_Free(v, arg0);
        return;
    }
    if (arg0 != 0) {
        Mem_Free2(arg0);
    }
}