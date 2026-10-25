// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E2B7C-0x800E2BD0 (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct { char _pad[0x20]; s32 sub; } Obj;
void fn_80069980(void *, f32);                                 /* field setter   */
s32 fn_80128CE0(void *, s32, f32 *, s32);  /* (script ctx, 0, &out, 1)  */
bool fn_800E2B7C(Obj *arg0, void *arg1) {
    f32 sp8;
    fn_80128CE0(arg1, 0, &sp8, 1);
    if (arg0->sub != 0) {
        fn_80069980(arg0->sub, sp8);
    }
    return true;
}
