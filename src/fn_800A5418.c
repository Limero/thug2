// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A5418-0x800A54AC (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_800A68BC(s32, s32, s32);
s32 Script_GenerateCRC(void *);
s32 sprintf(char *, const char *, ...);
extern char lbl_8029809C[];
// GetFreshId @ 0x800A5418
s32 GetFreshId(CStruct *arg0) {
    s32 sp48;
    char sp8[0x40];

    do {
        sprintf(sp8, lbl_8029809C, arg0->unk0x4++);
        if (arg0->unk0x4 > 0xF423F) {
            arg0->unk0x4 = 0;
        }
        sp48 = Script_GenerateCRC(sp8);
    } while (fn_800A68BC(arg0->unk0x8, &sp48, 1) != 0);
    return sp48;
}
