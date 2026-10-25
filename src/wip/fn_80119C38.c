// PARKED 2026-09-30: 8.5% -> 71.2% — structure exact (528B, perfect instruction multiset, 14/14 call targets, 7/11 branch targets); residual is a 4-register callee-saved colour rotation among r22/r23/r29/r30.
// FLAG: -fno-rerun-cse-after-loop
// family=m2c range=0x80119C38-0x80119E48 size=528B
//
// MEASURED: NEAR 71.2% (376/528 bytes), object .text = 0x210 = 528B = symbols.txt size:0x210
//           = range marker.  0 emitted inline instructions (no __asm__, no .long).
//           Object carries .text + .rela.text only (no private .rodata -> masked-EXACT
//           would be promote-clean; doc-14 pool caveat does not apply).
//
// WHAT WAS FIXED (all semantic, 8.5% -> 71.2%):
//  1. Missing `fr.f54 = lbl_8029D4F0;` store entirely (want 0x80119d3c `stfs f0,0x54(r1)`)
//     -- m2c had dropped it.  +1 lis +1 lfs +1 stfs.
//  2. fn_801195DC is 1-ARG, not 4 (want 0x80119d40 sets only r3).  -3 mr.
//  3. The `== 0` / `!= 0` polarity of the fn_800CD0E0 result (AGENTS 6a-4 / 138):
//     want emits `cmpwi r3,0; beq <lz-block>` with the r22=&sp8 arm OUT OF LINE behind
//     a `b`.  Writing the natural `if (call == 0) {A} else {B}` made GCC invert it to
//     `bne` + fall-through, shifting the whole tail by 2 words.  Swapping to
//     `if (call != 0) {r22=&sp8} else {A}` reproduced want's `beq` + `b` merge exactly.
//     THIS was the single biggest win (37.9% -> 49.2% masked / 71.2% official).
//  4. The float select layout: want is `fcmpu; cror so,eq,gt; bns <STORE>` with the
//     STORE as the branch TARGET and the else body INLINE.  Every if/else spelling
//     (including the ternary and `!(a>=b)`) put the store in the fall-through and the
//     else out of line.  The form that reproduces it is the early-return shape
//     `if (a >= b) { <else body>; return 0; }  <store>;`  (AGENTS 4p-10 / 4m-10
//     inverted-early-return family, float instance).  +11 words.
//  5. Restored the missing float test + optional fn_800CD3A0 + `arg3+0x7D0` store and
//     the `return 0` tail, plus the whole trailing call chain and return accumulator.
//  6. Frame is byte-exact via the frame-template struct: stwu -0x90 / stfd f31,0x88 /
//     stmw r22,0x60 / stw r0,0x94  (AGENTS 6q-86 / 6dy / 6de: every interior gap is
//     an explicit `char pad[]`; padding arrays are in ELEMENTS).
//  7. lbl_802FFE58 must be the BARE symbol (`extern s32 lbl_802FFE58;`, AGENTS 285);
//     the `*(s32 *)lbl` cast form emits an extra `lwz` pair.
//  8. The 16-byte copy is a real paired-single pair (psq_l/psq_st x2) under
//     `-mps-float` -- plain C 16-byte copies do NOT auto-pair (AGENTS 6am-157).
//
// CALLEE SIGNATURES (all audited against want's `bl`/displacement, not guessed):
//   void *fn_8005DEB4(void *, f32 *);            2 args  (r3=&sp8, r4=&sp30)
//   s32   fn_800CD0E0(void *, void *, void *);   3 args
//   void  fn_800CD3A0(void *, void *, u32);      3 args
//   void  fn_800CD008(void *, void *, void *);   3 args
//   void  fn_800CD074(void *, void *, void *);   3 args
//   void *fn_801195DC(void *);                   1 arg   (r3 = &sp18)
//   void  fn_8011976C(void *);                   1 arg
//   s32   fn_8011970C(Unk_DB0E2BAB *);           1 arg
//   void  fn_80119640(void *, s32);              2 args
//   void  fn_8011B938(void *,void *,void *,void *,void *);   5 args
//   s32   fn_8011ADD4(CStruct *,Unk_DB0E2BAB *,s32,s32,s32,s32,f32);  6 int + f32
//   s32   fn_8011AACC(Unk_C8FEE62D *,s32,Unk_DB0E2BAB *,f32);        3 int + f32
//   s32   Script_GetInteger(s32, s32);
//   float fn_800144C8(void);                     0 args
//
// AUDIT (must be re-run before any promote attempt):
//   call targets      14/14 exact, in want's order (incl. Script_GetInteger = 0x801257b8)
//   local `b` targets  3/3 exact (0x80119C84, 0x80119D28, 0x80119E30)
//   REL14             7/11 exact; 4 are ONE WORD EARLY (target -4):
//                       +0x124 got 0x80119DD4 / want 0x80119DD8
//                       +0x148 got 0x80119DB4 / want 0x80119DB8
//                       +0x1a8 got 0x80119E04 / want 0x80119E08
//                       +0x1c0 got 0x80119E04 / want 0x80119E08
//                     -> a one-instruction block-boundary difference in the tail.
//   ADDR16 HA/LO sets  5 symbols, perfectly paired:
//                       lbl_8029D4E8 / lbl_8029D4EC / lbl_8029D4F0 / lbl_80302C3C
//                       / lbl_802FFE58 -- all hand-decoded from want's lis+disp pairs
//                       (0x8029D4E8, 0x80302C3C, 0x8029D4EC, 0x8029D4F0, 0x802FFE58)
//                       and all present in config/G2TE52/symbols.txt, so the
//                       masked-score wrong-label hazard (AGENTS 277) cannot apply.
//
// RESIDUAL / DO-NOT-RE-GRIND:
//   The whole remaining gap is ONE callee-saved colour rotation.  Instruction
//   kinds, counts, order, block structure, frame, FPR frame, 16-byte PS copy and
//   every call target are all byte-correct; only these four registers differ:
//        want  r22=r22ptr  r23=sp18  r29=sp40  r30=arg3->sp18->f54->ret
//        got   r23=r22ptr  r29=sp18  r30=sp40  r22=sp18-home-copy
//   (r24=arg0, r25=arg2, r26=r26base, r27=temp_r3, r28=arg1, r31=sp30 already match.)
//   Measured and INERT or NEGATIVE: hard `register __asm__("rN")` pins on r22
//   (->r22 49.2%, ->r23 47.0%), a named local for sp18 (drops to 28-31% AND loses a
//   callee-saved register, so stmw r23), named locals for only the early or only
//   the late sp18 uses (identical 50.0%), a second name for r22 (18.3%),
//   staging the fn_8011B938 args (identical), staging the lbl_802FFE58 read
//   (identical), moving the f54 store after the two calls (43.2%), a
//   `__asm__ volatile("")` block fence in the float arm, `-fno-schedule-insns{,2}`,
//   `-fno-sched-spec`, `-fno-sched-interblock`, `-fno-gcse`, `-fno-thread-jumps`,
//   `-fno-expensive-optimizations`, `-Os`, `-O3`, `-fconserve-space`,
//   `-fno-caller-saves` (all 21-30% and 524B -- the only load-bearing flag is
//   `-fno-rerun-cse-after-loop`, which is what makes the object 528 instead of 524).
//   Ladder: 8.5% (m2c) -> 28.8% (structure restored) -> 32.6% (f54 store + 1-arg
//   801195DC) -> 37.9% (cror present) -> 49.2% (call-result polarity) -> 71.2%
//   (float-select early-return shape).  Parked on the allocation, not on semantics.
// Measured: DIFF 8.5%. m2c generated body; significant structural and regalloc divergence.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern const f32 lbl_8029D4E8;
extern const f32 lbl_8029D4EC;
extern const f32 lbl_8029D4F0;
extern const f32 lbl_80302C3C;
extern bool      lbl_802FFE58;

/* file-local layouts (M6.89d) ------------------------------------------- */
/* arg2->unk0x8 : u16 at +0x4, s32 at +0x1C */
typedef struct { char p0[0x4]; u16 h4; char p6[0x16]; s32 unk1c; } SUB_t;
/* arg2 : s32 at +0, ptr at +8 ; +0xC is the r26 base */
typedef struct { s32 unk0x0; char pad4[0x4]; SUB_t *unk0x8; } A2_t;
/* r26 = arg2 + 0xC : f32 at +0x4, s32 at +0x28, s32 at +0x2C */
typedef struct {
    char     p0[0x4];
    f32      f4;
    char     p8[0x20];
    s32      unk0x28;
    s32      unk0x2c;
} A2SUB_t;
/* arg1 : two 8-byte PS pairs at +0xA0 */
typedef struct { char pad[0xA0]; __ps_t p0; __ps_t p1; } A1_t;

void *fn_8005DEB4(void *, f32 *);
s32   fn_800CD0E0(void *, void *, void *);
void  fn_800CD3A0(void *, void *, u32);
void  fn_800CD008(void *, void *, void *);
void  fn_800CD074(void *, void *, void *);
void *fn_801195DC(void *);
void  fn_8011976C(void *);
s32   fn_8011970C(Unk_DB0E2BAB *);
void  fn_80119640(void *, s32);
void  fn_8011B938(void *, void *, void *, void *, void *);
s32   fn_8011ADD4(CStruct *, Unk_DB0E2BAB *, s32, s32, s32, s32, f32);
s32   fn_8011AACC(Unk_C8FEE62D *, s32, Unk_DB0E2BAB *, f32);
s32   Script_GetInteger(s32, s32);
float fn_800144C8(void);

s32 fn_80119C38(void *arg0, A1_t *arg1, A2_t *arg2, u32 arg3) {
    struct {
        __ps_t s8_0;      /* +0x08 */
        __ps_t s8_1;      /* +0x10 */
        char    s18[0x18];/* +0x18 */
        char    s30[0x10];/* +0x30 */
        char    s40[0x10];/* +0x40 */
        f32     f50;      /* +0x50 */
        f32     f54;      /* +0x54 */
    } fr;
    A2SUB_t *r26;
    f32      var_f31;
    void    *temp_r27;
    void    *r22;
    s32      temp_r3;
    s32      temp_r30;
    s32      var_r3;

    r26 = (A2SUB_t *)((char *)arg2 + 0xC);
    var_f31 = (r26->f4 != lbl_8029D4E8) ? r26->f4 : lbl_80302C3C;
    fr.s8_0 = arg1->p0;
    fr.s8_1 = arg1->p1;
    temp_r3 = (s32)fn_8005DEB4(&fr.s8_0, &fr.f50);
    var_r3 = 1;
    if (temp_r3 != 0) {
        r22 = 0;
        if (fn_800CD0E0(arg1, (void *)temp_r3, &fr.s8_0) != 0) {
            r22 = &fr.s8_0;
        } else {
            if ((u32)r26->unk0x2c <= arg3) {
                if (fr.f50 >= var_f31 + lbl_8029D4EC) {
                if (arg2->unk0x8->unk1c != 0) {
                    fn_800CD3A0(arg1, r26, arg3);
                }
                return 0;
                }
                r26->unk0x2c = arg3 + 0x7D0;
            }
        }
        fr.f54 = lbl_8029D4F0;
        fn_801195DC(&fr.s18);
        fn_8011976C(&fr.s18);
        if ((r22 != 0) || (fr.f50 < var_f31)) {
            fn_800CD008(&fr.s30, arg1, (void *)temp_r3);
            if (arg2->unk0x8->h4 & 1) {
                fn_800CD074(&fr.s40, arg1, (void *)temp_r3);
                fn_800144C8();
                fn_8011B938(arg0, &fr.f54, &fr.s30, &fr.s40, (void *)temp_r3);
            }
            fn_8011ADD4((CStruct *)arg0, (Unk_DB0E2BAB *)&fr.s18, (s32)&fr.s30,
                       r26->unk0x28, temp_r3, (s32)r22, var_f31);
        }
        if ((lbl_802FFE58 == 0) && (Script_GetInteger(0x6D2E270E, 0) != 0)) {
            fn_8011970C((Unk_DB0E2BAB *)&fr.s18);
        }
        temp_r30 = fn_8011AACC((Unk_C8FEE62D *)arg0, arg2->unk0x0,
                               (Unk_DB0E2BAB *)&fr.s18, fr.f54);
        fn_80119640(&fr.s18, 2);
        var_r3 = temp_r30;
    }
    return var_r3;
}
