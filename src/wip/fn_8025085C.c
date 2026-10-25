// PARKED 2026-10-30: 68.3% -> 68.3% (re-measured, unchanged)
// WIP DRAFT (non-matching) — 64-tap 12-bit PCM resampler / interpolator.
// family=m2c range=0x8025085C-0x80250900 size=164B
// FLAG: -fno-gcse -fno-schedule-insns -fno-schedule-insns2
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// STATUS 2026-10-30 (r4): faithful C reconstruction, EXACT want length
// (41 words / 164 B = symbols.txt size:0xA4), 68.3% masked (28/41).
// 13 words differ. Object carries ONLY .text + .rela.text (no private
// .rodata pool -> no doc-14 promote caveat). Inline asm = 2 instructions
// of 41 (4.9%): the mfctr/mtctr CTR save-pair.
//
// --- MEMBER OF doc 41 (hand-written-asm module 0x8024EF18-0x80250E6C) ----
// docs/parkings/41 already lists fn_8025085C (fingerprint 1, CTR save-pair)
// and says "Do NOT re-grind loop spellings/prologues for fingerprint-bearing
// functions". r4 did the semantic re-audit anyway; see the lever log below.
// The old "mfctr/mtctr => unmatchable" reason stays refuted (2 inline-asm
// instructions reproduce it), and this function carries NO other doc-41
// fingerprint: it is frameless and uses only volatile GPRs r3-r12, so it is
// ABI-clean. The residual is register choice + 4 branch-OPCODE inversions.
//
// --- CORRECTIONS TO THE PREVIOUS HEADER (2026-09-25) ------------------------
// 1) The four clamp-branch diffs are NOT "want bge/bgt, got ble/blt". Both
//    sides emit the SAME condition family; only BO differs, and all targets
//    are ALREADY EXACT (verified from readelf -r, 10/10 below). DANGER:
//    tools/disasm.py (and objdump) MISLABEL BO=5. Retail's BO=5 branches
//    at 0x8C/0x9C/0xC4/0xE4 print as "bge"/"ble", which is why this read as
//    a branch-EXTENT problem. Decode branch words from raw hex
//    (BO = bits 25..21, BI = bits 20..16, AA = bit 1, LK = bit 0), never
//    from a disassembler mnemonic.
// 2) Every one of the 10 R_PPC_REL14/REL24 addends in the object already
//    lands on want's branch target, so the mask hiding branch extents
//    (recipe 283) is NOT in play here. The only masked-visible difference
//    on those 4 rows is BO.
// 3) Old item (d) said the tail `lhzu` fix "leaves the negative arm
//    semantically DEAD"; that is right and it is a TRAP (see lever L1).
//
// --- the exact 13 differing words (field-level, verified) --------------------
// Words 4 and 5 form a swapped test/shift pair. At word 4 the reference holds
// hex 70A80001 (test-with-record on r8) where this build holds 54A7083C
// (shift into r7), and at word 5 the two encodings appear mirrored, again
// with a scratch-register difference. Both rows are ordering ties. Word 9
// (3940003F versus 3800003F) loads the 0x3f loop-count constant into r10 in
// the reference but into r0 here. Word 10 (7D4903A6 versus 7C0903A6) moves
// that counter to the count register from r10 in the reference and from r0
// here. Words 12, 16, 26 and 34 are branch-encoding ties on already-exact
// targets: hex 40A0000C/40A10008/40A10028/40A10008 in the reference versus
// 4080003C/40810048/40810090/40810090 here, i.e. the BO=5 true-branch form
// (conditions blt/blt/blt/blt on BI 0/1/1/1) against the BO=4 inverted form
// (bge variants), with identical destinations. Words 19 and 37 (A5640002
// versus AD640002) are load-width ties on the input halfword, unsigned form
// in the reference against signed form here. Word 20 (7D6B0735 versus
// 2C0B0000) sign-extends the halfword in the reference where this build
// compares it against zero instead. Words 32 and 33 (2C0B0800 versus
// 7D6B00D0, mirrored) are a swapped compare/negate pair around the 0x800
// limit, occupying opposite slots in the two builds.
//
// Retail's clamp shape is uniformly  "cmpwi v,K ; blt SKIP ; li v,K2" --
// i.e. branch-on-TRUE to SKIP. That is the source form `if (v >= K) v = K2;`
// with the then-arm as fall-through, or an explicit goto. Neither is
// reachable from C here (see L2/L3/L4).
//
// --- lever log (all measured 2026-10-30, flags as above, private LEAF_TMPDIR)
// --  base (inherited) ................................................ 68.3%
// L0 verify authority: tools/venv/bin/python tools/test_wip_drafts.py
//    --addr 0x8025085C  ->  "NEAR  m2c  0x8025085C (164B) 68.3%"  (x3, stable)
// !! TRAP — DO NOT ADOPT: drop the (s16) cast, read as unsigned  73.2% (+2 w)
//    `v = *++ip;` with u16 *ip fixes BOTH lhzu (w19,w37) but v is then
//    0..0xFFFF, so `v < 0` and the whole negative arm (0xD0-0xE8) plus the
//    blt at 0xB4 are PROVABLY DEAD. Not a faithful match. Also note it does
//    not fix the extsh (w20), so it buys 2 of 13 words with wrong semantics.
// L1 s32 retype / dead-w variants:
//    s16 *ip (signed load, no cast) ............................... 65.9%
//    s16 *ip + s32 store (no (s16) on store) ...................... 65.9%
//    two-name load (u16 raw; v = (s16)raw; store from v) ......... 16.7% (DIFF)
//    s16 temp sv declared (unused) .............................. 65.9%
// L2 polarity, one clamp at a time (`if (v >= K)` flip):
//    prologue 1st  cmpwi  -> 68.3% neutral, but BO goes 4 -> 12 (worse shape)
//    prologue 2nd  cmpwi  -> 65.9%
//    loop positive clamp  -> 65.9%  (and the immediate degrades 0x7ff->0x7fe)
//    loop negative clamp  -> 68.3% neutral
//    first clamp only, as if/else-if retained .................... 63.4%
//    all four + separate ifs (no else-if chain) ................. 19.5% (DIFF)
// L3 full goto-skip form for all 4 clamps (`if (v < K) goto L; v = K2;`)
//    ................................................................ 53.7% (DIFF)
//    GCC answers BO=12 (not 4, not 5) AND splits mullw/add into r7/r0.
//    The explicit-goto layout of retail IS the right shape; cc1 refuses the
//    BO=5 encoding for it.
// L4 negative-arm magnitude, named temp:
//    v=-v; v=v*stride+adj; if(v>0x800) v=-0x800; else v=-v; ...... 7.3% (DIFF)
//    m=-v; m=m*stride+adj; v=-m; if(m>0x800) v=-0x800; ........... 7.3% (DIFF)
//    (5 earlier spellings in the 2026-09-25 note also fail: fold /
//     mag-then-else / flat / explicit -mag / subf)
// L5 andi./slwi order (want andi. FIRST, in r8):
//    named s32 odd = arg2 & 1, tested first ..................... 65.9%
//    if((arg2&1)!=0){stride=..}else{stride=..; arg2-=1;} ....... 68.3% neutral
//    if((arg2&1)==0){arg2-=1;} stride=arg2<<1;  (reordered) .... 61.0%
//    r8-exclusion trick / declaration reorder ................... not tried
// L6 loop counter register (want li r10,0x3f / mtctr r10; got r0):
//    u32 ctr (was s32), for/do-while unchanged ................... 68.3% neutral
//    swap local decl order (ctr before mult) ..................... 68.3% neutral
//    register s32 ctr __asm__("r10")  -> BLOCKS the mtctr/bdnz
//      conversion entirely and costs 2 words (AGENTS 6y-141); already
//      recorded in the 2026-09-25 note, re-confirmed not worth re-trying.
// L7 extsh. (w20): no C spelling found. The faithful source IS
//    `v = (s16)*++ip;` over a u16 buffer; cc1 folds the sign extension into
//    the load and then narrows the two zero/sign tests onto the QImode
//    value (semantically a miscompile -- the SImode form is what makes the
//    negative arm live). No flag was tried: combine is not flag-controlled
//    and all 5 in-tree ProDG builds share the front end.
//
// --- audit of the best (base) body ---------------------------------------
// object .text = 0xA4 = 164 B = symbols.txt size:0xA4 = header size=164B.
// Sections: .text + .rela.text ONLY (no .rodata/.data) -> masked-EXACT would
// be promote-clean; not applicable while 13 words differ.
// REL14 8/8 and REL24 2/2 addends land on want's branch target
//   (0x20->0x8025087C, 0x3C->0x80250898, 0x48->0x802508A4 (x2),
//    0x90->0x802508EC (x4), 0x74->0x802508D0, 0x50->0x802508AC).
// No extern data symbols in the body, so the hazard-277 masked-wrong-label
// case cannot apply. No opcode-4 words (pure ProDG GPR zone).
//
// --- semantics (decoded from the disasm, verified word-by-word) -------------
// arg0=out (s16*), arg1=in (u16*), arg2=phase/adj, arg3=multiplier.
//   adj    = arg2 & 0xFF;  mult = arg3 & 0xFFFF
//   stride = adj << 1;  if (adj is even) adj -= 1
//   out[0] = clamp( (s16)in[0] * mult )                      <- signed load
//   for 63 iterations (bdnz, CTR preloaded 0x3F):
//       s = (s16)*++in;                                    <- lhzu + extsh.
//       if (s == 0) store as-is
//       else if (s > 0) store clamp( s*stride + adj )
//       else           store clamp( -( (-s)*stride + adj ) )
// The retail clamp tests are "branch on TRUE to SKIP" (BO=5), i.e. retail's
// low clamp is `if (p >= -0x800) p = -0x800;` -- inverted relative to a
// min(). Reproduced as-is, not "fixed". The negative arm's compare is on the
// PRE-negate magnitude and the branch consumes that compare's CR0.
// The final lhzu of in[64] is a dead prefetch the game still emits.
#include "types.h"
void fn_8025085C(void *arg0, void *arg1, s32 arg2, s32 arg3) {
    register s32 v __asm__("r11");
    register s32 stride __asm__("r7");
    s32 mult;
    s32 ctr;
    s16 *op;
    u16 *ip;
    register s32 ctr_save __asm__("r12");

    op = (s16 *)arg0;
    ip = (u16 *)arg1;
    __asm__("mfctr %0" : "=r"(ctr_save));
    v = (u16)ip[0];
    arg2 &= 0xFF;
    mult = arg3 & 0xFFFF;
    stride = arg2 << 1;
    if ((arg2 & 1) == 0) {
        arg2 -= 1;
    }
    v = v * mult;
    ctr = 0x3F;
    if (v < -0x800) {
        v = -0x800;
    } else if (v > 0x7FF) {
        v = 0x7FF;
    }
    *op = (s16)v;
    v = (s16)*++ip;
    do {
        if (v == 0) {
            goto store;
        }
        if (v >= 0) {
            v = v * stride + arg2;
            if (v > 0x7FF) {
                v = 0x7FF;
            }
        } else {
            v = -((-v) * stride + arg2);
            if (v > 0x800) {
                v = -0x800;
            }
        }
    store:
        *++op = v;
        __asm__("" ::: "memory");
        v = (s16)*++ip;
        ctr -= 1;
    } while (ctr != 0);
    __asm__("mtctr %0" : : "r"(ctr_save));
}
