// PARKED 2026-10-18: DIFF 14.3% (was 7.7% m2c husk), exact frame (0x60 with
// saves at 0x54/0x58/0x64). Full hand rebuild from a complete word-level
// decode of want (raw words + ps_disasm + targeted ngccc probe compiles for
// every PS sub-opcode used: merge00=C16, sum0=XO10, rsqrte=XO26, res=XO24).
// Fixed vs the husk: the whole paired-single middle (was `0;` stubs), the
// bogus static `sp40`, and the tail chain (GetFloat needs the GetStructure
// result chained in r3 -- 4 args, not 3).
// Decoded shape: two fn_801AE5A4 16B-desc fills (sp+0x18, sp+0x28), a
// paired-single block (sub/mul-square/sub/merge00(K)/madd/square-accumulate/
// sum0, then a res(rsqrte()) cheap-sqrt -- i.e. sqrt via composed estimates),
// the length to f31 across GetStructure(QB_WALK_PARAMETERS,0), a chained
// GetFloat(struct, QB_LADDER_BOTTOM_OFFSET_UP, &sp38, 1), fdivs by f31 to
// arg0+0x19B8, fn_8020D2E4(arg0,3), and a conditional store of
// arg0->unk1830 to [arg0->unk1858]+0x25C.
// FRAME FINDING (reusable): the compiler leaves sp+0..7 empty on its own
// (verified in minimal probes across ProDG 3.5-3.9.3, with and without calls
// and smalls) -- so a frame struct must NOT start with pad; the first pair
// member lands at sp+8 by itself. Declaration order does NOT move it.
// RESIDUAL: (1) FPR colors across the web (want f12/f13/f11/f0, got
// f10-first rotation) -- program order already mirrors want's instruction
// order, so this is allocator choice, not source order; needs a color lever.
// (2) Head `lwz r0;m r r5,r0` vs got `lwz r5` (1 word -- half the length gap).
// (3) 2 words short overall. Do not permute blindly; fix colors first.
// WIP DRAFT (non-matching) -- hand rebuild; original bytes in DOL, not
// reproduced here per repo policy.
// family=m2c range=0x800EA2CC-0x800EA3D0 size=260B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py -- never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern __ps_t lbl_8029ABB0;

void fn_801AE5A4(void *, s32, void *);
CStruct *GetStructure(s32, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
void fn_8020D2E4(void *, s32);

/* arg0->unk0x1830 points at this: two pointer slots at +0x48/+0x4C. */
typedef struct {
    char _00[0x48];
    void *m48;
    void *m4c;
} P1830_t;

typedef union {
    __ps_t p;
    f32 s[2];
} PairCC;

/* NOTE: no leading pad member -- the compiler places the first pair at
   sp+8 on its own (verified across ProDG 3.5-3.9.3); a _00[8] would push
   every pair slot 8 too high. The 12 bytes of named smalls below land at
   sp+0x48..0x53, putting the saves at 0x54/0x58 for a 0x60 frame. */
typedef struct {
    __ps_t p08;
    __ps_t p10;
    __ps_t p18;
    __ps_t p20;
    __ps_t p28;
    __ps_t p30;
    f32 f38;
    char _3c[4];
    PairCC p40;
} FrameCC;

void fn_800EA2CC(Unk_9C44AE00 *arg0) {
    __ps_t t12;
    __ps_t t13;
    __ps_t t11;
    __ps_t t0;
    void *v5;
    s32 h;
    f32 len;
    FrameCC fr;

    v5 = ((P1830_t *)arg0->unk0x1830)->m48;
    if (v5 == 0) {
        v5 = ((P1830_t *)arg0->unk0x1830)->m4c;
    }
    fn_801AE5A4(&fr.p18, arg0->unk0x1838, v5);
    fn_801AE5A4(&fr.p28, arg0->unk0x1838, (void *)arg0->unk0x1830);
    t12 = fr.p30;
    t13 = fr.p20;
    t11 = lbl_8029ABB0;
    h = QB_WALK_PARAMETERS;
    t13 = __builtin_ps_sub(t13, t12);
    t0 = fr.p18;
    fr.p10 = t13;
    t12 = fr.p28;
    t13 = __builtin_ps_mul(t13, t13);
    t0 = __builtin_ps_sub(t0, t12);
    fr.p08 = t0;
    t13 = __builtin_ps_merge00(t13, t11);
    t0 = __builtin_ps_madd(t0, t0, t13);
    t0 = __builtin_ps_sum0(t0, t0, t0);
    t0 = __builtin_ps_rsqrte(t0);
    t0 = __builtin_ps_res(t0);
    fr.p40.p = t0;
    len = fr.p40.s[0];
    GetFloat(GetStructure(h, 0), QB_LADDER_BOTTOM_OFFSET_UP, &fr.f38, 1);
    *((f32 *)((char *)arg0 + 0x19B8)) = fr.f38 / len;
    fn_8020D2E4(arg0, 3);
    if (arg0->unk0x1830 != 0) {
        /* corpus struct has no name for +0x1858 (pad0x1854+8); it is a word load. */
        *(s32 *)((char *)*(void **)((char *)arg0 + 0x1858) + 0x25C) = arg0->unk0x1830;
    }
}
