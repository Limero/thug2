// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009C66C-0x8009C6AC (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    char p0[0x28];
    s32 unk0x28;
    char p1[0x14];
    s32 unk0x40;
} Rec62C;
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 val;
} Elem66C;
void fn_8009C66C(Rec62C *arg0, f32 farg0) {
    s32 i;

    for (i = 0; i < arg0->unk0x40; i++) {
        Elem66C *temp_r9 = (Elem66C *) (i * 12 + arg0->unk0x28);
        temp_r9->val = temp_r9->val + farg0;
    }
}
