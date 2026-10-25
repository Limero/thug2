// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000702C-0x80007090 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
void fn_800063B4(void *);
void *fn_8000702C(Unk_C7387A53 *arg0, void *arg1, f32 farg0) {
    fn_800063B4(arg0);
    ((__ps_t *)arg0)[0] = ((__ps_t *)arg1)[0];
    ((__ps_t *)arg0)[1] = ((__ps_t *)arg1)[1];
    ((__ps_t *)arg0)[2] = ((__ps_t *)arg1)[2];
    ((__ps_t *)arg0)[3] = ((__ps_t *)arg1)[3];
    *(f32 *)&arg0->unk0x20 = farg0;
    return arg0;
}
