// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A35F0-0x801A362C (60B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_801A26E0(s32, s32);
typedef struct {
    char pad0x0[0x70];
    s16 unk0x70;
    char pad0x72[2];
    s32 unk0x74;
} Vt35F0;
void fn_801A35F0(s32 arg0) {
    void *temp_r3;
    Vt35F0 *temp_r9;

    temp_r3 = (void *)fn_801A26E0(arg0, 0);
    temp_r9 = ((Unk_C8FEE62D *)temp_r3)->unk0x14;
    ((s32 (*)(void *))temp_r9->unk0x74)((char *)temp_r3 + temp_r9->unk0x70);
}
