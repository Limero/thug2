// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E9BFC-0x800E9C84 (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"

extern f32 lbl_8029AB84;
extern f32 lbl_8029AB88;

typedef struct CStruct CStruct;
CStruct *GetStructure(s32, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);

f32 fn_800E9BFC(void *arg0) {
    __ps_t sp8[2];
    f32 sp18;
    register f32 ret __asm__("fr1");
    void *v;
    v = *(void **)((char *)arg0 + 0x1844);
    v = *(void **)((char *)v + 0x210);
    if ((*(u32 *)((char *)v + 0x48) & 0x10000000) == 0) {
        ret = lbl_8029AB88;
    } else {
        sp8[0] = *(__ps_t *)((char *)v + 0x20);
        sp8[1] = *(__ps_t *)((char *)v + 0x28);
        GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_HANG_VERT_ORIGIN_OFFSET,
                 &sp18, 1);
        ret = (lbl_8029AB84 - ((f32 *)sp8)[1]) * sp18;
    }
    return ret;
}
