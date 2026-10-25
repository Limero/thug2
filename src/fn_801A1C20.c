// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A1C20-0x801A1C7C (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

f32 fn_8002DE3C(void *);
void fn_80024610(void *);
void fn_801A1BE4(void *, s32, f32, f32);

void fn_801A1C20(void *arg0) {
    volatile double _dummy;   /* FPR-frame +8 quirk (issue-01): want 0x28, not 0x20 */
    f32 v;
    void *p;

    p = (char *)arg0 + 0x74;
    v = *(f32 *)((char *)p + 0x1c);
    fn_8002DE3C(p);
    fn_80024610(*(void **)((char *)arg0 + 0x18));
    fn_801A1BE4(arg0, 0, v, *(f32 *)((char *)p + 0x1c));
}
