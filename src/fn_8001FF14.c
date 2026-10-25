// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001FF14-0x8001FF58 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// fn_8001DD28(0,0) then GXInit(arg0,arg1) passthrough. GXInit declared
// `extern f32` so ngccc emits no crclr cr1eq before its bl (SN float-return
// convention, §4p item-27). Suggested name: GXInitPassthrough.
#include "types.h"
void fn_8001DD28(s32, s32);
extern f32 GXInit(s32, s32);
void fn_8001FF14(s32 arg0, s32 arg1) {
    fn_8001DD28(0, 0);
    GXInit(arg0, arg1);
}
