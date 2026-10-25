// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003FBF0-0x8003FC34 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

typedef struct {
    char pad0[0xC];
    u32 unk0xC;
    char pad1[0x78];
    f32 unk0x88;
    char pad2[0x44];
    f32 unk0xD0;
} O3FBF0;

// CScreenElement_SetAlpha @ 0x8003FBF0
void CScreenElement_SetAlpha(O3FBF0 *arg0, s32 arg1, f32 farg0) {
    if (arg0->unk0xD0 != farg0) {
        arg0->unk0xD0 = farg0;
        arg0->unk0xC |= 0x400;
    }
    if ((arg1 != 0) && (arg0->unk0x88 != farg0)) {
        arg0->unk0x88 = farg0;
        arg0->unk0xC |= 0x400;
    }
}
