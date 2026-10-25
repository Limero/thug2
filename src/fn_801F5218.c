// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F5218-0x801F5374 (348B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_801F1684(s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
s32 fn_80129EA0(CStruct *, u8 *);
void fn_801F203C(Unk_5FCDF30E *);
s32 GetArray(CStruct *, s32, s32 *, s32);
s32 fn_80129528(CStruct *, s32);
void fn_801F3170(Unk_127FDB99 *, CStruct *);
void CStruct_delete(CStruct *, s32);
s32 fn_801F5218(Unk_F0C166E4 *arg0, s32 arg1, void *arg2) {
    s32 sp8;
    s32 temp_r24;
    s32 temp_r25;
    s32 temp_r26;
    s32 var_r28;
    s32 var_r29;
    s32 var_i;
    s32 var_j;
    s32 var_r31;
    s32 var_r9;
    s32 *pOut;
    void *var_r30;
    void *var_walk;

    pOut = &sp8;
    temp_r25 = fn_801F1684(arg1);
    var_walk = (char *)arg0 + 0x20;
    temp_r26 = CStruct_ctor(CStruct_new(8));
    temp_r24 = fn_80129EA0(temp_r26, arg2);
    var_i = 0x32;
    do {
        var_r9 = 1;
        if ((s32) ((Unk_127FDB99 *)var_walk)->unk0x2BE == 0) {
            var_r9 = 0;
        }
        if ((var_r9 != 0) && ((s32) *(s32 *)var_walk == temp_r25)) {
            fn_801F203C(var_walk);
        }
        var_walk += 0x370;
        var_i -= 1;
    } while (var_i != 0);
    arg0->unk0xAC00 = 0;
    sp8 = 0;
    GetArray(temp_r26, QB_GOALS, pOut, 1);
    var_r28 = 0;
    var_j = 0;
    var_r31 = ((CStruct *)sp8)->unk0x4;
    if (var_r31 != 0) {
        var_r30 = (char *)arg0 + 0x20;
        do {
            var_r9 = 1;
            if ((s32) ((Unk_127FDB99 *)var_r30)->unk0x2BE == 0) {
                var_r9 = 0;
            }
            if (var_r9 == 0) {
                fn_801F3170(var_r30, (void *)fn_80129528(sp8, var_r28));
                *(s32 *)var_r30 = temp_r25;
                var_r28 += 1;
                var_r31 -= 1;
            }
            var_r30 += 0x370;
            var_j += 1;
        } while (var_j <= 0x31 && var_r31 != 0);
    }
    if (temp_r26 != 0) {
        CStruct_delete(temp_r26, 3);
    }
    return temp_r24;
}
