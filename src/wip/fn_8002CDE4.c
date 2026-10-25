// PARKED: NEAR 97.4% (312B, size-exact, 2 differing words — both candidate
// bodies below sit at exactly this score).
// family=hand range=0x8002CDE4-0x8002CF1C size=312B
//
// Two residuals, each 2 words, both pure sched1 (pre-regalloc) tie-breaks.
// BODY A (kept below, no qualifiers): the byte store to +0x75 and the word
// store to +0x168 come out transposed, stw first, so the +0x10 test's `cmpwi`
// lands between them instead of after both. Everything else — prologue, spin
// head, callback block, the other seven clearing stores, the anim-heap block,
// the 18-script loop and the epilogue — is byte-identical.
// BODY B (`*(volatile u8 *)&..0x75` / `*(volatile u32 *)&..0x168`): restores
// the want store order in C alone, and then the only residual is the two zero
// materializations transposed (`li r11,0` before `li r29,0` instead of after).
// 97.44% either way, so neither body dominates.
//
// The transposition is NOT source order: stb-first and stw-first source
// orders, mask split vs single-expression (`masked = f & 0x1FFFF`), the byte
// store hoisted above the mask, `ret` moved around it, both orderings of the
// two zero assignments, three placements of `bzero = 0`, and a `u8`-typed
// zero local (which does fix the `li` order but splits the two byte stores
// over r29/r11) all compile to the same pair. `-fno-schedule-insns` flips the
// store pair to want order but wrecks the rest of the schedule (80.8%);
// `-fno-schedule-insns2` changes nothing, so sched1 owns the pair.
//
// NOT A FIX: a zero-code `__asm__ volatile("" ::: "memory")` between the
// callback dispatch and `zero = 0` scores 100% on the reloc-masked metric but
// is refused by the branch-target audit (the barrier re-lays the block), i.e.
// the masked number is an artifact. Do not promote it.
//
// REFERENCE: fn_8002CB4C (promoted) is the same reset idiom and does emit
// stb-then-stw from the same source shape; there the +0x10 test sits at the
// end of the function instead of right after the block.
//
// LOAD-BEARING SHAPE (do not undo): the spin head is `if (f & 0x20000) {
// while (f & 0x20000) ; }` (the only non-volatile form with the self-branch);
// `| 0x10000` sets bit 16; the mask stays split as `masked = load` then
// `masked &= 0x1FFFF` so the `clrlwi` remains late; the return is s32 because
// the caller subtracts it from a count. The two asm statements emit no
// instruction: the file-scope `register s32 bzero __asm__("r11")` and the
// ordering barrier in the reset block. No FLAG lines.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
register s32 bzero __asm__("r11");
typedef struct T_8002CDE4 {
    char pad0x00[0x04];
    s32 unk0x4;
    char pad0x08[0x04];
    s32 unk0xC;
    void *unk0x10;
    s32 unk0x14;
    s32 unk0x18;
    s32 unk0x1C;
    s32 unk0x20;
    void (*unk0x24)(void *);
    void *unk0x28;
    char pad0x2C[0x48];
    u8 unk0x74;
    u8 unk0x75;
    char pad0x76[0xF0];
    u16 unk0x166;
    u32 unk0x168;
} T_8002CDE4;
void fn_8002CA64(void *, s32);
void fn_8002CA8C(CScript *);
extern char lbl_802FFE98[];
void fn_8000F2F8(Unk_9F352E7C *, s32);
void Mem_Free2(void *);
void fn_8000F320(Unk_F12C5E01 *self);
s32 fn_80010400(s32 arg0, s32 arg1, s32 arg2);
s32 fn_8002CDE4(T_8002CDE4 *arg0) {
    s32 zero;
    s32 masked;
    s32 mgr;
    s32 ret;
    CScript *stz;
    s32 idx;
    s32 count;
    char *base;
    CScript *v;

    if (arg0->unk0x168 & 0x20000) { while (arg0->unk0x168 & 0x20000) ; }
    arg0->unk0x168 |= 0x10000;
    if (arg0->unk0x24 != 0) {
        arg0->unk0x24(arg0->unk0x28);
        arg0->unk0x24 = 0;
    }
    zero = 0;
    masked = arg0->unk0x168;
    bzero = 0;
    ret = arg0->unk0x14;
    masked &= 0x1FFFF;
    arg0->unk0x75 = bzero;
    arg0->unk0x168 = masked;
    arg0->unk0x1C = zero;
    arg0->unk0x20 = zero;
    arg0->unk0x4 = zero;
    arg0->unk0x166 = zero;
    arg0->unk0x74 = bzero;
    arg0->unk0x18 = zero;
    arg0->unk0x14 = zero;
    if (arg0->unk0x10 != 0) {
        mgr = *(s32 *)&lbl_802FFE98;
        fn_8000F2F8((Unk_9F352E7C *)mgr, fn_80010400(mgr, QB_ANIMHEAP, 1));
        if (arg0->unk0x10 != 0) {
            Mem_Free2(arg0->unk0x10);
        }
        fn_8000F320((Unk_F12C5E01 *)*(s32 *)&lbl_802FFE98);
        arg0->unk0x10 = 0;
    }
    base = (char *)arg0 + 0x2C;
    stz = 0;
    idx = 0;
    count = 0x12;
    do {
        v = *(CScript **)((char *)(idx + (s32)base));
        if (v != 0) {
            fn_8002CA8C(v);
            v = *(CScript **)((char *)(idx + (s32)base));
            if (v != 0) {
                fn_8002CA64(v, 3);
            }
            *(CScript **)((char *)(idx + (s32)base)) = stz;
        }
        idx += 4;
        count -= 1;
    } while (count != 0);
    arg0->unk0xC = count;
    return ret;
}
