// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80151C80-0x80151DF8 (376B). Byte-identical.
#include "types.h"
extern char lbl_80301A38[];
#include "qb_constants.h"
#include "structs.h"

extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern s32 ContainsFlag(CStruct *, s32);
extern s32 GetText(CStruct *, void *, void *, s32);
extern void fn_80151C68(CStruct *, s32, s32);
extern void fn_800A3778(s32, s32, void *);
extern s32 fn_800F03D4(s32 *, void *, void *);
extern void fn_80151B4C(void);
extern void fn_80151B80(void);

s32 fn_80151C80(CStruct *arg0, s32 arg1, s32 arg2) {
    struct { s32 lead; s32 w0; s32 w1; s32 w2; s32 w3; s32 w4; } blk;
    u16 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 temp_r30;
    s32 var_r30;
    s32 *var_r31;

    sp24 = 0;
    if (arg2 == 5) {
        GetChecksum_2(arg0, 0, &sp24, 0);
    } else {
        GetInteger(arg0, 0, &sp24, 0);
    }
    if (ContainsFlag(arg0, QB_LINKS) == 0) {
        ContainsFlag(arg0, QB_UNKNOWN_0xBCEB479A);
    }
    temp_r30 = GetChecksum_2(arg0, QB_NAME, &sp28, 0);
    if (temp_r30 != 0) {
        blk.lead = sp28;
        fn_80151C68(&blk.w0, sp24, arg2);
        fn_800A3778(*(s32 *)&lbl_80301A38, (s32)fn_80151B4C, &blk.lead);
        return blk.w2;
    }
    if (GetText(arg0, QB_PREFIX, &sp2C, 0) != 0) {
        sp20 = (u16)temp_r30;
        var_r31 = (s32 *)fn_800F03D4(sp2C, &sp20, 1);
        var_r30 = 0;
        fn_80151C68(&blk.w0, sp24, arg2);
        while (var_r30 < sp20) {
            blk.lead = *(s32 *)var_r31;
            var_r30 += 1;
            fn_800A3778(*(s32 *)&lbl_80301A38, (s32)fn_80151B80, &blk.lead);
            var_r31 += 1;
        }
        return blk.w2;
    }
    return 0;
}
