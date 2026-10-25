// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012C678-0x8012C790 (280B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
unsigned int fn_8000A778(const char *str);
void Mem_Free_3(s32 arg0);
u8 *Mem_Alloc_3(s32 arg0);
s32 fn_8000AC98(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3);
extern s32 lbl_8030342C;
void fn_80134844(s32, s32);
Unk_5AA7B5D7 *fn_80125568(void *);
void *fn_8012C678(CScript *arg0, s32 arg1, u8 *arg2, s32 arg3, void *arg4) {
    s32 var_ctr;
    s32 var_r31;
    u32 var_r11;
    u8 *temp_r3_2;
    u8 *temp_r3_3;
    u8 *var_r11_2;
    u8 *var_r3;
    u8 *var_r9;
    u8 *var_r9_2;
    u8 temp_r0;
    u8 temp_r0_2;
    Unk_5AA7B5D7 *temp_r3;

    temp_r3 = fn_80125568(arg0);
    *(u8 *)((char *)temp_r3 + (s32)0x2) = 7;
    temp_r3_2 = Mem_Alloc_3(0x4E20);
    var_r31 = fn_8000AC98(arg2, temp_r3_2, arg3, 0);
    if (var_r31 >= arg3) {
        var_r11 = 0U;
        var_r3 = arg2;
        var_r9 = temp_r3_2;
        while (var_r11 < (u32) arg3) {
            *var_r9 = *var_r3;
            var_r11 += 1;
            var_r3 += 1;
            var_r9 += 1;
        }
        var_r31 = arg3;
    }
    temp_r3_3 = Mem_Alloc_3(var_r31 + 0x20);
    var_r11_2 = temp_r3_2;
    ((CStruct *)temp_r3_3)->unk0x0 = arg1;
    var_r9_2 = temp_r3_3 + 0x20;
    ((CStruct *)temp_r3_3)->unk0x4 = arg3;
    ((CStruct *)temp_r3_3)->unk0x8 = var_r31;
    if (var_r31 > 0) {
        var_ctr = var_r31;
        do {
            temp_r0_2 = *var_r11_2;
            var_r11_2 += 1;
            *var_r9_2 = temp_r0_2;
            var_r9_2 += 1;
            var_ctr -= 1;
        } while (var_ctr != 0);
    }
    temp_r3->unk0xC = temp_r3_3;
    Mem_Free_3(temp_r3_2);
    if (lbl_8030342C != 0) {
        fn_80134844(lbl_8030342C, (s32)arg0);
    }
    temp_r3->unk0x8 = fn_8000A778(arg4);
    return temp_r3;
}
