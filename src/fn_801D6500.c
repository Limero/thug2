// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801D6500-0x801D657C (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "dolphin/SN_PS.h"
#include "structs.h"

s32 fn_800EB67C(Unk_C8FEE62D *, Unk_C7387A53 *);

void fn_801D6500(Unk_71062261 *arg0) {
    if (*(s32 *)((char *)*((s32 * *)&arg0->unk0x15BC) + 0xC4) == 0) {
        if (fn_800EB67C(*((void * *)&arg0->unk0x15C0), (char *)arg0 + 0xB0) != 0) {
            __ps_t *d;
            s32 ent;
            s32 holder;
            s32 src;
            __ps_t t13;
            __ps_t t12;

            ent = arg0->unk0x15C0;
            holder = ((Unk_31DE137E *)ent)->unk0x1C;
            d = (__ps_t *)*((void * *)&arg0->unk0xC);
            t13 = d[23];
            src = *(s32 *)holder;
            t12 = d[24];
            t13 = ps_sub(t13, ((__ps_t *)src)[23]);
            d[23] = t13;
            t12 = ps_sub(t12, ((__ps_t *)src)[24]);
            d[24] = t12;
        }
    }
}
