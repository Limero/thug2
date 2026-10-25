// WIP DRAFT (non-matching) — hand reconstruction from the retail disassembly.
// family=m2c range=0x8006E2FC-0x8006E840 size=1348B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// FLAG: -mps-float
//
// PARKED 2026-10-05 (w_8006E2FC): DIFF 8.54% (300/328 words differ), object
// 1312 B vs want 1348 B (9 words short, all at the epilogue tail).  The m2c
// body this replaced scored 3.21% at 1248 B.  Everything below is now decoded
// and confirmed; the residual is register allocation + scheduling only.
//
// WHAT IS CONFIRMED CORRECT IN THIS BODY
//  * Signature: 7 GPR args (arg0..arg6) + 5 f32 args (farg0..farg4).  m2c's
//    13th `arg7` is phantom — no `lwz` above r1+0x104 exists in retail.
//  * Stack layout (Gsave = 0x108 exactly == retail):
//      r1+0x08 Vec4  t      (16B) — the {dx, dz} / {lo-pad, hi+pad} scratch
//      r1+0x18 Box   sp18   (32B) — fn_800063B8 dst (4 x __ps_t)
//      r1+0x38 Box   sp38   (32B) — fn_8000723C dst, widened by fn_8000728C
//      r1+0x58 Box   sp58   (32B) — padded query box
//      r1+0x78 Params sp78  (0x44) — fn_8006BD1C block + the spawn fields
//      r1+0xC0 s32, r1+0xC4 s32, r1+0xC8 Ps2  (dist2 for the search loop)
//    GCC lands every one of these on retail's offset (verified).
//  * All 21 call sites prototyped with retail arity => ZERO `crclr cr1eq`,
//    matching retail (retail has none either).  arg-pass order also matches.
//  * PS idiom: `psq_l/psq_st ...,W0,I0` + `ps_sub/ps_mul/ps_merge00/ps_madd/
//    ps_sum0` chain for the distance test, emitted verbatim (same ops, same
//    operands, different schedule).  KEY FACT for the repo: **3.9.3 emits
//    `psq_l %0,%1,0,0` for a plain `__ps_t` array/struct copy** — the "W0" that
//    `ps_diff.py`/`ps_disasm.py` print is what a whole 8-byte pair copy looks
//    like in this toolchain.  So `psq_l d(rX),W0` + `psq_st d(rY),W0` == one
//    `__ps_t` copy, NOT a 4-byte scalar.  That reinterpretation is what makes
//    the r1+8 scratch, the 32-byte boxes and the 0x44 param block line up.
//  * `Box` (4 x __ps_t) == `{f32 lo[4]; f32 hi[4]}`: fn_8000728C (byte-identical
//    sibling) proves lo at +0,+4,+8 and hi at +0x10,+0x14,+0x18, i.e. the
//    AABB's 6 live fields are {0,4,8} and {0x10,0x14,0x18}.  The overlap test
//    field offsets (0,0x10,8,0x18,4,0x14) and comparison order (x,x,z,z,y,y)
//    now match retail word-for-word.
//  * The search loop's eviction test is `(u32)now < stamp || stamp-now > 0x1F4`
//    then `stamp`-match `entry->id != arg4` — m2c had swallowed it into
//    `(0,0,0,0,0,0,...)`.  Struct is `{Vec4 pos; s32 id; s32 stamp;}` = 0x18.
//  * The vtable slot is `+0xC`, `s16` offset at `+0xB0` (`lha`) and the fn ptr
//    at `+0xB4` (`lwz`); return type is a POINTER (r3 survives `blrl`) and the
//    box lives at `self + ofs`.  fn_800546A0's arg is `obj[0]`.
//  * Outer walk is `for (p = list; *p; p++)` (GCC's bottom-tested rotation
//    gives retail's `lwz 0(r31) / mr r31,r23`), inner is
//    `cur = *b; b++` giving `lwzu r30,4(r28)`.
//  * The spawn block's second `else if` tests the **`arg4 == 0` saved in CR7**
//    (`mfcr r29` at +0x1F4, restored `mtcrf 0x80,r29`); the m2c
//    `(tmp!=0) && (tmp==0)` is a decode artefact of that.
//  * `(s32)(fn_800144C8() * lbl_80294BE8)` is what produces
//    `fctiwz/stfd 0x100(r1)/lwz 0x104(r1)`; the 8-byte scratch sits at the TOP
//    of the local area, so Gsave 0x108 is forced by it.
//
// RESIDUAL (300 words), in order of cost:
//  (1) FRAME: `stwu r1,-0x180` + `stmw r14` vs retail `-0x178` + `stmw r16`.
//      Gsave already matches (0x108); the frame is 8 B over purely because
//      GCC keeps TWO extra callee-saved GPRs: r16 = a *second* pseudo for
//      `&sp18` (retail remats `addi r29,r1,0x18` into one callee-saved reg),
//      and r17 = a *second* `lis 0x8036` page base for the two output arrays.
//      This one word shifts the whole body, so it is worth ~everything else.
//      This is the doc-81 §2 "the SUM/address is one callee-saved pseudo" wall.
//  (2) PROLOGUE colours/order: retail arg3=r17, arg5=r16 (mine r15, r14);
//      retail interleaves the GPR and FMR moves (r24,r18,[lis],r20,r19,f31,
//      r25,f29,r17,f28,r16,f27,f26), mine batches all 7 GPR moves then all 5
//      FMRs.  Same register *count* (7), different allocation order — a
//      reg_alloc_order artefact of pseudo birth order, not expressible in C
//      (a `register __asm__("rN")` pin set would be a 7!x5! search = banned).
//  (3) `lis r9,-0x7fd7` + `lis r11,-0x7fd7` (retail, two remats feeding
//      `lfs f30` and `addi r26,...,0x4b40`) is CSE'd by 3.9.3 into one `lis`.
//  (4) Overlap-test tail polarity: retail materialises the boolean
//      (`li r0,0 / b / li r0,1 / cmpwi r0,0 / beq`) with the LAST compare
//      inverted (`fcmpu f0,f13; ble`); got branches all six `bgt` at one reject
//      block.  Same condition, different block placement.
//  (5) Accept block byte-offset: retail `mr r29,r26` (per outer iter) then
//      `addi r29,r29,4`; got keeps `r30` and emits an extra `addi r28,r30,4`.
//  (6) `addi r9, r1, 8` remat inside the pad block (retail) is absent in got
//      (doc 81 §1 `volatile`-local lever; not tried here).
//  (7) minor: `subf r0,r0,r29` vs got's `subf r29,r29,r0`; `mr r27,r3` vs
//      got's `mr r30,r3` + `or. r27,r30,r30`; `addi r26,r9`/`addi r11,r11`
//      relocation ordering.
//
// RULED OUT (measured, each reverted):
//  * `Box sp18[4]`-style `__ps_t[]` arrays + a cast accessor macro instead of
//    the `Box` struct: byte-identical object (8.54% either way).
//  * `p++` at the end of the outer walk instead of `pn = p+1; ... p = pn;`:
//    7.93% (loses the `addi r23,r31,4` hoist shape).
//  * Recomputing the array byte offset from `n*4` once per outer iteration and
//    threading it through the accept block (retail's `mr r29,r26` shape):
//    7.69% and frame grew to 0x188.
//  * Hoisting `&sp18`/`&sp58` into explicit `f32 *` locals, and giving the vcall
//    a named fn-pointer local instead of inlining the call: no change.
//  * Inlining the vcall `cur->vt->fn(...)` is REQUIRED for the `lha`+`lwz`+
//    `add`+`mtlr`+`blrl` shape (with a named pointer GCC emitted the same ops,
//    but `Box*`-returning typedef is what keeps r3 live).
// NOT TRIED: `volatile` on `t` (for the `addi r9,r1,8` remat), any
// `register __asm__("rN")` pin, -fno-schedule*/-fno-gcse, and the ~20 flag /
// statement-order permutations (banned by the brief).
#include "types.h"
#include "structs.h"
#include "mem.h"

typedef float psf __attribute__((mode(PS)));

typedef union {
    psf ps;
    struct {
        f32 hi, lo;
    } flt;
} Ps2;

typedef union {
    Ps2 p[2];
    f32 f[4];
} Vec4;

/* 32-byte AABB: four __ps_t slots = {lox loy loz low, hix hiy hiz hiw} */
typedef struct {
    Ps2 e[4];
} Box;

extern char lbl_80301434[];
extern char lbl_80301468[];
extern char lbl_80366478[];
extern char lbl_803669A8[];
extern char lbl_80366BA8[];
extern char lbl_80294B40[];
extern f32 lbl_80294BE0;
extern f32 lbl_80294BE4;
extern f32 lbl_80294BE8;

typedef struct Unk_8006E2FC_Boxx Unk_8006E2FC_Boxx;
typedef Box *(*Unk_8006E2FC_Getaabb)(void *self);
struct Unk_8006E2FC_Boxx {
    Box box;
};

typedef struct Unk_8006E2FC_Vt Unk_8006E2FC_Vt;
struct Unk_8006E2FC_Vt {
    s32 pad[44];
    s16 ofs;
    s16 pad2;
    Unk_8006E2FC_Getaabb fn;
};

typedef struct Unk_8006E2FC_Obj Unk_8006E2FC_Obj;
struct Unk_8006E2FC_Obj {
    s32 unk0x0;
    s32 unk0x4;
    s32 unk0x8;
    Unk_8006E2FC_Vt *vt;
    s32 pad[2684];
    s32 unk0x2A00;
    s32 unk0x2A04;
};

typedef struct Unk_8006E2FC_Ent Unk_8006E2FC_Ent;
struct Unk_8006E2FC_Ent {
    Vec4 pos;
    s32 id;
    s32 stamp;
};

typedef struct Unk_8006E2FC_Params Unk_8006E2FC_Params;
struct Unk_8006E2FC_Params {
    Vec4 a;
    Vec4 b;
    f32 f20;
    f32 f24;
    f32 f28;
    f32 f2C;
    f32 f30;
    s32 s34;
    s32 s38;
    s32 s3C;
    s32 s40;
    s32 s44;
};

s32 Script_GetInteger(s32, s32);
s32 fn_800145AC(void);
void fn_8006F19C(s32);
s32 fn_8006F1B0(s32, s32);
void fn_8006F26C(s32, s32 *);
s32 fn_8006F828(s32, s32 *, s32);
s32 fn_8005CF80(s32, s32);
u32 fn_8000A778(s32);
void fn_800063B8(__ps_t *, __ps_t *, __ps_t *);
void fn_8000723C(__ps_t *, __ps_t *);
void fn_8000728C(f32 *, f32 *);
s32 fn_800554D8(s32);
s32 fn_801072A4(s32, s32);
s32 fn_800546A0(s32);
s32 fn_80083564(s32, s32, void *);
f32 fn_800144C8(void);
void fn_8006E000(s32, s32);
void fn_8006DF8C(s32);
s32 fn_8005C5B4(s32);
void fn_8006BD1C(void *);

s32 fn_8006E2FC(Vec4 *arg0, Vec4 *arg1, s32 arg2, s32 arg3, s32 arg4,
                s32 arg5, s32 arg6, f32 farg0, f32 farg1, f32 farg2,
                f32 farg3, f32 farg4) {
    Unk_8006E2FC_Ent *entry;
    Unk_8006E2FC_Ent *dead;
    Vec4 t;
    Box sp18;
    Box sp38;
    Box sp58;
    Unk_8006E2FC_Params sp78;
    s32 spC0;
    s32 spC4;
    Ps2 spC8;
    s32 *p;
    s32 *pn;
    s32 *b;
    s32 n;
    s32 i;
    Unk_8006E2FC_Obj *cur;
    Unk_8006E2FC_Obj *obj;
    Box *box;
    Ps2 s;
    Ps2 dx;
    Ps2 dz;
    f32 k1;
    s32 now;

    *(s32 *)lbl_80301468 = Script_GetInteger(0x26FCB7BE, 1);
    entry = NULL;
    if (arg4 != 0) {
        now = fn_800145AC();
        fn_8006F19C(*(s32 *)lbl_80301434);
        entry = (Unk_8006E2FC_Ent *)fn_8006F1B0(*(s32 *)lbl_80301434, 0);
        k1 = lbl_80294BE0;
        while (entry != NULL) {
            dead = NULL;
            if ((u32)now < (u32)entry->stamp ||
                (u32)entry->stamp - (u32)now > 0x1F4) {
                dead = entry;
            } else if (entry->id == arg4) {
                dx.ps = __builtin_ps_sub(arg0->p[0].ps, entry->pos.p[0].ps);
                dz.ps = __builtin_ps_sub(arg0->p[1].ps, entry->pos.p[1].ps);
                t.p[0].ps = dx.ps;
                t.p[1].ps = dz.ps;
                s.ps = t.p[1].ps;
                s.ps = __builtin_ps_mul(s.ps, s.ps);
                s.ps = __builtin_ps_merge00(s.ps, *(psf *)lbl_80294B40);
                dx.ps = __builtin_ps_madd(dx.ps, dx.ps, s.ps);
                s.ps = __builtin_ps_sum0(dx.ps, dx.ps, dx.ps);
                spC8.ps = s.ps;
                if (spC8.flt.hi < k1) {
                    break;
                }
            }
            p = (s32 *)fn_8006F1B0(*(s32 *)lbl_80301434, 0);
            if (dead != NULL) {
                spC0 = (s32)dead;
                fn_8006F26C(*(s32 *)lbl_80301434, &spC0);
                Mem_Free(dead);
            }
            entry = (Unk_8006E2FC_Ent *)p;
        }
        if (entry == NULL) {
            entry = (Unk_8006E2FC_Ent *)Mem_Alloc2(0x18);
            entry->id = arg4;
            entry->pos.p[0].ps = arg0->p[0].ps;
            entry->pos.p[1].ps = arg0->p[1].ps;
            entry->stamp = now;
            spC4 = (s32)entry;
            fn_8006F828(*(s32 *)lbl_80301434, &spC4, (s32)entry);
            return 1;
        }
    }
    if (arg6 == 0) {
        arg6 = fn_8005CF80(*(s32 *)lbl_80366478, fn_8000A778(arg2));
    }
    fn_800063B8(&sp18.e[0].ps, &arg0->p[0].ps, &arg1->p[0].ps);
    fn_8000723C(&sp38.e[0].ps, &sp18.e[0].ps);
    fn_8000728C((f32 *)&sp38.e[0].ps, (f32 *)&sp18.e[2].ps);
    sp58.e[0].ps = sp38.e[0].ps;
    sp58.e[1].ps = sp38.e[1].ps;
    sp58.e[2].ps = sp38.e[2].ps;
    sp58.e[3].ps = sp38.e[3].ps;
    t.f[0] = sp58.e[0].flt.hi - farg0;
    t.f[1] = sp58.e[0].flt.lo - farg0;
    t.f[2] = sp58.e[1].flt.hi - farg0;
    t.f[3] = lbl_80294BE4;
    sp58.e[0].ps = t.p[0].ps;
    sp58.e[1].ps = t.p[1].ps;
    t.f[0] = sp58.e[2].flt.hi + farg0;
    t.f[1] = sp58.e[2].flt.lo + farg0;
    t.f[2] = sp58.e[3].flt.hi + farg0;
    t.f[3] = lbl_80294BE4;
    sp58.e[2].ps = t.p[0].ps;
    sp58.e[3].ps = t.p[1].ps;
    obj = (Unk_8006E2FC_Obj *)fn_800554D8((s32)&sp18.e[0].ps);
    if (obj == NULL) {
        return 0;
    }
    n = 0;
    p = (s32 *)obj;
    while (*p != 0) {
        pn = p + 1;
        b = (s32 *)fn_801072A4((s32)&sp18.e[0].ps, (s32)&sp58.e[0].ps);
        cur = (Unk_8006E2FC_Obj *)(b != 0 ? *(s32 *)b : 0);
        while (cur != NULL) {
            box = cur->vt->fn((void *)((char *)cur + cur->vt->ofs));
            if (!(box->e[0].flt.hi > sp58.e[2].flt.hi ||
                  sp58.e[0].flt.hi > box->e[2].flt.hi ||
                  box->e[1].flt.hi > sp58.e[3].flt.hi ||
                  sp58.e[1].flt.hi > box->e[3].flt.hi ||
                  box->e[0].flt.lo > sp58.e[2].flt.lo ||
                  sp58.e[0].flt.lo > box->e[2].flt.lo)) {
                i = n * 4;
                *(s32 *)(lbl_80366BA8 + i) = (s32)cur;
                *(s32 *)(lbl_803669A8 + i) = fn_800546A0(cur->unk0x0);
                n = n + 1;
            }
            b = b + 1;
            cur = (Unk_8006E2FC_Obj *)(b != 0 ? *(s32 *)b : 0);
        }
        p = pn;
    }
    if (n <= 0) {
        return 0;
    }
    i = n * 4;
    *(s32 *)(lbl_80366BA8 + i) = 0;
    now = (arg4 == 0);
    *(s32 *)(lbl_803669A8 + i) = 0;
    if (now || arg0->f[0] != entry->pos.f[0] ||
        arg0->f[2] != entry->pos.f[2]) {
        now = 1;
        fn_8006BD1C(&sp78);
        sp78.a.p[0].ps = arg0->p[0].ps;
        sp78.a.p[1].ps = arg0->p[1].ps;
        sp78.b.p[0].ps = arg1->p[0].ps;
        sp78.b.p[1].ps = arg1->p[1].ps;
        sp78.f20 = farg0;
        sp78.f24 = farg1;
        sp78.f28 = farg2;
        sp78.f2C = farg3;
        sp78.f30 = farg4;
        sp78.s34 = arg6;
        sp78.s38 = arg3;
        sp78.s3C = (s32)entry;
        sp78.s40 = arg5;
        obj = (Unk_8006E2FC_Obj *)
            fn_80083564(*(s32 *)lbl_803669A8, *(s32 *)lbl_80366BA8, &sp78);
        if (obj == NULL) {
            now = 0;
        } else if (now) {
            fn_8006E000((s32)obj, (s32)(fn_800144C8() * lbl_80294BE8));
            fn_8006DF8C((s32)obj);
            obj->unk0x2A04 = fn_8005C5B4(arg6);
        }
    } else {
        now = 0;
    }
    if (entry != NULL) {
        entry->pos.p[0].ps = arg0->p[0].ps;
        entry->pos.p[1].ps = arg0->p[1].ps;
        entry->stamp = fn_800145AC();
    }
    return now;
}