// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A96B8-0x801A96FC (68B). Byte-identical.
#include "types.h"
#include "structs.h"

extern void fn_801A9C1C(s32, s32, void *);
extern void fn_801A9638(CScript *, Unk_43D5C83F *);

s32 fn_801A96B8(s32 arg0, s8 arg1) {
    struct ctx { s32 unk0; u8 unk4; s32 unk8; } ctx;

    ctx.unk4 = arg1;
    ctx.unk0 = 0;
    ctx.unk8 = 0;
    fn_801A9C1C(arg0 + 8, (s32)fn_801A9638, &ctx);
    return ctx.unk0;
}
