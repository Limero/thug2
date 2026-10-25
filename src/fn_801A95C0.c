// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A95C0-0x801A9600 (64B). Byte-identical.
#include "types.h"
#include "structs.h"

extern void fn_801A9C1C(s32, s32, void *);
extern void fn_801A9584(Unk_C7387A53 *, s32 *);

s32 fn_801A95C0(s32 arg0, s32 arg1) {
    struct ctx { s32 unk0; s32 unk4; } ctx;

    ctx.unk4 = arg1;
    ctx.unk0 = 0;
    fn_801A9C1C(arg0 + 8, (s32)fn_801A9584, &ctx);
    return ctx.unk0;
}
