// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F9F2C-0x801F9FD8 (172B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_801259C8(s32, s32);
s32 fn_8012954C(s32, s32);
s32 fn_801293FC(s32, s32);
void fn_801F9314(void *, s32 *);
void fn_801F9F2C(Unk_C7387A53 *arg0, s32 arg1) {
    u32 key;
    s32 sp8;
    s32 temp_r30;
    Unk_C7387A53 *var_r30;

    __asm__("" : : "m"(sp8), "m"(key));
    *(u8 *)&key = fn_801293FC(
        (temp_r30 = fn_8012954C(fn_801259C8(QB_GRAFFITICOLORS, 0), arg1)), 0);
    ((Unk_E01B0030 *)&key)->unk0x1 = fn_801293FC(temp_r30, 1);
    ((Unk_E01B0030 *)&key)->unk0x2 = fn_801293FC(temp_r30, 2);
    ((Unk_E01B0030 *)&key)->unk0x3 = 0x80;
    var_r30 = *((void * *)&arg0->unk0xC);
    if (var_r30 != NULL) {
        do {
            sp8 = key;
            fn_801F9314(var_r30, &sp8);
            var_r30 = *((void * *)&var_r30->unk0x24);
        } while (var_r30 != NULL);
    }
}
