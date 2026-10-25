// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AE0D4-0x800AE194 (192B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum(CStruct *, s32);
s32 fn_801259C8(s32, s32);
s32 fn_8009F498(s32);
s32 GetChecksum_3(s32, s32);
void fn_80060E84(s32, s32);
typedef struct {
    char _00[0x10];
    s16 off;
    char _pad12[2];
    void *fn;
} Fn800AE0D4Disp;
void fn_800AE0D4(void *arg0) {
    CStruct *temp_r29;
    u32 var_r30;
    CScript *temp_r31;
    Fn800AE0D4Disp *temp_r9;

    if ((s32)((Unk_0771A7B9 *)arg0)->unk0x34B8 == 0) {
        return;
    }
    temp_r29 = (CStruct *)fn_801259C8(QB_CUTSCENEOBJECTNAMES, 0);
    if (temp_r29 != NULL) {
        for (var_r30 = 0U; var_r30 < (u32)temp_r29->unk0x4; var_r30++) {
            s32 temp_r3 = fn_8009F498(GetChecksum(temp_r29, var_r30));
            if (temp_r3 != 0) {
                temp_r31 = (CScript *)GetChecksum_3(temp_r3, QB_MODEL);
                if (temp_r31 != NULL) {
                    s32 field = temp_r31->unk0x210;
                    if (field != 0) {
                        fn_80060E84(field, 1);
                        temp_r9 = (Fn800AE0D4Disp *)temp_r31->unk0x18;
                        ((void (*)(void *))temp_r9->fn)((char *)temp_r31 + temp_r9->off);
                    }
                }
            }
        }
    }
}
