// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80153EF4-0x80153FA4 (176B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305F9C;
s32 fn_8021B55C(void *, s32);
void fn_80137CB4(Unk_9F066EC1 *);
void fn_8013DE78(void *, Unk_C71E6DE1 *);

bool ScriptNotifyBailDone(s32 arg0, Unk_FFAD6788 *arg1) {
    struct { s8 b; char pad1[0xB]; s32 w; s8 e; char pad2[0x13]; } sp;
    s32 nm;
    Unk_9472DC69 *var_r11;
    Unk_31DE137E *temp_r4;
    s32 temp_r3;

    var_r11 = NULL;
    nm = lbl_80305F9C;
    if (arg1 != NULL) {
        temp_r4 = *((void * *)&arg1->unk0xBC);
        if ((temp_r4 != NULL) && (temp_r4->unk0x1C == QB_OBJECT_TYPE_SKATER)) {
            var_r11 = temp_r4;
        }
    }
    if ((var_r11 != NULL) && (var_r11->unk0xC8 != 0)) {
        temp_r3 = fn_8021B55C(nm, var_r11->unk0x2E8);
        if (temp_r3 != 0) {
            fn_80137CB4(&sp.b);
            sp.b = 0x45;
            sp.w = 2;
            sp.e = 8;
            fn_8013DE78(temp_r3, &sp.b);
        }
    }
    return true;
}
