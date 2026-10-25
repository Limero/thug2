// family=m2c range=0x800BBEDC-0x800BBFF8 size=284B
// FLAG: -mps-float
//
// 0x800BBEDC — paired-single leaf, 71 instructions, NO calls, NO mflr
// (frame 0x58 is pure locals).  Fully hand-reconstructed from the DOL; the
// previous m2c body was a 0;-stub husk that compiled to a 1-instruction object.
//
// WHAT IT IS (recovered from the decode; see the op-by-op table below).
// A normalised 2-D "sliding pair" evaluation over two 4-float vectors,
// finished with a reciprocal and a 0.01f epsilon in the y lane:
//     ret = 1.0f / ( x*(x + w) + y + 0.01f )
// arg0 : object, only +0x1C is read (f32 scale `s`)
// arg1 : 16-byte vector, read as two paired-single pairs (+0 and +8)
// arg2 : 16-byte vector, read as two paired-single pairs (+0 and +8)
// lbl_80298DFC = 1.0f   (lfs, held in an FPR to the fdivs at the tail)
// lbl_802A8CA0 = 0.01f  (psq_l, the epsilon merged into the y lane)
// The `s` factor is applied TWICE in a row (two ps_muls0 off the sp8 slot,
// the first one round-tripped through r1+8 = &sp8), then a broadcast+overwrite
// of the .hi word of the sp38/sp48 slots with 1.0f builds the {v, 1.0f} pairs.
//
// STATUS 2026-09-27: PARKED at 64 of 71 words.  Authoritative PS score
// (tools/ps_diff.py) 6/71 = 8.5%, got 256 B vs want 284 B; index-aligned
// masked want|got is 5 exact + 4 same-shape = 9/71.  Everything structural
// (frame, all ten slots, opcode set, op order) matches — see RESIDUAL.
// SCORE WITH:  tools/venv/bin/python tools/ps_diff.py 0x800BBEDC 284
//   ps_diff.py is the ONLY authoritative scorer for a PS draft
//   (test_wip_drafts.py / score_body.py / flagdiff.py are PS-unaware —
//   AGENTS.md §6au-204 — so their percentages here are meaningless).
//
// WHAT IS ALREADY EXACT (do not re-derive):
//   * frame 0x58 and ALL TEN stack slots at retail offsets.  A
//     `struct FR { volatile sn_ps sp8, sp10, sp18, sp20, sp28, sp30,
//     sp38, sp40, sp48, sp50; }` reproduces 0x8,0x10,0x18,0x20,0x28,0x30,
//     0x38,0x40,0x48,0x50 exactly (the locals region starts at r1+8, so the
//     struct needs NO leading pad — adding one costs 8 bytes of frame and
//     shifts every slot).  Both "store the pair, then overwrite its second
//     word" sites (psq_st 0x38 + stfs 0x3c, psq_st 0x48 + stfs 0x4c) fall
//     out of `volatile sn_ps` + `((volatile f32 *)&slot)[1] = k`.
//   * the whole arithmetic opcode stream.  Shape multiset of the 64 emitted
//     words vs want's 71 is IDENTICAL except for the seven register-copy
//     words listed under RESIDUAL — every ps_mul/ps_sub/ps_add/ps_madd/
//     ps_sum0/ps_muls0/ps_merge00/ps_merge10/ps_mr/psq_l/psq_st/lfs/fdivs
//     operand shape is right.
//   * the semantic op SEQUENCE is want's, in want's order (see the table).
//
// THE TWO BUILTIN FORMS THAT MATTER (both probed against cc1 3.9.3):
//   * `__builtin_ps_mergeXY(a,b)` = {lane_X(a), lane_Y(b)}; merge00 is the
//     broadcast want uses for both sp38/sp48 pair stores.
//   * `M2 = A*B; M2 = M2 - T0;` is FUSED by cc1 into a single `ps_msub`,
//     which retail does NOT do (want keeps ps_mul + ps_sub).  A zero-code
//     `__asm__("" : "+f"(M2))` barrier on the multiply result blocks the
//     fusion; two such barriers are the only asm in this file (no instruction
//     templates, no register pins).  Without them the object is 62 words with
//     2 ps_msub; with them 64 words and the opcode set matches exactly.
//     Only 3.9.3 compiles these builtins at all (3.5/3.5b140/3.7/3.8.1 all
//     ICE), so the version question is closed.
//
// RESIDUAL — precisely why it does not match (7 words + colouring + order):
//   (1) 7 register-copy words cc1 never materialises:
//         3x `ps_mr fD,fS`  — copy of a just-reloaded pair before psq_st
//                              (want 0x800BBF60/84/cc).  A `register f32
//                              __asm__("fr3")` pin on the stored copy is
//                              SILENTLY DROPPED (probed), so these need an
//                              asm `mr` wedge (banned here).
//         3x `fmr`          — `fmr f3,f4` before each `stfs 0x3c/0x4c`, and
//                              `fmr f1,f0` before the final `fdivs`.  Same
//                              dead-copy family (§6x-89); an fr3 pin does not
//                              produce them.
//         1x `addi r10,r1,8` — retail materialises &sp8 into r10 and uses it
//                              for 2 of the 3 sp8 accesses.  A
//                              `register s32 __asm__("r10")` pin was tried
//                              and made the output WORSE (the addi is
//                              strength-reduced away and the load order
//                              collapses) — reverted.
//   (2) Global PS register colouring: k lands in f5 and c in f4 here, the
//       reverse of want; every merge/mul/madd picks different fD.  This is
//       the same allocator wall that parks fn_80026D34 (2540 B) and
//       fn_80005854: the op stream is isomorphic, the numbers are not.
//   (3) Scheduler reorderings, each verified individually:
//         * want emits `stfs 0x3c` / `stfs 0x4c` IMMEDIATELY after their
//           pair store; cc1 sinks them one merge later.  A memory-clobber
//           fence fixes the adjacency but costs more elsewhere (index-
//           aligned score drops 9/71 -> 3/71), so it is not kept.
//         * want's argument-load order is r4+8, r5+8, r5+0, r4+0; cc1 emits
//           r5+8, r4+0, r5+0, r4+8.
//         * want keeps `ps_sub f13,f13,f12` between `ps_add f11` and
//           `stfs f11,0x20`; cc1 hoists it above the sp30 store.  A `"+f"`
//           barrier on U1 does not move it.
//
// OP TABLE (want index: instruction, role) — use this, not the m2c husk:
//   1-8  psq_l f8,8(r4) / lis r11 / psq_l f6,8(r5) / lis r9 /
//        psq_l f7,0(r5) / addi r9 / psq_l f9,0(r4) / addi r10,r1,8
//   9    ps_merge10 f10,f7,f6   p2 = {a2a.lo, a2b.hi}
//  10    lfs f4,-0x7204(r11)    k = 1.0f
//  11    ps_merge10 f13,f9,f8   p1 = {a1a.lo, a1b.hi}
//  12    psq_l f5,0(r9)         eps = {0.01f, 0.0f}
//  13-15 ps_mul f0,f10,f9 / ps_mul f13,f7,f13 / ps_sub f13,f13,f0
//  16-19 ps_merge00 f0,f13,f13 / psq_st f0,0x38 / fmr f3,f4 / stfs f3,0x3c
//  20-25 ps_merge00 f12,f9,f8 / psq_l f3,0x38 / ps_merge00 f0,f6,f7 /
//        ps_mul f0,f0,f12 / ps_mr f11,f3 / psq_st f11,0x10
//  26-32 ps_merge00 f6,f7,f6 / lfs f12,0x1c(r3) / stfs f12,0x40 /
//        ps_merge10 f12,f0,f0 / psq_l f3,0x40 / ps_sub f0,f0,f12 /
//        ps_merge10 f13,f13,f0
//  33-39 ps_mr f11,f3 / ps_muls0 f13,f13,f11 / psq_st f13,0x8 /
//        psq_l f13,0x8(r10) / ps_muls0 f13,f13,f11 / psq_st f13,0x8(r10) /
//        psq_l f12,0x8(r1)
//  40-47 ps_merge10 f0,f12,f13 / ps_mul f10,f12,f10 / ps_mul f0,f0,f7 /
//        ps_sub f10,f10,f0 / ps_merge00 f0,f10,f10 / psq_st f0,0x48 /
//        fmr f3,f4 / stfs f3,0x4c
//  48-53 ps_merge00 f13,f13,f12 / ps_mul f13,f13,f6 / psq_l f12,0x48 /
//        ps_mr f0,f12 / ps_merge10 f12,f13,f13 / psq_st f0,0x30
//  54-65 ps_add f11,f8,f0 / ps_sub f13,f13,f12 / psq_st f11,0x20 /
//        ps_merge10 f10,f10,f13 / ps_mul f8,f8,f11 / psq_st f10,0x28 /
//        ps_add f10,f9,f10 / ps_merge00 f8,f8,f5 / psq_st f10,0x18 /
//        ps_madd f9,f9,f10,f8 / ps_sum0 f9,f9,f9,f9 / psq_st f9,0x50
//  66-70 lfs f0,0x50 / fmr f1,f0 / fdivs f1,f4,f1 / addi r1 / blr
//
// The five stores to sp10/sp18/sp20/sp28/sp30 are DEAD in retail (nothing
// reloads them) — kept here as `volatile` members, which is what makes them
// survive DSE at all.
typedef float sn_ps __attribute__((mode(PS)));
typedef struct { f32 v[4]; } V4;
/* arg0 +0x1C is a FLOAT.  The shared Unk_31DE137E class types that slot s32
   (majority vote corpus-wide); a file-local layout is what makes the `lfs`
   come out instead of lwz+fctiwz (M6.89d-note). */
typedef struct { char pad_00[0x1C]; f32 scale; } OBJ;
extern f32 lbl_80298DFC;
extern f32 lbl_802A8CA0;
f32 fn_800BBEDC(OBJ *arg0, V4 *arg1, V4 *arg2) {
    struct FR {
        volatile sn_ps sp8, sp10, sp18, sp20, sp28, sp30, sp38, sp40, sp48, sp50;
    } fr;
    sn_ps a1b, a1a, a2b, a2a;
    sn_ps p1, p2, d0, d1, d2;
    sn_ps m2, m7, m8, m9, m11, m12, eps;
    sn_ps t0, t1, t2, t3, t3r, t4, t5, t6, u1, sc, sc2;
    volatile sn_ps *p8;
    f32 k, s;

    a1b = *(sn_ps *)&arg1->v[2];
    a2b = *(sn_ps *)&arg2->v[2];
    a2a = *(sn_ps *)&arg2->v[0];
    a1a = *(sn_ps *)&arg1->v[0];
    k = lbl_80298DFC;
    eps = *(sn_ps *)&lbl_802A8CA0;
    p8 = &fr.sp8;

    p2 = __builtin_ps_merge10(a2a, a2b);
    p1 = __builtin_ps_merge10(a1a, a1b);
    t0 = p2 * a1a;
    m2 = a2a * p1;
    __asm__("" : "+f"(m2));
    m2 = m2 - t0;
    fr.sp38 = __builtin_ps_merge00(m2, m2);
    ((volatile f32 *)&fr.sp38)[1] = k;
    d0 = __builtin_ps_merge00(a1a, a1b);
    t3r = fr.sp38;
    d1 = __builtin_ps_merge00(a2b, a2a);
    t1 = d1 * d0;
    fr.sp10 = t3r;
    d2 = __builtin_ps_merge00(a2a, a2b);
    s = arg0->scale;
    ((volatile f32 *)&fr.sp40)[0] = s;
    t1 = t1 - __builtin_ps_merge10(t1, t1);
    m7 = __builtin_ps_merge10(m2, t1);
    sc = fr.sp40;
    t2 = __builtin_ps_muls0(m7, sc);
    *p8 = t2;
    t3 = __builtin_ps_muls0(*p8, sc);
    *p8 = t3;
    t3r = *p8;
    m8 = __builtin_ps_merge10(t3r, t3);
    p2 = t3r * p2;
    __asm__("" : "+f"(p2));
    m8 = m8 * a2a;
    t4 = p2 - m8;
    fr.sp48 = __builtin_ps_merge00(t4, t4);
    ((volatile f32 *)&fr.sp48)[1] = k;
    t5 = __builtin_ps_merge00(t3, t3r) * d2;
    sc2 = fr.sp48;
    fr.sp30 = sc2;
    u1 = a1b + sc2;
    t5 = t5 - __builtin_ps_merge10(t5, t5);
    fr.sp20 = u1;
    m11 = __builtin_ps_merge10(t4, t5);
    a1b = a1b * u1;
    fr.sp28 = m11;
    m11 = a1a + m11;
    m12 = __builtin_ps_merge00(a1b, eps);
    fr.sp18 = m11;
    t6 = a1a * m11 + m12;
    t6 = __builtin_ps_sum0(t6, t6, t6);
    fr.sp50 = t6;
    return k / ((volatile f32 *)&fr.sp50)[0];
}
