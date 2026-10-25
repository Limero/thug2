// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007B9DC-0x8007BA3C (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_8007BAA8(void *);
#include "structs.h"
#include "mem.h"
s32 fn_80058778(s32, s32);
// f32 signature: want `lfs f1,0x5bd0(r9)` then a bare `bl` — without this
// prototype ngccc treats the float arg as a varargs call and emits an extra
// `crset cr1eq` (the 100B-vs-96B delta).
s32 fn_80094858(f32);
extern f32 lbl_80295BD0;
extern char lbl_80295BD8[];
void *fn_8007B9DC(Unk_C7387A53 *arg0) {
    fn_80058778(arg0, 0);
    arg0->unk0x50 = (s32)lbl_80295BD8;
    Mem_Alloc2(0x44);
    arg0->unk0x54 = fn_80094858(lbl_80295BD0);
    fn_8007BAA8(arg0);
    return arg0;
}
