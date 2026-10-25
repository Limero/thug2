// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80058F64-0x80058FB8 (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -Os
#include "types.h"
#include "types.h"
#include "structs.h"
extern char lbl_80293528[];
extern f32 lbl_80293494;
void *fn_80058F48(void *);
void *fn_80058F64(CScript *arg0) {
    f32 temp_f0;

    fn_80058F48(arg0);
    temp_f0 = lbl_80293494;
    arg0->unk0x34 = (s32)lbl_80293528;
    arg0->unk0x18 = 1;
    *((f32 *)&arg0->unk0x1C) = temp_f0;
    *((f32 *)&arg0->unk0x20) = temp_f0;
    return arg0;
}
