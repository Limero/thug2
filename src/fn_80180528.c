// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80180528-0x801805DC (180B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void *fn_801259C8(s32, s32);
extern s32 fn_8012954C(CStruct *, s32);
extern s32 fn_801293FC(CStruct *, s32);
extern f32 fn_8012570C(s32, s32);

void fn_80180528(Unk_C7387A53 *arg0) {
    u8 *var_r31;
    s32 var_r29;
    void *temp_r28;
    s32 temp_r30;

    var_r29 = 0;
    var_r31 = (u8 *)arg0 + 0x87;
    temp_r28 = fn_801259C8(QB_SPECIAL_BAR_COLORS, 1);
    do {
        temp_r30 = fn_8012954C((s32)temp_r28, var_r29);
        var_r29 += 1;
        *(var_r31 - 3) = ((u8)fn_801293FC(temp_r30, 0));
        *(var_r31 - 2) = ((u8)fn_801293FC(temp_r30, 1));
        *(var_r31 - 1) = ((u8)fn_801293FC(temp_r30, 2));
        *(var_r31 - 0) = ((u8)fn_801293FC(temp_r30, 3));
        var_r31 += 4;
    } while (var_r29 <= 2);
    *((f32 *)&arg0->unk0x94) = fn_8012570C(QB_SPECIAL_BAR_INTERPOLATOR_RATE, 1);
}
