// rotateY @ 0x8001D1B0  (retail p_matrix.o::rotateY, 172B; PSMTXRotRad axis 0x79)
// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001D1B0-0x8001D270 (192B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_80291130;
void PSMTXRotRad(void *, s32, f32);
void PSMTXConcat(void *, void *, void *);
void rotateY(void *arg0, s32 arg1, f32 farg0) {
    f32 sp8[12];
    switch (arg1) {
    case 0:
        PSMTXRotRad(arg0, 0x79, farg0 * lbl_80291130);
        return;
    case 1:
        PSMTXRotRad(sp8, 0x79, farg0 * lbl_80291130);
        PSMTXConcat(arg0, sp8, arg0);
        return;
    case 2:
        PSMTXRotRad(sp8, 0x79, farg0 * lbl_80291130);
        PSMTXConcat(sp8, arg0, arg0);
        return;
    }
}
