// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80096E4C-0x80096F20 (212B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_8037B614[];
#include "structs.h"
void fn_8001D424(f32 *);
void PSMTXMultVec(void *, void *, f32 *);

// lbl_8037B5E8 + 0x130 .. +0x144: six f32 bounds, addressed off one base reg.
typedef struct {
    u8 pad0x0[0x130];
    f32 b[6];
} Bounds;

extern Bounds lbl_8037B5E8;

s32 fn_80096E4C(Unk_C7387A53 *arg0) {
    f32 sp[4];
    s32 var_r3;
    f32 *av = (f32 *)arg0;

    fn_8001D424(sp);
    PSMTXMultVec(lbl_8037B614, arg0, sp);
    if (av[3] < sp[2] - lbl_8037B5E8.b[4]
     || av[3] < lbl_8037B5E8.b[5] - sp[2]
     || av[3] < lbl_8037B5E8.b[0] * sp[2] - lbl_8037B5E8.b[2] * sp[0]
     || av[3] < lbl_8037B5E8.b[0] * sp[2] + lbl_8037B5E8.b[2] * sp[0]
     || av[3] < lbl_8037B5E8.b[1] * sp[2] - lbl_8037B5E8.b[3] * sp[1]) {
        var_r3 = 0;
    } else {
        var_r3 = 1;
        if (av[3] < lbl_8037B5E8.b[1] * sp[2] + lbl_8037B5E8.b[3] * sp[1]) {
            var_r3 = 0;
        }
    }
    return var_r3;
}
