// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8014137C-0x801414F0 (372B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
extern s32 lbl_80305F9C;
extern f32 lbl_8029F764;
extern f32 lbl_8029F768;
extern f32 lbl_8029F76C;
extern f32 lbl_8029F770;
extern f32 lbl_8029F774;
extern f32 lbl_8029F778;
extern f32 lbl_8029F77C;
static f32 fn_8012570C(s32 arg0, s32 arg1);
static s32 fn_8009CF2C(s32 arg0);
static s32 fn_8021D358(s32 arg0, u16 arg1);
static s32 fn_8022A848(void *arg0);
static s32 fn_80229B94(void *arg0);
static s32 ScriptInSplitScreenGame(s32 arg0, s32 arg1);
static s32 Script_GetInteger(s32 arg0, s32 arg1);
static s32 fn_801A6F44(s32 arg0, s32 arg1);
struct arr_s {
    char pad[0x2BC];
    f32 arr[64];
};
f32 fn_8014137C(void *arg0, s32 arg1) {
    volatile double _dummy;
    register void *self __asm__("r31");
    register s32 temp_r30 __asm__("r30");
    f32 var_f1;
    f32 var_f31;
    s32 temp_r3b;
    s32 temp_r3c;

    self = arg0;
    var_f1 = ((Unk_4915AEDE *)lbl_80305EAC)->unk0x420;
    if (var_f1 == lbl_8029F764) {
        var_f1 = ((struct arr_s *)self)->arr[arg1];
        if (var_f1 == lbl_8029F768) {
            var_f1 = fn_8012570C(QB_SKATER_DEFAULT_STATS, 0);
        }
    }
    var_f31 = var_f1;
    __asm__ volatile("" ::: "memory");
    if (fn_8009CF2C(lbl_80305F9C) != 0) {
        temp_r30 = fn_8021D358(lbl_80305F9C, ((Unk_7F52D842 *)self)->unk0x1A);
        if (temp_r30 != 0) {
            __asm__("" ::: "r3");
            if (fn_8022A848((void *)temp_r30) != 0) {
                var_f31 = lbl_8029F76C;
            } else {
                if (fn_80229B94((void *)temp_r30) != 0) {
                    var_f31 = lbl_8029F770;
                } else {
                    var_f31 = lbl_8029F774;
                }
            }
        } else {
            var_f31 = lbl_8029F774;
        }
    } else if (ScriptInSplitScreenGame(0, 0) != 0) {
        if (((temp_r3b = fn_8021D358(lbl_80305F9C, ((Unk_7F52D842 *)self)->unk0x1A)) != 0)
            && (fn_8022A848((void *)temp_r3b) != 0)) {
            var_f31 = lbl_8029F76C;
        }
    }
    temp_r3c = ((Unk_4915AEDE *)lbl_80305EAC)->unk0x24;
    if (fn_801A6F44(temp_r3c, Script_GetInteger(QB_CHEAT_STATS_13, 0)) != 0) {
        var_f31 = lbl_8029F778;
    }
    if (*(s32 *)(*(s32 *)(((Unk_871921FD *)self)->unk0x2A4 + (s32)0x1C) + (s32)0x80) != 0) {
        var_f31 += lbl_8029F77C;
    }
    return var_f31;
}
