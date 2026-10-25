// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DDD34-0x800DDD98 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

typedef struct {
    char pad0x0[0x30];
    s16 unk0x30;
    char pad0x32[0x2];
    s32 (*unk0x34)(void *);
    s16 unk0x38;
    char pad0x3A[0x2];
    s32 (*unk0x3C)(void *);
} DDD34_vt;

void fn_800DDD34(Unk_31DE137E *arg0, s32 arg1) {
    void *temp_r11;
    DDD34_vt *temp_r9;
    DDD34_vt *temp_r9_2;

    temp_r11 = arg0->unk0x1C;
    if (temp_r11 != NULL) {
        if (arg1 != 0) {
            temp_r9 = ((Unk_9994C3F5 *)temp_r11)->unk0x8;
            ((void (*)(void *))temp_r9->unk0x34)(temp_r11 + temp_r9->unk0x30);
            return;
        }
        temp_r9_2 = ((Unk_9994C3F5 *)temp_r11)->unk0x8;
        ((void (*)(void *))temp_r9_2->unk0x3C)(temp_r11 + temp_r9_2->unk0x38);
    }
}
