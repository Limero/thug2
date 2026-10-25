# 82 — ngccc switch case-tree: no-`default` dispatch, `u8` case temps, and the `p += N` / `return p` pointer-copy wall

**Status: SOLVED — `fn_8012B2A0` (QB text-token walker, 436B) is byte-exact
(109/109 words) and promoted; the DOL stayed byte-identical.** Five switch/dispatch
rules plus the varint-tail register recipe below are what it took.

All findings verified on ProDG/3.9.3 with the default game flags
(`-O2 -G0 -mcpu=750 -fno-common`), no asm bodies.

---

## 1. A large sparse `switch` needs NO `default:` clause

The retail body is a ~74-case byte `switch` whose decision tree has **25 compare
pairs** and no jump table. `ngccc` reproduces that tree *exactly* — but only when the
source has **no `default:` label** and instead falls out of the switch:

```c
u8 *fn_8012B2A0(u8 *p) {
    u8 op = p[0];
    switch (op) {
    case 0x00: break;                    /* <- explicit, empty body */
    case 0x01: /* ... 47 labels ... */ p += 1; break;
    ...
    }
    return p;                            /* <- everything unlisted lands here */
}
```

Why it matters (measured, `fn_8012B2A0`):

| source | root node of the emitted tree |
|---|---|
| 30 clusters **+ `default:`** | `cmpwi 0x2b; beq` — node = **0x2B** (wrong) |
| 30 clusters, **no `default:`** | `cmpwi 0x2d; bgt / cmpwi 0x2c; bge` — node = **0x2C-0x2D** (retail) |

`default:` is an extra node in GCC's `balance_case_nodes` count, so adding it shifts
the balanced split one cluster to the left. Same effect, smaller: listing the *other*
five empty `case` labels that share the default body (`0x10/0x19/0x1D/0x2A/0x31`)
also pushes the root back onto 0x2B. **Rule: for a byte-valued dispatch whose default
is a no-op, write the empty `case` you need and let the post-switch `return` handle
the rest — do not write `default:`.**

Corollary (same file): the retail 3-way leaf is `cmpwi 1; beq; bgt; blr`
(one threshold used twice). Reproducing it needs **one explicit empty `case` label
in that subtree** (`case 0x00: break;`) so the node has three clusters; with only
`{0x01,0x02}` ngccc emits `cmpwi 1; beq; cmpwi 2; beq` (two thresholds) instead.
Adding that one label: 14.3% → 64.9%.

## 2. The case temp's *type* is load-bearing — use `u8`, never `u32`

Retail compares are opcode-11 (`cmplwi`, unsigned). With the m2c default
(`u32 op = p[0]`) ngccc emits **two** compares per range test
(`cmpwi X; beq; cmplwi X; bgt`) because it cannot prove the sign; with `u8 op` (or
`switch (p[0])` directly) it emits the retail single unsigned test.

`fn_8012B2A0`: `u32 op` 4.3% → `u8 op` 16.4%. Same tree, different range tests.

## 3. `return p + N` inside switch arms makes ngccc copy the cursor

With a per-arm `return p + N`, ngccc allocates the cursor pointer to r8/r9 and
inserts `mr r8,r3` at entry, and the shared default tail becomes `mr r3,r8; blr`.
Retail keeps the cursor in **r3** the whole time (`lbz r0,0(r3)` … `addi r3,r3,1`).

The fix is not a pin, it is the shape: **mutate `p` in the arm, `return p` once after
the switch.**

```c
switch (op) {
case 0x01: /* ... */ p += 1; break;
case 0x1B: /* ... */ p += 1; p += v; break;
}
return p;
```

`basic_block_reorder` then merges the single post-switch `blr` into each tail, giving
retail's `addi r3,r3,1; blr` pairs with no copy. 2.7% → 14.3%, and combined with §1
it is the difference between a 468B and an exactly-436B object.

A corollary that matters: **`p += N` in only some arms is not enough** — every arm
that needs to reach the tail must do `p += N; break;`, including the ones that
"return nothing" (which is exactly why the empty `case 0x00: break;` of §1 works).

## 4. Increment-then-load, not load-then-increment, or you lose the `lbzu`

Retail's skip-string and varint bodies are chains of **`lbzu`** (load byte and bump
the base). ngccc only fuses the increment into the load when the load reads the
*already-incremented* pointer:

| source | emitted |
|---|---|
| `v = p[5]; p += 5;` | `lbz r11,5(r3)` + `addi r3,r3,5` (**not** fused) |
| `p += 5; v = *p;` | `lbzu r0,5(r3)` ✓ |
| `v = *p++;` | `lbz r11,0(r3)` + `addi r3,r3,1` (**not** fused) |
| `v = *++p;` | `lbzu r0,1(r3)` ✓ |

Same rule as recipes §4p store order, applied to the pointer: **the statement that
bumps `p` must textually precede the dereference that should fold into it.**
`fn_8012B2A0`: 71.2% → 80.7%.

Note also that the string-loop byte and the varint accumulator must be **separate
locals** (`u8 c` vs `u32 v`); sharing one variable puts both in the same register and
costs the retail `r0` in the loop (80.7% → 82.6%).

## 5. Tail-block layout follows ARM SOURCE ORDER, not case-value order

`basic_block_reorder` emits the arm bodies in the order they appear in the source.
Retail's tail order is `+1, +5, +0xD, +9, varint, strskip, varint*6, +3` — i.e.
`0x1E`/`0x1F` are written **before** `0x1B/0x1C`, which is not case-value order.
Reordering the arms to match: 64.9% → 71.2% and the object reaches exactly 436B.

## 6. The varint tail: one pin, one anonymous temp, two `<<=` temps

The four byte lanes are `lbzu r9` (accumulator `v`), `lbzu r0`, `lbzu r11`,
`lbzu r10`, and the 16/24-bit shifts stay **in place** (`slwi r11,r11,16`,
`slwi r10,r10,24`). Spelling that reproduces it:

```c
v = *++p;
v += *++p << 8;      /* anonymous: first extra byte lands in scratch r0 */
b2 = *++p; b2 <<= 16; v += b2;
b3 = *++p; b3 <<= 24; v += b3;
```

with

```c
u32 b2;
register u32 b3 __asm__("r10");
```

* `b2`/`b3` must be `u32` with `<<=`. A `u8` temp, or the expression form
  `v += b3 << 24;`, lets combine fold the shift into the add and the byte read goes
  through the scratch register (94.5%, or a 356B object when all four fold).
* **The pin on `b3` is the whole residual.** Unpinned, `b3` colours `r0` — the same
  scratch the anonymous first temp used — so the add reads `r0` instead of retail's
  separate `r10`. Pinning it to `r10` produces retail's extra copy and the function
  is byte-exact.
* Every other lane order / declaration order is inert (pseudo uid does not decide the
  post-reload rotation), and `-fno-schedule-insns2` is **not** needed once the pin is
  in place: the pinned body is exact at DEFAULT flags (`-fno-schedule-insns2` was a
  crutch for the unpinned body's accumulator colour).
* The multiply tail stays `v *= 6; p += v;` (gives `mulli r9`).

## Trap worth knowing

Four `u8` temps accumulated one at a time (`v += b1 << 8; ...`) are **required**;
writing the whole varint as a 32-bit byte-swap lets combine fold it into a single
access (`lbzu r0,1(r3); addi r3,r3,4; add r3,r3,r0`, 356B object). If a want shows a
`lbzu` chain of four byte loads, do not "simplify" the shifts — and note that the
`<scratch>` colour of an unpinned temp is what tells you a pin is missing.
