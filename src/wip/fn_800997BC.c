// PARKED 2026-09-28 (ag800997BC): best 85.3% masked, SIZE-EXACT 680B (170 insns,
// same as retail).  The previous note claimed the `mr r12,r1 / lis / ori / stwux`
// frame-pointer prologue was unreachable from C -- THAT IS WRONG: any function
// with a LARGE local array makes ProDG/3.9.3 emit exactly that form.  The whole
// 604B nested-loop body was rebuilt from the disassembly and now matches
// structurally instruction-for-instruction; only register ROLES differ.
// SOLVED SO FAR (all verified byte-level):
//   * `s32 sp8[8192]` local  -> the want's frame-pointer prologue + frame 0x8018
//     (sp8[] lives at r1+8; the array size must be 8192 so the frame is exactly
//     0x8018, not 0x8028).
//   * `if (outcnt < count) { do {...} while (i < count); }` "variable-0 compare"
//     loop-1 guard (AGENTS 6c-27) -- the guard really is on the zeroed counter.
//   * loop 1 hoists the `e->f14->f4->f6 & 1` loads ABOVE the `first == -1` test.
//   * `switch (pass)` with cases 0..3 reproduces the want's
//     `cmpwi cr1/cr6/cr7` hoisted dispatch + `beq cr1/cr6/cr7` chain verbatim.
//   * `*out = *(QE_t **)((char *)(off + (s32)self->f58));`  (RE-READ of the
//     element instead of reusing `e`) is what makes want re-load the element in
//     every case body and keep a second `mr r7,r9` copy of the array base.
//   * offset-FIRST addressing `(char *)(off + (s32)ptr)` flips lwzx/stwx into the
//     rA=offset/rB=base form (AGENTS 6k-66 / 6au-200); also for the
//     `tbl + (fC<<5)` address and the final copy-back store.
//   * counter-zero stores must be written ASCENDING (0x60,0x62,0x64,0x66);
//     ngccc then emits them rotated right by one (0x66,0x60,0x62,0x64) in BOTH
//     the init block and the else branch.
//   * `register s32 o8 __asm__("r8")` for the `out` write pointer and
//     `register s32 i4 __asm__("r4")` for the inner-loop index (8.8% -> 85.3%).
//   * `b10 = qb->f6 & 1; b2 = b10;` — the intermediate `b10` looks dead and is
//     NOT: pinning the scratch copy to r10 changes the inner loop's scheduling
//     and is worth 3 words (83.5% vs 80.6% with the copy deleted).  DO NOT
//     "clean up" that pair.
//   * NO `// FLAG:` line: flagdiff on -fno-schedule-insns/-insns2/-sched-spec/
//     -sched-interblock/-gcse/-strength-reduce/-branch-count-reg, -O1 and -O3
//     all score 85.3% or worse; the default flag set is already optimal.
// RESIDUAL (25 differing words, all pure register-role / emission-order):
//   * want homes the array base in r7 (`mr r7,r9` + `stwx rX,r6,r7`); ngccc
//     coalesces the two `self->f58` webs into r10 and leaves the r7 copy dead.
//     Pinning arr->r7 (27.7%), a `"+r"` barrier on it (29.2%) and hoisting
//     `arr = self->f58` out of the loop (28.7%) all REGRESS.
//   * want puts `e->f14` in r10 and reuses it for the masked `f6&1`; ngccc uses
//     r11 for both.  Pinning the inner `b` to r10 regresses to 72.9%.
//   * loop 1: want's index is r8 (a separate live range from the pinned r4
//     inner index).  Splitting loop 1 into its own variable is score-neutral
//     (85.3%) but only trades one 5-word slide for another.
//   * `slwi r0,r5,2` / `li r6,0` (off=0) emit in the opposite order.
// CLASS: big-function allocator wall (AGENTS 6y-273 "fewer temporaries than the
// original", 6an-216 full-web pinning).  Do NOT re-grind the prologue or the
// switch -- both are solved; only the register colouring is left.
// WIP DRAFT (non-matching) — body hand-rebuilt from disassembly, not m2c output
// family=m2c range=0x800997BC-0x80099A64 size=680B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
typedef struct { char p0[6]; u8 f6; char p1[5]; u16 fC; } QB_t;
typedef struct { char p0[4]; QB_t *f4; } QP_t;
typedef struct { char p0[0x14]; QP_t *f14; } QE_t;
typedef struct {
    char p0[8];
    s32 f08;
    char p1[0x2C];
    char *f38;
    char p2[0x1C];
    s32 *f58;
    char p3[2];
    u16 f5E;
    u16 f60;
    u16 f62;
    u16 f64;
    u16 f66;
} T_t;

extern void fn_8026A07C(s32 *, s32, s32, void *);
extern char fn_80098EC0[];

void fn_800997BC(T_t *self) {
    s32 sp8[8192];
    register s32 o8 __asm__("r8");
    register s32 i4 __asm__("r4");
    s32 first;
    s32 pass;
    s32 outcnt;
    s32 *p;
    s32 *arr;
    QE_t *e;
    s32 b;
    s32 b2;
    register s32 b10 __asm__("r10");
    s32 v;
    s32 off;
    QP_t *q;
    QB_t *qb;
    s32 k;
    s32 *q2;
    s32 w;
    s32 t;

    fn_8026A07C(self->f58, (s32)self->f5E, 4, (void *)fn_80098EC0);

    if (self->f08 != 0) {
        self->f60 = 0;
        self->f62 = 0;
        self->f64 = 0;
        self->f66 = 0;
        first = -1;
        i4 = 0;
        outcnt = 0;
        if (outcnt < (s32)self->f5E) {
            p = self->f58;
            do {
                e = (QE_t *)*p;
                p += 1;
                if (e != NULL) {
                    q = e->f14;
                    qb = q->f4;
                    b = qb->f6 & 1;
                    if (first == -1) {
                        if (b != 0) {
                            first = i4;
                        }
                    }
                }
                i4 += 1;
            } while (i4 < (s32)self->f5E);
        }
        pass = 0;
        for (;;) {
            i4 = 0;
            if (i4 < (s32)self->f5E) {
                o8 = (s32)&sp8[outcnt];
                off = 0;
                do {
                    arr = self->f58;
                    e = *(QE_t **)((char *)(off + (s32)self->f58));
                    if (e != NULL) {
                        qb = e->f14->f4;
                        b10 = qb->f6 & 1;
                        b2 = b10;
                        v = (*(u16 *)((char *)((qb->fC << 5) + (s32)self->f38) + 4) >> 3) & 1;
                        if (first == -1) {
                            if (b2 != 0) {
                                first = i4;
                            }
                        }
                        switch (pass) {
                        case 0:
                            if (v == 0) {
                                *(s32 *)o8 = *(QE_t **)((char *)(off + (s32)self->f58));
                                outcnt += 1;
                                *(s32 *)((char *)(off + (s32)arr)) = 0;
                                o8 += 4;
                                self->f60 = (u16)(self->f60 + 1);
                            }
                            break;
                        case 1:
                            if (v != 0) {
                                if (b2 == 0) {
                                    if (i4 < first) {
                                        *(s32 *)o8 = *(QE_t **)((char *)(off + (s32)self->f58));
                                        outcnt += 1;
                                        *(s32 *)((char *)(off + (s32)arr)) = b2;
                                        o8 += 4;
                                        self->f62 = (u16)(self->f62 + 1);
                                    }
                                }
                            }
                            break;
                        case 2:
                            if ((v != 0) && (b2 != 0)) {
                                *(s32 *)o8 = *(QE_t **)((char *)(off + (s32)self->f58));
                                outcnt += 1;
                                *(s32 *)((char *)(off + (s32)arr)) = 0;
                                o8 += 4;
                                self->f64 = (u16)(self->f64 + 1);
                            }
                            break;
                        case 3:
                            *(s32 *)o8 = *(QE_t **)((char *)(off + (s32)self->f58));
                            outcnt += 1;
                            *(s32 *)((char *)(off + (s32)arr)) = 0;
                            o8 += 4;
                            self->f66 = (u16)(self->f66 + 1);
                            break;
                        }
                    }
                    i4 += 1;
                    off += 4;
                } while (i4 < (s32)self->f5E);
            }
            pass += 1;
            if (pass > 3) {
                break;
            }
        }
        k = 0;
        if (k < (s32)self->f5E) {
            q2 = &sp8[0];
            w = 0;
            do {
                t = *q2;
                k += 1;
                q2 += 1;
                *(s32 *)((char *)(w + (s32)self->f58)) = t;
                w += 4;
            } while (k < (s32)self->f5E);
        }
    } else {
        self->f60 = self->f5E;
        self->f62 = 0;
        self->f64 = 0;
        self->f66 = 0;
    }
}
