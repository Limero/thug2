// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A3308-0x800A33E4 (220B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_800A4F5C(CStruct *, CScript *);
void fn_8009E1F0(Unk_C8FEE62D *, s32);
s32 GetFreshId(CStruct *);
extern CStruct *lbl_80301A78;
void fn_800A3308(Unk_C7387A53 *arg0, Unk_C8FEE62D *arg1) {
    s32 temp_r0;
    CStruct *temp_r30;
    CStruct *temp_r10;
    CStruct *temp_r8;
    CStruct *temp_r9;
    CStruct *var_r11;
    s32 key;
    s32 u;

    temp_r30 = lbl_80301A78;
    temp_r10 = (CStruct *)((char *)arg1 + 0x2C);
    arg1->unk0x10 = (s32)arg0;
    temp_r8 = (CStruct *)((char *)arg0 + 4);
    key = temp_r10->unk0x8;
    var_r11 = temp_r8;
    for (;;) {
        temp_r9 = (CStruct *)var_r11->unk0xC;
        temp_r0 = temp_r9->unk0x4;
        var_r11 = temp_r9;
        if (temp_r0 == -1) {
            var_r11 = NULL;
        }
        if (var_r11 == NULL) {
            break;
        }
        if ((s32)var_r11->unk0x8 <= key) {
            u = var_r11->unk0x10;
            temp_r10->unk0xC = (s32)var_r11;
            temp_r10->unk0x10 = u;
            ((CStruct *)var_r11->unk0x10)->unk0xC = (s32)temp_r10;
            var_r11->unk0x10 = (s32)temp_r10;
            goto done;
        }
    }
    u = temp_r8->unk0x10;
    temp_r10->unk0xC = (s32)temp_r8;
    temp_r10->unk0x10 = u;
    ((CStruct *)temp_r8->unk0x10)->unk0xC = (s32)temp_r10;
    temp_r8->unk0x10 = (s32)temp_r10;
done:
    arg0->unk0x20 = -1;
    if ((s32)arg1->unk0x18 == -1) {
        fn_8009E1F0(arg1, GetFreshId(temp_r30));
    }
    fn_800A4F5C(temp_r30, (CScript *)arg1);
}
