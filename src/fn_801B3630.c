// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B3630-0x801B36FC (204B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetChecksum_3(Unk_6A70655D *, s32);
extern s32 fn_800D5060(Unk_31DE137E *);
void fn_801B3630(Unk_C7387A53 *arg0) {
    __ps_t *o = *((__ps_t * *)&arg0->unk0xC);

    if (fn_800D5060((void *)GetChecksum_3((s32)o, QB_MOTION)) != 0) {
        ((__ps_t *)arg0)[41] = o[15];
        ((__ps_t *)arg0)[42] = o[16];
        ((__ps_t *)arg0)[43] = o[17];
        ((__ps_t *)arg0)[44] = o[18];
        ((__ps_t *)arg0)[45] = o[19];
        ((__ps_t *)arg0)[46] = o[20];
        ((__ps_t *)arg0)[47] = o[21];
        ((__ps_t *)arg0)[48] = o[22];
    } else {
        o[26] = ((__ps_t *)arg0)[41];
        o[27] = ((__ps_t *)arg0)[42];
        o[28] = ((__ps_t *)arg0)[43];
        o[29] = ((__ps_t *)arg0)[44];
        o[30] = ((__ps_t *)arg0)[45];
        o[31] = ((__ps_t *)arg0)[46];
        o[32] = ((__ps_t *)arg0)[47];
        o[33] = ((__ps_t *)arg0)[48];
    }
}
