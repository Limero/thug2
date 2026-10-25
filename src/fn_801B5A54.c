// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B5A54-0x801B5BBC (360B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern void *GetChecksum_3(Unk_6A70655D *, s32);
extern f32 fn_801B608C(s32);
extern f32 fn_801B61B0(s32);
extern void fn_801B5BBC(Unk_C7387A53 *);

void fn_801B5A54(s32 arg0) {
    volatile struct {
        __ps_t T[8];
        __ps_t ra;
        __ps_t rc;
        __ps_t rd;
        __ps_t rb;
        __ps_t v1;
        __ps_t v2;
    } fr;
    register char *a0 __asm__("r31");
    register char *cv __asm__("r30");
    f32 pav;
    f32 pbv;
    register __ps_t *spp __asm__("r9");
    register __ps_t *dpp __asm__("r10");
    register __ps_t *rpp __asm__("r8");
    register f32 p68 __asm__("fr13");
    register f32 p70 __asm__("fr0");
    register __ps_t w0 __asm__("fr0");
    register __ps_t w13 __asm__("fr13");
    register __ps_t rdReg __asm__("fr11");
    Unk_DF2324A8 *o1;
    Unk_5F85C510 *o2;

    a0 = (char *)arg0;
    cv = (char *)GetChecksum_3(((Unk_E266FB50_2 *)a0)->unk0xC, QB_MOTION);
    pav = fn_801B608C(a0);
    pbv = fn_801B61B0(a0);
    fn_801B5BBC(a0);
    __asm__ volatile(
        "lfs 13, 0xa4(31)\n\t"
        "li 0, 4\n\t"
        "lfs 0, 0x34(30)\n\t"
        "mtctr 0\n\t"
        "lwz 9, 0xc(31)\n\t"
        "addi 10, 1, 8\n\t"
        "fmuls 0, 0, 13\n\t"
        "mr 8, 10\n\t"
        "fmuls 13, 0, 31\n\t"
        "addi 9, 9, 0xd0\n\t"
        "fmuls 0, 0, 30\n\t"
        ".long 0x42000000"
        : "=r"(spp), "=r"(dpp), "=r"(rpp), "=f"(p68), "=f"(p70)
        : "r"(a0), "r"(cv));
    __asm__ volatile("" :: "f"(pav), "f"(pbv));
    dpp[0] = spp[0];
    *(f32 *)&fr.v1 = p68;
    dpp[1] = spp[1];
    *(f32 *)&fr.v2 = p70;
    dpp[2] = spp[2];

    o1 = ((Unk_E266FB50_2 *)a0)->unk0xC;
    dpp[3] = spp[3];
    dpp[4] = spp[4];
    dpp[5] = spp[5];
    dpp[6] = spp[6];
    dpp[7] = spp[7];
    w0 = fr.v1;
    w13 = ((__ps_t volatile *)rpp)[1];
    __asm__ volatile(
        "ps_mr 9, 0\n\t"
        "psq_l 12, 40(1), 0, 0\n\t"
        "psq_l 0, 112(1), 0, 0\n\t"
        "psq_l 11, 8(1), 0, 0\n\t"
        "ps_muls0 12, 12, 9\n\t"
        "ps_mr 10, 0\n\t"
        "psq_st 12, 72(1), 0, 0\n\t"
        "psq_l 0, 48(1), 0, 0\n\t"
        "ps_muls0 13, 13, 10\n\t"
        "ps_muls0 0, 0, 9\n\t"
        "psq_st 13, 96(1), 0, 0\n\t"
        "ps_muls0 11, 11, 10\n\t"
        "psq_st 0, 80(1), 0, 0\n\t"
        "psq_st 11, 88(1), 0, 0"
        : "=f"(rdReg)
        : "f"(w0), "f"(w13) : "fr9", "fr10", "fr12");
    o1->unk0x58 = __builtin_ps_add(o1->unk0x58, rdReg);
    o1->unk0x60 = __builtin_ps_add(o1->unk0x60, fr.rb);
    o2 = ((Unk_E266FB50_2 *)a0)->unk0xC;
    *((__ps_t volatile *)&o2->unk0x58) = __builtin_ps_add(o2->unk0x58, fr.ra);
    o2->unk0x60 = __builtin_ps_add(*((__ps_t volatile *)&o2->unk0x60), fr.rc);
}
