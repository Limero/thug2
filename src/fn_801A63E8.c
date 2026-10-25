// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A63E8-0x801A6464 (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void *Mem_NewZero(s32);
s32 fn_801A44A0(void *);
bool fn_801A63E8(Unk_C7387A53 *arg0, s32 arg1) {
    s32 n;
    s32 i;
    s32 idx;
    void *node;
    s32 *base;
    s32 *base2;
    n = arg0->unk0x2C;
    for (i = 0; i < n; i++) ;
    idx = arg0->unk0x2C * 4;
    base = (s32 *)((char *)arg0 + 0x3C);
    node = Mem_NewZero(0x74);
    *(s32 *)((char *)base + idx) = fn_801A44A0(node);
    base2 = (s32 *)((char *)arg0 + 0x30);
    *(s32 *)((char *)base2 + arg0->unk0x2C * 4) = arg1;
    arg0->unk0x2C = arg0->unk0x2C + 1;
    return true;
}
