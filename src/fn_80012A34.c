// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80012A34-0x80012AB4 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

/* 16-byte PIP record at lbl_8031362C; 200 entries (0xC80 of 0xC84 claimed). */
typedef struct {
    s32 *resource;
    s32 owner;
    s32 value;
    s32 refcount;
} T_8031362C;

extern char lbl_8031362C[];
void *fn_80012754(s32 arg0);

s32 fn_80012A34(s32 arg0) {
    char *base = lbl_8031362C;
    T_8031362C *e = (T_8031362C *)base;
    s32 off;
    s32 i;
    s32 *p;

    for (i = 0; i < 0xC8; i++, e++) {
        off = i * 0x10;
        if (e->resource == NULL || e->owner != arg0) {
            continue;
        }
        base += 8;
        return *(s32 *)((char *)base + off);
    }
    p = (s32 *)fn_80012754(arg0);
    if (p != NULL) {
        return *p;
    }
    return 0;
}
