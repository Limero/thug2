// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F6B44-0x801F6C04 (192B). Byte-identical.
#include "types.h"
#include "structs.h"

extern char lbl_802AE378[];
extern s32 GetChecksum_4(CStruct * arg0, void * arg1, void *arg2, s32 arg3);
extern s32 fn_801F443C(Unk_AF33B3CC * arg0);

bool fn_801F6B44(Unk_F0C166E4 *arg0, CStruct *arg1) {
    s32 sp8;
    s32 var_r29;
    s32 var_r3;
    s32 var_r9;
    Unk_127FDB99 *var_r31;

    sp8 = 0;
    GetChecksum_4(arg1, (s32)lbl_802AE378, &sp8, 0);
    var_r31 = (void *)((char *)arg0 + 0x20);
    var_r29 = 0x32;
    arg0->unk0xAC00 = NULL;
    do {
        var_r9 = 1;
        if (var_r31->unk0x2BE == 0) {
            var_r9 = 0;
        }
        if ((var_r9 != 0) && (var_r31->unk0x114 == sp8) && (fn_801F443C((s32)var_r31) == 0)) {
            arg0->unk0xAC00 = (s32)var_r31;
        }
        var_r31 = (void *)((char *)var_r31 + 0x370);
        var_r29 -= 1;
    } while (var_r29 != 0);
    if (arg0->unk0xAC00 == NULL) {
        return false;
    }
    return true;
}
