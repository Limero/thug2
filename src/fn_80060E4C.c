// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80060E4C-0x80060E84 (56B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

typedef struct {
    char pad0[0x48];
    u32 b0 : 1;
    u32 b1 : 1;
    u32 flag : 1;
    u32 rest : 29;
} T60E4C;

s32 fn_80060E84(T60E4C *, s32);

void fn_80060E4C(T60E4C *arg0, s32 arg1)
{
    arg0->flag = arg1;
    fn_80060E84(arg0, arg1 ^ 1);
}
