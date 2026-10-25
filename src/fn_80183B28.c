// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80183B28-0x80183BC0 (152B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

typedef struct N_80183B28 {
    char pad0x0[0x8];
    s16 unk0x8;
    char pad0xA[0x2];
    void (*unk0xC)(void *, s32);
    char pad0x10[0x4];
    struct N_80183B28 *unk0x14;
    s32 unk0x18;
} N_80183B28;

s32 fn_8018B46C(void *, s32 *);
void fn_8018B568(void *, s32 *);
void fn_80191DBC(void *);

bool fn_80183B28(Unk_C7387A53 *arg0, s32 arg1) {
    volatile s32 sp8;
    s32 temp_r29;
    N_80183B28 *temp_r3;
    N_80183B28 *temp_r9;

    temp_r29 = (char *)arg0 + 4;
    sp8 = arg1;
    temp_r3 = (N_80183B28 *)fn_8018B46C(temp_r29, &sp8);
    fn_80191DBC(temp_r3->unk0x18);
    fn_8018B568(temp_r29, (sp8 = arg1, &sp8));
    if (arg0->unk0x38 == arg1) {
        arg0->unk0x38 = 0;
    }
    if (temp_r3 != NULL) {
        temp_r9 = temp_r3->unk0x14;
        temp_r9->unk0xC((char *)temp_r3 + temp_r9->unk0x8, 3);
    }
    return true;
}
