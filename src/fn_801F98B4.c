// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F98B4-0x801F9988 (212B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
extern f32 lbl_802AE568;
extern f32 lbl_802AE56C;
extern char lbl_802AE430[];

bool fn_801F98B4(Unk_C7387A53 *arg0, Unk_EA529D06 *arg1, Unk_EA529D06 *arg2, CStruct *arg3, CStruct *arg4,
                s32 arg5) {
    void *head;
    Unk_F68EF90C *node;
    volatile __ps_t slotA;
    volatile __ps_t slotB;
    volatile __ps_t slotC;
    __ps_t *pa;
    __ps_t *wp;
    __ps_t base0;
    __ps_t base1;
    __ps_t np0;
    register __ps_t np1 __asm__("fr13");
    __ps_t d0;
    __ps_t d1;
    __ps_t acc;
    __ps_t sq;
    __ps_t cpair;
    __ps_t np;
    register f32 best;
    register f32 ky;
    register f32 dist __asm__("fr13");
    register s32 found __asm__("r3");

    head = *((void * *)&arg0->unk0xC);
    if (head == NULL) {
        return false;
    }
    best = lbl_802AE568;
    ky = lbl_802AE56C;
    node = head;
    for (found = 0, pa = (__ps_t *)&slotA; node != NULL;
         node = node->unk0x24, found += 1) {
        if (found == arg5) {
            continue;
        }
        wp = (__ps_t *)node;
        base0 = arg1->unk0x0;
        np0 = *++wp;
        base1 = arg1->unk0x8;
        np1 = wp[1];
        d0 = __builtin_ps_sub(np0, base0);
        slotA = d0;
        d1 = __builtin_ps_sub(np1, base1);
        __asm__ volatile("" : "+f"(d1));
        ((Unk_C7780169_3 *)&slotA)->unk0x4 = ky;
        slotB = d1;
        acc = slotA;
        sq = ((Unk_7AAFF886_2 *)pa)->unk0x8;
        cpair = *(volatile __ps_t *)lbl_802AE430;
        sq = __builtin_ps_mul(sq, sq);
        sq = __builtin_ps_merge00(sq, cpair);
        acc = __builtin_ps_madd(acc, acc, sq);
        acc = __builtin_ps_sum0(acc, acc, acc);
        slotC = acc;
        dist = ((Unk_7D81B2AB_4 *)&slotC)->unk0x0;
        {
            f32 cmpv;
            __asm__("" : "=f"(cmpv) : "0"(dist));
            if (!(cmpv < best)) {
                continue;
            }
            np = node->unk0x8;
            best = cmpv;
            arg2->unk0x0 = np;
            arg2->unk0x8 = wp[1];
            *((f32 *)&arg3->unk0x0) = best;
            arg4->unk0x0 = found;
        }
    }
    return true;
}