// PARKED: **80.8% (46 words, size-exact 960B)**. Hand-rebuilt from the want;
// every semantic decision below is verified against the original bytes.
// Advances over the 40.8% draft: `goto latch` entry (fixes loop rotation),
// `tag & ~0xC0` selector (exact rlwinm shape), tag/name/val pins (r29/r28/r5),
// lbl_802FFE98 global (matches promoted sib fn_8012A544; the old 0x802FE898
// claim was wrong), separate-statement cases 10/12 (sibling idiom),
// `u8 *p = arg1` local copy (sibling idiom), split `p += strlen; p += 1`.
// Corrections to older notes: selector is `& ~0xC0` (not `& 0x3F`); the loop
// needs an explicit `goto latch` (plain do-while falls through, while-form
// gets peeled); case 10 ctor is `CStruct_ctor()` no-arg (sibling form).
// Remaining walls: (a) frame 0x68 vs want 0x80 - 0x20 dead hole above locals
// with zero accesses (no spills/outgoing/saves cause found); trailing pads of
// every shape sort to the BOTTOM and shift locals, dead scalars vanish, so the
// hole is unfakeable - it must come from the original's own (unaccessed)
// locals; (b) case-17 load uses r9-based `lhz r5,2(r9)` vs want r1+0x1e
// (shared-sp1C-base CSE; separate 2-byte locals sort to bottom, so the base
// cannot be split); this 1 extra insn cascades into latch/epilogue misalignment
// (~14 words); (c) prologue `mr r31` after `lfs f29` (scheduler puts load
// first); (d) mask `clrlwi` vs want `rlwinm` (same r29, backend quirk);
// (e) case-6 setup `mr/addi` order; (f) t5a home f31 vs f30.
// family=m2c range=0x80129EA0-0x8012A260 size=960B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// The buffer/compression-lookup-table serialiser: `u8 *fn(CStruct *ctx, u8 *p)`
// walks a tag-prefixed byte stream and replays it into the script object; a zero
// tag terminates. m2c's skeleton (the tag bits, the 15 switch cases and the case
// ORDER) was already right; what it got wrong, all fixed here:
//  1. the prologue: `CStruct_dtor(ctx)` then `fn_8000F2F8(g, g->unk0x12C)` and
//     `fn_8000F320(g)` on exit, where `g` is `lbl_802FFE98` (Mgr*), same as
//     the promoted sibling fn_8012A544 (m2c's address was right; an interim
//     0x802FE898 edit was wrong and has been reverted).
//  2. **the switch selector is `tag & 0x3F`, not `& 0x3C`** (want
//     `rlwinm r29,r29,0,0x1a,0x17` = ~0xC0; m2c's `& 0xFFFFFF3F` constant was
//     right but the switch expression was wrong). This is the single biggest
//     correctness bug in the function.
//  3. it is a do-while whose CONDITION reads the tag (`while ((tag = *p++))`),
//     not a `loop:` label at the top — want jumps from the prologue straight to
//     the latch at 0x8012A220;
//  4. tag&0x80 arm: `GetChecksum(fn_801259C8(QB_..._8, 0), *p++)` — a `u8`
//     read, not `*(s32 *)(p+1)`; tag&0x40 arm: the 16-bit read feeds
//     GetChecksum directly (`lhz r4, 8(r1)`), not `(u8)`;
//  5. case 12: `fn_80128F94` takes its receiver and returns it
//     (`obj = fn_80128F94(fn_8003E7CC(0xC))`) and `fn_8012A544(p)`'s return
//     value is the NEW `p`;
//  6. case 10 is RECURSIVE: `obj = CStruct_ctor(CStruct_new(8));
//     p = fn_80129EA0(obj, p); fn_80127CD4(ctx, name, obj);` (m2c lost the
//     recursive call and the CStruct_new/CStruct_ctor pair);
//  7. case 16 does its own `AddInteger(ctx, name, *p++)` — want sets r4 before
//     the shared tail and branches one instruction later, so it is NOT part of
//     the shared AddInteger tail that cases 1/15/17 use;
//  8. case 14 sign-extends (`lbz`+`extsb` => `(s8)*p++`) while case 16 does not
//     (`lbz` only => `(u8)*p++`); 15 is `s16` (`lha`), 17 `u16` (`lhz`);
//  9. cases 5/6 must copy the first float(s) into temps BEFORE the following
//     read, so they are live across the next call and land in callee-saved
//     f30/f31 (that is why want saves f29 AND f30 AND f31; without the copies
//     only f31 is saved and the frame collapses by 0x20).
//
// fn_8012CB2C / fn_8012CB60 are deliberately LEFT UNPROTYPED: want has
// `crclr cr1eq` before every one of those calls and nowhere else
// (AGENTS-recipes items 16/27), so they need the implicit-int form while every
// other callee here is prototyped.
//
// FRAME: locals are declared in want's slot order and this draft now produces
// want's offsets exactly (u16 @8, s32 @c, s32 @10, f32 @14, s32 @18, the 15/17
// cell @1c, f32 @20/24/28/2c/30). **The two 16-bit values of cases 15/17 must
// share ONE 4-byte cell** (`u16 sp1C[2]`), because size-sorted slot allocation
// would otherwise put a 2-byte local at the BOTTOM (measured: 0x8/0xa) instead
// of want's 0x1c/0x1e.
//
// BLOCKER (all one cause — the frame): want's frame is 0x80 with 5 saved GPRs at
// 0x54 and 3 FPRs at 0x68, i.e. **0x20 bytes of dead space between the locals
// (ending 0x34) and the GPR save area**. This compiler cannot produce a gap
// there: every padding shape tried — `volatile double`/`volatile f32` dummies,
// `volatile double _pad[3]`, a non-volatile `struct {f32 v; char p[0x14];}` —
// is allocated at the BOTTOM of the local area and shifts every real local up
// by its own size (so the offsets then stop matching). With no padding the
// frame is 0x68; with 0x18-0x20 of padding it is 0x80 but the locals move.
// Second-order: the shared 4-byte cell makes cc1 CSE its base into a callee-saved
// GPR (`addi r26, r1, 0x1c` + `stmw r26`), where want computes the two 0x1c/0x1e
// addresses independently; and declaring the 15/17 temps in per-case blocks
// instead removes that r26 but costs 34 points of layout, so it is not free.
// Also still open: want keeps `p` in r31 and `tag`/`name` in r29/r28 (this draft
// swaps tag/name), emits `mr r31,r4` before `lfs f29` (this draft loads f29
// first), and does not rotate the do-while (it falls into the body, want jumps
// to the latch).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct {
    char pad0x0[0x12C];
    void *unk0x12C;
} Mgr;

extern f32 lbl_8029E650;
extern void *lbl_802FFE98;

s32 CStruct_dtor(CStruct *);
void fn_8000F2F8(void *, void *);
void fn_8000F320(void *);
void *fn_801259C8(s32, s32);
s32 GetChecksum(void *, s32);
void AddInteger(CStruct *, s32, s32);
void fn_8012772C(CStruct *, s32, f32);
void AddChecksum(CStruct *, s32, s32);
void AddString(CStruct *, s32, u8 *);
void fn_80127618(CStruct *, s32, u8 *);
void fn_80127A18(CStruct *, s32, f32, f32);
void fn_8012788C(CStruct *, s32, f32, f32, f32);
void fn_80127CD4(CStruct *, s32, void *);
void AddArrayPointer(CStruct *, s32, void *);
void *CStruct_new(s32);
void *CStruct_ctor(void);
void *fn_8003E7CC(s32);
void *fn_80128F94(void *);
void *fn_8012A544(void *, u8 *);
u32 strlen(u8 *);

u8 *fn_80129EA0(CStruct *arg0, u8 *arg1) {
    u8 *p = arg1;
    u16 sp8;
    s32 spC;
    s32 sp10;
    f32 sp14;
    s32 sp18;
    struct {
        s16 s;
        u16 u;
    } sp1C;
    f32 sp20;
    f32 sp24;
    f32 sp28;
    f32 sp2C;
    f32 sp30;
    register s32 name __asm__("r28");
    register u8 tag __asm__("r29");
    register s32 val __asm__("r5");
    void *obj;
    f32 tmp_f29;
    f32 t5a, t6a, t6b;

    tmp_f29 = lbl_8029E650;
    CStruct_dtor(arg0);
    fn_8000F2F8(lbl_802FFE98, ((Mgr *)lbl_802FFE98)->unk0x12C);
    goto latch;
    do {
        if (tag & 0x80) {
            name = GetChecksum(fn_801259C8(QB_WRITETOBUFFER_COMPRESSIONLOOKUPTABLE_8, 0), *p++);
        } else if (tag & 0x40) {
            obj = fn_801259C8(QB_WRITETOBUFFER_COMPRESSIONLOOKUPTABLE_16, 0);
            fn_8012CB60(&sp8, p);
            p += 2;
            name = GetChecksum(obj, sp8);
        } else {
            fn_8012CB2C(&spC, p);
            p += 4;
            name = spC;
        }
        switch (tag & ~0xC0) {
        case 1:
            fn_8012CB2C(&sp10, p);
            p += 4;
            val = sp10;
            goto addint;
        case 2:
            fn_8012CB2C(&sp14, p);
            p += 4;
            fn_8012772C(arg0, name, sp14);
            break;
        case 13:
            fn_8012CB2C(&sp18, p);
            p += 4;
            AddChecksum(arg0, name, sp18);
            break;
        case 19:
            fn_8012772C(arg0, name, tmp_f29);
            break;
        case 18:
            AddInteger(arg0, name, 0);
            break;
        case 14:
            AddInteger(arg0, name, (s8)*p++);
            break;
        case 16:
            AddInteger(arg0, name, *p++);
            break;
        case 15:
            fn_8012CB60(&sp1C.s, p);
            p += 2;
            val = sp1C.s;
            goto addint;
        case 17:
            fn_8012CB60(&sp1C.u, p);
            p += 2;
            val = sp1C.u;
            goto addint;
        case 3:
            AddString(arg0, name, p);
            p += strlen(p);
            p += 1;
            break;
        case 4:
            fn_80127618(arg0, name, p);
            p += strlen(p);
            p += 1;
            break;
        case 5:
            fn_8012CB2C(&sp20, p);
            p += 4;
            t5a = sp20;
            fn_8012CB2C(&sp24, p);
            p += 4;
            fn_80127A18(arg0, name, t5a, sp24);
            break;
        case 6:
            fn_8012CB2C(&sp28, p);
            p += 4;
            t6a = sp28;
            fn_8012CB2C(&sp2C, p);
            p += 4;
            t6b = sp2C;
            fn_8012CB2C(&sp30, p);
            p += 4;
            fn_8012788C(arg0, name, t6a, t6b, sp30);
            break;
        case 10:
            obj = CStruct_new(8);
            obj = CStruct_ctor();
            p = fn_80129EA0(obj, p);
            fn_80127CD4(arg0, name, obj);
            break;
        case 12:
            obj = fn_8003E7CC(0xC);
            obj = fn_80128F94(obj);
            p = fn_8012A544(obj, p);
            AddArrayPointer(arg0, name, obj);
            break;
        }
        continue;
    addint:
        AddInteger(arg0, name, val);
    latch:
    } while ((tag = *p++));
    fn_8000F320(lbl_802FFE98);
    return p;
}
