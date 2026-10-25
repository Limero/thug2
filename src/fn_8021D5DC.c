// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021D5DC-0x8021D66C (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern char lbl_802A8030[];
void *fn_8021D578(s32 arg0, void *out);
void *fn_8021D5AC(s32 arg0, void *out);

/* 16-byte out-param block: sized to give want's 0x28 frame (locals 0x8..0x17)
   so no pad and no "m" pin are needed.  Only +4 (flag) and +8 (name ptr) are
   touched. */
typedef struct { s32 pad0; s32 flag; void *name; s32 pad8; } FR5DC;

void *fn_8021D5DC(s32 arg0, s32 arg1) {
    FR5DC fr;
    Unk_A8B25094 *entry;
    Unk_59AB5482 *fp;
    s32 *p = (s32 *)&fr;

    /* int base, NOT struct members: keeps want's `stw .. 4(r4)` / `8(r4)`
       register form instead of folding to an r1 displacement. */
    p[1] = 0;
    p[2] = (s32)lbl_802A8030;
    entry = fn_8021D578(arg0, (void *)&fr);
    fp = (Unk_59AB5482 *)&fr;
    __asm__("" : "+r"(fp));
    if (entry != 0) {
        do {
            if (entry->unk0x11 == arg1) {
                fp->unk0x8 = (s32)lbl_802A8030;
                return entry;
            }
            entry = fn_8021D5AC(arg0, (void *)&fr);
        } while (entry != 0);
    }
    fp->unk0x8 = (s32)lbl_802A8030;
    return NULL;
}
