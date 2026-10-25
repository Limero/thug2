// RE-TRIAGED 2026-10-19: still parked — the post-sched2 permutation wall
// stands and link-identical CFG needs the split-asm window. Parked as-is.
// PARKED 2026-09-30: 4.4% -> 93.4%
//
// Full hand-rebuild (the m2c draft was a statics-DCE husk: its 27 paired-single
// copies were rendered as `0;` and deleted, 596B object for a 732B want).
// Structure now byte-exact everywhere except ONE 18-insn window at the end of
// the fall-through path (indices 153-170, 0x801B2660-0x801B26A8): four psq_l +
// two ps_sub + the `lis/lfs` of lbl_802ABF10 + the call-arg scalars, all
// present with the right registers and the right offsets, but emitted in a
// different order.
//
// RESIDUAL (12/183 words, all in that one window). The original interleaves
// the four pair loads with the scalar constant setup, the two pair
// subtractions, and the store sequence in source order.
// Got: the two PINNED minuend loads are emitted first, then both
// soft subtrahend loads, then the scalars, then both subs, then the stores.
// `cc1 -dr` shows the POST-RELOAD RTL is ALREADY in want's order (f13 load,
// subtrahend load, sub0, f0 load, subtrahend load, sub1), and neither
// -fno-schedule-insns nor -fno-schedule-insns2 changes the window, so the
// permutation is introduced after sched2 and no source spelling reaches it.
// Exhausted here: grouped vs interleaved statement order, separate variable
// sets per block (b0/b1/v2/v3), pins on the results (fr13/fr0 on top of the
// minuend pins), pins on the subtrahends (fr12/fr11, both orders), volatile
// reads of minuend and of subtrahend, `volatile` on the sp88 array, zero-code
// "+f" and `"+r"` barriers, memory fences at 5 placements, `extern const f32`
// on lbl_802ABF10, all 24 declaration orders, all 24 pointer-assignment
// orders, and 15 compiler flags (-fno-schedule-insns{,2}, -fno-sched-spec,
// -fno-sched-interblock, -fno-thread-jumps, -O1/-Os/-O3: only -Os and
// -fno-schedule-insns{,2} change anything, all worse).  UNLESS a lever is
// found for the 2 hard-reg psq_l loads floating past the 2 soft ones, do NOT
// re-run the flag/permutation ladder on this window.
//
// SEPARATE FINDING — THIS DRAFT IS NOT LINK-IDENTICAL even at 100% masked.
// The loop-2 decrement-branch at 0x801B2494 must SELF-target with the ten
// block-1 pair copies sitting in the loop's PREHEADER, i.e. the body runs
// ONCE. Plain C only reaches that window by putting the copies INSIDE the
// do-while body, which makes the body execute 4x and the latch branch back
// to the body start — the masked score cannot see this (branch fields are
// masked), so the linked bytes would differ. The doc-30 split-asm window
// reproduces the exact CFG with 3 emitted instructions (counter setup, the
// ten copies, self-targeting decrement-branch) and is the SEMANTICALLY
// correct form.
// Measured: 91.80% (loses 3 words because without a real loop the address of
// sp8 stops being reused, and the three fn_801B1D00 sites then need a
// stack-slot address re-materialisation that plain C will not split off the
// pinned home). Left as the pure-C 93.44% version per the no-asm preference;
// asm route is the next thing to try if the tail window is ever cracked.
//
// Tooling note: the file-local `A_t` typedef means test_wip_drafts.py's
// issue-01 `volatile double _dummy;` injection (inserted after the first `{`)
// lands INSIDE the typedef and shifts every field by +8 in that variant.  The
// tool keeps the better of the two variants so the reported 93.4% is the clean
// build, but any hand-run of the dummy variant will show bogus struct offsets.
//
// family=m2c range=0x801B23FC-0x801B26D8 size=732B
// extra_cflags: -mps-float
typedef struct {
    char    _000[0x0C];
    s32     unk0x0C;
    char    _010[0xA8];
    f32     unk0xB8;
    char    _0BC[0x04];
    __ps_t  unk0xC0;
    __ps_t  unk0xC8;
} A_t;

void fn_8012834C(void *arg0, void *arg1, void *arg2, s32 arg3);
f32  fn_801B19DC(void *arg0);
f32  fn_801B16A0(void *arg0, f32 arg1);
s32  fn_801B1D00(void *a0, void *a1, void *a2, f32 f1, f32 f2, f32 f3);
f32  fn_80005C28(void *a0, s32 a1, s32 a2, s32 a3);
void fn_80007BFC(void *a0, void *a1, void *a2);
void fn_801B17E4(void *a0, void *a1);

extern f32  lbl_802ABF04;
extern f32  lbl_802ABF08;
extern f32  lbl_802ABF0C;
extern f32  lbl_802ABF10;
extern char lbl_802ABEF4[];

s32 fn_801B23FC(void *arg0, void *arg1) {
    __ps_t  sp8[8];
    __ps_t  sp48[8];
    __ps_t  sp88[4];
    f32     spA8;
    __ps_t *p8;
    register __ps_t *p48 __asm__("r30");
    __ps_t *p88;
    f32    *pa8;
    s32     ctr;
    s32     ctr2;
    __ps_t *pm;
    register __ps_t a0 __asm__("fr13");
    register __ps_t a1 __asm__("fr0");
    __ps_t  v0;
    __ps_t  v1;
    f32     t0;
    f32     t1;
    f32     t2;
    f32     t3;

    ctr = 4;
    while (--ctr != 0) ;
    p8 = &sp8[0];
    pa8 = &spA8;
    p48 = &sp48[0];
    p88 = &sp88[0];
    pm = (s32 *)((A_t *)arg0)->unk0x0C;
    __asm__ __volatile__("" ::: "memory");
    ctr2 = 4;
    do {
    sp8[0] = pm[26];
    p8[1] = pm[27];
    sp8[2] = pm[28];
    sp8[3] = pm[29];
    sp8[4] = pm[30];
    sp8[5] = pm[31];
    sp8[6] = pm[32];
    sp8[7] = pm[33];
    sp8[6] = pm[11];
    sp8[7] = pm[12];
    } while (--ctr2 != 0) ;
    spA8 = lbl_802ABF04;
    fn_8012834C(arg1, (void *)lbl_802ABEF4, pa8, 0);
    t0 = fn_801B19DC(arg0);
    if (fn_801B1D00(arg0, sp8, p48, t0, fn_801B16A0(arg1, t0), spA8) == 0) {
        t1 = t0 + lbl_802ABF08;
        if (fn_801B1D00(arg0, sp8, p48, t1, fn_801B16A0(arg1, t1), spA8) == 0) {
            t2 = t0 - lbl_802ABF0C;
            if (fn_801B1D00(arg0, sp8, p48, t2, fn_801B16A0(arg1, t2), spA8) == 0) {
                a0 = ((A_t *)arg0)->unk0xC0;
                a1 = ((A_t *)arg0)->unk0xC8;
                v0 = a0 - sp8[6];
                v1 = a1 - sp8[7];
                sp88[2] = v0;
                sp88[3] = v1;
                sp88[0] = v0;
                sp88[1] = v1;
                t3 = fn_80005C28(((A_t *)arg0)->unk0x0C + 0x78, p88, 2, 1);
                if (fn_801B1D00(arg0, p8, p48, t3, fn_801B16A0(arg1, t3), spA8) == 0) {
                    sp48[0] = sp8[0];
                    sp48[1] = p8[1];
                    sp48[2] = sp8[2];
                    sp48[3] = sp8[3];
                    sp48[4] = sp8[4];
                    sp48[5] = sp8[5];
                    sp48[6] = sp8[6];
                    sp48[7] = sp8[7];
                    return 0;
                }
            }
        }
    }
    sp48[0] = sp8[0];
    sp48[1] = p8[1];
    sp48[2] = sp8[2];
    sp48[3] = sp8[3];
    sp48[4] = sp8[4];
    sp48[5] = sp8[5];
    fn_80007BFC((char *)arg0 + 0x20, p8, p48);
    a0 = sp48[6];
    a1 = sp48[7];
    v0 = a0 - sp8[6];
    v1 = a1 - sp8[7];
    sp88[2] = v0;
    sp88[3] = v1;
    sp88[1] = v1;
    sp88[0] = v0;
    ((A_t *)arg0)->unk0xB8 = lbl_802ABF10;
    fn_80005C28(((A_t *)arg0)->unk0x0C + 0x78, p88, 2, 1);
    fn_801B17E4(arg0, arg1);
    return 1;
}
// 2026-10-22: 94.0% (was 93.4%): `sp88[1]` stored before `sp88[0]`.
