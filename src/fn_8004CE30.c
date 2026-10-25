// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004CE30-0x8004CEA4 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80300434[];
void GetElement_2(void *, s32, s32, s32);
void CObject_RemoveRefLink(s32, void *);
void fn_800427AC(s32, Unk_E80761A5 *);
void fn_8004CE30(Unk_E80761A5 *arg0, s32 arg1) {
    struct { s32 a; s32 b; s32 c; s32 d; } sp8;
    s32 v;

    GetElement_2(&sp8, *(s32 *)&lbl_80300434, arg1 + QB_THE_SCORE, 0);
    v = sp8.a;
    if (v != 0) {
        fn_800427AC(v, arg0);
    }
    if (sp8.a != 0) {
        CObject_RemoveRefLink(sp8.a, &sp8);
        sp8.a = 0;
    }
}
