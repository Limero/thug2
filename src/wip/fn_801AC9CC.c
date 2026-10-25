// WIP DRAFT (non-matching) — hand-rebuilt from the PS disassembly.
// family=m2c range=0x801AC9CC-0x801ACBC0 size=500B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
//
// PARKED 2026-10-02 (w75/0x801AC9CC): DIFF 42.4% (53/125 masked words; was
// DIFF 2.2% from the m2c body) — just under the 50% NEAR line — object
// .text 496B vs want 500B (1 word short). Structure is now RIGHT — frame
// 0xC0, stfd f29/f30/f31 @0xa8/0xb0/0xb8, `lwz r27,0x50(r25)` count +
// `fmuls f29,f31,f31` + `mr r25/r28` param homes, the li/andi/li/cmpwi/li
// flags bool, all three fabs/guard blocks, both call pairs, the
// cr3-pretest + cr4-select tail and the whole epilogue match. What is left is
// pure local-alloc/scheduling, in four places:
//   (a) loop test: want `cmpwi r27,0` then `addi r27,r27,-1` (no temp); ngccc
//       emits `mr r0,r27` + `cmpwi r0,0` (the POST_DEC_EXPR result pseudo from
//       expand_inc), at BOTH the preheader guard and the latch. Tried
//       `for(i=n;i!=0;i--)`+`first+i-1` (12%), `while(i){i--;...}` (38%),
//       `for(i=n-1;;i--)`+`if(i==0)break` (18%, GCC splits the loop),
//       `if(n==0)return 0;` prefix (12%, same split), plain `register s32 i`
//       — all worse. `while(i--)` alone is the right RTL shape.
//   (b) want keeps `&d` (the Vec4 pair temp at sp+8) in a loop-invariant
//       callee-saved r19 (`addi r19,r1,8` in the preheader) and uses it for
//       ONE of the two reloads (`lfs f0,8(r19)`) while the other uses r1
//       (`lfs f12,8(r1)`). A `Vec4 *pd = &d` pointer local does hoist it
//       (and does buy the 13-reg `stmw r19,0x74(r1)` prologue!) but permutes
//       the whole parameter home set (arg0 lands in r24, arg2 in r19) and the
//       score drops to 24%.
//   (c) the "other" pointer: want `lwz r0,0x48(r31); mr r29,r0; cmpwi r0,0;
//       bne; lwz r29,0x4c(r31)` (copy kept, test on the load temp, `o` in r29).
//       With `o = e->p48 ? e->p48 : e->p4c` ngccc coalesces to r30 and tests r30
//       directly; writing it as an explicit `if (e->p48) o = e->p48; else
//       o = e->p4c;` DOES produce the `mr rX,r0` copy but reshuffles every
//       parameter register (32%) and drops the frame back to 0xb8.
//   (d) PS block (14 words): want hoists all four psq_l above both ps_sub
//       (f12=arg1.p0, f0=e.p0, f13=e.p1, f11=arg1.p1 => 4 live FPRs);
//       ngccc interleaves (arg1.p0, e.p0, arg1.p1, ps_sub, e.p1, ps_sub) and
//       recycles f0 for the second pair. Same wall as doc29 fn_800EA4D8 /
//       fn_800FDE38 "intra-BB scheduling". `-fno-schedule-insns` (31%) and
//       `-fno-schedule-insns2` (38%) both hurt; volatile pair array buys the
//       4-load shape but adds a second `lfs` (46.8% at the WRONG 504B size,
//       i.e. structurally wrong).
// Also measured and rejected: declaration order of the 8 locals (bit-identical
// for all four orders), swapping the two `d.p[]= ps_sub(...)` statements
// (identical), `volatile` union array (extra reload), extracting the four
// operands into named __ps_t temps (41.6%). Corrected a stale wall: the two
// opcode-4 words @0x801ACAB4/0x801ACACC are `ps_sub` A-forms (XO5=20), NOT
// VMX `vmsumshm` — docs/parkings/29's "hard VMX wall" reason for this address
// is invalid and this function is fully emittable from C with -mps-float.
#include "types.h"

typedef union {
    __ps_t p[2];
    f32 f[4];
} Vec4;

typedef struct Elem {
    char pad0x00[0x28];
    Vec4 v;
    char pad0x38[0x10];
    struct Elem *p48;
    struct Elem *p4c;
    u32 flags;
    char pad0x54[0xC];
} Elem;

typedef struct {
    char pad0x00[0x48];
    Elem *first;
    s32 pad0x4C;
    s32 n;
} List;

typedef struct {
    __ps_t m[8];
} Mat;

s32 fn_800E9D30(Elem *o, s32 i);
void fn_801AE688(Mat *out, void *a1, Elem *a2);
s32 fn_800EA4D8(void *a0, Vec4 *b, Vec4 *c, Mat *d, void *e);
s32 fn_800EA7D0(void *a0, Vec4 *b, Vec4 *c, Mat *d, void *e);

s32 fn_801AC9CC(List *arg0, Vec4 *arg1, s32 arg2, void *arg3, Mat *arg4, Elem **arg5, f32 farg0, f32 farg1) {
    Elem *e;
    Elem *o;
    Vec4 d;
    Mat mat;
    s32 i;
    s32 ok;
    s32 r;
    f32 rr;

    rr = farg0 * farg0;
    for (i = arg0->n; i--; ) {
        e = arg0->first + i;
        ok = 1;
        if (!(e->flags & 0x20)) {
            ok = 0;
        }
        if (ok && fn_800E9D30(e, 2)) {
            if (!(fabsf(e->v.f[0] - arg1->f[0]) > farg0)) {
                if (!(fabsf(e->v.f[2] - arg1->f[2]) > farg0)) {
                    if (!(fabsf(e->v.f[1] - arg1->f[1]) > farg1)) {
                        d.p[0] = __builtin_ps_sub(e->v.p[0], arg1->p[0]);
                        d.p[1] = __builtin_ps_sub(e->v.p[1], arg1->p[1]);
                        if (!((d.f[0] * d.f[0]) + (d.f[2] * d.f[2]) > rr)) {
                            o = e->p48 ? e->p48 : e->p4c;
                            if (arg2) {
                                fn_801AE688(&mat, arg0, e);
                                r = fn_800EA4D8(arg3, &e->v, &o->v, &mat, arg4);
                            } else {
                                fn_801AE688(&mat, arg0, o);
                                r = fn_800EA7D0(arg3, &o->v, &e->v, &mat, arg4);
                            }
                            if (r == 1) {
                                if (arg2) {
                                    *arg5 = e;
                                } else {
                                    *arg5 = o;
                                }
                                return 1;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}