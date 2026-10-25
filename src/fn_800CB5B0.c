// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CB5B0-0x800CB68C (220B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

// Guess-twin: CSNode2 is a 0x34-byte node guess (unk0x4 @0x4, unk0xC @0xC,
// unk0x30 @0x30); node+0x2C reuses the same layout via cast. Signature from
// register use: (node=r3, unused=r4, ef0=r5, ef1=r6); returns 1. tmp is
// pinned to r9 and the stack-temp reload is pinned to r11 (both load-bearing:
// they fix the pre-copy load home and the loop's carried compare value).
//
// PARKED 2026-10-20 at 96.36% (53/55), size EXACT 220B. Semantic order:
// cache the walk head, save a prefetch alias that nulls on the -1 sentinel,
// optionally fill the stack temp through the resolver call, then walk the
// node chain comparing the saved key; a hit calls the quaternion setter with
// the resolved value, a miss with the alias's field. Return 1.
// 2026-10-20 TWIN TRANSFER (fn_800CBEC0/fn_800CC268/fn_800A5E8C, all promoted
// byte-identical with the same -1-sentinel/nullify/walk idiom and the same
// `or. r9,r9,r9` loop test): the or. is a TEST-AFTER-COPY lowering — the twin
// loop splits next into `c` (`c = b->next; if (c->s==-1) c=0; b=c`) and the
// back test on post-copy `b` combines to or. (the copy coalesces, no extra
// mr), while a test on a directly-loaded value stays cmpwi. Verified here:
// single-var check (cmpwi) -> c-split check (or., no mr, size still exact).
// The twin's do-while+outer-if entry (`b BEE0`, outer test deleted) does NOT
// transfer: with a join from the body (break/goto-call — forced here because
// hit+miss share one call site) the outer test persists as cmpwi/beq; with
// return-exits it also persists (plus n2c home shifts). Twin bisection:
// break keeps or. but adds the outer test; the goto+c-split form used here
// has the twin's CFG ([b check] entry, or. back test) with zero extra tests.
// The c-split relies on c/tmp coalescing to r9 (no mr emitted); the `c = tmp`
// init before `goto check` is load-bearing (without it the prologue reload
// is miscompiled, 13%).
// RESIDUAL (1 word, 0x800CB5E0): the prologue sentinel load reads the alias
// copy (r31) instead of the pre-copy register (r9) — copy-prop substitutes
// savenode for tmp at the load (fires through volatile too). Reading before
// the alias birth fixes the home (r9) but swaps the saved-reg set (r30/r31,
// 87.3%); `+r` barriers on either local and `register` pins on the saved
// homes do the same (83.6-85.5% — allocation perturbation, not just the web).
// Load home and saved-reg colouring form a complete seesaw from birth order.
// PARKED 2026-10-20 at 98.18% (54/55), size EXACT 220B.

typedef struct CSNode2 {
    s32 unk0x0;
    s32 unk0x4;
    s32 unk0x8;
    s32 unk0xC;
    char pad0x10[0x20];
    s32 unk0x30;
} CSNode2;

s32 fn_80128E34(void *, u32, void *, s32);
s32 fn_8012EFA4(void *, s32, void *, s32);

s32 fn_800CB5B0(CSNode2 *arg0, s32 unused, CSNode2 *ef0, CSNode2 *ef1) {
    CSNode2 *node_home;
    register s32 zero __asm__("r11");
    CSNode2 *n2c;
    CSNode2 *ef0v;
    register CSNode2 *tmp __asm__("r9");
    CSNode2 *ef1v;
    s32 sp8;
    CSNode2 *savenode;
    CSNode2 *c;
    register s32 sp8v __asm__("r11");
    s32 s6;
    s32 v;

    node_home = arg0;
    zero = 0;
    n2c = (CSNode2 *)((char *)node_home + 0x2C);
    ef0v = ef0;
    tmp = n2c->unk0xC;
    ef1v = ef1;
    sp8 = zero;
    v = tmp->unk0x4;
    savenode = tmp;
    __asm__ volatile("" :: "r"(savenode));
    if (v == -1) {
        savenode = NULL;
    }
    if (ef0v == NULL) {
        goto skipcall;
    }
    fn_80128E34(ef0v, 0x5CFCCF35U, &sp8, 0);
skipcall:
    sp8v = sp8;
    s6 = sp8v;
    if (sp8v == 0) {
        goto invalid;
    }
    tmp = n2c->unk0xC;
    c = tmp;
    goto check;
body:
    if (tmp->unk0x30 == sp8v) {
        goto call;
    }
    c = tmp->unk0xC;
check:
    if (c->unk0x4 == -1) {
        c = NULL;
    }
    tmp = c;
    if (tmp != 0) {
        goto body;
    }
call:
    fn_8012EFA4(ef1v, 6, node_home, s6);
    goto done;
invalid:
    fn_8012EFA4(ef1v, 6, node_home, savenode->unk0x30);
done:
    return 1;
}
