// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80033CFC-0x80033ED0 (468B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 fn_8006FB50(s32, s32);
s32 fn_8006FB8C(s32, s32);
s32 fn_8005525C(void);
s32 fn_8005527C(void);
s32 fn_80033CFC(CScript *arg0, s32 arg1, CStruct *arg2) {
    u32 swv1;
    s32 sp10;
    s32 spC;
    s32 sp8;
    register s32 cur __asm__("r3");

    switch (swv1 = arg1) {
    case QB_INVALIDATECACHE:
        arg0->unk0x18 = fn_8006FB50(arg0->unk0x1C, 0);
    default:
        return 2;
    case QB_PLAYSEQUENCE:
        if (GetChecksum_2(arg2, QB_DIFFERENCEANIMNAME, &sp8, 0) == 0) {
            GetChecksum_2(arg2, QB_ANIMNAME, &sp8, 1);
        }
        GetFloat(arg2, QB_DIFFERENCEANIMAMOUNT, (char *)arg0 + 0x24, 0);
        arg0->unk0x18 = fn_8006FB8C(arg0->unk0x1C, arg0->unk0x20 + sp8);
        break;
    case QB_REPLACEANIM:
        GetChecksum_2(arg2, QB_ANIM, &spC, 1);
        cur = arg0->unk0x1C;
        if ((s32)cur != 0) {
            fn_8005527C();
            arg0->unk0x1C = 0;
        }
        arg0->unk0x1C = fn_8005525C();
        fn_8006FB50(arg0->unk0x1C, 0);
        arg0->unk0x18 = fn_8006FB8C(arg0->unk0x1C, arg0->unk0x20 + spC);
        break;
    case QB_UPDATEDIFFERENCEANIM:
        sp10 = 0;
        if (GetChecksum_2(arg2, QB_DIFFERENCEANIMNAME, &sp10, 0) == 0) {
            GetChecksum_2(arg2, QB_ANIMNAME, &sp10, 0);
        }
        if (sp10 != 0) {
            arg0->unk0x18 = fn_8006FB8C(arg0->unk0x1C, arg0->unk0x20 + sp10);
        }
        GetFloat(arg2, QB_DIFFERENCEANIMAMOUNT, (char *)arg0 + 0x24, 1);
        break;
    }
    return 1;
}
