// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F11A8-0x801F124C (164B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801F11A8(CScript *arg0, Unk_F5317C5D *arg1, s32 arg2, s32 arg3) {
    register s32 var_r9 __asm__("r9");
    register s32 temp_r11 __asm__("r11");
    register s32 temp_r12 __asm__("r12");
    register s32 var_r0 __asm__("r0");
    s32 temp_r10;
    s32 temp_r4;

    temp_r10 = arg1->unk0xA;
    if (temp_r10 != 0) {
        if (temp_r10 < 0) {
            goto neg_path;
        }
        temp_r11 = *(s32 *)((char *)arg0 + *((s16 *)&arg1->unk0xC));
        var_r9 = temp_r10 * 8 + temp_r11;
        temp_r11 = *(s32 *)(var_r9 - 8);
        __asm__("" ::: "memory");
        temp_r12 = *(s32 *)(var_r9 - 4);
        __asm__("" : "+r"(temp_r12));
        var_r9 = temp_r12;
        goto joined;
neg_path:
        var_r9 = arg1->unk0xC;
joined:
        temp_r4 = arg1->unk0x8;
        if (temp_r10 >= 0) {
            var_r0 = (temp_r11 >> 0x10) + temp_r4;
        } else {
            var_r0 = temp_r4;
        }
        ((void (*)(void *, s32, s32))var_r9)((char *)arg0 + var_r0, arg2, arg3);
    } else {
        var_r9 = arg0->unk0x18;
        ((void (*)(void *, s32))((Unk_E71E4713 *)var_r9)->unk0x64)(
            (char *)arg0 + ((Unk_E71E4713 *)var_r9)->unk0x60,
            *(s32 *)arg1);
    }
}
