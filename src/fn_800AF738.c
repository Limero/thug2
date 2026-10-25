// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AF738-0x800AF78C (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -Os
#include "types.h"
#include "structs.h"
extern float lbl_80298668[];
void fn_800AB80C(void);
void fn_800ACC2C(void *, s32);
void fn_800AF738(Unk_8B173D47 *arg0) {
    f32 temp_f0;

    if (arg0->unk0x34B8 == 0) {
        temp_f0 = lbl_80298668[0];
        *((f32 *)&arg0->unk0x3484) = temp_f0;
        *((f32 *)&arg0->unk0x3480) = temp_f0;
        fn_800AB80C();
        fn_800ACC2C(arg0, arg0->unk0x34D4);
    }
}
