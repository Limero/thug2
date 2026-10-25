// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80077C9C-0x80077CFC (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
// MSL prototypes in the repo's const form — the draft's `char *` params
// tripped ngccc's builtin-declaration warning (same codegen, re-verified).
char *strcpy(char *, const char *);
char *strcat(char *, const char *);
s32 fn_8009B6AC(char *);
extern char lbl_80295810[];
s32 fn_80077C9C(Unk_C7387A53 *arg0, char *arg1) {
    char buf[0x100];
    s32 t;
    s32 r;

    strcpy(buf, arg1);
    strcat(buf, lbl_80295810);
    t = fn_8009B6AC(buf);
    r = 1;
    arg0->unk0xC = t;
    if (t == 0) {
        r = 0;
    }
    return r;
}
