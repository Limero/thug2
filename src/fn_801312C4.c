// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801312C4-0x80131314 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
typedef union U12C4 { s32 word; struct { u32 a : 2; u32 flag : 1; u32 rest : 29; } bf; } U12C4;
typedef struct S12C4 { char pad0x0[0xCC]; U12C4 v; } S12C4;
S12C4 *fn_8012ED7C(S12C4 *);
void fn_801312C4(s32 arg0) {
    S12C4 *r = 0;

    while ((r = fn_8012ED7C(r)) != 0) {
        if (r->v.word < 0) {
            r->v.bf.flag = arg0;
        }
    }
}
