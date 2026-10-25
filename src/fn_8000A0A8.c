// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000A0A8-0x8000A13C (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-gcse
#include "types.h"
#include "structs.h"
extern char lbl_8028FF88[];
s32 fn_8000A19C(void *, s32);
typedef struct {
    s32 _unused;
    s32 cur;
    s32 vtable;
} Ctx8000A0A8;

void fn_8000A0A8(Unk_C8FEE62D *arg0) {
    Ctx8000A0A8 ctx;
    Ctx8000A0A8 *c1;
    Ctx8000A0A8 *c;
    s32 mid;
    register s32 node_s __asm__("r11");
    s32 id;

    c1 = &ctx;
    c1->vtable = (s32) lbl_8028FF88;
    c1->cur = 0;
    __asm__ __volatile__("" ::: "memory");
    c = c1;
    goto head;
body:
    fn_8000A19C(id, 3);
head:
    mid = (s32) arg0 + 0x24;
    c->cur = mid;
    node_s = *(s32 *) ((char *) mid + (s32) 0xC);
    if (*(s32 *) ((char *) node_s + (s32) 4) == -1) {
        node_s = 0;
    }
    c->cur = node_s;
    id = (node_s == 0) ? 0 : *(s32 *) ((char *) node_s + (s32) 4);
    if (id != 0) {
        goto body;
    }
    c->vtable = (s32) lbl_8028FF88;
}

/* PARKED 2026-09-26 (re-scored 86.5% NEAR, 5 masked word diffs, 148B == want).
 *
 * WHAT THIS IS (semantics now established, not m2c guesswork):
 *   A "drain the list" helper of the fn_8000A0xx node/allocator family, the
 *   empty-list branch of the sibling dispatcher fn_8000A288 (which calls
 *   fn_8000A3DC for the non-empty case and this function for count == 0).
 *   It builds a 3-word stack object at r1+8 whose +8 slot gets vtable
 *   lbl_8028FF88 and whose +4 slot is the "current node" cursor, then walks
 *   the chain anchored at arg0+0x24 (link at +0xC) handing each node's
 *   payload (node+4) to fn_8000A19C(node->f4, 3).  node->f4 == -1 is the
 *   end-of-list sentinel (f4 doubles as the -1 terminator and as the value
 *   passed to the callback), matching the identical idiom in the PROMOTED
 *   src/fn_8000A288.c (`node = ((Unk_DB0E2BAB *)headv)->unk0xC;
 *   if (node->unk0x4 == -1) node = NULL;`) — so the node/arg0 types here are
 *   the same Unk_DB0E2BAB / Unk_C8FEE62D classes that promoted file uses.
 *   Types/protos swept this pass and all score identically (86.5%):
 *   fn_8000A19C as (s32,s32) / void(s32,s32) / (s32,void*) / (void*,s32) /
 *   (void*,void*) / old-style / undeclared; node->unk0x4 as s32 or void*;
 *   `id` as s32 or void*; mid->next as void* / s32 / u32 / s32* / char*.
 *   So the residual is NOT a signature/type defect.
 *
 * THE 5 REMAINING DIFFS (2 groups, both plain ProDG-GCC scheduling):
 *  (1) prologue 4-word permutation, 0x8000A0C8-0x8000A0D4:
 *        want: mr r30,r3 | stw r9,8(r11) | stw r0,4(r11) | mr r31,r11
 *        got : mr r31,r11 | mr r30,r3 | stw r0,4(r11) | stw r9,8(r11)
 *      i.e. want has the two reg-reg moves SANDWICHING the two init stores;
 *      every ProDG version hoists BOTH moves to the front of the block.  The
 *      source already writes the stores between the `c1 = &ctx` birth and the
 *      `c = c1` copy, so this is a compiler artifact, not a source order bug.
 *      Forcing the right store order by hand (vtable store first, matching
 *      promoted fn_8000A13C's `child->unk0x14 = lbl_8028FFB8; ...` style)
 *      gives 83.8% — the masked compare then loses the accidental
 *      `stw r0,4(r11)` word match.  The 86.5% body is kept; the store order
 *      is cosmetic here, both are ~equally far from EXACT.
 *  (2) loop head 2-word swap, 0x8000A0E8-0x8000A0EC:
 *        want: addi r9,r30,0x24 | stw r9,4(r31) | lwz r11,0xc(r9)
 *        got : addi r9,r30,0x24 | lwz r11,0xc(r9) | stw r9,4(r31)
 *      GCC issues the critical-path load (it feeds cmpwi/bne) ahead of the
 *      cold cursor store.  Source order is already store-then-load and no
 *      spelling moves it.
 *
 * RULED OUT THIS PASS (plain C only, no inline asm, no permutation brute force):
 *   flags: -fno-gcse is the only one that matters.  -fno-schedule-insns
 *     (73.0%, also recolors the node web to r9), -fno-schedule-insns2 (83.8%),
 *     both (67.6%), -fno-sched-spec / -fno-sched-interblock /
 *     -fno-sched-spec-load / -fno-strength-reduce / -fno-thread-jumps /
 *     -fno-expensive-optimizations / -fno-inline-functions (all 86.5%, no
 *     change), -O1 (67.6%), -O3 (86.5%).  With BOTH schedule passes off the
 *     `mr r31,r11` copy DOES land last (matching want) but then the param
 *     copy + both stores hoist to 0x8000A0B8-0x8000A0D0 — the same total
 *     3-word slide, so no flag fixes both halves at once.
 *   all five ProDG builds (3.5 / 3.5b140 / 3.7 / 3.8.1 / 3.9.3) emit the
 *     IDENTICAL 86.5% object -> not a compiler-version artifact.
 *   loop shape: `for(;;){...if(id==0)break;call;}` 35.1% and a do-while
 *     43.2% both lose want's rotated `[preheader][call blk][head]` layout;
 *     the goto form is what produces it.  Plain `while` + break does NOT
 *     rotate to want's shape.
 *   24/24 permutations of the 4 preheader statements (birth / 2 stores /
 *     copy) — best is the current order at 86.5%.
 *   pointer-web shape: single `c` (24.3%), copy BEFORE the stores (24.3%,
 *     the webs merge), nested scope for c1 (83.8%), copy through a `char *`
 *     alias or `*(Ctx **)&c1` (83.8%), loop web as s32 / void* / char* alias
 *     (83.8%), local as `s32 ctx[3]` (83.8%), mixed direct-member/pointer
 *     store (83.8%), 2-word struct store of {0, vtable} (compile FAIL —
 *     wants a 64-bit reg pair).  Hard-reg pins (`register s32 __asm__("r11")`
 *     on the preheader web, `"r31"` on the loop web, both) do not move the
 *     copy either; pinning the loop web alone collapses allocation to 21.6%.
 *   loop-head spelling: named base + `mid->next` vs `*(s32 *)(mid+0xC)`,
 *     s32 / char* / s32* typed mid, staged `tv = (s32) mid` temp, volatile
 *     cursor store, comma-expression forms (`a = b, c = d`, `(a = b, e)`),
 *     and load-first source order (75.7%) — all 86.5% or worse.
 *
 * Parking family: doc-15 (call-arg-setup/expand_call emission order) cousin —
 * an issue-01-free pure ProDG regalloc/scheduling artifact, allocator-quirk
 * relative of the §6w-98 / §6y-124 pin cases.  NOT doc-06/PS, NOT
 * §6n-1 doc-14, NOT a stale-marker problem (range/size re-checked against
 * symbols.txt: 0x8000A0A8 + size:0x94 = 0x8000A13C, marker agrees).
 */
