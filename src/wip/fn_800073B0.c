/* fn_800073B0 — Box(a) vs Box(b) slab/segment test: returns 1 and leaves the
 * intersection point + surface normal in a 16-byte local slot.
 *
 * family=m2c range=0x800073B0-0x800079D8 size=1576B
 * extra_cflags: -mps-float
 *
 * ============================================================================
 * STATUS: PARKED (was a `return 0` stub).  Full semantic reconstruction done;
 * the body compiles clean with ngccc 3.9.3 -mps-float and is structurally
 * correct, but it does NOT match byte-for-byte.  Current sweep verdict and the
 * precise remaining blocker are at the bottom of this header.
 * ============================================================================
 *
 * ----------------------------------------------------------------------------
 * WHAT THE FUNCTION IS (fully recovered from the DOL)
 * ----------------------------------------------------------------------------
 * Args (from the sole call site, fn_800FDE38+0xE2 = 0x800FDF18):
 *     r3 = box A,  r4 = box B,  r5 = &out_point(Vec4),  r6 = &out_normal(Vec4)
 * The caller loads r5/r6 (r1+0x48 / r1+0x58) and reads a 4-float point out of
 * the first buffer afterwards, so the real signature is 4-arg.  RETAIL CODE
 * NEVER TOUCHES r5/r6: it writes both Vec4s into its OWN 16-byte stack slot at
 * sp+0x08 (0x48..0x54 with the 0x40 frame) — twice, in place.  The draft keeps
 * the 2-arg form that reproduces those bytes; unused params emit no code, so
 * widening the def to 4 params is byte-neutral if a future round needs it.
 *
 * Both boxes are {Vec4 lo; Vec4 hi;} (24 bytes used, offsets 0x00/0x04/0x08 =
 * lo.x/y/z and 0x10/0x14/0x18 = hi.x/y/z; 0x0C and 0x1C are never touched).
 * Same layout as the promoted sibling src/fn_800079D8.c ("Bounds6").
 *
 * Control flow:
 *   1. inlo = (B.lo inside A)          six compares, 0x800073C8..0x80007438
 *   2. inhi = (B.hi inside A)          six compares, 0x8000733C..0x800074B8
 *   3. if (inlo && inhi) return 0;     0x800074BC  (i.e. "A swallows B" => miss)
 *   4. six slab reject tests (y-hi, y-lo, x-hi, x-lo, z-hi, z-lo) -> return 0
 *      0x800074CC..0x80007574
 *   5. dx/dy/dz = B's extent, each `== 0` replaced by lbl_8028FE2C (1e-6f)
 *      0x80007578..0x800075C0
 *   6. six face tests.  For each face the ray from B.lo along B's own diagonal
 *      is clipped against A's six planes; the parameter t at the crossed plane
 *      is scaled by the two other B extents and the hit point must land inside
 *      A.  Each hit writes a 4-float hit point (w = 1.0f) and then a 4-float
 *      unit face normal (w = 0.0f) into the same sp+0x08 slot and returns 1.
 *
 * Constant pool (sec 8 .rodata2, verified by reading the DOL):
 *     lbl_8028FE28 = 0.0f        lbl_8028FE2C = 1.0e-06f
 *     lbl_8028FE30 = 1.0f        lbl_8028FE34 = -1.0f
 * The normal written per face is +1.0f / -1.0f on the struck axis and
 * lbl_8028FE28 (0.0f) on the other two, w = 0.
 *
 * ----------------------------------------------------------------------------
 * THE `0xExxxxxxxx` / `0xF0xxxxxx` WORDS (identified this round)
 * ----------------------------------------------------------------------------
 * The 32 opcode-4 words in the six hit blocks are NOT PS arithmetic.  binutils
 * prints 0xE0 09 00 08 as `lq r0,0(r9)` and 0xF0 0B 00 08 as `xsmaddasp`; the
 * promoted sibling src/fn_800079D8.c emits the same pair for its
 * `*(__ps_t *)dst = *(__ps_t *)src` copies.  They are the -mps-float
 * load/store lowering ARTIFACTS:
 *     one 16-byte (Vec4) write through a __ps_t lvalue
 *         = 4 real `stfs` + 2 x `lq` + 2 x `xsmaddasp`/`xsaddsp` (dead)
 * Probed directly (tools/venv wibo + ngccc 3.9.3 -mps-float, /tmp probes):
 * a `volatile Vec4` written by scalars emits 4 stfs and NO artifacts, while
 * `*(volatile __ps_t *)&v` emits the lq/xs pair.  Each hit block therefore does
 * 8 stfs + 5 in-block artifacts (+3 merged into the shared return tail).
 * The draft reproduces this with four dead `*(volatile __ps_t *)&res.x =
 * *(volatile __ps_t *)&res.x;` self-copies per hit block.  Those copies are
 * load-bearing for codegen (removing them drops ~8 words per block) but they are
 * DEAD in the original too, so nothing is lost semantically.
 *
 * ----------------------------------------------------------------------------
 * FPR MAP OF WANT (useful for any retry)
 * ----------------------------------------------------------------------------
 *   callee-saved: f27=b->hi.y  f28=b->hi.x  f29=a->lo.x  f30=a->hi.y
 *                 f31=b->hi.z      (prologue saves exactly f27..f31, frame 0x40)
 *   scratch:      f8=0.0f  f9=dz  f10=dx  f11=dy  f1=a->lo.y  f2=a->hi.x
 *                 f3=b->lo.y  f4=a->lo.z  f5=b->lo.x  f6=a->hi.z  f7=b->lo.z
 *                 f0/f12/f13 = the rolling compare temp
 *
 * ----------------------------------------------------------------------------
 * REMAINING BLOCKER (why this is still parked)
 * ----------------------------------------------------------------------------
 * Everything is right except the ALLOCATION of the box fields, and that one
 * difference shifts the whole 394-word body.  Specifically, WANT emits **12
 * extra `fmr` home-copies** that no source form reproduced so far:
 *   phase 2 : fmr f28,f13 / fmr f29,f0 / fmr f31,f0
 *   slab    : fmr f3,f13 / fmr f30,f0 / fmr f1,f0 / fmr f5,f13 / fmr f2,f0
 *             fmr f7,f13 / fmr f6,f0 / fmr f4,f0
 *   extents : fmr f27,f0
 * i.e. WANT loads every long-lived field into a scratch temp (f13/f0) and then
 * COPIES it into the home register, while ngccc folds each load straight into
 * the home and compares the home.  The draft's conditions deliberately re-read
 * `b->lo.y` / `a->hi.y` etc. (rather than reusing the named local) to try to
 * force the extra web — that gets phase 1 byte-identical and the slab section
 * structurally identical, but cc1 still coalesces the load into the home.
 * This is the documented big-function allocator wall (AGENTS §6ay-273 "fewer
 * temporaries than the original", §6an-216 full-web pinning, §6y-127 allocator
 * homing cascade) — NOT a missing recipe, and NOT a flag/struct/type issue.
 * The 5 hard-register pins below are the minimum needed to get the frame to
 * 0x40 and the stfd span to f27..f31; wider pin sets (16 pins) measured no
 * better (same 8% / 15% shape), so the extra ones were dropped.
 *
 * Secondary residual (documented, not ground): the hit-block store run emits
 * [+8, +0xC, +0x10, +0x14] where WANT emits [+8, +0x10, +0x14, +0xC].  That is
 * the store-rotation family (AGENTS recipes 24/64/159/206/253) and is normally
 * closed with a permutation search; deliberately NOT ground here.
 *
 * Ruled out: `-mcpu`/O-level/ProDG-version sweeps (frame/allocator invariant),
 * negated-compare forms (they emit `cror`+`bso`, WANT uses plain `ble`/`bge` —
 * all guards must be written POSITIVE, see below), 0x0C/0x1C box slots
 * (never read), `-mps-float` off (WANT has 32 opcode-4 artifact words), frame
 * dummy (0x38 vs 0x40 is the missing 5th stfd, not the FPR +8 quirk).
 *
 * Retry hints:
 *   - The blocker is only worth another round if you have a lever that makes
 *     cc1 keep a scratch copy for a variable that is also compared.  All the
 *     source-shape levers (double reads, decl order, comma staging, volatile
 *     reloads) were measured and stay at 8%.
 *   - Keep every guard in POSITIVE form.  `if (!(x <= y))` produces
 *     `cror cr0un,cr0eq,cr0lt` + `bso` and is a 2-word-per-site regression.
 *   - `zero` is deliberately loaded late (just before the extent block) so the
 *     `lis` for the constant page does not hoist to the entry block.
 *   - Blocks +Y/-Y compare `dy > 0.0f` / `dy <= 0.0f` against a FRESH
 *     `lbl_8028FE28` load, not against `zero`; blocks +X/-X use `zero`.  That
 *     asymmetry is in WANT (0x8000771C / 0x800077C0 / 0x80007870 / 0x80007914).
 *   - Verify with:
 *       tools/venv/bin/python tools/test_wip_drafts.py --addr 0x800073B0 \
 *           --extra-cflags "-mps-float"
 *       tools/venv/bin/python tools/want_got.py 0x800073B0 \
 *           --file src/wip/fn_800073B0.c
 *
 * Suggested rename: AABB_Intersect (segment-vs-box, reports contact normal).
 */
#include "types.h"

typedef struct { f32 x, y, z, w; } Vec4;
typedef struct { Vec4 lo; Vec4 hi; } Bounds;

extern f32 lbl_8028FE28;
extern f32 lbl_8028FE2C;
extern f32 lbl_8028FE30;
extern f32 lbl_8028FE34;

s32 fn_800073B0(Bounds *a, Bounds *b) {
    volatile Vec4 res;
    /* Allocation pins only — these 5 values are the ones WANT homes in
     * f27..f31; they are what makes the frame 0x40 and the stfd span exact. */
    register f32 bx1 __asm__("fr28");
    register f32 by1 __asm__("fr27");
    register f32 bz1 __asm__("fr31");
    register f32 ax0 __asm__("fr29");
    register f32 ay1 __asm__("fr30");
    register f32 bx0;
    register f32 by0;
    register f32 bz0;
    register f32 ay0;
    register f32 az0;
    register f32 ax1;
    register f32 az1;
    register f32 dx;
    register f32 dy;
    register f32 dz;
    register f32 zero;
    s32 inlo, inhi;

    /* 1. is B's min corner inside A? */
    inlo = 0;
    if (b->lo.x >= a->lo.x && b->lo.y >= a->lo.y && b->lo.z >= a->lo.z &&
        b->lo.x <= a->hi.x && b->lo.y <= a->hi.y && b->lo.z <= a->hi.z) {
        inlo = 1;
    }

    /* 2. is B's max corner inside A?  (=> A fully contains B => no contact) */
    inhi = 0;
    bx1 = b->hi.x;
    ax0 = a->lo.x;
    bz1 = b->hi.z;
    {
        f32 tmp_hix = b->hi.x, tmp_loy = a->lo.y, tmp_hiy = b->hi.y;
        f32 tmp_loz = a->lo.z, tmp_hiz = b->hi.z, tmp_hix2 = b->hi.x;
        f32 tmp_hiy2 = b->hi.y, tmp_hiz2 = b->hi.z;
        if (tmp_hix >= ax0 && tmp_hiy >= tmp_loy && tmp_hiz >= tmp_loz &&
            tmp_hix2 <= a->hi.x && tmp_hiy2 <= a->hi.y && tmp_hiz2 <= a->hi.z) {
            inhi = 1;
        }
    }

    if (inlo == 0 || inhi == 0) {
        /* 3. slab reject tests, y-hi / y-lo / x-hi / x-lo / z-hi / z-lo */
        ay1 = a->hi.y;
        if (b->lo.y > ay1) {
            if (b->hi.y > ay1) {
                return 0;
            }
        }
        by0 = b->lo.y;
        ay0 = a->lo.y;
        if (b->lo.y < ay0) {
            if (b->hi.y < ay0) {
                return 0;
            }
        }
        bx0 = b->lo.x;
        ax1 = a->hi.x;
        if (b->lo.x > ax1) {
            if (b->hi.x > ax1) {
                return 0;
            }
        }
        if (b->lo.x < ax0) {
            if (b->hi.x < ax0) {
                return 0;
            }
        }
        az1 = a->hi.z;
        if (b->lo.z > az1) {
            if (bz1 > az1) {
                return 0;
            }
        }
        bz0 = b->lo.z;
        az0 = a->lo.z;
        if (b->lo.z < az0) {
            if (bz1 < az0) {
                return 0;
            }
        }

        /* 4. B's extents, epsilon-guarded against a zero divide */
        zero = lbl_8028FE28;
        by1 = b->hi.y;
        dx = bx1 - bx0;
        dy = by1 - by0;
        dz = bz1 - bz0;
        if (dx == zero) {
            dx = lbl_8028FE2C;
        }
        if (dy == zero) {
            dy = lbl_8028FE2C;
        }
        if (dz == zero) {
            dz = lbl_8028FE2C;
        }

        /* 5. A's +x face crossed from inside B */
        if (bx0 < ax1 && bx1 > ax1 && dx > zero) {
            f32 py = (ax1 - bx0) * dy / dx + by0;
            f32 pz = (ax1 - bx0) * dz / dx + bz0;
            if (py < ay1 && py > ay0 && pz < az1 && pz > az0) {
                res.x = ax1; res.y = py; res.z = pz; res.w = lbl_8028FE30;
                *(volatile __ps_t *)&res.x = *(volatile __ps_t *)&res.x;
                *(volatile __ps_t *)&res.x = *(volatile __ps_t *)&res.x;
                res.x = lbl_8028FE30; res.y = zero; res.z = zero; res.w = zero;
                *(volatile __ps_t *)&res.x = *(volatile __ps_t *)&res.x;
                *(volatile __ps_t *)&res.x = *(volatile __ps_t *)&res.x;
                return 1;
            }
        }
        /* 6. A's -x face */
        if (bx0 < ax0 && bx1 > ax0 && dx > zero) {
            f32 py = (ax0 - bx0) * dy / dx + by0;
            f32 pz = (ax0 - bx0) * dz / dx + bz0;
            if (py < ay1 && py > ay0 && pz < az1 && pz > az0) {
                res.x = ax0; res.y = py; res.z = pz; res.w = lbl_8028FE30;
                *(volatile __ps_t *)&res.x = *(volatile __ps_t *)&res.x;
                *(volatile __ps_t *)&res.x = *(volatile __ps_t *)&res.x;
                res.x = lbl_8028FE34; res.y = zero; res.z = zero; res.w = zero;
                *(volatile __ps_t *)&res.x = *(volatile __ps_t *)&res.x;
                *(volatile __ps_t *)&res.x = *(volatile __ps_t *)&res.x;
                return 1;
            }
        }
        /* 7. A's +y face (compares against a fresh 0.0f load) */
        if (by0 > ay1 && by1 < ay1 && dy > lbl_8028FE28) {
            f32 px = (ay1 - by0) * dx / dy + bx0;
            f32 pz = (ay1 - by0) * dz / dy + bz0;
            if (px < ax1 && px > ax0 && pz < az1 && pz > az0) {
                res.x = px; res.y = ay1; res.z = pz; res.w = lbl_8028FE30;
                *(volatile __ps_t *)&res.x = *(volatile __ps_t *)&res.x;
                *(volatile __ps_t *)&res.x = *(volatile __ps_t *)&res.x;
                res.x = zero; res.y = lbl_8028FE30; res.z = zero; res.w = zero;
                *(volatile __ps_t *)&res.x = *(volatile __ps_t *)&res.x;
                *(volatile __ps_t *)&res.x = *(volatile __ps_t *)&res.x;
                return 1;
            }
        }
        /* 8. A's -y face */
        if (by0 < ay0 && by1 > ay0 && dy <= lbl_8028FE28) {
            f32 px = (ay0 - by0) * dx / dy + bx0;
            f32 pz = (ay0 - by0) * dz / dy + bz0;
            if (px < ax1 && px > ax0 && pz < az1 && pz > az0) {
                res.x = px; res.y = ay0; res.z = pz; res.w = lbl_8028FE30;
                *(volatile __ps_t *)&res.x = *(volatile __ps_t *)&res.x;
                *(volatile __ps_t *)&res.x = *(volatile __ps_t *)&res.x;
                res.x = zero; res.y = lbl_8028FE34; res.z = zero; res.w = zero;
                *(volatile __ps_t *)&res.x = *(volatile __ps_t *)&res.x;
                *(volatile __ps_t *)&res.x = *(volatile __ps_t *)&res.x;
                return 1;
            }
        }
        /* 9. A's +z face */
        if (bz0 > az1 && bz1 < az1 && dz > lbl_8028FE28) {
            f32 px = (az1 - bz0) * dx / dz + bx0;
            f32 py = (az1 - bz0) * dy / dz + by0;
            if (px < ax1 && px > ax0 && py < ay1 && py > ay0) {
                res.x = px; res.y = py; res.z = az1; res.w = lbl_8028FE30;
                *(volatile __ps_t *)&res.x = *(volatile __ps_t *)&res.x;
                *(volatile __ps_t *)&res.x = *(volatile __ps_t *)&res.x;
                res.x = zero; res.y = zero; res.z = lbl_8028FE30; res.w = zero;
                *(volatile __ps_t *)&res.x = *(volatile __ps_t *)&res.x;
                *(volatile __ps_t *)&res.x = *(volatile __ps_t *)&res.x;
                return 1;
            }
        }
        /* 10. A's -z face; its rejects branch straight to the `return 0` */
        if (bz0 < az0 && bz1 > az0 && dz <= lbl_8028FE28) {
            f32 px = (az0 - bz0) * dx / dz + bx0;
            f32 py = (az0 - bz0) * dy / dz + by0;
            if (px < ax1 && px > ax0 && py < ay1 && py > ay0) {
                res.x = px; res.y = py; res.z = az0; res.w = lbl_8028FE30;
                *(volatile __ps_t *)&res.x = *(volatile __ps_t *)&res.x;
                *(volatile __ps_t *)&res.x = *(volatile __ps_t *)&res.x;
                res.x = zero; res.y = zero; res.z = lbl_8028FE34; res.w = zero;
                *(volatile __ps_t *)&res.x = *(volatile __ps_t *)&res.x;
                *(volatile __ps_t *)&res.x = *(volatile __ps_t *)&res.x;
                return 1;
            }
        }
    }
    return 0;
}
