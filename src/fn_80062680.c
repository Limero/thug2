// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80062680-0x800626E8 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 lbl_80301B48;
s32 fn_800F2AD8(s32, s32, s32);
s32 fn_80062B18(Unk_FFAD6788 *);

s32 fn_80062680(Unk_2FEA250A *arg0) {
    CStruct *temp_r3;
    void **var_r9;
    void **volatile sp8;
    CStruct *temp_r9;
    s32 base;

    if ((s16)arg0->unk0x4E == 1) {
        base = lbl_80301B48;
        temp_r3 = (CStruct *)arg0->unk0x10;
        var_r9 = NULL;
        if (temp_r3 != NULL) {
            var_r9 = (void **)temp_r3->unk0x4;
        }
        sp8 = var_r9;
        temp_r9 = (CStruct *)*var_r9;
        return fn_80062B18((Unk_FFAD6788 *)fn_800F2AD8(base, temp_r9->unk0x10, 1));
    }
    return 0;
}
