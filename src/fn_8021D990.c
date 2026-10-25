// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021D990-0x8021DA20 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern char lbl_802A83F8[];
void *fn_8021D454(s32 arg0, void *out, s32 flag);
void *fn_8021D4E8(s32 arg0, void *out, s32 flag);
s32 fn_80229B5C(void *entry);

s32 fn_8021D990(s32 arg0) {
    s32 sp8;
    s32 pad2[2];
    void *entry;
    s32 count;

    ((Unk_59AB5482 *)&sp8)->unk0x8 = (s32)lbl_802A83F8;
    ((Unk_59AB5482 *)&sp8)->unk0x4 = 0;
    entry = fn_8021D454(arg0, &sp8, 0);
    count = 0;
    if (entry != 0) {
        do {
            if (fn_80229B5C(entry) == 0) {
                count += 1;
            }
            {
                register s32 pl __asm__("r4");
                pl = (s32) &sp8;
                entry = fn_8021D4E8(arg0, (void *)pl, 0);
            }
        } while (entry != 0);
    }
    __asm__("" : : "m"(sp8), "m"(pad2[0]));
    ((Unk_59AB5482 *)&sp8)->unk0x8 = (s32)lbl_802A83F8;
    return count;
}
