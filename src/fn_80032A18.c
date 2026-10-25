// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80032A18-0x80032A60 (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

void fn_8002DD70(s32);
extern f32 lbl_80291B44;

void fn_80032A18(Unk_C8FEE62D *arg0) {
    f32 v;

    fn_8002DD70((s32)arg0 + 4);
    v = lbl_80291B44;
    *(s32 *)((char *)arg0 + 0x3C) = 0;
    *(f32 *)((char *)arg0 + 0x60) = v;
    *(f32 *)((char *)arg0 + 0x64) = v;
}
