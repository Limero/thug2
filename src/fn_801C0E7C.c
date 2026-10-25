// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C0E7C-0x801C0FF4 (376B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern char lbl_80300434[];
extern f32 lbl_802AC6F8;
extern f32 lbl_802AC6FC;
extern s32 lbl_802AC6E4[];

s32 fn_80141FA4(Unk_5FCDF30E * arg0);
void GetElement_2(void *arg0, s32 arg1, s32 arg2, s32 arg3);
void CObject_RemoveRefLink(CStruct * arg0, CStruct * arg1);
void fn_800450B4(Unk_E80761A5 * arg0, s32 arg1);
void CScreenElement_SetAlpha(Unk_6A70655D * arg0, f32 arg1, s32 arg2);

void fn_801C0E7C(Unk_DB0E2BAB *arg0) {
    struct { s32 a; s32 b; s32 c; s32 d; } sp8;
    s32 val;
    s32 v;
    s32 var_r10;
    Unk_71062261 *p;

    GetElement_2(&sp8, *(s32 *)&lbl_80300434,
                fn_80141FA4(arg0->unk0xC) - QB_UNKNOWN_0x69751A23, 0);
    val = sp8.a;
    if (val != 0) {
        void *lp = (void *)&sp8;
        __asm__("" : "+r"(lp));
        CObject_RemoveRefLink(val, lp);
        sp8.a = 0;
    }
    var_r10 = 5;
    if ((s32)arg0->unk0x28 != 0) {
        p = *((void * *)&arg0->unk0x2C);
        if ((s32)*(s32 *)(p->unk0xC + (s32)0x120) != 0) {
            v = *(s32 *)(p->unk0x15BC + (s32)0x34);
        } else {
            v = *(s32 *)(p->unk0x15BC + (s32)0x34) ^ 1;
        }
        var_r10 = 4;
        if (v != 0) {
            var_r10 = 3;
        }
    } else {
        p = *((void * *)&arg0->unk0x2C);
        if ((s32)*(s32 *)(p->unk0xC + (s32)0x120) != 0) {
            v = *(s32 *)(p->unk0x15BC + (s32)0x34);
        } else {
            v = *(s32 *)(p->unk0x15BC + (s32)0x34) ^ 1;
        }
        if (v != 0) {
            var_r10 = 2;
            if ((s32)arg0->unk0x24 != 0) {
                var_r10 = 1;
            }
        } else if ((s32)arg0->unk0x24 != 0) {
            var_r10 = 0;
        }
    }
    if (var_r10 != (s32)arg0->unk0x1C) {
        arg0->unk0x1C = var_r10;
        if (var_r10 == 5) {
            CScreenElement_SetAlpha((void *)val, lbl_802AC6F8, 1);
            return;
        }
        fn_800450B4((void *)val, lbl_802AC6E4[var_r10]);
        CScreenElement_SetAlpha((void *)val, lbl_802AC6FC, 1);
    }
}
