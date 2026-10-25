// WIP DRAFT (non-matching) — hand-rebuilt C body (replaces the m2c draft)
// family=m2c range=0x800A0FFC-0x800A11D8 size=476B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
//
// PARKED 2026-10-02 (w75/0x800A0FFC): 10.2% -> 36.1% (43/119 words), object now
// SIZE-EXACT (476B) and the prologue/epilogue are byte-identical, but the whole
// paired-single region still differs in FPR/GPR ALLOCATION (not in semantics and
// not in instruction count): every basic block emits the same instruction
// MULTISET as retail, only the registers differ. Concrete residual examples
// come from the paired-single diff tool. In the first block the want loads
// frame offset 8 into f12 at 0078 while the output loads it into f0 there,
// and the want loads from r11 offset 8 into f0 at 007C while the output loads
// frame offset 16 into f13 there. The want forms its stack base with an
// address add of r1 by 8 at 005C while the output loads a page anchor there,
// and the want extends that base by 0x7b28 at 0068 where the output has no
// equivalent, which accounts for one extra stack base register plus one extra
// constant-address register. The normalise step rotates f12 and f13 at 0094.
// In the tail the want loads frame offset 0x50 into f13 at 0170 and copies it
// to f31 at 0174, while the output loads that offset straight into f31, so
// the output is one instruction short in the tail, which also shifts the
// following 8 words.
// Tried (all measured; base = 43/119 = 36.1%, 476B):
//   10.2%  m2c base, `fn_8009F498(sp38, arg0)` 2-arg call
//   15.5%  + `VecObj *fn_8009F498(s32)` — retail passes ONLY the checksum
//          (r4 is never written before the bl) and tests the RETURN value
//          against 0, so the callee is a 1-arg lookup returning the object.
//          THIS WAS A REAL SEMANTIC BUG in the m2c draft, now fixed.
//   21.8%  + scratch area = `volatile S V[10]` (pair array, 80B). Frame
//          formula measured as `frame = 0x30 + 8*n`, so V[10] lands the
//          stmw at 0x68 / stfd at 0x70,0x78 / LR at 0x84 — the retail
//          prologue exactly. This also reproduces retail's four DEAD scalar
//          stores (V[1].w[1]=eps@0x14, V[3].w[1]=eps@0x24, V[7].w[1]=1.0@0x44,
//          V[8].w[1]=1.0@0x4c) and its dead pair duplicates (V[4]=D@0x28,
//          V[5]=C@0x30) — see the matched sibling src/fn_801B19DC.c for the
//          same `V[n].p = v; V[n].w[1] = scalar;` idiom. Each element's slot
//          then lands on retail's offsets 0x08/0x10/0x18/0x20/0x28/0x30/
//          0x40/0x48/0x50, and the s32 out-param lives INSIDE the array at
//          V[6] == 0x38 (a separate s32 local instead gives 0x60 -> 25.2%).
//   36.1%  + read the V elements DIRECTLY inside the builtins instead of via
//          `a`/`b`/`c`/`d` temps (see "NOTE" below). Staging every read
//          gives 21.8% / 464B (3 instructions short); staging only some
//          gives 5.8%. The direct-read form happens to emit the same total
//          instruction count as retail, so everything after it stays aligned.
//   18.5%  same body but a NON-volatile `S V[10]` (address escapes through
//          `&V[6].i[0]`) — dead stores survive but the offsets/order shift.
//   36.1%  neutral: `-fno-sched-spec`, `-fno-sched-interblock`, `-fno-gcse`,
//          `-fno-schedule-insns` (-1), `-fno-thread-jumps`, `extern char
//          lbl_80297B28[]` + `*(volatile __ps_t*)`, scratch as one named
//          `struct { S v[10]; } sc`, scratch via `volatile S *V = Vbuf`,
//          splitting every dot into 3 statements (mul/merge00/madd).
//
// NOTE for the next agent: ngccc DOES CSE repeated volatile reads of the same
// array element here, but it does NOT merge two reads that are consumed by the
// same multiply/madd in one expression — `mul(V[1].p, V[1].p)` emits TWO
// psq_l. Retail emits one. That asymmetry is the whole reason the body has to
// be left un-staged.
//
// PARKING ROOT CAUSE: FPR allocation. Applies to every spill-heavy -mps-float
// body in this family (0x800A0E6C / 0x800A0F2C / 0x800A9200 / 0x800A9298 are
// the same shape). The house solutions for the byte-exact PS bodies are all
// `register __ps_t x __asm__("frN")` pins plus inline asm windows
// (src/fn_8000714C.c, src/fn_801B19DC.c, src/wip/fn_800A0F2C.c); with pure C
// and no pins ProDG picks a different but equally valid colour for the PS web.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern __ps_t lbl_80297B28;
extern f32 lbl_80297BA8;
extern f32 lbl_80297BAC;
extern f32 lbl_80297BB0;
extern f32 lbl_80297BB4;

f32 Kenacosf(f32);
void GetChecksum_2(CStruct *, s32, volatile s32 *, s32);
void fn_8012772C(s32, s32, f32);

typedef union { __ps_t p; f32 w[2]; s32 i[2]; } S;

typedef struct {
    char pad0x0[0x58];
    __ps_t unk0x58;
    __ps_t unk0x60;
    char pad0x68[0x10];
    __ps_t unk0x78;
    __ps_t unk0x80;
} VecObj;

VecObj *fn_8009F498(s32);

s32 fn_800A0FFC(VecObj *arg0, CStruct *arg1, CScript *arg2) {
    volatile S V[10];
    __ps_t a;
    __ps_t b;
    __ps_t c;
    __ps_t d;
    __ps_t t;
    __ps_t inv;
    SN_PS_type dot;
    f32 eps;
    f32 v31;
    VecObj *o;

    V[6].i[0] = 0;
    GetChecksum_2(arg1, 0, &V[6].i[0], 1);
    o = fn_8009F498(V[6].i[0]);
    eps = lbl_80297BA8;
    v31 = eps;
    if (o != NULL) {
        V[0].p = arg0->unk0x78;
        V[1].p = arg0->unk0x80;
        V[1].w[1] = eps;
        dot.ps = __builtin_ps_madd(V[0].p, V[0].p,
                 __builtin_ps_merge00(__builtin_ps_mul(V[1].p, V[1].p), lbl_80297B28));
        dot.ps = __builtin_ps_sum0(dot.ps, dot.ps, dot.ps);
        if (dot.flt.hi > eps) {
            inv = __builtin_ps_rsqrte(dot.ps);
            a = __builtin_ps_muls0(V[0].p, inv);
            V[7].p = inv;
            V[0].p = a;
            V[7].w[1] = lbl_80297BAC;
            V[1].p = __builtin_ps_mul(V[1].p, V[7].p);
        }
        c = __builtin_ps_sub(o->unk0x60, arg0->unk0x60);
        V[3].p = c;
        V[3].w[1] = eps;
        d = __builtin_ps_sub(o->unk0x58, arg0->unk0x58);
        b = V[3].p;
        V[5].p = c;
        V[4].p = d;
        dot.ps = __builtin_ps_merge00(__builtin_ps_mul(b, b), lbl_80297B28);
        V[2].p = d;
        dot.ps = __builtin_ps_madd(d, d, dot.ps);
        dot.ps = __builtin_ps_sum0(dot.ps, dot.ps, dot.ps);
        if (dot.flt.hi > eps) {
            inv = __builtin_ps_rsqrte(dot.ps);
            V[8].p = inv;
            d = __builtin_ps_muls0(d, inv);
            V[2].p = d;
            V[8].w[1] = lbl_80297BAC;
            b = __builtin_ps_mul(b, V[8].p);
            V[3].p = b;
        }
        t = __builtin_ps_mul(V[1].p, V[3].p);
        dot.ps = __builtin_ps_madd(V[0].p, V[2].p,
                 __builtin_ps_merge00(t, lbl_80297B28));
        dot.ps = __builtin_ps_sum0(dot.ps, dot.ps, dot.ps);
        V[9].p = dot.ps;
        v31 = V[9].w[0];
    }
    eps = Kenacosf(v31) * lbl_80297BB0 - lbl_80297BB4;
    fn_8012772C(arg2->unk0x18, QB_DOTPROD, v31);
    fn_8012772C(arg2->unk0x18, QB_ORIENTATION, eps);
    return 1;
}