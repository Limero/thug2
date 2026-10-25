// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E2BD0-0x800E2C2C (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct { char _pad[0x20]; s32 sub; } Obj;
void fn_80069988(void *, f32);                                 /* field setter   */
void fn_80069890(void *);              /* sub->flush()              */
s32 fn_80128CE0(void *, s32, f32 *, s32);  /* (script ctx, 0, &out, 1)  */
bool fn_800E2BD0(Obj *arg0, void *arg1) {
    f32 sp8;
    fn_80128CE0(arg1, 0, &sp8, 1);
    if (arg0->sub != 0) {
        fn_80069988(arg0->sub, sp8);
        fn_80069890(arg0->sub);
    }
    return true;
}
