// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003A80C-0x8003A8D0 (196B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-strength-reduce -fno-schedule-insns2
#include "types.h"
#include "structs.h"
void Mem_Free(void *);
void fn_8003AE28(Unk_31DE137E *);
void fn_80126F40(CStruct *, CStruct *);
void *fn_8003A80C(Unk_31DE137E *arg0, Unk_31DE137E *arg1) {
    s32 temp_r0;
    s32 var_r10;
    void *var_r11;
    void *var_r9;

    if (arg1 == arg0) {
        return arg0;
    }
    fn_80126F40((char *)arg0 + 0x58, (char *)arg1 + 0x58);
    if (arg0->unk0x60 != NULL) {
        Mem_Free(arg0->unk0x60);
        arg0->unk0x60 = NULL;
    }
    if (arg1->unk0x60 != NULL) {
        fn_8003AE28(arg0);
        var_r11 = arg0->unk0x60;
        var_r10 = 0x44A0;
        var_r9 = arg1->unk0x60;
        do {
            var_r10 -= 0x18;
            temp_r0 = ((Unk_DB0E2BAB *)var_r9)->unk0x0;
            ((Unk_DB0E2BAB *)var_r11)->unk0x0 = temp_r0;
            temp_r0 = ((Unk_DB0E2BAB *)var_r9)->unk0x4;
            ((Unk_DB0E2BAB *)var_r11)->unk0x4 = temp_r0;
            temp_r0 = ((Unk_DB0E2BAB *)var_r9)->unk0x8;
            ((Unk_DB0E2BAB *)var_r11)->unk0x8 = temp_r0;
            temp_r0 = ((Unk_DB0E2BAB *)var_r9)->unk0xC;
            ((Unk_DB0E2BAB *)var_r11)->unk0xC = temp_r0;
            temp_r0 = ((Unk_DB0E2BAB *)var_r9)->unk0x10;
            ((Unk_DB0E2BAB *)var_r11)->unk0x10 = temp_r0;
            temp_r0 = ((Unk_DB0E2BAB *)var_r9)->unk0x14;
            ((Unk_DB0E2BAB *)var_r11)->unk0x14 = temp_r0;
            var_r9 += 0x18;
            var_r11 += 0x18;
        } while (var_r10 != 0);
    }
    return (arg0->unk0x64 = (s32)arg1->unk0x64, arg0);
}
