// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F0B88-0x801F0DC4 (572B). Byte-identical.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305F9C;
extern void fn_801D16C0(Unk_F65AFC12 *);
extern void fn_801F0F58(void *);
extern void fn_801F0E84(CScript *);
extern s32 fn_8021D358(s32, s32);
extern s32 fn_8022A9D0();
extern s32 fn_8021B55C(s32, s32);
extern s32 ContainsFlag(CStruct *, s32);
extern void fn_801F0DC8(void *, s32, s32, s32, s32);
s32 fn_801F0B88(Unk_DB0E2BAB *arg0, s32 arg1, CStruct *arg2) {
    s32 *temp_r30;
    s32 temp_r29;
    s32 var_r0;
    s32 var_r3;
    void *temp_r11;
    Unk_EE36B018 *temp_r9;

    switch ((u32)arg1) {
    case QB_RESETSWITCHED:
        temp_r11 = arg0->unk0x34;
        if ((s32)*(s32 *)(*(s32 *)((char *)((char *)temp_r11) + 0xC) + 0x120) != 0) {
            var_r0 = *(s32 *)(*(s32 *)((char *)((char *)temp_r11) + 0x15BC) + 0x34);
        } else {
            var_r0 = *(s32 *)(*(s32 *)((char *)((char *)temp_r11) + 0x15BC) + 0x34) ^ 1;
        }
        if (var_r0 == 0) {
            goto block_ret1;
        }
        goto block_f58;
    case QB_FLIPAFTER:
        arg0->unk0x20 = 1;
        goto block_ret1;
    case QB_ROTATEAFTER:
        arg0->unk0x24 = 1;
        goto block_ret1;
    case QB_BOARDROTATEAFTER:
        arg0->unk0x28 = 1;
        goto block_ret1;
    case QB_ISFLIPAFTERSET:
        var_r0 = arg0->unk0x20;
block_test:
        var_r3 = 0;
        if (var_r0 != 0) {
            var_r3 = 1;
        }
        return var_r3;
    case QB_FLIPANDROTATE:
        fn_801D16C0(arg0->unk0x34);
    case QB_FLIP:
    block_f58:
        fn_801F0F58(arg0);
        goto block_ret1;
    case QB_ROTATENOFLIP:
        fn_801D16C0(arg0->unk0x34);
        goto block_ret1;
    case QB_BOARDROTATE:
        temp_r9 = arg0->unk0xC;
        fn_8021D358(lbl_80305F9C, temp_r9->unk0x1A);
        temp_r29 = lbl_80305F9C;
        temp_r30 = (s32 *)fn_8021B55C(temp_r29, fn_8022A9D0());
        if (ContainsFlag(arg2, QB_NORMAL) != 0) {
            fn_801F0DC8(arg0, *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0xC) + 0x18), 0, *(s32 *)temp_r30, 1);
        } else {
            fn_801F0DC8(arg0, *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0xC) + 0x18), arg0->unk0x1C ^ 1, *(s32 *)temp_r30, 1);
        }
        goto block_ret1;
    case QB_BOARDISROTATED:
        var_r0 = arg0->unk0x1C;
        goto block_test;
    case QB_PLAYANIM:
        fn_801F0E84(arg0);
    default:
        var_r3 = 2;
        return var_r3;
    }
block_ret1:
    var_r3 = 1;
    return var_r3;
}
