# Issue 26 — u64-shift libcall `crclr` scheduling (8011E0E4 / 8011DC88 family)

**Status: IMPROVED (2026-08-23) — old-style-proto fix applied at whole-function
scale.** Rebuilt E0E4 and DC88 bodies from disasm with `u64 fn_80273480();` /
`u64 fn_80273B68();` everywhere (replacing inline-asm `crclr 6` + new-style
protos): ALL crclr sites + r3:r4 returns now match; E0E4 36.75% → **43.59%**,
DC88 33.56% → **39.73%**. Residual is the LOOP REGION only: retail loads
`count` via `lwz r0 → mr rCS`, reuses arg regs for `i`, materializes the
store-zero const in r26/r24-page, and reloads field pairs per-iteration into
callee-saved homes — GCC instead hoists the load out of the loop or loads
direct-to-arg-regs. Resisted: staging temps, assignment-in-call, split 32-bit
loads, while-forms, memory-clobber barriers (GCC 2.95 does NOT invalidate
register-held copies across asm memory clobbers — important negative),
register pins (they corrupt incoming-arg delivery), all sched flags (regress).
Same allocator wall as the D870 exemplar.

---

# ORIGINAL ANALYSIS (historical)

**Status:** PARKED (M8.xx). Partial fix PROVEN — see "What works"
below; the residual is scheduler placement of the crclr at multi-call sites.

## The problem

The game computes 64-bit shifts with helper calls to two 64-byte functions:

- `fn_80273480` = `__ashldi3` (u64 `<<`)
- `fn_80273B68` = `__lshrdi3` (u64 `>>`)

WANT emits, before EVERY such `bl`:

```
crclr cr1eq
bl fn_80273480          ; returns r3:r4 pair
```

Three ways to get the call into C, each failing differently:

| Form | crclr | r3:r4 result | Verdict |
|---|---|---|---|
| natural `x << n` on `unsigned long long` | exact | exact | **unlinkable** — ngccc emits references to libgcc symbols (`__ashldi3`) that don't resolve in this link |
| new-style proto `u64 fn_80273480(unsigned long long, int);` | DROPPED | exact | loses the crclr word |
| **old-style proto `u64 fn_80273480();`** | **exact** | **exact** | WORKS — proven on `src/wip/fn_8011D870.c` |

So the call itself is fully solvable: declare the helpers OLD-STYLE
(`u64 fn_80273480();`, no param list) and ngccc reproduces both the `crclr
cr1eq` AND the r3:r4 pair return. This mirrors recipe 21/60 (unprototyped /
old-style forms preserve cr-setup) extended to 64-bit pair returns.

## The residual blocker (why E0E4/DC88 stay parked)

At functions with MANY shift-helper calls interleaved with other calls
(E0E4: 6 sites; DC88: same family + regalloc drifts), the scheduler floats
the crclr above the call-arg setup or merges paths differently than WANT at
~half the sites — a ~4-word cascade per misplaced site. Inline-asm crclr
(`__asm__("crclr 6")`) matches the single word but the scheduler then moves
it. DC88 additionally has count-copy/mask-temp register-home drifts.

**Retry hint:** rebuild E0E4/DC88 bodies on the D870 old-style-proto shape
(concurrent agents discovered it independently — group 4 never tried it),
then attack only the remaining site-order diffs.

## Where to look

- Working exemplar (old-style protos): `src/wip/fn_8011D870.c` lines 22-23.
- Parked members: **drafts removed** — `src/wip/fn_8011E0E4.c` and
  `src/wip/fn_8011DC88.c` were deleted in commit b7cf86e9 (2026-08-23
  src/wip cleanup); both functions remain unmatched auto-asm. Regenerate the
  drafts (`tools/fill_wip_drafts.py --addr 0x8011E0E4 / 0x8011DC88 --force`)
  or hand-rebuild per the recipe before retrying the loop-region wall.
- Helpers: `symbols.txt` `fn_80273480`/`fn_80273B68` (.text, size:0x40).
- Related: AGENTS.md recipes 21/60 (old-style/unprototyped calls keep
  cr-setup), doc 15 (call-arg-setup scheduling).
