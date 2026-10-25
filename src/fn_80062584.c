// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80062584-0x80062594 (16B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct S_80062584 {
    char pad0x0[0x48];
    u32 a:3;
    u32 b:1;
    u32 c:28;
} S_80062584;
void fn_80062584(S_80062584 *arg0, s32 arg1) {
    arg0->b = arg1;
}
