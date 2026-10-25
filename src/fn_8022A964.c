// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022A964-0x8022A9A4 (64B). Byte-identical.
#include "types.h"
#include "structs.h"

extern s32 fn_800145AC(void);

s32 fn_8022A964(CScript *arg0) {
    return (u32)(fn_800145AC() - arg0->unk0x1E8) > 0x1388;
}
