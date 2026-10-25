// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F2270-0x800F2324 (180B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
u32 strlen(const char *);
s32 strcasecmp(const char *, const char *);
typedef struct { char *name; s32 val; } Ent;
extern char lbl_80301B50[];
s32 fn_800F2270(s32 arg0, char *arg1) {
    s32 n;
    char *p;
    Ent *e;
    n = strlen(arg1);
    p = arg1 + n;
    if (p > arg1) {
        if (arg1[n] == '.') {
            goto ext;
        }
        do {
            p--;
            if (p <= arg1) {
                break;
            }
        } while (*p != '.');
    }
    if (*p == '.') {
        goto ext;
    }
    goto nf;
match:
    return e->val;
ext:
    p = p + 1;
    e = (Ent *)&lbl_80301B50;
    if (e[0].name == 0) {
        goto nf;
    }
    for (;;) {
        if (strcasecmp(e->name, p) == 0) {
            goto match;
        }
        e++;
        if (e->name == 0) {
            break;
        }
    }
nf:
    return 0;
}
