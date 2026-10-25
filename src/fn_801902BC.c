// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801902BC-0x801903B0 (244B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetArray(CStruct *, s32, s32 *, s32);
extern s32 fn_80129528(CStruct *, s32);
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern void *fn_801A8DD8(s32, s32);
extern s32 fn_801A8848(void *, void *);
extern s32 fn_801A8580(void *, void *);
extern s32 lbl_80305F1C;

void fn_801902BC(Unk_C7387A53 *arg0, Unk_C8FEE62D *arg1, s32 arg2) {
    s32 tbl;
    s32 sp8;
    s32 spC;
    s32 count;
    s32 i;
    s32 r;
    void *n;

    tbl = lbl_80305F1C;
    sp8 = 0;
    r = GetArray((CStruct *)arg0->unk0x20, QB_KILL_CLUSTERS, &sp8, 0);
    if (r != 0) {
        i = 0;
        count = ((CStruct *)sp8)->unk0x4;
        if (i < count) {
            do {
                GetChecksum_2((CStruct *)fn_80129528((CStruct *)sp8, i), QB_ID, &spC, 1);
                if (fn_801A8DD8(tbl, spC) != 0) {
                    if (arg2 != 0) {
                        n = fn_801A8DD8(tbl, spC);
                        if (n != 0) {
                            fn_801A8848(n, arg1);
                        }
                    } else {
                        fn_801A8580(fn_801A8DD8(tbl, spC), arg1);
                    }
                }
                i += 1;
            } while (i < count);
        }
    }
}
