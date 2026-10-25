// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009C738-0x8009C778 (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    char p0[0x34];
    s32 unk0x34;
    char p1[8];
    s32 unk0x40;
} Rec738;
typedef struct {
    f32 unk0;
    f32 val;
} Elem738;
void fn_8009C738(Rec738 *arg0, f32 farg0) {
    s32 i;

    for (i = 0; i < arg0->unk0x40; i++) {
        Elem738 *temp_r9 = (Elem738 *) (i * 8 + arg0->unk0x34);
        temp_r9->val = temp_r9->val + farg0;
    }
}
