// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CC2D4-0x800CC314 (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct {
    char _pad0[0x24];
    s32 *unk24;
} S_800CC2D4_A;

typedef struct {
    char _pad0[0x210];
    s32 *unk210;
} S_800CC2D4_B;

typedef struct {
    char _pad0[0x48];
    s32 unk48;
} S_800CC2D4_C;

s32 fn_800CC2D4(void *arg0) {
    S_800CC2D4_B *b;
    s32 f;
    s32 m;
    s32 v;
    s32 res;

    b = (S_800CC2D4_B *)((S_800CC2D4_A *)arg0)->unk24;
    res = 0;
    b = (S_800CC2D4_B *)b->unk210;
    if (b != NULL) {
        f = ((S_800CC2D4_C *)b)->unk48;
        m = 0x20000000;
        v = 0;
        if (f & QB_UNKNOWN_0x40000000) {
            v = (f & m) == 0;
        }
        if (v != 0) {
            res = 1;
        }
    }
    return res;
}
