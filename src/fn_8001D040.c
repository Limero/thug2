// translate @ 0x8001D040  (retail p_matrix.o::translate, 172B)
// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001D040-0x8001D0F0 (176B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void PSMTXTrans(void *, f32, f32, f32);
void PSMTXConcat(void *, void *, void *);
void translate(void *arg0, f32 *arg1, s32 arg2) {
    f32 sp8[12];
    switch (arg2) {
    case 0:
        PSMTXTrans(arg0, arg1[0], arg1[1], arg1[2]);
        return;
    case 1:
        PSMTXTrans(sp8, arg1[0], arg1[1], arg1[2]);
        PSMTXConcat(arg0, sp8, arg0);
        return;
    case 2:
        PSMTXTrans(sp8, arg1[0], arg1[1], arg1[2]);
        PSMTXConcat(sp8, arg0, arg0);
        return;
    }
}
