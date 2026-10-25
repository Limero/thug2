// WIP DRAFT (non-matching) — hand reconstruction 2026-10-04
// family=m2c range=0x80096F20-0x800971A0 size=640B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// ---------------------------------------------------------------------------
// PARKED (2026-10-04): 78.1% NEAR at the EXACT 640B size (was 3.0% DIOR).
// Score: test_wip_drafts.py --addr 0x80096F20 -> NEAR 78.1% (160/160 words,
// 125 index-aligned masked matches; best variant kept here).
//
// SEMANTICALLY COMPLETE — this is a real reconstruction, not an m2c husk:
//   * fn_80096F20 draws a debug ortho-projected box per scene-graph node child.
//     Outer `while` over fn_80098D3C(lbl_803018A8, 0); inner `for` over
//     fn_80061F2C(node->unk4) / fn_80061DE8(node->unk4, i) -> *(obj**)(+0x30).
//   * GfxObj local is 0x110 bytes at frame 0x08: Vec3 at 0x30/0x3C, the Mtx
//     that PSMTXCopy/PSMTXConcat work on at 0x48, flag word at 0xBC. The Mtx
//     MUST be a field of the same struct: &mtx (r1+0x50) and the object
//     (r1+0x08, field 0xBC) are both live, so they cannot be separate locals.
//   * frame 0x190 with `Vec`(8-aligned) locals at 0x118/0x128 and the __ps_t
//     pair temp at 0x138 reproduces every frame offset exactly; the +8 headroom
//     comes free from the pins (recipe 129b), no `volatile double` needed.
//   * constants: 64.0f (0x802974C8), 36.0f (0x802974CC), 1.0f/0.0f (D0/D4).
//   * queue_front=0x800169FC, Camera_orthographic=0x80017480, PSMTXCopy=
//     0x8025DFA0, PSMTXConcat=fn_8001D39C, obj draw=fn_80093820.
//   * `&= ~0x1000000` must be written as a 1-BIT BITFIELD clear
//     (`flags.b.b24 = 0` over a union with the plain word) — see the note at
//     the bottom; a plain `&= 0xFEFFFFFF` miscompiles in ngccc (recipe 16).
//
// REMAINING BLOCKER (35 of 160 words): ngccc 2.95/3.9.3 rematerialises the
// frame address `&sp8` as a fresh `addi rX,r1,8` at every use, where the game
// compiler homed it in r31 once in the loop preheader. That single missing
// `addi r31,r1,8` also makes the function 4 bytes SHORT of the want, so the
// masked index score cannot move past ~78%. Consequences: 6 x `addi r3,r1,8`
// vs `mr r3,r31`, `stw r0,0xc4(r1)` vs `stw r0,0xbc(r31)`.
//
// Measured and rejected for the &sp8 home (all measured on this function):
//   - `register GfxObj *sp __asm__("r31") = &sp8;`  -> 166 words (+6), 69-80 eq
//   - same pin with `sp = &sp8;` inside the loop      -> 164-166 words
//   - unnamed pinned `sp` (recipe 6b "named local wins a saved reg") -> worse
//   - `volatile` on the slot (recipe 180 forces per-site remat) -> inverse of
//     what is wanted, and recipe 165's `-fno-expensive-optimizations` only
//     kills such homing, never creates it.
//   - no-pins baseline: 158 words / 81 of 160 stream-equal (pins are load-
//     bearing; each of hp/cf/cnt/nd/gp/i/ob loses 2-5 words when unpinned).
// Flag sweep on the final body (-fno-schedule-insns/-insns2/-gcse/-peephole/
// -strength-reduce/-cse-follow-jumps/-O1, -fno-expensive-optimizations):
// none changes the 35-word residual.
// Remaining residual classes (all coin-flips of the documented
// M5.0o/M5.0r regalloc+scheduler family):
//   (a) `addi r23,r30,0` for the lbl_803018A8 anchor vs want's second `lis`;
//   (b) `addi r27,r27,0` (pinned anchor) vs want's `lis r11; addi r27,r11,-0x4828`;
//   (c) lbl_802974C8's anchor duplicated into r22+r24 (10 saved regs, stmw r22)
//       instead of the single r24 — the only cause of the r22 prologue diff;
//   (d) loop-entry `lwz` placement / preheader instruction ordering;
//   (e) src = (__ps_t *)ob costs one `mr r31,r30`; inlining the cast removes it
//       but drops the object to 159 words.
//
// BITFIELD NOTE (recipe 16 extension, worth promoting): for `x & CONST` whose
// mask needs a rotate, ngccc/3.9.3 emits SH=0 and ROTATES the mask, so
// `x &= 0xFEFFFFFF` produces `rlwinm x,0,8,6` (effective mask 0xFFFFFF7F) —
// semantically wrong. The want's `rlwinm r0,r0,0,0x19,0x17` (mask 0xFEFFFFFF,
// clears bit 24) is emitted EXACTLY by `struct { unsigned lo:24; unsigned b24:1;
// unsigned hi:7; }` bitfield store, while `flags.all |= 0x80` / `|= 0x200` in a
// union with that struct still give plain `ori`. So a flags word mixes plain
// `|=` and a 1-bit-field clear — model it as a union of the word and the
// bitfield struct.
// ---------------------------------------------------------------------------
#include "structs.h"

extern s32 lbl_803018A8;
extern f32 lbl_802974C8;
extern f32 lbl_802974CC;
extern f32 lbl_802974D0;
extern f32 lbl_802974D4;
extern char lbl_8037B644[];
extern char lbl_8037B6A4[];
extern char lbl_8037B6E0[];
extern char lbl_8037B7D8[];

typedef union Pair {
    __ps_t ps;
    struct {
        f32 hi, lo;
    } flt;
} Pair;

typedef struct Vec {
    f32 x, y, z;
} __attribute__((aligned(8))) Vec;

typedef union Word {
    s32 all;
    struct {
        unsigned b0_23 : 24;
        unsigned b24 : 1;
        unsigned b25_31 : 7;
    } b;
} Word;

typedef struct Flg {
    s32 unk0x0;
    Word flags;
} Flg;

typedef struct Obj {
    char pad0x00[0x18];
    char pad0x18[0x20];
    f32 unk0x38;
    f32 unk0x3C;
    f32 unk0x40;
    char pad0x44[0xC];
    u16 unk0x50;
    char pad0x52[0x2];
    Flg *unk0x54;
} Obj;

typedef struct GfxObj {
    char pad0x00[0x48];
    f32 mtx[16];
    char pad0x88[0x34];
    s32 unk0xBC;
    char pad0xC0[0x50];
} GfxObj;

typedef struct Node {
    s32 unk0x0;
    s32 unk0x4;
} Node;

void GX_SetZMode(s32, s32, s32);
void fn_80098D28(s32);
Node *fn_80098D3C(s32, s32);
s32 fn_80061F2C(s32);
void *fn_80061DE8(s32, s32);
void queue_front(GfxObj *);
void Camera_orthographic(GfxObj *, s32, s32, s32, s32);
void fn_800175E0(GfxObj *, f32, f32);
void fn_80016AB0(GfxObj *, f32, f32, f32);
void fn_80016AC4(GfxObj *, f32, f32, f32);
void fn_80016AD8(GfxObj *, f32, f32, f32);
void fn_8001737C(GfxObj *);
void fn_80016A88(GfxObj *, s32);
void PSMTXCopy(void *, void *);
void fn_8001D39C(void *, void *);
void fn_80093820(Obj *, s32);

void fn_80096F20(void) {
    GfxObj sp8;
    Vec va;
    Vec vb;
    Pair tmp[2];
    __ps_t *src;
    s32 var_r9;
    f32 f30, f31;
    f32 t0, t1, t2;
    register s32 *hp __asm__("r23");
    register f32 *cf __asm__("r24");
    register s32 cnt __asm__("r25");
    register Node *nd __asm__("r26");
    register Pair *gp __asm__("r27");
    register s32 i __asm__("r28");
    f32 *mtxp;
    register Obj *ob __asm__("r30");

    cf = &lbl_802974C8;
    hp = &lbl_803018A8;
    GX_SetZMode(0, 7, 0);
    fn_80098D28(*hp);
    for (;;) {
        nd = fn_80098D3C(*hp, 0);
        if (nd == NULL) {
            break;
        }
        if (nd->unk0x4 != 0) {
            cnt = fn_80061F2C(nd->unk0x4);
            for (i = 0; i < cnt; i++) {
                cf = &lbl_802974C8;
                f31 = lbl_802974CC;
                f30 = *cf;
                gp = (Pair *)lbl_8037B7D8;
                src = (__ps_t *)fn_80061DE8(nd->unk0x4, i);
                ob = *(Obj **)((char *)src + 0x30);
                src = (__ps_t *)ob;
                var_r9 = 1;
                if (ob->unk0x50 == 0) {
                    var_r9 = 0;
                }
                if (var_r9 != 0) {
                    queue_front(&sp8);
                    sp8.unk0xBC = 1;
                    Camera_orthographic(&sp8, 0, 0, 0x80, 0x80);
                    fn_800175E0(&sp8, *cf, *cf);
                    va.x = ob->unk0x38;
                    va.y = ob->unk0x3C;
                    va.z = ob->unk0x40;
                    vb.x = ob->unk0x38;
                    vb.y = ob->unk0x3C + f30;
                    vb.z = ob->unk0x40;
                    gp[0].ps = src[7];
                    gp[1].ps = src[8];
                    gp[0].flt.lo += f31;
                    tmp[0].ps = src[3];
                    tmp[1].ps = src[4];
                    t0 = tmp[0].flt.hi * f31;
                    t1 = tmp[0].flt.lo * f31;
                    t2 = tmp[1].flt.hi * f31;
                    vb.x += t0;
                    vb.y += t1;
                    vb.z += t2;
                    va.x += t0;
                    va.y += t1;
                    va.z += t2;
                    fn_80016AB0(&sp8, vb.x, vb.y, vb.z);
                    fn_80016AC4(&sp8, lbl_802974D0, lbl_802974D4,
                                lbl_802974D4);
                    fn_80016AD8(&sp8, va.x, va.y, va.z);
                    fn_8001737C(&sp8);
                    mtxp = sp8.mtx;
                    PSMTXCopy(mtxp, lbl_8037B6E0);
                    fn_8001D39C(lbl_8037B644, mtxp);
                    fn_8001D39C(lbl_8037B6A4, mtxp);
                    ob->unk0x54->flags.all |= 0x80;
                    fn_80093820(ob, 0x10);
                    ob->unk0x54->flags.b.b24 = 0;
                    ob->unk0x54->flags.all |= 0x200;
                    fn_80016A88(&sp8, 2);
                }
            }
        }
    }
}