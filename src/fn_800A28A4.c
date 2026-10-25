// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A28A4-0x800A28F0 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_80297DD8[];
typedef struct SFX {
    void *unk0x0;
    void *unk0x4;
} SFX;
void fn_800A28F0(void);
void fn_800A2D10(s32, void *, s32, ...);
void fn_800A28A4(void) {
    SFX sp8;

    sp8.unk0x4 = lbl_80297DD8;
    fn_800A28F0();
    fn_800A2D10(-1, &sp8, 0);
}
