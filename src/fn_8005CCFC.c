// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005CCFC-0x8005CDF4 (248B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_802936D8[];
extern s32 lbl_803009CC[];

s32 strcat(s32, s32);
s32 strcpy(s32, s32);
s32 strlen(s32);
s32 fn_8005CF80(void *, s32);
s32 fn_8000A778(s32);

s32 fn_8005CCFC(void *arg0, s32 arg1) {
    s32 res;
    s32 hash;
    s32 i;
    s32 t;
    s32 *p;
    char sp8[0x200];

    res = 0;
    hash = fn_8000A778(arg1);
    i = 0;
    for (;;) {
        t = lbl_803009CC[i];
        if (t <= 0) break;
        res = fn_8005CF80(arg0, hash * t);
        if (res != 0) break;
        i++;
    }
    if (res == 0) {
        strcpy(sp8, arg1);
        if (strlen(sp8) > 4) {
            sp8[strlen(sp8) - 4] = 0;
            strcat(sp8, lbl_802936D8);
        }
        hash = fn_8000A778(sp8);
        p = lbl_803009CC;
        for (;;) {
            t = *p;
            if (t <= 0) break;
            res = fn_8005CF80(arg0, hash * t);
            if (res != 0) break;
            p++;
        }
    }
    return res;
}
