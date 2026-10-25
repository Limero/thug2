// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80184A2C-0x80184BB0 (388B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern u8 lbl_802A9498;
extern char lbl_802A949C[];
extern s32 lbl_80300434;
extern void *fn_801840F0(Unk_C7387A53 * arg0, s32 arg1);
extern s32 fn_8018C060(Unk_C7387A53 * arg0);
extern void GetElement_2(s32 *, s32, s32, s32);
extern void fn_800427AC(Unk_E80761A5 *, u8 *);
extern void CObject_RemoveRefLink(CStruct *, CStruct *);
void fn_80184A2C(Unk_C7387A53 *arg0) {
    char sp8[0x40];
    struct { s32 v; char _p[12]; } sp48s;
    s32 count;
    CStruct *walker;
    s32 i;
    Unk_C8FEE62D *obj;
    Unk_07FDFB02 *vt;
    s32 ms;

    count = 0;
    walker = arg0->unk0x2C;
    if (walker->unk0x4 == -1) {
        walker = 0;
    }
    if (walker != 0) {
        do {
            walker = walker->unk0xC;
            count += 1;
            if (walker->unk0x4 == -1) {
                walker = 0;
            }
        } while (walker != 0);
    }
    i = 0;
    sp8[0] = lbl_802A9498;
    while (i < count) {
        obj = fn_801840F0(arg0, i);
        vt = obj->unk0x14;
        if (((s32 (*)(void *))vt->unk0x5C)((char *)obj + vt->unk0x58) != 0) {
            i = 0;
            ms = fn_8018C060(obj);
            obj = 0;
            if (ms > 0) {
                obj = ms / 60000;
                i = (ms % 60000) / 1000;
            }
            sprintf(sp8, lbl_802A949C, obj, i);
            break;
        }
        i++;
    }
    GetElement_2(&sp48s.v, lbl_80300434, QB_THE_TIME, 0);
    if (sp48s.v != 0) {
        fn_800427AC((void *)sp48s.v, (u8 *)sp8);
    }
    /* Pure-C replacement for the former asm memory barrier: the volatile
       re-read of sp48s.v forces a fresh lwz after the call above, so ngccc
       can't prove the field unchanged and jump-thread this second guard's
       false edge onto the epilogue. (doc-24 case a) */
    {
        s32 keep = *(volatile s32 *)&sp48s.v;
        if (keep != 0) {
            CObject_RemoveRefLink(keep, (s32)&sp48s.v);
            sp48s.v = 0;
        }
    }
}
