// WIP DRAFT (non-matching) — rewritten 2026-10-02 from scratch (was m2c junk, 9.0%)
// family=m2c range=0x80043EE8-0x80044088 size=416B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// FLAG: -fno-rerun-cse-after-loop
//
// PARKED 2026-10-02 (w75/0x80043EE8): NEAR 65.4%, 416B exact length, frame
// 0x70 / stfd f31,0x68 / lr@0x74 all correct, and the whole float + link-list
// loop body is byte-identical.  Residual = reload homes TWO addresses too many:
// want keeps `&sp8` (r27) and `&sp18` (r30) in callee-saved regs and remats
// `&sp34`/`&sp38` per call site (`addi r4,r1,0x34` / `addi r5,r1,0x38` inside
// the loop, want 0x80043F8C/0x80043F94); got hoists all three
// (`addi r25,r1,0x34` / `addi r26,r1,0x38` in the preheader + `mr r4,r25`),
// so it saves 9 GPRs (stmw r23,0x44) instead of 7 (stmw r25,0x4c) and every
// colour is off.  `plink` (the &sp8 pointer temp) IS the lever that homes
// &sp8 in r27 — it works; nothing tried removes the two address homes.
// Tried: volatile s32/f32 out-params (§6al-180 remat lever) — does NOT fire for
// struct-member addresses, confirmed here as separate locals too (§6al-221);
// f32[2] pair (CSEs to ONE home, still 8 regs); separate-locals split (9);
// `char *`-offset args from plink (GCC re-homes, `addi r26,r27,0x30`);
// loop-body-scoped pair (slot moves to 0x48, still homed); `void *` params;
// goto-threaded tail (no change); 15 flag probes (-Os/-fno-cse-*/-fno-schedule-*/
// -fno-strength-reduce/-fno-peephole/...) all worse.  Frame-template struct is
// load-bearing (recipe §6q-86): it puts the link node at r1+8, the 24-byte
// blur pair at r1+0x18 and sp30/sp34/sp38 at 0x30/0x34/0x38 exactly; plain
// locals put the scalars 8 bytes low.
// Reusable: for this body `-fno-rerun-cse-after-loop` is LOAD-BEARING (50.0%
// flagless -> 65.4% with it): without it ngccc re-runs cse after the loop and
// folds the trailing `if (sp8) RemoveRefLink` on the loop-exit edge, deleting
// that block — 8 bytes short and every later offset shifts.
#include "types.h"

extern const f32 lbl_80292504;

typedef struct {
    char pad0x0[0x58];
    s16 unk0x58;
    char pad0x5A[0x2];
    s32 (*unk0x5C)(void *);
} T43EE8VT;

typedef struct {
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;
    f32 f4;
    f32 f5;
} T43EE8S24;

typedef struct T43EE8KID {
    char pad0x0[0x70];
    struct T43EE8KID *unk0x70;
    char pad0x74[0x108];
    f32 unk0x17C;
    char pad0x180[0x28];
    s32 unk0x1A8;
} T43EE8KID;

typedef struct {
    char pad0x0[0x8];
    T43EE8VT *unk0x8;
    char pad0xC[0x58];
    T43EE8KID *unk0x64;
    char pad0x68[0x114];
    f32 unk0x17C;
    char pad0x180[0x44];
    void *unk0x1C4;
} T43EE8SELF;

typedef struct {
    T43EE8KID *unk0x0;
    void *unk0x4;
    void *unk0x8;
} T43EE8LINK;

/* r1+8 link node, r1+0x18 blur pair, r1+0x30/0x34/0x38 scratch */
typedef struct {
    T43EE8LINK sp8;
    char pad0xC[4];
    T43EE8S24 sp18;
    s32 sp30;
    f32 sp34;
    f32 sp38;
} T43EE8Frame;

T43EE8S24 *CBlurEffect_SetMorph(void *, void *, s32 *);
void fn_8003F710(void *, f32 *, f32 *);
void fn_800503C8(void *, T43EE8S24 *, s32);
void CScreenElement_SetMorph(void *, void *);
void CObject_AddRefLink(void *, T43EE8LINK *);
void CObject_RemoveRefLink(void *, T43EE8LINK *);

void fn_80043EE8(T43EE8SELF *arg0, void *arg1) {
    T43EE8Frame f;
    T43EE8LINK *plink;
    T43EE8S24 *temp_r29;
    T43EE8KID *temp_r31;
    f32 temp_f31;
    f32 temp_f13;

    if (arg0->unk0x1C4 != 0) {
        ((s32 (*)(void *))arg0->unk0x8->unk0x5C)((char *)arg0 + arg0->unk0x8->unk0x58);
        temp_r29 = CBlurEffect_SetMorph(arg0->unk0x1C4, arg1, &f.sp30);
        plink = &f.sp8;
        f.sp8.unk0x4 = 0;
        f.sp8.unk0x8 = 0;
        f.sp8.unk0x0 = arg0->unk0x64;
        if (arg0->unk0x64 != 0) {
            CObject_AddRefLink(arg0->unk0x64, plink);
        }
        if (f.sp8.unk0x0 != 0) {
            temp_f31 = lbl_80292504;
            do {
                f.sp18 = *temp_r29;
                fn_8003F710(f.sp8.unk0x0, &f.sp34, &f.sp38);
                f.sp38 = f.sp8.unk0x0->unk0x17C * temp_f31 + f.sp38;
                temp_f13 = arg0->unk0x17C * temp_f31 - f.sp38;
                f.sp18.f5 = f.sp18.f5 + (temp_r29->f3 * temp_f13 - temp_f13);
                fn_800503C8(f.sp8.unk0x0->unk0x1A8, &f.sp18, f.sp30);
                temp_r31 = f.sp8.unk0x0->unk0x70;
                if (f.sp8.unk0x0 != 0) {
                    CObject_RemoveRefLink(f.sp8.unk0x0, plink);
                    f.sp8.unk0x0 = 0;
                }
                f.sp8.unk0x0 = temp_r31;
                if (temp_r31 != 0) {
                    CObject_AddRefLink(temp_r31, plink);
                }
            } while (f.sp8.unk0x0 != 0);
        }
        if (f.sp8.unk0x0 != 0) {
            CObject_RemoveRefLink(f.sp8.unk0x0, plink);
            f.sp8.unk0x0 = 0;
        }
    }
    CScreenElement_SetMorph(arg0, arg1);
}
