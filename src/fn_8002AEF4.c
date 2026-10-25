// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002AEF4-0x8002AFB0 (188B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern f32 lbl_8029166C;
void fn_8002BA64(CStruct *, s32);
void *fn_8002AE84(Unk_C7387A53 *, s32);
s32 fn_8002AE7C(Unk_C7387A53 *);
typedef struct {
    char p0[0x8];
    Unk_C8FEE62D *unk0x8;
} VTAEF4;
bool fn_8002AEF4(Unk_C7387A53 *arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1) {
    f32 temp_f0;
    f32 temp_f30;
    f32 temp_f31;
    s32 temp_r3;
    s32 var_r30;
    void *temp_r3_2;
    Unk_C8FEE62D *temp_r9;
    volatile double _dummy1;
    volatile double _dummy2;
    temp_f0 = lbl_8029166C;
    temp_f31 = farg0 * temp_f0;
    var_r30 = 0;
    temp_f30 = farg1 * temp_f0;
    temp_r3 = fn_8002AE7C(arg0);
    if (var_r30 < temp_r3) {
        do {
            temp_r3_2 = fn_8002AE84(arg0, var_r30);
            temp_r9 = ((VTAEF4 *)temp_r3_2)->unk0x8;
            if (((s32 (*)(void *, f32, f32, s32))temp_r9->unk0x14)(temp_r3_2 + *(s16 *)((char *)temp_r9 + 0x10), temp_f31, temp_f30, arg2) != 0) {
                fn_8002BA64(temp_r3_2, arg1);
            }
            var_r30 += 1;
        } while (var_r30 < temp_r3);
    }
    return true;
}
