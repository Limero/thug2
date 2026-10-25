// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8014DB40-0x8014DC40 (256B). Byte-identical.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80301A38;
extern s32 fn_800A398C(s32 arg0, s32 arg1);
extern s32 GetChecksum_3(Unk_6A70655D * arg0, u32 arg1);
extern s32 fn_8005DE90(s32 arg0);
extern s32 fn_800246AC(void * arg0);
extern s32 fn_80024660(void * arg0);
extern s32 fn_8005DDF4(s32 arg0, CStruct * arg1);
s32 fn_8014DB40(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_r3;
    s32 temp_r31;
    CScript *temp_r30;
    s32 temp_r9;
    s32 temp_r3;
    Unk_89391A04 *vt;
    s32 src;

    temp_r31 = fn_800A398C(*(s32 *)&lbl_80301A38, arg0);
    var_r3 = 0;
    if (temp_r31 != 0) {
        temp_r30 = GetChecksum_3(temp_r31, QB_CAMERA);
        if (temp_r30 != 0) {
            if (arg2 != 0) {
                src = fn_800246AC(fn_8005DE90(arg1));
                ((__ps_t *)temp_r31)[15] = ((__ps_t *)src)[0];
                ((__ps_t *)temp_r31)[16] = ((__ps_t *)src)[1];
                ((__ps_t *)temp_r31)[17] = ((__ps_t *)src)[2];
                ((__ps_t *)temp_r31)[18] = ((__ps_t *)src)[3];
                ((__ps_t *)temp_r31)[19] = ((__ps_t *)src)[4];
                ((__ps_t *)temp_r31)[20] = ((__ps_t *)src)[5];
                ((__ps_t *)temp_r31)[21] = ((__ps_t *)src)[6];
                ((__ps_t *)temp_r31)[22] = ((__ps_t *)src)[7];
                temp_r3 = fn_80024660(fn_8005DE90(arg1));
                ((__ps_t *)temp_r31)[11] = ((__ps_t *)temp_r3)[0];
                ((__ps_t *)temp_r31)[12] = ((__ps_t *)temp_r3)[1];
                vt = temp_r30->unk0x18;
                ((s32 (*)(void *))(vt->unk0x14))((char *)temp_r30 + vt->unk0x10);
            }
            fn_8005DDF4(arg1, temp_r30->unk0x1C);
        }
        var_r3 = 1;
    }
    return var_r3;
}
