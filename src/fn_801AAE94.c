// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AAE94-0x801AAF28 (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern const f32 lbl_802ABBB4;
void fn_801AAE94(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    f32 a, b, A, B, C, D, E, F, K;
    a = arg0[0]; b = arg1[0];
    if (a < b) { A = a; B = b; } else { A = b; B = a; }
    a = arg0[1]; b = arg1[1];
    if (a < b) { C = a; D = b; } else { C = b; D = a; }
    a = arg0[2]; b = arg1[2];
    if (a < b) { E = a; F = b; } else { E = b; F = a; }
    K = lbl_802ABBB4;
    arg2[0] = A; arg2[1] = C; arg2[2] = E; arg2[3] = K;
    arg3[0] = B; arg3[1] = D; arg3[2] = F; arg3[3] = K;
}
