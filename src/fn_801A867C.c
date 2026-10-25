// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A867C-0x801A871C (160B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 Mem_NewZero(s32);
void *fn_801A80B0(void *, s32);
s32 remove_orphan_cluster(void *, s32);
bool fn_801A867C(s32 arg0, s32 arg1) {
    Unk_C8FEE62D *node;
    char *base;
    s32 old;
    s32 var_r3;

    node = fn_801A80B0((void *)Mem_NewZero(0x1C), arg1);
    if (node == NULL) {
        return false;
    }
    if (remove_orphan_cluster(node, arg1) == 0) {
        s32 vtbl = node->unk0x14;
        ((s32 (*)(void *, s32))(((Unk_F5317C5D *)vtbl)->unk0xC))(
            (char *)node + ((Unk_F5317C5D *)vtbl)->unk0x8, 3);
        return false;
    }
    base = (char *)arg0 + 0x48;
    old = ((Unk_1D62F22E_2 *)base)->unk0x10;
    node->unk0xC = (s32)base;
    node->unk0x10 = old;
    *(s32 *)(((Unk_1D62F22E_2 *)base)->unk0x10 + 0xC) = (s32)node;
    ((Unk_1D62F22E_2 *)base)->unk0x10 = (s32)node;
    return true;
}
