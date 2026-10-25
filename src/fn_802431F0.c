// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802431F0-0x802432A0 (176B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void *fn_80241E38(void *, u32);
extern s32 fn_80238964(s32);
extern void *fn_80236EF4(CStruct *, s32, s32 *);
s32 fn_802431F0(Unk_C7387A53 *arg0) {
    u32 j;
    u32 k;
    s32 count;
    Unk_9994C3F5 *ent;
    Unk_9994C3F5 *node;
    u32 n;

    count = 0;
    j = 0;
    if ((u32)count < *((u32 *)&arg0->unk0x30)) {
        do {
            ent = fn_80241E38(arg0, j);
            node = fn_80236EF4(fn_80238964((s32)ent), ent->unk0x8, 0);
            if (node->unk0x8 & 0x80) {
                count++;
            } else {
                n = node->unk0x30;
                for (k = 0; k < n; k++) {
                    count++;
                }
            }
            j++;
        } while (j < *((u32 *)&arg0->unk0x30));
    }
    return count;
}
