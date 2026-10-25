// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801252BC-0x801252F0 (52B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    u32 a : 8;
    u32 b : 1;
    u32 c : 7;
    u32 d : 16;
    s32 unk0x04;
    s32 unk0x08;
    s32 unk0x0C;
} T252BC;
void *fn_801252BC(void *arg0) {
    T252BC *p = (T252BC *)arg0;
    p->unk0x0C = 0;
    p->unk0x04 = 0;
    p->unk0x08 = 0;
    p->c = 0;
    p->d = 0;
    p->b = 0;
    return arg0;
}
