# 33 — Inlined-iterator volatile/register webs (list-op family)

**Status: PARTIALLY SOLVED (2026-09-22; WALL 1 SOLVED 2026-09-25).** The
**stack-homed iterator slots recipe** below reproduces retail's caller-saved +
spilled iterator webs exactly and cracked the first members of the class. On
2026-09-25 WALL 1 (the loop-tail load order that capped every call-style
walker at ~80%) was **closed** by splitting each volatile-slot reload into its
own per-use-site variable — 4 members promoted EXACT. The larger 0x8013xxxx
walks (signature #3/#4 dead-arm survivors) are still OPEN, as are WALL 2
(guard rotation, fn_8007E030) and WALL 3 (per-byte parameter homing,
fn_8006239C).

## SOLVED LEVER (2026-09-22) — stack-homed iterator "slots" struct

Retail frequently homed the GetFirst/GetNext iterator state (head + cursor) in
**caller-saved registers that spill to the stack across the body's `bl`**, not
in callee-saved r30/r31: frame `stwu r1,-0x18` with *no* `stmw`, slots at
`8(r1)` and `0x10(r1)` (8 bytes apart) and a post-`bl` reload from those slots.
Plain-local C makes ngccc use callee-saved r30/r31 instead (`stmw`, frame
0x10), so every downstream register shifts and the draft scores ~8%.

The proven source shape (copied from the promoted sibling **fn_80061140**,
0x80061140, and reused verbatim in **fn_80061F34** — promoted EXACT 2026-09-22):

```c
struct {
    void * volatile slot208;   // head
    s32 pad20c;                // spacer -> puts slot210 at +0x10
    void * volatile slot210;   // cursor
} slots;
...
slots.slot208 = head;
if (head) cursor = head->unk0x4; else cursor = NULL;   // else-arm matters
slots.slot210 = cursor;
if (cursor != head) {
    do {
        ... ;
        cur_tmp = (T *)slots.slot210;
        head_tmp = (void *)slots.slot208;
        temp_r0 = (void *)cur_tmp->unk0x4;
        slots.slot210 = temp_r0;
    } while (temp_r0 != head_tmp);
}
```

Calibrations (measured on the 0x80061xxx family):
- **`volatile` on the cursor is load-bearing** — it forces the store/reload
  homing; a plain local goes to callee-saved. **The head member is volatile
  only when want reloads it in the loop tail** (fn_80061F34: `lwz r11,8(r1)`),
  and must be **NON-volatile when want keeps the head in a live register**
  (fn_80062250: `mr r6,r9`, never reloads 8(r1)) — volatile-head there = 61.7%,
  non-volatile-head = 83.0%.
- **The `pad20c` spacer is what sets the 8-byte slot spacing** (slots at 8 and
  0x10). Without it the slots land at 8/0xc and the frame is 0x10, not 0x18.
- **The NULL default must be the `else` arm** (`if (h) c = h->next; else c =
  NULL;`) — the `c = NULL; if (h) c = ...;` form schedules `li r0,0` before the
  head compare (78.7% vs 83.0% on fn_80062250).
- Transferable across the family: fn_80061F34 went 7.7% → **EXACT 100%** by
  swapping only the iterator prologue/loop tail to the sibling's shape;
  fn_80062250 (bit-set/clear walk) went 0% → 83.0% with the same struct.

Diagnostic: scan for a want prologue that is `stwu` with **no `stmw`/`stfd`**
but contains a `bl` followed within a few insns by `lwz rX, 8(r1)` /
`lwz rX, 0x10(r1)` (stack-homed iterator), and an m2c draft scoring <10%.

### The whole 0x8006xxxx / 0x8007Exxx family (2026-09-22 sweep)

A byte-signature scan (`lwz rX,0x10(r3)` + `stw rX,8(r1)` + `lwz rX,0x10(r1)` +
no `stmw`) finds **14 members**; 12 of them are in `src/wip` and all were
decoded and redrafted with the recipe above:

| addr | before → after | note |
|---|---|---|
| `fn_80060F44` | 4.0 → **EXACT 100%** (promoted) | head stays in a **register** (leaf, no `bl`): `void * slot208` **non-volatile** is load-bearing here; test uses `next != slot208`. |
| `fn_80060C60` | 36.7 → **100.0** (promoted 2026-09-25) | was "tail-order wall" — SOLVED, see WALL 1 |
| `fn_800624AC` | 0 → **100.0** (promoted 2026-09-25) | same wall, SOLVED |
| `fn_8007E3E4` | 0 → **100.0** (promoted 2026-09-25) | same wall, SOLVED |
| `fn_80062438` | 17.2 → 82.8 | three-var tail + `goto test` entry; r11/r9 color swap left |
| `fn_80062250` | 0 → 85.1 | negated-hash disjunct (semantic); `li r7,1` tail hoist left |
| `fn_8007E030` | 13.3 → 35.0 | guard-rotation fork (below) |
| `fn_8006239C` | 5.1 → 25.6 | per-byte parameter homing wall (below) |
| `fn_80062594` | 12.1 → **100.0** (promoted 2026-09-25) | three-var tail + **unmasked bitfield assign** |

### ~~NEW WALL 1~~ SOLVED 2026-09-25 — loop-tail load order: split the RELOAD, not the slot

**This wall is closed. It was never a scheduler problem — it was a reused
temporary.** The original analysis kept trying to *reorder two statements*; the
fix is to give **each use site its own C variable**.

want's loop tail is
`[reload slot210 -> r11][reload slot208 -> r11][next = cur->unk0x4 -> r0][cmpw][stw slot210][bne]`
i.e. the cursor slot is read **twice** (once for the callee argument, once for
the next-pointer) and the head slot **once**, in between the two cursor reads.
With one shared `cur` temp, ngccc collapses the two cursor reloads into a single
`r9` web and sinks the head reload after the volatile store, because the store
cannot be crossed. With the reads spelled as **three distinct variables**, the
three webs stay distinct and the exact order falls out with no pins, no flags
and no statement reordering:

```c
do {
    curA = (CStruct *)slots.slot210;      /* r11 — callee-arg load */
    fn_8005F188(*(s32 *)curA->unk0x0, arg1);
    curB = (CStruct *)slots.slot210;      /* r9  — next-pointer load */
    hd   = (CStruct *)slots.slot208;      /* r11 — head reload, IN BETWEEN */
    next = (void *)curB->unk0x4;          /* r0 */
    slots.slot210 = next;
} while (next != (void *)hd);
```

The split must be **by use site, not by slot** — that is why the earlier
`head local before next` experiments (36.7 / 29.0 / 58.1) all failed: they
introduced a *second* variable for slot208 while still reusing ONE variable for
the two slot210 reads. All four wall-1 members went 80% → **EXACT 100%**:

| addr | before → after |
|---|---|
| `fn_800624AC` | 80.6 → **100.0** (promoted) |
| `fn_80060C60` | 80.0 → **100.0** (promoted) |
| `fn_8007E3E4` | 80.0 → **100.0** (promoted) |
| `fn_80062594` | 17.1 → **100.0** (promoted) |

`fn_80062594` needed a second, independent lever for its earlier 17%: the
`0x48` bit-set is a **bitfield view assigned the RAW value** (`f4 = arg1`, no
`& 1`) so ngccc fuses the zero-accumulator `li` + `rlwimi` insert. The
mask/or spelling emits `rlwinm`+`or`+`or` instead; masking the assigned value
(17.6%) also breaks the fusion. Recipe: **an `rlwimi` whose source is a
zero accumulator means the field was assigned unmasked** — see §6n recipe 110
for the general bitfield-insert rule.

`fn_80062438` (the accumulate variant) also picked up the three-var tail but
needs the `goto test;` entry as well (want branches to a *shared* test block,
so a plain `while` rotates the guard away): 65.5 → **82.8%**, capped only by a
scratch-color swap of `curB`/`hd` (r11↔r9) that 6 declaration-order perms and 4
renames cannot reach — it wants a `register ... __asm__("r11")` pin.

`fn_80062250` (the bit set/clear walk) got a *semantic* fix instead: the guard
disjunct is the **negated** hash test, `(arg1 == node->unk0x8) || (arg1 !=
0xC4E78E22)`, not m2c's `|| (arg1 == 0xC4E78E22)`. Probed all 4 polarity
spellings × 5 tail orders: the negated form is 85.1% regardless of tail order,
so this is branch polarity, not scheduling. Residual is the loop-tail `li r7,1`
hoist (see §4p-17 / AGENTS §6z-129 family).

### NEW WALL 2 — guard rotation when there is no `bl` (fn_8007E030)

Without a call in the loop, ngccc **proves `slot208 == head`** (the slot is
written once and never re-stored), folds the two tests into one and rotates the
entry guard. So the volatile/non-volatile head switch is a fork with no winner:
non-volatile head → correct tail order, rotated guard (35.0%); volatile head →
guard kept, tail reordered and +2 words (30.6%).

### NEW WALL 3 — per-byte parameter homing (fn_8006239C)

want homes four `s8` parameters to consecutive stack bytes with four `stb` and
then word-copies them into the call's by-ref temp; ngccc instead packs them into
one register with four `rlwimi` (and burns r31), shifting every later
instruction. A named 4-byte struct with member stores *and* with an initializer
list, `__attribute__((packed))`, a struct passed by value as parameter 2, and
four loose `s8` locals all still coalesce — best 25.6%. **Open question: what C
construct forces per-byte parameter homing in ngccc?**

## Signature (any of these in the masked diff ⇒ suspect this doc)

1. **Shared-volatile webs**: want routes {q,nctr,sel}→r11 and
   {container,firstitem,cursor}→r10 simultaneously (fn_8013BF38); got spreads
   them across r0/r8/r12 or steals an extra callee-saved home.
2. **Split-lis / init-interleave**: address materializations (`lis/addi`)
   interleave with head-init stores and `mr` arg-saves in the prologue
   (fn_8013DC7C: arg1→r31 saved FIRST, addr staged via freed r4).
3. **Dual-sentinel-tail loops**: loop tails test two sentinels and crossjump;
   want places the shared return-tail BETWEEN loop bodies, got emits it last
   (fn_8013B76C, fn_8013BB68).
4. **Inline-helper-boundary copies**: the only missing instructions are
   `mr rX, rY` boundary copies between what were separate inlined helpers
   (fn_8013C6F0: got is 11 insns short, ALL missing are `mr r10,r31`-class).
5. **Scratch-web recoloring**: macro structure byte-exact, residuals are pure
   short-lived web colors (got r0/r9 where want r10/r11) (fn_8013C950).

## Exemplars (sweep verdicts)

| Function | Size | Final % | Notes |
|---|---|---|---|
| fn_8013BF38 | 0x5F8 | 33.3% | was compile-FAIL; rebuilt from disasm; prologue+case-0 head EXACT (needs `-fno-schedule-insns`) |
| fn_8013CC84 | 0xD84 | ~2% pos / ~51% seq | semantic body fully reconstructed (arities, widths, lbl folds); case-2 out-of-line ordering ~300 insns resists |
| fn_8013B76C | 0x190 | 32% | saved-reg window 5 vs 6: want keeps lbl_8029F2C0 in r28 across 3 calls AND node3 gets own reg |
| fn_8013BB68 | 0x124 | 30% | &entry webs split call-arg reg vs saved r27 restores; start copied to r4 INSIDE memcpy block |
| fn_8013C950 | 0x334 | 30.9% | dispatch tree + 3 walk loops + frame exact; residual = coloring only |
| fn_8013E364 | 0xC4 | 21.7% | base-copy role mirroring (want r9/r8/r10 vs got r11/r10/r8); twin of BD50 wall |
| fn_8013DC7C | 0x168 | 16.5% | prologue init-interleave (signature #2) |
| fn_8013BD50 | 0xB8 | 24.4% | twin of BC8C (r9/r8/r10 roles) |
| fn_8013BC8C | 0xC4 | 25.0% | see above |
| fn_8013C6F0 | 0x260 | 23.4% | signature #4 exemplar |

NEAR-tier siblings (best partial states, retry first when new levers appear):
**fn_8013E870 97.4%**, fn_8013B5C4 96.4%, fn_8013B8FC 92.9%, fn_8013DEE0 80%,
fn_8013C548 75.5%.
additions (2026-08-24, zone 0x8013Fxxx — all DIFF-tier parks,
flags were literal no-ops on these bodies, 12+ lowerings each exhausted):
- fn_8013FC10 (360B): **SOLVED 2026-09-28** (5.6% → 100%). The recipe came
  from its promoted sibling **src/fn_8013F980.c** (twin-port): two rotated
  sentinel walks over stack-homed iterators, with the rodata2 descriptor
  constants stored+restored (volatile-survival). The port needed one extra
  thing this member's note never had — the sibling's `volatile`-field struct
  layout, which is what makes the redundant stores/reloads survive. 14 of 90
  instructions are emitted asm (15.6%, disclosed; under the 30% cap). See
  AGENTS §6bf.
- fn_8013F980 (188B, 40.9%): ctx {pad,walker,end}@sp8 over link-chain at
  `(arg0+0x30)->c`, sentinel -1→NULL; three opaque this-webs w(r9)/it(r7)/
  ld(r8) + count pinned r10 reproduce ALL redundant stores/reloads and the
  exit end-store; residual = helper-boundary mr placement (#4) + head ternary
  in-place overwrite then `or.`-copy to r11.
- fn_8013FA3C (336B, 12.7%): twin of F980, clear-bytes variant; d2 walk uses
  plain displacement access (no webs); arg0 live in r3 across both walks.
- fn_8013F818 (360B, 9.2%): max-tracking variant (returns max of byte +0x24/
  +0x18); same skeleton, same wall.

## Tried and exhausted (per-draft notes carry details)

6+ ternary/if/goto lowering shapes; all five ProDG versions (codegen-identical);
flag matrix `-fno-schedule-insns`, `-fno-schedule-insns2`, `-fno-sched-spec`,
`-fno-gcse` alone and paired; register pins incl. `"0"`-matched restores and
`__asm__("mr %0,%1")` walker wedges; opaque-copy wedges (`"=r"`, `"=b"`);
memory barriers; block reorders; duplicated-tail crossjump bait; tail-order
gotos; C++ frontend probe (same codegen). A GCC 2.95 rematerialization bug was
found on the way: `"+r"` barriers on r1-relative pointers DROP the offset.

## Root asymmetry (why it resists)

The game compiler ran the iterator inline BEFORE global regalloc saw the whole
function (or came from a build where the helper was `static` and inlined late),
so its dead `li`s and provably-redundant branch arms SURVIVE in retail bytes
(fn_8013B8FC entry chk-compare lands in r0 vs want r9 because want kept a
redundant arm). Stock GCC eliminates that dead code at every -O level; no
source form resurrects an eliminated instruction. Until a construct is found
that makes ngccc keep dead branch arms / reproduce helper-boundary `mr`s, this
family stays parked.

## Retry hints

- Crack ONE member ⇒ immediately retry the twins (BC8C↔BD50↔E364 share the
  role-mirroring wall; B76C↔BB68 the sentinel-tail wall).
- Any new way to force BLOCK ORDER (case-2 out-of-line in CC84) likely
  unlocks the biggest single win (0xD84 body).
- The `-fno-schedule-insns` requirement on BF38's matching prologue suggests
  trying flag pairs FIRST on new members before structural work.

## (2026-08-23, fn_80171288 — 908B, ~5%)

Eight dead `mr rX,r6` (denominator) fills interleaved between the
7th-entry copy stores (r4,r10,r30,r29,r7,r28,r27,r5 — none read afterwards;
r30 even overwrites the arg0 home) plus a dead `mr r10,r11`, at
0x80171B4B8–14E8 / 0x80171370. Classic inlined-call argument-staging residue:
the fills occupy r27–r29 and therefore OWN want's stmw span (r26..r31, frame
0x178); every reconstruction lands on stmw r25..r31 / frame 0x188 instead,
and the regalloc roles (t=r10, idx live in r3 across the branch, ratio=f8)
hang off those webs. Secondary wall on the same fn: ONE shared stack slot
0x158/0x15c serves BOTH the int→f64 magic conversions AND the fctiwz/stfd/lwz
roundtrips of all three lerp components (see AGENTS.md §6aa-131) — ngccc gives
each cast a private slot. Retry this member together with the BC8C/BD50/E364
twins if a dead-code-resurrection construct is ever found.

 adjacent member (2026-08-24): fn_801A3ABC (900B, 43.4%) — FLOAT
scratch-web allocation variant of the same coloring class: page-anchor `lis`
homed in r30 vs want's per-site scratch anchors, ternary-select operand regs,
`fmuls` dest reusing a dead v31 vs fresh scratch. Everything semantic is
correct (2-arg field-passed fn_801ADCD0 per recipe 18, 0-arg fn_80124F44,
`(s32 ptr, hash)`->f32 fn_801F0610, corrected hash decode with SIGNED lis
trap, frame via 2 volatile doubles, fr30/fr31 pins). Retry when a lever for
float-web recoloring appears.

## 2026-09-16 — CRACKED (1 member): the webs ARE reachable — reassign ONE variable

`fn_8008076C` (384B) promoted to EXACT and its residual was exactly this class.
Retail colours ALL FOUR reloads of `node->unk0x14` (preheader check, the body's
`op[1]`/`op[2]` reads, and the trailing while-test) as **one** register (r11);
the m2c draft respelled the reload *inline inside each expression*, giving four
independent pseudos and four colours (r6 / r11 / r11 / r9).

The source shape that reproduces retail is a single variable **re-assigned from
the same memory expression before each use**:

    sub = *((void **)&node->unk0x14);      /* preheader, feeds the if-test */
    ...
    do {
        op[0] = ...sub...;                 /* peeled iteration reuses it */
        sub = *((void **)&node->unk0x14);  /* real reload, SAME variable */
        op[1] = ...sub...;
        sub = *((void **)&node->unk0x14);
        op[2] = ...sub...;
        ...
        sub = *((void **)&node->unk0x14);  /* last statement of the do-block */
    } while (... sub ...);                 /* so the bottom test reuses it too */

Every re-assignment is still a genuine load (the intervening stores block CSE),
but they all share ONE pseudo -> ONE colour.

**Tell:** a PEELED first iteration.  If want's first body use reads the value with
no preceding reload, the header check and the body reads are the same variable.
Do not reach for `volatile`, extra temps or `register` pins first — collapsing N
inline spellings into 1 re-assigned variable is the move that works.

## 2026-10-07 — SOLVED: the 12-byte-iterator frame + two-web walls (fn_8000B6F8)

`fn_8000B6F8` (0x8000B6F8, 248B) went **88.7% → 100.0% (0 diffs)** and was
promoted.  It is the member of the fn_8000BD04 family (BD04 / BA88 / BB70 /
BC4C all park on these same two walls), so the recipe below applies to all of
them:

```c
void fn_8000B6F8(Holder *arg0) {
    s32 scratch;            /* 4-byte address-taken scalar: the ONLY decl
                               shape that makes ngccc materialise a per-use
                               address pseudo (a struct/array decl folds,
                               giving ONE `addi rX,r1,8` and no `mr`) */
    s32 pad1, pad2;         /* keep-alive pads, see below */
    ...
    ((It *)&scratch)->f08 = (s32)lbl_802901D8;
    ((It *)&scratch)->f04 = arg0->f20;
    ...
    while (v != 0) {
        register Nd *lnode __asm__("r11");   /* zero-emission register pin */
        fn_8000BEEC(v);
        lnode = ((It *)&scratch)->f04->f0C;
        ...
    }
    __asm__("" : : "m"(pad1), "m"(pad2));    /* zero-emission keep-alive */
    ((It *)&scratch)->f08 = (s32)lbl_802901D8;
}
```

**WALL 1 — frame base (`addi rX,r1,8` vs `r1+0x10`), locals [8,0x18), frame
0x20.**  Rules established by ~30 measured forms:
- an **address-taken scalar is allocated LAST**, i.e. ABOVE every other live
  local, whatever the declaration order;
- a **volatile** object is allocated FIRST, i.e. at offset 8, so a
  `volatile s32 pad[2]` always pushes the iterator to r1+0x10 (this is the
  exact shape both fn_8000BC4C and fn_8000BD04 parked on);
- a **struct/array** object of the right size IS placed at r1+8 (12 bytes at
  8 → locals [8,0x18) → frame 0x20, `stmw r30,0x18`, LR 0x24 — all match),
  but it folds the address and loses the second web;
- pure-C pads are DCE'd (`pad = 0`, `pad = pad`, `(void)&pad`, `s32 pad[1]`,
  self-address compares) and the frame collapses back to 0x18.
- **FIX:** plain `s32` pads + a zero-code memory-constraint barrier
  (`__asm__("" : : "m"(pad1), "m"(pad2));`) after the body.  0 emitted
  instructions, pads land above the iterator, frame/prologue become exact.
  (Not a hack unique to this function: the promoted `fn_801F9F2C` uses the
  same barrier.  Place it AFTER the pads' last "use" — end of body works.)

**WALL 2 — in-loop walk register (r11 vs r9), 6 words.**  want's in-loop child
load is `lwz r11,0xc(r9)` with the reload base in r9; ngccc reuses r9 for the
child in **every** pure-C spelling measured (`node = it.f04->f0C`, split
`cur`/`nxt`, two-statement same-variable, ternary vs if/else, `(void)cur`
keep-live).  An if/else spelling does produce r11 but loses the select shape
(26 diffs).  `register Nd *lnode __asm__("r11")` on the **loop-only** walk
variable emits 0 instructions and is exact; the pre-loop walk needs no pin
(its base is a register, not a reload, and lands r9 naturally).

Measured ladder: 88.7% (pads only) → 90.3% (barrier only) → 98.4% (pin only)
→ **100.0%** (both).  Emitted asm share: 0 of 62 instructions.

**Retry hint for the twins — DONE 2026-10-08, WALL 1 closed on all three.**
The lever *does* close fn_8000BC4C / fn_8000BD04's WALL 1 (the unresolved
`addi r9,r1,0x10`), and it also fixes fn_8000BB70's frame (0x10 -> 0x18) once
its iterator is switched to the address-taken-scalar form:

| fn | before | after | note |
|---|---|---|---|
| `fn_8000BD04` | 40.0%, `addi r9,r1,0x10` | **42.22%**, `addi r9,r1,8` | first 18 words == want |
| `fn_8000BC4C` | 40.0%, `addi r9,r1,0x10` | **42.22%**, `addi r9,r1,8` | byte-for-byte twin |
| `fn_8000BB70` | frame 0x10, no base reg | **6.52%**, frame 0x18 == want | iterator -> `s32 sp8` + `((It *)&sp8)` first |

**The placement of the barrier is the whole trick.** The 2026-10-03 round had
already measured this barrier on BC4C but inserted it *after the node's first
store* and reported a net loss (it let cc1 CSE the `lbl_802901D8` address and
hoist the final vtable store). Inserted at the **end of the body**, immediately
before the trailing `it.f08 = lbl_802901D8`, neither happens and the prologue
comes out byte-exact. If a future member rejects the barrier, try the other
end before giving up on it.

WALL 2 (the pre-loop `li r11,0` dead store + merge) is **unaffected** by either
lever, confirmed by re-measuring five spellings *with* the barrier in place:
`p = p ? p->f04 : 0; v = p;` (176B), ternary into the pinned var (180B),
`goto Lzero/Lmerge` (176B), `switch (p != NULL)` (200B), and an extra
`it.f04 = p` write-back before the value read (180B). Want keeps a real merge
(`li r11,0; b .B; .A: lwz r11,4(r11); .B: or. r3,r11,r11`) while ngccc proves
the zero arm and jump-threads it past the merge. That is the family's root
asymmetry (see above), not a scheduling choice.

**Member — `fn_80219B18` (328B, integer-only, two iterator locals): 316B, 3
words short.**  Same family, and the residue lands on both walls above.

- Body: two 0x10-byte iterator locals (`a` at r1+8, `b` at r1+0x18), each
  `{s32 pad; s32 cur; void *vt; s32 pad2;}`, with `vt` set to lbl_802A83F8 /
  lbl_802A8030 in the prologue and reset before the return.  Walk 1 is
  `fn_8021D454`/`fn_8021D4E8(arg0, &a, 0)` and is byte-identical here; walk 2
  is the inlined GetNext idiom of the promoted twin `src/fn_8021D454.c`
  (`*(cur+0xC)`, with a `-1` in its `+0x4` meaning end of chain).
- Only one spelling keeps want's **duplicated entry test**: the advance block
  inlined as a helper that returns the node, called once before the loop and
  once at its end (312-316B).  The same block written out twice puts the loop
  in do/while form (272B); `while ((node = next(&b)) != 0)` (268B) and an
  if/else return inside the helper (272B) rotate it as well, and a `for` loop
  compiles identically to `while`.
- Residual, 3 words: WALL 2 at both walk-2 sites — want keeps `li r11,0; b`
  and `or. r11,r3,r3`, ngccc if-converts and jump-threads past the merge
  (`register ... asm("r11")` on the walk variable measures 316B here, i.e. no
  change, so the pin covers only WALL 2's *register* half); plus one prologue
  word — want builds `&a` in a volatile register and copies it into the
  callee-saved one the tail uses, and stores `b`'s `cur` through a freshly
  materialised `&b` while `b`'s `vt` store stays r1-relative.
