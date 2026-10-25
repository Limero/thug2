// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80026CA0-0x80026D34 (148B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8002AFB0(Unk_EFFBA1A0 *, s32);
s32 fn_8002684C(Unk_DCC2F5B0 *, Unk_F48B5CA1 *);
s32 fn_80026670(Unk_57FB3CEB *, Unk_F48B5CA1 *);
s32 fn_8002D2A0(void);
s32 fn_8002D718(void);
s32 fn_80026CA0(CStruct *arg0, CStruct *arg1) {
    s32 temp_r0;
    s32 var_r30;
    s32 var_r3;
    void *temp_r9;

    temp_r9 = (char *)arg1 + 0xC;
    var_r30 = 0;
    *((f32 *)&arg0->unk0x0) = (f32) *((f32 *)&arg1->unk0x8);
    arg0->unk0x4 = (s32) arg1->unk0x4;
    temp_r0 = arg1->unk0x4;
    if (temp_r0 & QB_UNKNOWN_0x10000000) {
        var_r3 = fn_8002684C(arg0, temp_r9);
        goto block_4;
    }
    if (temp_r0 & 0x800000) {
        var_r3 = fn_80026670(arg0, temp_r9);
block_4:
        var_r30 = var_r3;
    }
    if (arg0->unk0x4 & 0x800) {
        fn_8002D2A0();
        fn_8002AFB0(arg0, fn_8002D718());
    }
    return var_r30;
}
