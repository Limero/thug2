// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005EF7C-0x8005EFF4 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct {
    char pad0x0[0x10];
    s16 unk0x10;
    char pad0x12[0x2];
    s32 unk0x14;
} VtEF7C;
void fn_8005EF7C(Unk_C8FEE62D *arg0, s32 arg1) {
    VtEF7C *temp_r9;
    CStruct *temp_r3;
    s32 temp_r0;

    temp_r9 = (VtEF7C *)arg0->unk0x14;
    temp_r3 = (CStruct *)((s32 (*)(void *))temp_r9->unk0x14)((char *)arg0 + temp_r9->unk0x10);
    if (temp_r3 != NULL) {
        /* ONE reused scratch: want's r0 holds the mode value, the
           arg0->unk0x8 load and the trailing zero store in turn. */
        temp_r0 = 2;
        if (arg1 != 0) {
            temp_r0 = 1;
        }
        temp_r3->unk0x4 = temp_r0;
        temp_r0 = arg0->unk0x8;
        if (temp_r0 != 0) {
            temp_r3->unk0x8 = temp_r0;
        }
        temp_r3->unk0xC = 0;
    }
}
