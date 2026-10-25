// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80081630-0x800816AC (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct {
    char pad0x0[0x188];
    s16 unk0x188;
    s32 unk0x18C;
} DispRec_80081630;
void fn_80081630(Unk_DB0E2BAB *arg0, s32 arg1) {
    s32 i;
    CStruct *temp_r11;
    DispRec_80081630 *temp_r9;

    for (i = 0; i < arg0->unk0x24; i++) {
        temp_r11 = *(CStruct **)((char *)arg0->unk0x20 + i * 4);
        temp_r11->unk0x10 = (s32) ((u32) temp_r11->unk0x10 | 0x80000000);
    }
    if (arg1 != 0) {
        temp_r9 = (DispRec_80081630 *) arg0->unk0x14;
        ((s32 (*)(void *)) temp_r9->unk0x18C)((char *) arg0 + temp_r9->unk0x188);
    }
}
