// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010CA64-0x8010CB44 (224B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_80119470(void);
s32 fn_8010BBC4(s32, void *, s32);
s32 fn_8010BB8C(s32);
s32 fn_80128978(s32, s32);
s32 GetStructure(s32, s32);
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
s32 fn_8010C5DC(CStruct *, s32, f32);
s32 fn_8010C6C0(CStruct *, Unk_01476648 *);
s32 fn_8010CA64(Unk_01476648 *arg0, s32 arg1, s32 arg2, f32 farg0) {
    s32 sp8;
    s32 padA;
    s32 padB;
    s32 temp_bb8c;
    s32 temp_r3;
    s32 var_r29;

    __asm__("" : : "m"(sp8), "m"(padA), "m"(padB));
    var_r29 = 0;
    if (fn_80119470() != 0) {
        return 0;
    }
    sp8 = 0;
    if (fn_8010BBC4(arg1, &sp8, QB_SOUNDACTIONS) != 0) {
        temp_bb8c = fn_8010BB8C(arg2);
        if (fn_80128978(sp8, temp_bb8c) == 0) {
            GetStructure_2(GetStructure(QB_TERRAIN_DEFAULT, 1), QB_SOUNDACTIONS, &sp8, 1);
        }
        temp_r3 = fn_8010C5DC(sp8, arg2, farg0);
        if (temp_r3 != 0) {
            var_r29 = fn_8010C6C0(temp_r3, arg0);
        }
    }
    return var_r29;
}
