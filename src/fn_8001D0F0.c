// rotateX @ 0x8001D0F0  (retail p_matrix.o::rotateX, 172B; PSMTXRotRad axis 0x78)
// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001D0F0-0x8001D1B0 (192B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_8029112C;
void PSMTXRotRad(void *, s32, f32);
void PSMTXConcat(void *, void *, void *);
void rotateX(void *arg0, s32 arg1, f32 farg0) {
    f32 sp8[12];
    switch (arg1) {
    case 0:
        PSMTXRotRad(arg0, 0x78, farg0 * lbl_8029112C);
        return;
    case 1:
        PSMTXRotRad(sp8, 0x78, farg0 * lbl_8029112C);
        PSMTXConcat(arg0, sp8, arg0);
        return;
    case 2:
        PSMTXRotRad(sp8, 0x78, farg0 * lbl_8029112C);
        PSMTXConcat(sp8, arg0, arg0);
        return;
    }
}
