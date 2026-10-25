// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80024564-0x800245E0 (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern f32 lbl_8029133C;
extern f32 lbl_80291340;
f32 tanf(f32);
f32 fn_8005E1DC(void);
void fn_80024564(Unk_FFAD6788 *arg0) {
    volatile double _dummy;
    volatile double _dummy2;
    volatile double _dummy3;
    f32 a;
    f32 b;
    f32 n;
    f32 d;
    a = lbl_8029133C;
    b = lbl_80291340;
    n = tanf(*(f32 *)&arg0->unk0xBC * a * b);
    d = tanf(fn_8005E1DC() * a * b);
    *(f32 *)&arg0->unk0xC0 = n / d;
}
