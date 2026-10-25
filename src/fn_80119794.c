// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80119794-0x801197FC (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern char lbl_80387E44[];

s32 fn_80119470(void);
void InitSoundFX(void *);

void *fn_80119794(Unk_9994C3F5 *arg0) {
    s32 temp_r3;
    s32 var_ctr;
    void *var_r9;

    temp_r3 = fn_80119470();
    if (temp_r3 == 0) {
        arg0->unk0x8 = temp_r3;
        InitSoundFX(arg0);
        var_ctr = 0x3B;
        var_r9 = (void *)lbl_80387E44;
        do {
            ((CStruct *)var_r9)->unk0x0 = 0;
            ((CStruct *)var_r9)->unk0x4 = 0;
            var_r9 += 0x3C;
            var_ctr -= 1;
        } while (var_ctr != 0);
    }
    return arg0;
}
