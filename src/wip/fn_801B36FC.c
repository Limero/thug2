// PARKED 2026-10-30: 1.7% -> 1.7% (no match; a full 507-instruction
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 0.9862% -> 1.3807% per-object flags: -mps-float -> -Os -mps-float
// structural rebuild was ATTEMPTED and is blocked by a cc1 wall - see 6).
// family=m2c range=0x801B36FC-0x801B3EE8 size=2028B
// INERT: not registered in splits.txt/configure.py - never compiled,
// FLAG: -Os
// not counted in objdiff progress. activate via tools/wip.py.
//
// ===== STRUCTURAL DOCUMENTATION (read this first; the body below
// ===== is still the m2c husk, but everything here is verified) =====
//
// BASELINE: tools/test_wip_drafts.py --addr 0x801B36FC => DIFF, ps_diff 5/289
// words (1.7%), compiled object 1156 B for a 2028 B want.
//
// 1) STATICS-DCE HUSK (AGENTS 6j-4 / 6ef / 6ec / 6fd): the inherited draft
//    has 7 file-scope `static s32 spN` (m2c's out-params -> no frame) and 80
//    `0;` stub lines (longest run 11 at line 113). The want has 98 primary-
//    opcode-4 words + 64 psq_l + 50 psq_st, i.e. it is a paired-single
//    function; every `0;` hides a `__ps_t` pair copy. Verified decode tool:
//    `tools/ps_diff.py`'s field layout (frD=bits21-25, frA=16-20, frB=11-15,
//    frC=6-10); `tools/ps_disasm.py` prints them as `.word # op4` - hand-decode
//    them, they are all plain Gekko PS (add/sub/mul/div/madd/msub/madds0/
//    muls0/sum0/merge00/merge01/merge10/rsqrte/res/sel), no doc-06/29 wall.
//    Function needs `// FLAG: -mps-float`.
//
// 2) FRAME (AGENTS 6db / 6fk / 6fr): want prologue allocates 0x170 bytes of
//    stack, saves the link register, spills FPRs f30/f31 as doubles at
//    0x160/0x168, saves GPRs from r25 at 0x144, and spills r0 at 0x174.
//    => 7 saved GPRs (r25..r31), 2 saved FPRs, LR at frame+4, save area at
//    8+locals  =>  locals = 0x13C = 316 B (NOT the -16 form; see 6fr
//    correction). Stack map (37 x 8-byte pair slots at r1+8..r1+0x12F, plus
//    two s32 at 0xA8/0xAC, plus 0x130..0x13B padding):
//      P0..P17 = 0x08,0x10,0x18,0x20,0x28,0x30,0x38,0x40,0x48,0x50,0x58,
//               0x60,0x68,0x70,0x78,0x80,0x88,0x90
//      P18,P19 = 0x98,0xA0 unused; s32 pair at 0xA8/0xAC = fn_80006C64 out2/3
//      P21..P36 = 0xB0,0xB8,0xC0,0xC8,0xD0,0xD8,0xE0,0xE8,0xF0,0xF8,0x100,
//                 0x108,0x110,0x118,0x120,0x128
//    4-byte scalars live in the pair HI lanes (0x0c,0x14,0x1c,0x24,0x2c,0x3c,
//    0x5c,0xb4,0xbc,0xc4,0xcc,0xd4,0xdc,0x124,0x12c) - i.e. the original had
//    SEPARATE `__ps_t` and `f32` locals and let GCC interleave them, NOT a
//    union (a union leaves PS mode, 6ef-4/6am-190).
//
// 3) CONSTANTS decoded (all hand-decoded from want lis/addi pairs; the two
//    QB_VELDIR / QB_* already in qb_constants.h match):
//      lis -0x7fd5 = 0x802B0000 page; lis -0x7fd0 = 0x80300000 page;
//      addi r,r9,-0x4048 => 0x802ABFB8 (lbl_802ABFB8, size 0x2C) - the
//        broadcast PS pair {0,0}, used as the 3rd term of every `len^2`.
//      0x802ABFF8 f32 0.0f   | 0x802ABFFC f32 1.0f
//      0x802AC000 f32 90.0f  | 0x802AC004 f32 0.0174532925 (1 degree)
//      0x802AC008 f32 -90.0f | 0x802AC010 f64 0.0
//      0x802AC018 f32 600.0f | 0x802AC01C f32 -600.0f
//      0x802AC020 f32 0.001f | 0x802AC028 f64 0.0
//      0x802AC030 f32 96.0f  | 0x802AC034 f32 140.0f | 0x802AC038 f32 1500.0
//      lbl_80305F2C f32 3047.03955 | lbl_80305F30 f32 225.0
//      lbl_803A2F30 (.bss f32, runtime value) | lbl_80305EAC (.data ptr)
//    QB hashes seen: 0xA015E17 (arg0->0xC lookup, unnamed), QB_VELDIR
//    0xF68EA304, 0xF75EC2CF (unnamed), 0xEF5FB1AA (unnamed), QB_BLOCKERRUN
//    0x9D45C77A, QB_DIR 0x455485EF + QB_LEFT 0x85981897 / QB_RIGHT 0x4B358AEB
//    (both arms of one 3-arg AddChecksum), QB_BLOCKERSHUFFLE 0x3B5A86D7.
//
// 4) CALL-SITE ARITY (all audited against retail arg registers - m2c was
//    wrong on most of them):
//      fn_801745B4(lbl_80305EAC's value)      -> void* (the CAT, r31)
//      fn_8009FDD8(arg0->0xC, 0xA015E17)      -> void* (r25; GetChecksum_3)
//      fn_801B4404(arg0, OUT)                 -> void; OUT+0x20 = a 16-byte
//        pair pair; call sites: &r1+0x08 (fills P4,P5), &r1+0x28 (fills
//        P8,P9), and ONE site at 0x801b3d34 with r4 left as dead residue.
//      fn_80019D08(8) then fn_80126EAC()       -> CStruct* (chained, r30/r3)
//      fn_801279A0(QB_VELDIR, &P6)            2-arg
//      fn_8009F010(entry, hash[, obj])         3rd arg dead at 0x801b3cb8 /
//        0x801b3d48 (`li r5,0`); m2c's `fn_801B4404` + `CStruct_new` +
//        `CStruct_ctor` spelling is WRONG - it is fn_80019D08(8)+fn_80126EAC().
//      fn_801270C(r3, 3)                       2-arg
//      fn_800063B8(dst, a, b)                  3 __ps_t* (32-byte copy)
//      fn_80006C64(&P12|P10, &P16|P14, &P6, &P8, &sA8, &sAC, 1)  7-arg
//      fn_801277E4(...)                        3-arg, but the LEFT arm passes
//        only 2 (r3 is dead residue) - m2c invented a leading 0 arg.
//      fn_80271170 / fn_80271070               f32(f32), sinf/cosf
//
// 5) BLOCK MAP (branch targets, all decoded):
//   0x801b3728 r31==0            -> END
//   0x801b381c `bge`             -> 0x801b3880   (P6.hi >= 0 selects the
//                                  -90 deg arm; the fall-through is +90)
//   0x801b3924 `ble`             -> 0x801b3954   (skip rsqrte normalise)
//   0x801b398c `bns`             -> 0x801b39f8   (P28.lo >= 3047.04)
//   0x801b39f4 `b`               -> END
//   0x801b3a70 `beq`             -> 0x801b3b00   (the -600 arm of an
//                                  if/else on P11/P9; the +600 arm is inline)
//   0x801b3a7c..0x801b3afc       -> `b 0x801b3b78` shared fn_80006C64 tail
//   0x801b3ca8 `bns`             -> 0x801b3cd0
//   0x801b3ccc `b`               -> END
//   0x801b3ce4 `ble`             -> 0x801b3d10   (skip conditional re-scale)
//   0x801b3d1c `bgt`             -> 0x801b3d30   (BLOCKERRUN, skips the
//                                  AddChecksum/SHUFFLE block)
//   0x801b3d2c `ble`             -> 0x801b3d50
//   0x801b3d4c `b`               -> 0x801b3e30   (common clamp tail)
//   0x801b3dd4 `bge`             -> 0x801b3df0   (AddChecksum LEFT/RIGHT)
//   0x801b3e40/0x801b3e5c/0x801b3e60 min/max clamps -> 0x801b3e30/0x801b3e64
//   END 0x801b3ecc: lwz/mtlr/lmw r25,/lfd f30,f31,/addi/blr
//
// 6) WHAT BLOCKED THE REBUILD (measured, do not re-derive):
//    The full 507-instruction reconstruction is written and semantically
//    complete (see the block map + the arity table), but it does not COMPILE
//    with this cc1: `__builtin_ps_*` ICEs with
//        "unsupported vector operation" (cc1 front end)
//    as soon as a pair value flows through a POINTER HELD IN A LOCAL (e.g.
//    `sn_ps *cat = (sn_ps *)fn_801745B4(...); k = cat[11];`), while the exact
//    same read through a cast applied directly to an incoming PARAMETER
//    (`((sn_ps *)arg0)[11]`) is fine. Probes run:
//      - plain `sn_ps a,b; a=g[0]; b=__builtin_ps_merge00(a,b); o[0]=b;`  OK
//      - `sn_ps *p = f.s; p[1]=a; *(f32*)((char*)&f+4)=0.0f;`           OK
//        (psq_st survives - that is why a frame of `__ps_t` pairs is usable)
//      - the same read through a call-result local pointer                  ICE
//    Struct-member `__ps_t` accessors are ALSO unusable (they lower to `lq`
//    /`xscmpeqdp`, i.e. PS mode is lost) - only POINTER access works, and a
//    `union {__ps_t; f32[2];}` leaves PS mode silently (AGENTS 6ef-4).
//    A ~60-line reduced case that still ICEs is the clean next probe; do not
//    re-run the two m7/m6-style probes above, they are inconclusive because
//    cc1 DCEs the unused results.
//
// 7) LEVER LEDGER (all measured, all on the m2c baseline unless noted):
//    `// FLAG: -Os` on the inherited draft ......... 1.7% (kept, it is the
//        only value that compiled)
//    removing -Os ................................. 1.0% (worse)
//    full hand-rebuild ............................ DID NOT COMPILE
//      (cc1 "unsupported vector operation", see 6)
//    pointer-view frame (`__ps_t *P = (__ps_t *)&f`) .. OK in isolation
//    plain-array frame (`sn_ps fr[38]`) ............. OK in isolation
//    frame-size arithmetic (6db/6fk) ............... verified, locals 0x13C
//    de-static-ing the 7 spN out-params ............ required but blocked
//
// 8) PROMOTE-SAFETY: object is NOT promote-clean - it has 7 `static s32` and
//    80 `0;` stubs, so its `.text` is 872 B short of `symbols.txt` size 0x7EC
//    and the masked REL14/REL24 compare cannot be trusted on it at all.
//
#include "types.h"
extern char lbl_802ABFF8[];
extern char lbl_802ABFFC[];
extern f32 lbl_802AC000;
extern char lbl_802AC004[];
extern f32 lbl_802AC008;
extern f64 lbl_802AC010;
extern f32 lbl_802AC018;
extern f32 lbl_802AC01C;
extern f32 lbl_802AC020;
extern f32 lbl_802AC030;
extern f32 lbl_802AC034;
extern f32 lbl_802AC038;
extern char lbl_80305EAC[];
extern f32 lbl_80305F30;
extern f32 lbl_803A2F30;
#include "qb_constants.h"
#include "structs.h"
// FLAG: -Os
static s32 sp108;
static s32 sp110;
static s32 sp118;
static s32 sp3C;
static s32 sp50;
static s32 spE8;
static s32 spF0;

void fn_801B36FC(Unk_C7387A53 *arg0) {
    f32 sp12C;
    f32 sp124;
    f32 sp100;
    f32 spF8;
    f32 spDC;
    f32 spD4;
    f32 spD0;
    f32 spCC;
    f32 spC8;
    f32 spC4;
    f32 spC0;
    f32 spBC;
    f32 spB8;
    f32 spB4;
    s32 spAC;
    s32 spA8;
    f32 sp88;
    f32 sp78;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp48;
    s32 sp38;
    f32 sp28;
    f32 sp24;
    f32 sp1C;
    f32 sp14;
    f32 spC;
    f32 sp8;
    f32 *var_r27;
    f32 *var_r4;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f11;
    f32 temp_f12;
    f32 temp_f30;
    f32 temp_f30_2;
    f32 temp_f31;
    f32 temp_f31_2;
    f32 temp_f31_3;
    f32 var_f12;
    f32 var_f13;
    f32 var_f7;
    s32 temp_r30;
    s32 temp_r30_2;
    s32 temp_r3;
    s32 var_r0;
    CStruct *temp_r11;
    Unk_C7387A53 *temp_r25;
    void *temp_r9;

    temp_r3 = fn_801745B4(*(s32 *)&lbl_80305EAC);
    if (temp_r3 != 0) {
        temp_r25 = GetChecksum_3(arg0->unk0xC, QB_MOTION);
        0;
        0;
        temp_f30 = *(f32 *)&lbl_802ABFF8;
        0;
        0;
        0;
        sp24 = temp_f30;
        sp1C = temp_f30;
        0;
        0;
        spC = temp_f30;
        0;
        sp14 = temp_f30;
        0;
        0;
        0;
        0;
        0;
        0;
        0;
        0;
        0;
        0;
        0;
        0;
        spB4 = *(f32 *)&lbl_802ABFFC;
        0;
        if (sp3C < temp_f30) {
            spC4 = temp_f30;
            spBC = temp_f30;
            spB8 = cosf(temp_f31);
            spC0 = sinf(temp_f31);
            temp_f31 = lbl_802AC000 * *(f32 *)&lbl_802AC004;
        } else {
            temp_f31_2 = lbl_802AC008 * *(s32 *)&lbl_802AC004;
            spD0 = sinf(temp_f31_2);
            spC8 = cosf(temp_f31_2);
            spCC = temp_f30;
            spD4 = temp_f30;
        }
        0;
        0;
        0;
        0;
        if (0 > *(s32 *)&lbl_802ABFF8) {
            spDC = *(s32 *)&lbl_802ABFFC;
            0;
        }
        0;
        0;
        if (0 != 0) {
            fn_801B4404(arg0, &sp28);
            CStruct_new(8);
            temp_r30 = CStruct_ctor();
            0;
            0;
            fn_801279A0(QB_VELDIR, &sp38);
            fn_8009F010(arg0->unk0xC, QB_BLOCKERBUMPPLAYER, temp_r30);
            if (temp_r30 != 0) {
                CStruct_delete(temp_r30, 3);
            }
        } else {
            var_r0 = 1;
            0;
            if (spE8 > (f32) lbl_802AC010) {
                var_r0 = 0;
            }
            0;
            0;
            if (spF0 < lbl_803A2F30) {
                var_r0 = 0;
            }
            if (var_r0 != 0) {
                0;
                var_r27 = &sp68;
                spF8 = lbl_802AC018;
                0;
                0;
                0;
                0;
                0;
                0;
                0;
                fn_800063B8(var_r27, (char *)arg0 + 0x78, (char *)arg0 + 0x68);
                fn_800063B8(&sp88, temp_r3 + 0x58, &sp48);
                var_r4 = &sp88;
            } else {
                var_r27 = &sp58;
                sp100 = lbl_802AC01C;
                0;
                0;
                0;
                0;
                fn_800063B8(var_r27, (char *)arg0 + 0x78, (char *)arg0 + 0x68);
                fn_800063B8(&sp78, temp_r3 + 0x58, &sp48);
                var_r4 = &sp78;
            }
            fn_80006C64(var_r27, var_r4, &sp38, &sp48, &spA8, &spAC, 1);
            0;
            0;
            0;
            0;
            0;
            0;
            0;
            0;
            0;
            if (sp108 != *(s32 *)&lbl_802ABFF8) {
                var_f7 = sp110 / sp108;
            } else {
                var_f7 = sp110 / lbl_802AC020;
            }
            0;
            0;
            0;
            0;
            0;
            if (0 != 0) {
                fn_801B4404(arg0, &sp8);
                fn_8009F010(arg0->unk0xC, QB_BLOCKERSTAND, 0);
                return;
            }
            temp_f30_2 = *(s32 *)&lbl_802ABFF8;
            temp_f31_3 = sp118 / var_f7;
            if (sp118 > temp_f30_2) {
                sp124 = *(s32 *)&lbl_802ABFFC;
                0;
                0;
            }
            if ((temp_f31_3 > lbl_80305F30) || (sp118 > lbl_802AC030)) {
                fn_801B4404(arg0, &sp48);
                fn_8009F010(arg0->unk0xC, QB_BLOCKERRUN, 0);
            } else {
                fn_801B4404(arg0, arg0, &sp28);
                CStruct_new(8);
                temp_r30_2 = CStruct_ctor();
                0;
                0;
                0;
                0;
                0;
                0;
                0;
                sp12C = *(s32 *)&lbl_802ABFFC;
                if (sp5C < temp_f30_2) {
                    AddChecksum(QB_DIR, QB_LEFT);
                } else {
                    AddChecksum(temp_r30_2, QB_DIR, QB_RIGHT);
                }
                fn_8009F010(arg0->unk0xC, QB_BLOCKERSHUFFLE, temp_r30_2);
                if (temp_r30_2 != 0) {
                    CStruct_delete(temp_r30_2, 3);
                }
            }
            temp_f0 = lbl_802AC034;
            var_f13 = temp_f0;
            if (temp_f31_3 > temp_f0) {
                var_f13 = temp_f31_3;
            }
            temp_r25->unk0x30 = var_f13;
            temp_f0_2 = lbl_802AC038;
            var_f12 = temp_f0_2;
            if (var_f13 < temp_f0_2) {
                var_f12 = var_f13;
            }
            temp_r25->unk0x30 = var_f12;
            fn_801B5BBC(arg0);
            temp_f11 = temp_r25->unk0x30;
            temp_r9 = arg0->unk0xC;
            temp_r11 = temp_r9 + 0x58;
            temp_f12 = arg0->unk0xA4;
            sp58 = (sp48 * temp_f11 * temp_f12) + ((Unk_C7387A53 *)temp_r9)->unk0x58;
            sp5C = temp_r11->unk0x4;
            sp60 = (sp50 * temp_f11 * temp_f12) + temp_r11->unk0x8;
            sp64 = *(s32 *)&lbl_802ABFFC;
            0;
        }
    }
}
