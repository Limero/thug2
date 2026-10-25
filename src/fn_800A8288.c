// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A8288-0x800A8328 (160B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_800A7D1C(s32, s32);
#include "structs.h"
#include "mem.h"
void fn_800A8288(CStruct *arg0) {
    void *temp_r9;
    void *var_r31;

    if ( arg0->unk0x0 != NULL) {
        fn_800A807C();
        temp_r9 = arg0->unk0x0;
        if (temp_r9 != NULL) {
            var_r31 = temp_r9 + (*(s32 *)((char *)temp_r9 - 0x8) * 8);
            if (temp_r9 != var_r31) {
                do {
                    var_r31 -= 8;
                    fn_800A7D1C(var_r31, 0);
                } while ( arg0->unk0x0 != var_r31);
            }
            Mem_Free2(arg0->unk0x0 - 8);
        }
        arg0->unk0x0 = NULL;
        if ((s32) arg0->unk0x4 != 0) {
            fn_800A7D1C((s32) arg0->unk0x4, (void *)3);
        }
        arg0->unk0x4 = 0;
    }
}
