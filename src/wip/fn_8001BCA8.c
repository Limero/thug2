// PARKED 2026-10-19: still 51.3% NEAR (92/192 words). Retried with address
// locals/params as u32 (aram_top/mem_top/arena_beg/arena_end/dsp_lo/carve +
// 0x84000U/0x1FU unsigned + void* memset args) — principled address-vs-delta
// typing instead of casts. Zero movement: residual is still the arena-carve
// r9/r11 color swap (want carve in r11 + 13CC anchor in r9, got swapped)
// cascading into the sprintf float block via the extra mr. Not a type issue.
// PARKED 2026-09-28 (b3_08): best 51.3% (was 50.8%). Residual: arena carve
// register coloring coin flip — want carve(0x84000) in r11 + 13CC anchor in
// r9, got has them swapped (r9/r11). This 1-register difference cascades into
// a 1-instruction shift (extra `mr r30,r10`) across the entire sprintf float
// conversion block (~50 words) and the AX buffer tail (~39 words). FIX:
// vm_size constant was wrong — want computes mem_top + 0x239800
// (addis 0x24 + addi -0x6800 = 0x240000-0x6800), NOT +0x1D800 as the prior
// agent recorded (arithmetic error: 0x240000-0x6800 = 0x239800). Tried and
// rejected: all 6 arena-carve store permutations, carve as const/named-local/
// dsp_hi, 13C4 store moved after arena carve, float conversions split into
// separate statements, 2^-20 as named local, local decl order swaps, and
// flags -fno-schedule-insns/-insns2/-sched-spec/-gcse/-sched-interblock/
// -expensive-optimizations/-branch-count-reg/-strength-reduce (all 51.3%
// or worse). Known family: doc-15 arg-setup/register-coloring coin flip.
// WIP DRAFT (non-matching) — hand-reconstructed from the DOL disassembly.
// family=m2c range=0x8001BCA8-0x8001BFA8 size=768B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// WHAT IT IS: one-shot audio subsystem bring-up (AX / AI / ARQ / ARAM).
// ARInit(0,0) -> ARQInit -> AIInit(0) -> AXInit -> AXSetMode(2) ->
// AXSetCompressor(0) -> fn_8001D768 (ARQ heap-range init) ->
// fn_8001DB98 (current ARAM heap top) -> 1MB-align the top of usable memory,
// hand the DSP init the ARAM size, carve 0x84000 out of the OS ARENA1 and
// OSSetArenaLo past it, sprintf an OSVReport memory report, then take six
// AX buffers out of ARAM (0x400 stream, 0x219800 dsp, 4x 0x8000).
//
// STATUS 2026-09-26: 21.2% -> 50.8% NEAR (96 of 192 instruction words differ).
// The body below is a ground-truth reconstruction from the disassembly, not
// an edit of the m2c draft. Everything structural is now byte-exact or
// verified-equivalent:
//   * frame 0x240 / `stmw r25,0x224(r1)` / LR at 0x244 / msg buffer at
//     r1+0x10 / int->double scratch double at r1+0x218 (reached by
//     declaring msg[0x200] so the anonymous 8-byte conversion temp lands
//     at 0x218 instead of 0x220 — a 0x208 msg pushes the frame to 0x248)
//   * exactly 7 callee-saved GPRs, r25=0x180000, r26=arena delta,
//     r27=ARAM top, r28/r29/r30=page anchors, r31=new arena end
//   * all 20 calls typed so WANT's zero crclr count is reproduced
//     (ARInit 2, ARQInit 0, AIInit 1, AXInit 0, AXSetMode 1,
//     AXSetCompressor 1, fn_8001D768 0, fn_8001DB98 0->s32,
//     fn_8001D814 2->s32, fn_8025E9AC 3, lbl_8025EDA0 1,
//     lbl_8025F0D4 2, fn_8025EA48 1, OSGetArenaLo/Hi 0->s32,
//     OSSetArenaLo 1, memset 3 (void), sprintf varargs, OSVReport 2,
//     and six more fn_8001D814 in the buffer tail)
//   * two DIFFERENT aligns: `& ~0x1F` for the ARENA1 carve is ngccc's
//     `rlwinm rX,rX,0,0,26`, while the ARAM top is masked 1MB —
//     `(x - 0x241C00) & 0xFFFFF000` = `rlwinm rX,rX,0,0,19`. The 2026-09-10
//     note only covered the 32B form; the m2c draft's `QB_UNKNOWN_0xFFDBE400`
//     / `QB_UNKNOWN_0xFFFFF000` pair was already correct for this one.
//   * arena carve uses the `add rD,rA,rC` form with 0x84000 held in a
//     register (needs the size as a named local, not an inline literal)
//   * `subf rA,rS,rT` is rT-rS, so the stored delta is
//     `OSGetArenaHi() - new_end`, i.e. NEGATIVE headroom
//   * sprintf is 8 float + 8 int args (f1..f5 converted, f6/f7/f8 loaded
//     straight from rodata2 into their arg registers) plus one spare int;
//     0x180000/0x219800/0x18000/0x8000 are plain literals, only 0x180000
//     ALSO exists as a variable (r25) for its float conversion
//   * int->float is the plain `(f32)(f64)(s32)x` cast: it stores the
//     0x43300000 magic half to the stack and subtracts a rodata2 double
//     (0x80291078 = 2^52+2^31 signed, 0x80291088 = 2^52 unsigned). This
//     is the §4n/doc-14 shape — the object carries a 16-byte .rodata with
//     exactly 0x4330000080000000 and 0x4330000000000000, so
//     tools/fix_fp_pool.py retargets the pool pair onto lbl_80291078 /
//     lbl_80291088 at link and the object stays promote-eligible.
//     Do NOT "fix" this into an explicit union/f64 temp.
//   * the six AX buffer pointers are `lbl_8037B5E8 + 0x190..0x1A4`
//     (0x8037B778..0x8037B79C) via one base register, and the base is
//     materialised AFTER the first fn_8001D814 call
//
// REMAINING BLOCKER: one extra `mr r30,r10` in the sprintf argument
// shuffle (the reload of the 0x219800 constant copies it to
// {r3,r5,r28,r30} where WANT copies it to {r4,r5,r28}, r10 itself being
// the 8th arg). That single extra word shifts the whole 5-conversion
// float block and the vararg store/arg block by one instruction, which
// is most of the 98-word residue; the shapes, immediates, offsets and
// call sequence on both sides of it are already identical. This is a
// doc-15 arg-setup scheduling coin flip, not a structural defect.
// Already tried and rejected (all <= 50.8%, default flags best):
// -fno-schedule-insns / -insns2 / both / -fno-sched-spec / -fno-gcse /
// -fno-sched-interblock / -fno-expensive-optimizations (44.1%),
// old-style vs prototyped sprintf, constant-first vs value-first fmuls
// operand order, 0x1D800 add operand order, making 0x219800 / 0x18000 /
// 0x8000 into named variables (2.5-10.8% — they must stay literals),
// named k = lbl_80291080, named vm = 0x1D800, splitting `msg` out of a
// frame-template struct, and all 6 permutations of the three global
// stores in the arena carve (this one, `sz`-store-first, is the best).
// Residual register colours: r3 vs r4 for the re-read of lbl_803213C8,
// `addis 0x24/addi -0x6800` vs `addis 0x2/addi -0x2800` for +0x1D800,
// and `fmuls f0,f0,f4` vs `fmuls f0,f4,f0` on the last conversion.
// Promotion caveat beyond the above: fn_8025E9AC / fn_8025EA48 /
// lbl_8025EDA0 / lbl_8025F0D4 are direct `bl` targets in the original but
// are `type:label` in symbols.txt, so promoting this needs those four
// given `scope:global`.
extern f32 lbl_80291080;   /* 2^-20 : bytes -> MB */
extern f64 lbl_80291078;   /* 2^52 + 2^31 : int->double signed bias */
extern f64 lbl_80291088;   /* 2^52       : int->double unsigned bias */
extern f64 lbl_80291090;   /* 2.099609375 */
extern f64 lbl_80291098;   /* 0.09375    == 0x18000 in MB */
extern f64 lbl_802910A0;   /* 0.03125    == 0x8000 in MB */
extern char lbl_80290FB8[];

extern s32 lbl_803213C0;   /* signed ARENA1 headroom delta */
extern s32 lbl_803213C4;
extern s32 lbl_803213C8;   /* 1MB-aligned top of usable memory */
extern s32 lbl_803213CC;   /* DSP ARENA1 low  */
extern s32 lbl_803213D0;   /* DSP ARENA1 high */
extern s32 lbl_803213D4;
extern s32 lbl_80362748;   /* 0x84000 : DSP carve size */
extern s32 lbl_80300194;
extern char lbl_8037B5E8[];

extern void fn_8025E9AC(s32, s32, s32);
extern void fn_8025EA48(s32);
extern void lbl_8025EDA0(s32);
extern void lbl_8025F0D4(s32, s32);
extern void ARInit(s32, s32);
extern void ARQInit(void);
extern void AIInit(s32);
extern void AXInit(void);
extern void AXSetMode(s32);
extern void AXSetCompressor(s32);
extern s32 OSGetArenaLo(void);
extern s32 OSGetArenaHi(void);
extern void OSSetArenaLo(s32);
extern void memset(void *, s32, s32);
extern void OSVReport(char *, s32);
extern s32 sprintf(char *, char *, ...);
extern void fn_8001D768(void);
extern s32 fn_8001DB98(void);
extern s32 fn_8001D814(u32, s32);

/* the six AX buffer slots live at lbl_8037B5E8 + 0x190..0x1A4
   (0x8037B778..0x8037B79C); one base register + displacements, so the
   base is taken as lbl_8037B5E8 and NOT as the 0x8037B778 label */
struct AXBufPtrs {
    char _pad0[0x190];
    s32 *stream;  /* 0x190 : 0x400   */
    s32 *dsp;     /* 0x194 : 0x219800 */
    s32 *voice0;  /* 0x198 : 0x8000  */
    s32 *voice1;  /* 0x19C */
    s32 *voice2;  /* 0x1A0 */
    s32 *voice3;  /* 0x1A4 */
};

void fn_8001BCA8(void) {
    u32 aram_top;          /* fn_8001DB98() : ARAM heap top */
    u32 mem_top;           /* 1MB-aligned top of usable memory */
    u32 arena_beg;         /* OSGetArenaHi() : ARENA1 start */
    s32 mem_start;         /* "Start Mem" : signed headroom delta */
    u32 arena_end;         /* OSGetArenaLo(), then the OSSetArenaLo target */
    u32 dsp_lo;            /* 32B-aligned ARENA1 end */
    u32 carve;             /* 0x84000 */
    s32 aram_size;         /* 0x180000 */
    s32 vm_size;
    struct AXBufPtrs *bufp;
    s32 *stream;
    char msg[0x200];

    ARInit(0, 0);
    ARQInit();
    AIInit(0);
    AXInit();
    AXSetMode(2);
    AXSetCompressor(0);
    fn_8001D768();

    aram_size = 0x180000;
    aram_top = fn_8001DB98();
    mem_top = (aram_top - 0x241C00) & 0xFFFFF000;
    lbl_803213C8 = mem_top;
    fn_8025E9AC(0x180000, fn_8001D814(mem_top, 0), lbl_803213C8);
    lbl_8025EDA0(1);
    lbl_803213C4 = 0x7E000000;
    lbl_8025F0D4(0x7E000000, lbl_803213C8);
    fn_8025EA48(lbl_80300194);

    arena_end = OSGetArenaLo();
    arena_beg = OSGetArenaHi();
    carve = 0x84000U;
    dsp_lo = (arena_end + 0x1FU) & ~0x1FU;
    lbl_803213CC = dsp_lo;
    lbl_80362748 = carve;
    lbl_803213D0 = dsp_lo + carve;
    memset((void *)dsp_lo, 0, 0x84000);
    memset((void *)lbl_803213D0, 0, lbl_80362748);
    lbl_803213D4 = lbl_803213D0;
    arena_end = (lbl_803213D0 + lbl_80362748 + 0x1F) & ~0x1F;
    OSSetArenaLo(arena_end);
    mem_start = arena_beg - arena_end;

    vm_size = lbl_803213C8 + 0x239800;
    sprintf(msg, lbl_80290FB8,
            (f32)(f64)(s32)mem_start * lbl_80291080, 0x219800,
            (f32)(f64)(u32)vm_size * lbl_80291080, vm_size,
            (f32)(f64)(s32)aram_top * lbl_80291080, aram_top,
            (f32)(f64)(s32)lbl_803213C8 * lbl_80291080, lbl_803213C8,
            (f32)(f64)(s32)aram_size * lbl_80291080, 0x180000,
            lbl_80291090, 0x219800,
            lbl_80291098, 0x18000,
            lbl_802910A0, 0x8000);
    OSVReport(msg, 0);
    lbl_803213C0 = mem_start;

    stream = (s32 *)fn_8001D814(0x400, 0);
    bufp = (struct AXBufPtrs *)lbl_8037B5E8;
    bufp->stream = stream;
    bufp->dsp = (s32 *)fn_8001D814(0x219800, 0);
    bufp->voice0 = (s32 *)fn_8001D814(0x8000, 0);
    bufp->voice1 = (s32 *)fn_8001D814(0x8000, 0);
    bufp->voice2 = (s32 *)fn_8001D814(0x8000, 0);
    bufp->voice3 = (s32 *)fn_8001D814(0x8000, 0);
}
