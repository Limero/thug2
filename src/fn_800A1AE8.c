// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A1AE8-0x800A1B5C (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_8009FC60(void *, void *, void *);
#include "structs.h"
s32 fn_8009FCD8(s32, s32);
typedef struct { char pad0x0[0x48]; s16 unk0x48; char pad0x4A[2]; s32 unk0x4C; } View1AE8;
void *fn_800A1AE8(s32 arg0, CStruct *arg1, Unk_C7387A53 *arg2, s32 arg3) {
    void *temp_r31;
    View1AE8 *temp_r9;

    temp_r31 = fn_800A1A84();
    fn_8009FCD8((s32) temp_r31, arg2);
    fn_8009FC60(temp_r31, arg1, arg2);
    if (arg3 != 0) {
        temp_r9 = (View1AE8 *)((Unk_9994C3F5 *)temp_r31)->unk0x8;
        ((s32 (*)(void *))temp_r9->unk0x4C)(temp_r31 + temp_r9->unk0x48);
    }
    return temp_r31;
}
