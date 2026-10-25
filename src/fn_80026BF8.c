// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80026BF8-0x80026C44 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct S26BF8 {
    char pad0[0x38];
    u32 a : 17;
    s32 f : 8;
    u32 b : 7;
} S26BF8;
s32 fn_8002D2A0(void);
void fn_8002D548(s32, S26BF8 *);
void fn_80026BF8(S26BF8 *arg0) {
    arg0->f = arg0->f + 1;
    fn_8002D548(fn_8002D2A0(), arg0);
}
