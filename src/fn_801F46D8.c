// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F46D8-0x801F4820 (328B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_801F2EA0(s32);
extern void fn_801F2AE0(Unk_31DE137E *, s32);
extern void fn_801F2CCC(s32, s32);
extern s32 CStruct_new(s32);
extern s32 CStruct_ctor(s32);
extern void AddChecksum(CStruct *, s32, s32);
extern void Script_RunScript(s32, s32, s32, s32, s32);
extern void CStruct_delete(CStruct *, s32);
s32 fn_801F46D8(Unk_13D0EFB0 *arg0, __ps_t *arg1, f32 farg0, f32 farg1) {
    __ps_t *dst;
    register s32 temp_r9 __asm__("r9");
    s32 temp_r30;
    s32 temp_r9_2;
    s32 temp_r31;
    s32 var_r3;

    var_r3 = 0;
    if (arg0->unk0x2BB == 0) {
        return var_r3;
    }
    if (fn_801F2EA0(arg0) == 0) {
        return 0;
    }
    __asm__("" : "=r"(dst)
            : "r"((char *)(((arg0->unk0x2BB << 5) + (s32)arg0)) + 0x120));
    dst[0] = arg1[0];
    dst[1] = arg1[1];
    *(f32 *)((char *)arg0 + (arg0->unk0x2BB << 5) + 0x130) = farg0;
    *(f32 *)((char *)arg0 + (arg0->unk0x2BB << 5) + 0x134) = farg1;
    fn_801F2AE0(arg0, arg0->unk0x2BB);
    temp_r9 = arg0->unk0x2BA;
    if (arg0->unk0x2BB == temp_r9) {
        arg0->unk0x2BA = temp_r9 + 1;
    }
    __asm__("" :: "r"(temp_r9));
    temp_r9_2 = arg0->unk0x2BB - 1;
    arg0->unk0x2BB = temp_r9_2;
    fn_801F2CCC(arg0, (u8)temp_r9_2);
    if (arg0->unk0x2BB == 0) {
        temp_r31 = CStruct_ctor(CStruct_new(8));
        AddChecksum(temp_r31, 0, QB_PEDPOSITION);
        Script_RunScript(QB_CREATE_CAG_HELPER_TEXT, temp_r31, 0, 0, 0);
        if (temp_r31 != 0) {
            CStruct_delete(temp_r31, 3);
        }
    }
    var_r3 = 1;
    return var_r3;
}
