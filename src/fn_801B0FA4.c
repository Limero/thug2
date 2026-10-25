// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B0FA4-0x801B107C (216B). Byte-identical.
#include "types.h"
#include "structs.h"

extern char lbl_802ABDA4[];
extern char lbl_802ABDA8[];
extern char lbl_802ABDB4[];
extern s32 fn_80128610(CStruct *, void *, void *, s32);
extern s32 fn_80129528(CStruct *, s32);
extern void fn_801B0B3C(Unk_C8FEE62D *, CStruct *);
extern s32 fn_80128C20(CStruct *, void *, void *, s32);
extern void fn_801B0144(Unk_F96D0DC8 *, Unk_1D62F22E *);

void fn_801B0FA4(CStruct *arg0, CStruct *arg1) {
    void *sp8;
    s32 spC;
    s32 var_r31;
    s32 var_r29;

    sp8 = NULL;
    fn_80128610(arg1, (s32)lbl_802ABDA8, &sp8, 0);
    if (arg0->unk0x4 == ((CStruct *)sp8)->unk0x4) {
        var_r31 = 0;
        if (var_r31 < (s32)arg0->unk0x4) {
            var_r29 = 0;
            do {
                fn_801B0B3C(
                    (void *)(arg0->unk0xC + var_r29),
                    fn_80129528(sp8, var_r31)
                );
                var_r29 += 0x20;
                var_r31 += 1;
            } while (var_r31 < (s32)arg0->unk0x4);
        }
        spC = (s32)lbl_802ABDA4;
        fn_80128C20(arg1, (s32)lbl_802ABDB4, &spC, 0);
        fn_801B0144(arg0->unk0x8, spC);
    }
}
