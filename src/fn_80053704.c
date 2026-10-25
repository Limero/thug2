// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80053704-0x80053790 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

s32 strcmp(const char *, const char *);
s32 Script_GenerateCRC(const char *);
void fn_80053AF8(const char *, s32 *);
void fn_8007BCAC(s32);

extern char lbl_80364A38[];
extern char lbl_80364BF8[];

void fn_80053704(const char *arg0) {
    char *base;
    char *name;
    s32 *slot;
    char *end;
    s32 sp8;

    base = lbl_80364A38;
    slot = (s32 *)((char *)base + 0x18);
    name = base;
    end = base + 0x1A4;
    do {
        if (strcmp(name, arg0) == 0) {
            sp8 = Script_GenerateCRC(arg0);
            fn_80053AF8(lbl_80364BF8, &sp8);
            fn_8007BCAC(*slot);
            *slot = 0;
            return;
        }
        name += 0x1C;
        slot = (s32 *)((char *)slot + 0x1C);
    } while ((s32)name <= (s32)end);
}
