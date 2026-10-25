// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015DCCC-0x8015DD90 (196B). Byte-identical.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
extern char lbl_802A820C[];
extern char lbl_802A8210[];
extern char lbl_802A8214[];
extern void fn_801276E8(CStruct * arg0, void * arg1, s32 arg2);
s32 ScriptGetSkaterPosition(void *arg0, Unk_EFC8CFAD *arg1) {
    volatile __ps_t sp8[2];
    volatile __ps_t *pv;
    f32 temp_f30;
    f32 temp_f31;
    register void *temp_r11 __asm__("r11");
    s32 var_r3;

    if (arg1->unk0xBC == 0) {
        var_r3 = 0;
    } else {
        temp_r11 = *((void * *)&arg1->unk0xBC);
        sp8[0] = ((Unk_DF2324A8 *)temp_r11)->unk0x58;
        pv = sp8;
        pv[1] = ((Unk_DF2324A8 *)temp_r11)->unk0x60;
        temp_f31 = *((f32 *)&((CStruct *)pv)->unk0x4);
        temp_f30 = *((f32 *)&((CStruct *)pv)->unk0x8);
        fn_801276E8(arg1->unk0x18, (s32)lbl_802A820C, (s32)*(f32 *)&sp8[0]);
        fn_801276E8(arg1->unk0x18, (s32)lbl_802A8210, (s32)temp_f31);
        fn_801276E8(arg1->unk0x18, (s32)lbl_802A8214, (s32)temp_f30);
        var_r3 = 1;
    }
    return var_r3;
}
