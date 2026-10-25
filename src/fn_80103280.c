// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80103280-0x80103320 (160B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 Mem_Free2(s32);
void fn_80102ADC(void *, s32);
s32 fn_80102D18(Unk_ECD1B899 *);
bool fn_80103280(Unk_C7387A53 *arg0) {
    void *temp_r3;
    void *temp_r9;
    void *var_r31;
    if (arg0->unk0x34 != NULL) {
        temp_r3 = fn_80102D18((Unk_ECD1B899 *)arg0->unk0x34);
        if (temp_r3 != NULL) {
            Mem_Free2(temp_r3);
        }
        temp_r9 = arg0->unk0x34;
        if (temp_r9 != NULL) {
            var_r31 = temp_r9 + (*(s32 *)((char *)temp_r9 - 0x8) * 8);
            if (temp_r9 != var_r31) {
                do {
                    var_r31 -= 8;
                    fn_80102ADC(var_r31, 0);
                } while (arg0->unk0x34 != var_r31);
            }
            Mem_Free2(arg0->unk0x34 - 8);
        }
        arg0->unk0x34 = NULL;
        return true;
    }
    return false;
}
