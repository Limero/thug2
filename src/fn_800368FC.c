// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800368FC-0x80036960 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8003A31C(CStruct *);
s32 fn_8003A324(void *, s32);
typedef struct {
    char pad0x0[0x18];
    s32 *unk0x18;
} S_368FC;
// arg0->unk0x18 is the destination array base; arg1 is a CStruct whose
// +0x4 count bounds the loop. Each iteration copies one 8-entry (0x20-byte)
// group index from arg1 into arg0, advancing both by one group.
void fn_800368FC(S_368FC *arg0, CStruct *arg1) {
    s32 i;
    s32 off;

    i = 0;
    off = 0;
    while (i < fn_8003A31C(arg1)) {
        *(s32 *)((char *)off + (s32)arg0->unk0x18) = fn_8003A324(arg1, i);
        i++;
        off += 0x20;
    }
}
