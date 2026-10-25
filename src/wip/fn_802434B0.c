// WIP DRAFT — PARKED at 20.0% NEAR (10/50 insns, group D)
// Float-array element converter: switch(type){0,2: b=a[5],sc=054C; 1,3: b=a[3],
// sc=0544} then int->float via 0x43300000-magic dance scaled by rodata floats.
// Blockers:
//  1. WANT loads the three constants (default f32 @0x802C12AC, f64 magic
//     @0x802C12B0) as 2-insn [lis page][lfs/lfd disp] folds -- i.e. the
//     original binary had SYMBOLS at those addresses. symbols.txt has none
//     there (they fall inside the unlabeled blob starting lbl_802C0F0F) and
//     this task forbids config edits, so every C spelling I tried yields
//     either [lis][addi][lfs] 3-insn forms or hoisted-shared anchors that
//     cascade the whole schedule.
//  2. WANT keeps per-case lis anchors (no GCSE sharing across cases); GCC
//     always merges mine into one callee-saved anchor (stw r31 appears).
//  3. FPR roles (want f1=res/default, f13=magic, f12=scale) only partially
//     reproducible: fr13/fr12 register pins work, fr1 pin breaks the lfs fold.
// Levers tried (~15 shapes): extern-struct pun (packed AND unpacked), char[]
// delta arithmetic from lbl_802B054C/0544/802C0F0F, named base pointers for
// lwzx forms (works), per-case macro with shared tail via crossjumping
// (structure matches: duplicated case prefixes + merged tail), union store
// orders both ways, "+f" barriers, input-use fences, volatile casts,
// fr12/fr13/fr1 register pins, flags -fno-gcse / -fno-rerun-cse-after-loop /
// -fno-schedule-insns2 (all DIFF). xoris+stw+stw+lfd+fsub+frsp+fmuls tail
// itself IS correct (matches when scheduled together).
// family=m2c range=0x802434B0-0x802435B8 size=264B
// UPDATED 2026-09-13 (c): extended flag matrix (recipe 49) found `-fno-schedule-insns` -> 0.00% to 16.67%.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// FLAG: -ffixed-r9
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 18.2% ([1]rev->18.2%).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802B054C[];
extern char lbl_802B0544[];
f32 fn_802434B0(s32 arg0, s32 arg1) {
    union {
        u32 w[2];
        f64 d;
    } cvt;
    s32 idx4;
    s32 type;
    s32 x;
    s32 y;
    s32 b;
    f32 scale;
    f32 res;
    f64 magic;
    char *pc;
    char *p14;
    char *p1c;

#define THING(BYTE_OFF, SC) \
    p14 = (char *)arg0 + 0x14; \
    x = *(s32 *)(p14 + idx4); \
    p1c = (char *)arg0 + 0x1c; \
    y = *(s32 *)(p1c + idx4); \
    magic = *(f64 *)(lbl_802B054C + 0xD64); \
    b = *(u8 *)((char *)arg0 + arg1 * 6 + (BYTE_OFF)); \
    scale = *(f32 *)(SC);

    idx4 = arg1 * 4;
    pc = (char *)arg0 + 0xC;
    type = *(s32 *)(pc + idx4);
    res = ((Unk_50FBB2DD *)lbl_802B054C)->unk0xD60;
    switch (type) {
    case 0:
        THING(5, lbl_802B054C)
        break;
    case 2:
        THING(5, lbl_802B054C)
        break;
    case 1:
    case 3:
        THING(3, lbl_802B0544)
        break;
    }
    res = (f32)(cvt.d - magic) * scale;
    cvt.w[0] = QB_INT_TO_DOUBLE_BIAS;
    cvt.w[1] = (u32)(b + x + y) ^ 0x80000000;
    return res;
}
