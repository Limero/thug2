// WIP DRAFT (non-matching) — hand-rebuilt from disasm (PS skel-bone matrix update).
// REFRESHED 2026-10-07 (FPR-pin RETARGET sweep): 2.9825% -> 10.8772%
//   the `ang` pin was retargeted fr1 -> fr21 (nothing else touched).  New axis:
//   fr-pin REMOVAL had been swept, retargeting had not.  AGENTS-recipes §6hk.
// family=hand range=0x801AA2D4-0x801AABBC size=2280B
// PARKED: 3.2% (-mps-float). Structure fully reconstructed & semantically
// faithful: triple chained call 38C04(C9780(FDD8(obj,QB_SKELETON)),QB_BONE_HEAD,m1)
// (FDD8's return feeds C9780 — r3 never reloaded), doc-30 bdnz-$ spin window
// reproduced verbatim (li/lis/mtctr/lfs-f1-arg/addi x3/bdnz$), escape-pointer
// psb forces the sp88 store-reload of the E0C rot-matrix ptr, both 4x4
// products + vec-matrix product written in want's exact operand order, all
// __ps_t pair copies incl. the shuffled tail of product-1's writeback.
// Prologue/epilogue/frame match byte-exact (volatile-double dummy gives the
// 0xF8 frame). Remaining blocker = allocator wall (docs/parkings family,
// cf. fn_8017EF1C/fn_801815EC): want homes arg0 in r30 / m1 in r31 while this
// cc1 unconditionally stages the entry param through r31 first (mr r31,r3),
// cascading every saved-reg role down one slot. Resisted: local+file-scope
// register pins on arg0/r30 and m1/r31, hidden dead leading param (r4 form),
// av-temp copy, m1-before-obj statement order, -fno-schedule-insns(+insns2),
// decl-init reorder, inline-m1-in-call-arg. Same wall as parks.
// extra_cflags: -mps-float
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 3.0% ([4]rev->3.0%).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802ABAE0;
extern f32 lbl_802ABAE4;
extern f32 lbl_802ABAE8;
extern f32 lbl_802ABAEC;
s32 GetChecksum_3(void *, u32);
s32 fn_800C9780(void *);
s32 fn_80038C04(s32, u32, void *);
void *fn_80003E0C(f32, void *);

void fn_801AA2D4(Unk_97629F74 *arg0) {
    volatile double _dummy;
    f32 m[16];
    f32 prod[16];
    void *sb[2];
    Unk_C5CAA753 *m1;
    Unk_5EF41E38 *m1b;
    Unk_5EF41E38 *m1c;
    Unk_5EF41E38 *m2p;
    Unk_2DDDDA62 *v;
    char *w;
    char *x;
    Unk_2CEAE3B4 *obj;
    Unk_5EF41E38 *mp;
    void **psb;
    void *sb2[2];
    register char *pb __asm__("r25");
    register void **psb2 __asm__("r22");
    register char *pe __asm__("r21");
    register f32 ang __asm__("fr21");

    if (arg0->unk0x120 != 0) {
        obj = arg0->unk0x118;
        m1 = (char *)arg0 + 0x78;
        m1b = m1;
        v = (char *)arg0 + 0xA8;
        w = (char *)arg0 + 0x88;
        x = (char *)arg0 + 0x98;
        psb = &sb[0];
        fn_80038C04(fn_800C9780(GetChecksum_3(obj, QB_SKELETON)), QB_BONE_HEAD, m1);
        __asm__ volatile("li 0,4\n\t"
                         "lis 9,lbl_802ABAE0@ha\n\t"
                         "mtctr 0\n\t"
                         "lfs 1,lbl_802ABAE0@l(9)\n\t"
                         "addi %0, 1, 0x18\n\t"
                         "addi %1, 1, 0x90\n\t"
                         "addi %2, 1, 0x54\n\t"
                         "bdnz $"
                         : "=r"(pb), "=r"(psb2), "=r"(pe), "=f"(ang)
                         :
                         : "r0", "r9", "ctr");
        psb[1] = m1;
        psb[0] = fn_80003E0C(ang, m);
        sb2[0] = m1c = m1;
        mp = (char *)psb[0];
        /* ---- product 1: sb[0](rot mtx) x m1 -> prod ---- */
        prod[0] = ((Unk_59AB5482_2 *)mp)->unk0xC * ((Unk_59AB5482_2 *)m1)->unk0x30 +
                  (mp->unk0x8 * ((Unk_59AB5482_2 *)m1)->unk0x20 +
                   (((Unk_59AB5482_2 *)mp)->unk0x0 * ((Unk_59AB5482_2 *)m1)->unk0x0 +
                    ((Unk_59AB5482_2 *)mp)->unk0x4 * ((Unk_59AB5482_2 *)m1)->unk0x10));
        prod[1] = ((Unk_59AB5482_2 *)mp)->unk0xC * ((Unk_59AB5482_2 *)m1)->unk0x34 +
                  (mp->unk0x8 * ((Unk_59AB5482_2 *)m1)->unk0x24 +
                   (((Unk_59AB5482_2 *)mp)->unk0x0 * ((Unk_59AB5482_2 *)m1)->unk0x4 +
                    ((Unk_59AB5482_2 *)mp)->unk0x4 * ((Unk_59AB5482_2 *)m1)->unk0x14));
        prod[2] = ((Unk_59AB5482_2 *)mp)->unk0xC * ((Unk_59AB5482_2 *)m1)->unk0x38 +
                  (mp->unk0x8 * ((Unk_59AB5482_2 *)m1)->unk0x28 +
                   (((Unk_59AB5482_2 *)mp)->unk0x0 * ((Unk_2DDDDA62 *)m1)->unk0x8 +
                    ((Unk_59AB5482_2 *)mp)->unk0x4 * ((Unk_59AB5482_2 *)m1)->unk0x18));
        prod[3] = ((Unk_59AB5482_2 *)mp)->unk0xC * ((Unk_59AB5482_2 *)m1)->unk0x3C +
                  (mp->unk0x8 * ((Unk_59AB5482_2 *)m1)->unk0x2C +
                   (((Unk_59AB5482_2 *)mp)->unk0x0 * ((Unk_59AB5482_2 *)m1)->unk0xC +
                    ((Unk_59AB5482_2 *)mp)->unk0x4 * ((Unk_59AB5482_2 *)m1)->unk0x1C));
        prod[4] = ((Unk_59AB5482_2 *)mp)->unk0x1C * ((Unk_59AB5482_2 *)m1)->unk0x30 +
                  (((Unk_59AB5482_2 *)mp)->unk0x18 * ((Unk_59AB5482_2 *)m1)->unk0x20 +
                   (((Unk_59AB5482_2 *)mp)->unk0x10 * ((Unk_59AB5482_2 *)m1)->unk0x0 +
                    ((Unk_59AB5482_2 *)mp)->unk0x14 * ((Unk_59AB5482_2 *)m1)->unk0x10));
        prod[5] = ((Unk_59AB5482_2 *)mp)->unk0x1C * ((Unk_59AB5482_2 *)m1)->unk0x34 +
                  (((Unk_59AB5482_2 *)mp)->unk0x18 * ((Unk_59AB5482_2 *)m1)->unk0x24 +
                   (((Unk_59AB5482_2 *)mp)->unk0x10 * ((Unk_59AB5482_2 *)m1)->unk0x4 +
                    ((Unk_59AB5482_2 *)mp)->unk0x14 * ((Unk_59AB5482_2 *)m1)->unk0x14));
        prod[6] = ((Unk_59AB5482_2 *)mp)->unk0x1C * ((Unk_59AB5482_2 *)m1)->unk0x38 +
                  (((Unk_59AB5482_2 *)mp)->unk0x18 * ((Unk_59AB5482_2 *)m1)->unk0x28 +
                   (((Unk_59AB5482_2 *)mp)->unk0x10 * ((Unk_2DDDDA62 *)m1)->unk0x8 +
                    ((Unk_59AB5482_2 *)mp)->unk0x14 * ((Unk_59AB5482_2 *)m1)->unk0x18));
        prod[7] = ((Unk_59AB5482_2 *)mp)->unk0x1C * ((Unk_59AB5482_2 *)m1)->unk0x3C +
                  (((Unk_59AB5482_2 *)mp)->unk0x18 * ((Unk_59AB5482_2 *)m1)->unk0x2C +
                   (((Unk_59AB5482_2 *)mp)->unk0x10 * ((Unk_59AB5482_2 *)m1)->unk0xC +
                    ((Unk_59AB5482_2 *)mp)->unk0x14 * ((Unk_59AB5482_2 *)m1)->unk0x1C));
        prod[8] = ((Unk_59AB5482_2 *)mp)->unk0x2C * ((Unk_59AB5482_2 *)m1)->unk0x30 +
                  (((Unk_59AB5482_2 *)mp)->unk0x28 * ((Unk_59AB5482_2 *)m1)->unk0x20 +
                   (((Unk_59AB5482_2 *)mp)->unk0x20 * ((Unk_59AB5482_2 *)m1)->unk0x0 +
                    ((Unk_59AB5482_2 *)mp)->unk0x24 * ((Unk_59AB5482_2 *)m1)->unk0x10));
        prod[9] = ((Unk_59AB5482_2 *)mp)->unk0x2C * ((Unk_59AB5482_2 *)m1)->unk0x34 +
                  (((Unk_59AB5482_2 *)mp)->unk0x28 * ((Unk_59AB5482_2 *)m1)->unk0x24 +
                   (((Unk_59AB5482_2 *)mp)->unk0x20 * ((Unk_59AB5482_2 *)m1)->unk0x4 +
                    ((Unk_59AB5482_2 *)mp)->unk0x24 * ((Unk_59AB5482_2 *)m1)->unk0x14));
        prod[10] = ((Unk_59AB5482_2 *)mp)->unk0x2C * ((Unk_59AB5482_2 *)m1)->unk0x38 +
                   (((Unk_59AB5482_2 *)mp)->unk0x28 * ((Unk_59AB5482_2 *)m1)->unk0x28 +
                    (((Unk_59AB5482_2 *)mp)->unk0x20 * ((Unk_2DDDDA62 *)m1)->unk0x8 +
                     ((Unk_59AB5482_2 *)mp)->unk0x24 * ((Unk_59AB5482_2 *)m1)->unk0x18));
        prod[11] = ((Unk_59AB5482_2 *)mp)->unk0x2C * ((Unk_59AB5482_2 *)m1)->unk0x3C +
                   (((Unk_59AB5482_2 *)mp)->unk0x28 * ((Unk_59AB5482_2 *)m1)->unk0x2C +
                    (((Unk_59AB5482_2 *)mp)->unk0x20 * ((Unk_59AB5482_2 *)m1)->unk0xC +
                     ((Unk_59AB5482_2 *)mp)->unk0x24 * ((Unk_59AB5482_2 *)m1)->unk0x1C));
        prod[12] = ((Unk_59AB5482_2 *)mp)->unk0x3C * ((Unk_59AB5482_2 *)m1)->unk0x30 +
                   (((Unk_59AB5482_2 *)mp)->unk0x38 * ((Unk_59AB5482_2 *)m1)->unk0x20 +
                    (((Unk_59AB5482_2 *)mp)->unk0x30 * ((Unk_59AB5482_2 *)m1)->unk0x0 +
                     ((Unk_59AB5482_2 *)mp)->unk0x34 * ((Unk_59AB5482_2 *)m1)->unk0x10));
        prod[13] = ((Unk_59AB5482_2 *)mp)->unk0x3C * ((Unk_59AB5482_2 *)m1)->unk0x34 +
                   (((Unk_59AB5482_2 *)mp)->unk0x38 * ((Unk_59AB5482_2 *)m1)->unk0x24 +
                    (((Unk_59AB5482_2 *)mp)->unk0x30 * ((Unk_59AB5482_2 *)m1)->unk0x4 +
                     ((Unk_59AB5482_2 *)mp)->unk0x34 * ((Unk_59AB5482_2 *)m1)->unk0x14));
        prod[14] = ((Unk_59AB5482_2 *)mp)->unk0x3C * ((Unk_59AB5482_2 *)m1)->unk0x38 +
                   (((Unk_59AB5482_2 *)mp)->unk0x38 * ((Unk_59AB5482_2 *)m1)->unk0x28 +
                    (((Unk_59AB5482_2 *)mp)->unk0x30 * ((Unk_2DDDDA62 *)m1)->unk0x8 +
                     ((Unk_59AB5482_2 *)mp)->unk0x34 * ((Unk_59AB5482_2 *)m1)->unk0x18));
        prod[15] = ((Unk_59AB5482_2 *)mp)->unk0x3C * ((Unk_59AB5482_2 *)m1)->unk0x3C +
                   (((Unk_59AB5482_2 *)mp)->unk0x38 * ((Unk_59AB5482_2 *)m1)->unk0x2C +
                    (((Unk_59AB5482_2 *)mp)->unk0x30 * ((Unk_59AB5482_2 *)m1)->unk0xC +
                     ((Unk_59AB5482_2 *)mp)->unk0x34 * ((Unk_59AB5482_2 *)m1)->unk0x1C));
        m1->unk0x0 = ((Unk_18AF37A6 *)prod)->unk0x0;
        *((__ps_t *)&((Unk_2DDDDA62 *)m1)->unk0x8) = ((Unk_18AF37A6 *)prod)->unk0x8;
        m1->unk0x10 = ((Unk_18AF37A6 *)prod)->unk0x10;
        m1->unk0x18 = ((Unk_18AF37A6 *)prod)->unk0x18;
        m1->unk0x20 = ((Unk_18AF37A6 *)prod)->unk0x20;
        m1->unk0x38 = ((Unk_18AF37A6 *)prod)->unk0x38;
        m1->unk0x28 = ((Unk_18AF37A6 *)prod)->unk0x28;
        m1->unk0x30 = ((Unk_18AF37A6 *)prod)->unk0x30;
        /* ---- quat q into m[0..3]; V += ---- */
        m[0] = lbl_802ABAE4;
        m[2] = lbl_802ABAE8;
        m[3] = lbl_802ABAE4;
        m[1] = lbl_802ABAE4;
        *((f32 *)&v->unk0x0) += ((Unk_59AB5482_2 *)x)->unk0x0 * m[2] +
                           (m[0] * ((Unk_59AB5482_2 *)m1b)->unk0x0 + m[1] * ((Unk_59AB5482_2 *)w)->unk0x0);
        ((Unk_E266FB50_3 *)v)->unk0x4 += ((Unk_59AB5482_2 *)m1b)->unk0x24 * m[2] +
                           (m[0] * ((Unk_59AB5482_2 *)m1b)->unk0x4 + ((Unk_59AB5482_2 *)m1b)->unk0x14 * m[1]);
        *((f32 *)&((Unk_E266FB50_3 *)v)->unk0x8) += ((Unk_59AB5482_2 *)m1b)->unk0x28 * m[2] +
                           (m[0] * m1b->unk0x8 + ((Unk_59AB5482_2 *)m1b)->unk0x18 * m[1]);
        ((Unk_18AF37A6 *)m)->unk0x0 = v->unk0x0;
        ((Unk_18AF37A6 *)m)->unk0x8 = *((__ps_t *)&((Unk_E266FB50_3 *)v)->unk0x8);
        /* ---- quat p into m[4..7]; V = p ---- */
        m[4] = lbl_802ABAE4;
        m[7] = lbl_802ABAEC;
        m[6] = lbl_802ABAE4;
        m[5] = lbl_802ABAE4;
        obj = arg0->unk0x118;
        m1c = m1;
        m2p = (char *)obj + 0x78;
        v->unk0x0 = ((Unk_18AF37A6 *)m)->unk0x10;
        *((__ps_t *)&((Unk_E266FB50_3 *)v)->unk0x8) = ((Unk_18AF37A6 *)m)->unk0x18;
        /* ---- product 2: m1c x m2p -> m[4..15] ---- */
        m[4] = ((Unk_59AB5482_2 *)m1c)->unk0x4 * ((Unk_59AB5482_2 *)m2p)->unk0x10 +
               (((Unk_59AB5482_2 *)m1c)->unk0x0 * ((Unk_59AB5482_2 *)m2p)->unk0x0 +
                (m1c->unk0x8 * ((Unk_59AB5482_2 *)m2p)->unk0x20 + ((Unk_59AB5482_2 *)m1c)->unk0xC * ((Unk_59AB5482_2 *)m2p)->unk0x30));
        m[5] = ((Unk_59AB5482_2 *)m1c)->unk0x4 * ((Unk_59AB5482_2 *)m2p)->unk0x14 +
               (((Unk_59AB5482_2 *)m1c)->unk0x0 * ((Unk_59AB5482_2 *)m2p)->unk0x4 +
                (m1c->unk0x8 * ((Unk_59AB5482_2 *)m2p)->unk0x24 + ((Unk_59AB5482_2 *)m1c)->unk0xC * ((Unk_59AB5482_2 *)m2p)->unk0x34));
        m[6] = ((Unk_59AB5482_2 *)m1c)->unk0x4 * ((Unk_59AB5482_2 *)m2p)->unk0x18 +
               (((Unk_59AB5482_2 *)m1c)->unk0x0 * m2p->unk0x8 +
                (m1c->unk0x8 * ((Unk_59AB5482_2 *)m2p)->unk0x28 + ((Unk_59AB5482_2 *)m1c)->unk0xC * ((Unk_59AB5482_2 *)m2p)->unk0x38));
        m[7] = ((Unk_59AB5482_2 *)m1c)->unk0x4 * ((Unk_59AB5482_2 *)m2p)->unk0x1C +
               (((Unk_59AB5482_2 *)m1c)->unk0x0 * ((Unk_59AB5482_2 *)m2p)->unk0xC +
                (m1c->unk0x8 * ((Unk_59AB5482_2 *)m2p)->unk0x2C + ((Unk_59AB5482_2 *)m1c)->unk0xC * ((Unk_59AB5482_2 *)m2p)->unk0x3C));
        m[8] = ((Unk_59AB5482_2 *)m1c)->unk0x14 * ((Unk_59AB5482_2 *)m2p)->unk0x10 +
               (((Unk_59AB5482_2 *)m1c)->unk0x10 * ((Unk_59AB5482_2 *)m2p)->unk0x0 +
                (((Unk_59AB5482_2 *)m1c)->unk0x18 * ((Unk_59AB5482_2 *)m2p)->unk0x20 + ((Unk_59AB5482_2 *)m1c)->unk0x1C * ((Unk_59AB5482_2 *)m2p)->unk0x30));
        m[9] = ((Unk_59AB5482_2 *)m1c)->unk0x14 * ((Unk_59AB5482_2 *)m2p)->unk0x14 +
               (((Unk_59AB5482_2 *)m1c)->unk0x10 * ((Unk_59AB5482_2 *)m2p)->unk0x4 +
                (((Unk_59AB5482_2 *)m1c)->unk0x18 * ((Unk_59AB5482_2 *)m2p)->unk0x24 + ((Unk_59AB5482_2 *)m1c)->unk0x1C * ((Unk_59AB5482_2 *)m2p)->unk0x34));
        m[10] = ((Unk_59AB5482_2 *)m1c)->unk0x14 * ((Unk_59AB5482_2 *)m2p)->unk0x18 +
                (((Unk_59AB5482_2 *)m1c)->unk0x10 * m2p->unk0x8 +
                 (((Unk_59AB5482_2 *)m1c)->unk0x18 * ((Unk_59AB5482_2 *)m2p)->unk0x28 + ((Unk_59AB5482_2 *)m1c)->unk0x1C * ((Unk_59AB5482_2 *)m2p)->unk0x38));
        m[11] = ((Unk_59AB5482_2 *)m1c)->unk0x14 * ((Unk_59AB5482_2 *)m2p)->unk0x1C +
                (((Unk_59AB5482_2 *)m1c)->unk0x10 * ((Unk_59AB5482_2 *)m2p)->unk0xC +
                 (((Unk_59AB5482_2 *)m1c)->unk0x18 * ((Unk_59AB5482_2 *)m2p)->unk0x2C + ((Unk_59AB5482_2 *)m1c)->unk0x1C * ((Unk_59AB5482_2 *)m2p)->unk0x3C));
        m[12] = ((Unk_59AB5482_2 *)m1c)->unk0x24 * ((Unk_59AB5482_2 *)m2p)->unk0x10 +
                (((Unk_59AB5482_2 *)m1c)->unk0x20 * ((Unk_59AB5482_2 *)m2p)->unk0x0 +
                 (((Unk_59AB5482_2 *)m1c)->unk0x28 * ((Unk_59AB5482_2 *)m2p)->unk0x20 + ((Unk_59AB5482_2 *)m1c)->unk0x2C * ((Unk_59AB5482_2 *)m2p)->unk0x30));
        m[13] = ((Unk_59AB5482_2 *)m1c)->unk0x24 * ((Unk_59AB5482_2 *)m2p)->unk0x14 +
                (((Unk_59AB5482_2 *)m1c)->unk0x20 * ((Unk_59AB5482_2 *)m2p)->unk0x4 +
                 (((Unk_59AB5482_2 *)m1c)->unk0x28 * ((Unk_59AB5482_2 *)m2p)->unk0x24 + ((Unk_59AB5482_2 *)m1c)->unk0x2C * ((Unk_59AB5482_2 *)m2p)->unk0x34));
        m[14] = ((Unk_59AB5482_2 *)m1c)->unk0x24 * ((Unk_59AB5482_2 *)m2p)->unk0x18 +
                (((Unk_59AB5482_2 *)m1c)->unk0x20 * m2p->unk0x8 +
                 (((Unk_59AB5482_2 *)m1c)->unk0x28 * ((Unk_59AB5482_2 *)m2p)->unk0x28 + ((Unk_59AB5482_2 *)m1c)->unk0x2C * ((Unk_59AB5482_2 *)m2p)->unk0x38));
        m[15] = ((Unk_59AB5482_2 *)m1c)->unk0x24 * ((Unk_59AB5482_2 *)m2p)->unk0x1C +
                (((Unk_59AB5482_2 *)m1c)->unk0x20 * ((Unk_59AB5482_2 *)m2p)->unk0xC +
                 (((Unk_59AB5482_2 *)m1c)->unk0x28 * ((Unk_59AB5482_2 *)m2p)->unk0x2C + ((Unk_59AB5482_2 *)m1c)->unk0x2C * ((Unk_59AB5482_2 *)m2p)->unk0x3C));
        m1->unk0x0 = ((Unk_18AF37A6 *)m)->unk0x10;
        *((__ps_t *)&((Unk_2DDDDA62 *)m1)->unk0x8) = ((Unk_18AF37A6 *)m)->unk0x18;
        m1->unk0x10 = ((Unk_18AF37A6 *)m)->unk0x20;
        m1->unk0x18 = ((Unk_18AF37A6 *)m)->unk0x28;
        m1->unk0x20 = ((Unk_18AF37A6 *)m)->unk0x30;
        m1->unk0x28 = ((Unk_18AF37A6 *)m)->unk0x38;
        m1->unk0x30 = ((Unk_18AF37A6 *)m)->unk0x40;
        m1->unk0x38 = ((Unk_18AF37A6 *)m)->unk0x48;
        obj = arg0->unk0x118;
        /* ---- product 3: objmtx x q(=old V) -> m[8..13] ---- */
        m[8] = m[1] * obj->unk0x88 +
               (m[0] * obj->unk0x78 +
                (m[2] * obj->unk0x98 + m[3] * obj->unk0xA8));
        m[9] = m[1] * obj->unk0x8C +
               (m[0] * obj->unk0x7C +
                (m[2] * ((Unk_A6BFE3BE *)obj)->unk0x9C + m[3] * ((Unk_A6BFE3BE *)obj)->unk0xAC));
        m[10] = m[1] * obj->unk0x90 +
                (m[0] * obj->unk0x80 +
                 (m[2] * obj->unk0xA0 + m[3] * obj->unk0xB0));
        m[11] = m[1] * obj->unk0x94 +
                (m[0] * obj->unk0x84 +
                 (m[2] * obj->unk0xA4 + m[3] * ((Unk_A6BFE3BE *)obj)->unk0xB4));
        /* ---- tail pairs ---- */
        arg0->unk0x58 = ((Unk_18AF37A6 *)m)->unk0x10;
        arg0->unk0x18 = ((Unk_18AF37A6 *)m)->unk0x10;
        arg0->unk0x60 = ((Unk_18AF37A6 *)m)->unk0x18;
        arg0->unk0x20 = ((Unk_18AF37A6 *)m)->unk0x18;
        arg0->unk0x58 += ((Unk_DF2324A8 *)obj)->unk0x58;
        arg0->unk0x60 += ((Unk_DF2324A8 *)obj)->unk0x60;
    }
}
