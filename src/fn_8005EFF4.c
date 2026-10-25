// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005EFF4-0x8005F058 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct {
    char pad0x0[0x18];
    s16 unk0x18;
    char pad0x1A[0x2];
    s32 unk0x1C;
} VtEFF4;
void fn_8005EFF4(Unk_C8FEE62D *arg0, s32 arg1) {
    VtEFF4 *temp_r9;
    CStruct *temp_r3;

    temp_r9 = (VtEFF4 *)arg0->unk0x14;
    temp_r3 = (CStruct *)((s32 (*)(void *))temp_r9->unk0x1C)((char *)arg0 + temp_r9->unk0x18);
    if (temp_r3 != NULL) {
        temp_r3->unk0x4 = (arg1 != 0) ? 1 : 2;
        temp_r3->unk0xC = 0;
    }
}
