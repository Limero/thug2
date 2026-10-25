// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004602C-0x800460CC (160B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_802927FC;
extern f32 lbl_80292800;
void fn_8009F9AC(s32, s32);
void fn_8004602C(void *arg0) {
    volatile double _dummy;
    volatile double _dummy2;
    f32 temp_f31;
    f32 temp_f30;
    s32 var_r30;
    void *obj;
    void *temp_r9;
    s16 off;
    void *var_r31;

    temp_f31 = lbl_802927FC;
    temp_f30 = lbl_80292800;
    var_r31 = (char *)arg0 + 0x190;
    var_r30 = 0x19;
    do {
        if (*(s32 *)((char *)var_r31 + 0) != 0) {
            fn_8009F9AC(*(s32 *)((char *)var_r31 + 0), 1);
            obj = (void *)*(s32 *)((char *)var_r31 + 0);
            temp_r9 = (void *)*(s32 *)((char *)obj + 8);
            off = *(s16 *)((char *)temp_r9 + 0x38);
            temp_r9 = (void *)*(s32 *)((char *)temp_r9 + 0x3C);
            ((s32 (*)(void *))temp_r9)((char *)obj + off);
        }
        *(f32 *)((char *)var_r31 + 0x10) = temp_f31;
        var_r30 -= 1;
        *(f32 *)((char *)var_r31 + 0x14) = temp_f31;
        *(f32 *)((char *)var_r31 + 0x18) = temp_f31;
        *(f32 *)((char *)var_r31 + 0x1C) = temp_f30;
        var_r31 = (char *)var_r31 + 0x20;
    } while (var_r30 != 0);
    *(s32 *)((char *)arg0 + 0x4B0) = var_r30;
}
