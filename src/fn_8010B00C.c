// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010B00C-0x8010B0AC (160B). Byte-identical.
#include "types.h"
#include "structs.h"
extern f32 lbl_8029CD9C;
extern f32 lbl_80302BF4;
extern s32 fn_800557B8(s32, f32);
extern s32 fn_80024660(void *);
extern void *fn_80107998(Unk_C7387A53 *, void *, s32);
extern s32 fn_80107B20(Unk_E9DCA07D *, s32, void *);
extern void CObject_RemoveRefLink(CStruct *, CStruct *);
s32 fn_8010B00C(void *arg0, CStruct *arg1) {
    struct { char sp8[0xA8]; s32 spB0; char pad[0x14]; } l;
    s32 *p;
    f32 temp_f1;
    s32 temp_r3;
    s32 var_r31;

    temp_f1 = lbl_80302BF4 * lbl_8029CD9C;
    temp_r3 = fn_800557B8(arg1, temp_f1);
    if (temp_r3 == 0) {
        fn_80107998(l.sp8, (void *)fn_80024660(arg0), arg1);
        var_r31 = fn_80107B20(l.sp8, 1, 0) ^ 1;
        p = &l.spB0;
        if (*p != 0) {
            CObject_RemoveRefLink((void *)*p, p);
            *p = temp_r3;
        }
        return var_r31;
    }
    return 0;
}
