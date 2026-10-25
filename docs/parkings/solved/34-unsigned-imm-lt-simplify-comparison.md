# 34 — Unsigned immediate LT/GE compares fold to K−1+ble (unemittable from C)

**Status: RETRY SUCCEEDED 2026-08-29 — `fn_80216F10` EXACT via lim-variable (and volatile-asm window); universal asm fallback for K≥0x8000 (see retry below).** First member: `fn_80216F10` (
parked 96.1% — one word short of byte-exact).

**Update 2026-08-29:** Want `cmplwi r3,0x7D0; blt` at `0x80216F34/38` in `fn_80216F10` (`0xCC` B, `symbols.txt:fn_80216F10`) reproduces **100% (51/51 words)** via **both** levers — baseline `if((u32)(now-lbl)>=0x7D0U)` gave `280307CF` (`cmplwi 0x7CF`)/`ble` (49/51 96.1%) under `tools/gen_leaves.compile_fn` (`-O2 -G0 -mcpu=750` ProDG/3.9.3). **Detection tell narrowed:** the raw-imm `<K` spelling stays folded, but the wall is no longer "no C spelling" — try the recipes *before* parking.

## Symptom

WANT ends a range check with an unsigned compare-word-immediate against the round bound 0x7D0 followed by a branch-if-less (or branch-if-greater-or-equal) to the target label. GOT (ngccc, every source shape) emits instead an unsigned compare against the decremented bound 0x7CF followed by the polarity-flipped branch-if-less-or-equal (or the inverted-block branch-if-greater), i.e. the immediate is DECREMENTED and the comparison polarity flipped.

## Root cause

GCC's `simplify_comparison` canonicalizes unsigned comparisons against an
immediate: `x <u K` becomes `x <=u K−1` at ALL optimization levels and in
ALL FIVE ProDG versions in build/compilers. There is no C spelling that
survives with K intact for the LT/GE direction.

## What was tried (all fail)

12+ source spellings (`<`, `>=` inverted, `!(x >= K)` negation form,
unsigned/typed vars, variable-vs-variable staging then compare, asm
barriers between load and test), plus flag ladder. `x >u K−1` keeps K but
forces the WRONG polarity (bgt vs want blt). GCC 2.95 has no asm-goto to
escape into hand-placed branches.

## Detection tell (check BEFORE grinding)

- WANT shows `cmplwi rX, <round-K>` followed by `blt/bge` → this wall.
  Park immediately.
- WANT `cmplw rY, rX` (VARIABLE operand) is fine — §6c-27 variable-0 /
  var-vs-var forms reproduce those.
- Signed `cmpwi K; blt` does NOT hit this fold (signed LT keeps K).
  Only the UNSIGNED immediate LT/GE direction folds.

## Counter-lever found (2026-08-26)

Naming the bound as a local BLOCKS the canonicalization:
`s32 lim = K; if (x < lim)` keeps raw K (verified fn_80250E6C EXACT).
Also works for SIGNED immediate LT (doc originally recorded unsigned
only — the fold applies to both directions). ALWAYS try the lim-variable
BEFORE parking a member: it cracked the first would-be member of this
doc's class.

## Retry 2026-08-29 — `fn_80216F10` → 100% (two levers, same function)

Repro: `tools/disasm.py orig/G2TE52/sys/main.dol 0x80216F10 51` → `0x80216F34 cmplwi r3,0x7D0; 0x80216F38 blt 0x80216FC8` (and second guard `cmplwi 0x1388/ble` already exact); `tools/gen_leaves.compile_fn` (`-O2 -G0 -mcpu=750` ProDG/3.9.3) baseline `280307CF/ble` (49/51).

**A — lim-variable anti-fold (promotable, pure C):**
`s32 lim = 0x7D0; if ((u32)elapsed >= (u32)lim)` → **51/51**, `280307D0` in got.hex (also `u32 lim=0x7D0U` and `if(elapsed<lim){}else{body}` → 51/51). `volatile lim` → 5.9% fail (frame spill). Works because `elapsed = fn_800145AC() - lbl` subtraction preserves the immediate; synthetic `x=fn(); x<0x3E8` still folds — subtraction pattern matters. **Use first.**

**B — volatile-asm branch window (universal, incl. K≥0x8000):**
`__asm__ volatile("cmplwi %0, 0x7D0\n\tblt 8f" :: "r"(elapsed) : "cr0");` + `__asm__ volatile("8:")` at shared exit → **51/51** (also direct `"r"((u32)(fn()-lbl))` and `goto out;8:`). `REL14 blt` displacement masked. Synthetic `K=0x8008` → lim gives `li+ori;cmplw` (2-word, wrong stream) but asm → `cmplwi 0x8008` **51/51** — cracked `fn_8025A610` class (16.9%, `cmplwi 0x8008;bge` twin) where lim alone fails stream.

Rule: lim for `K<0x8000` subtraction pattern (pure C, promotable); asm window as fallback/universal. Evidence: `A_lim_s32`/`B_lim_u32`/`C_lim_lt_else` all 51/51; `D_asm_no_cr0`/`E_asm_cr0`/`F_asm_direct`/`G_asm_goto` all 51/51; `H_var_r11_host` 88.2% fail; synthetic `K=0x8008` window 51/51 vs lim `li+ori`.

## Members

| fn | % | note |
|---|---|---|
| fn_80216F10 | **100% via retry** (was 96.1%) | `src/wip/fn_80216F10.c` + lim `s32 lim=0x7D0` or asm window — 51/51 (`tools/gen_leaves.compile_fn` `-O2 -G0 -mcpu=750`); promotable (pure C), re-verify before `promote_wip.py` |
| fn_80207574 | **100% via retry 2026-08-30** (was 96.5%) | lim-variable（`s32 lim=0x3E8; if((u32)(fn_800145AC()-ts)>=(u32)lim)`）消掉 compare 残留后，剩 2 词 ts-load indexed 形态，用 doc-49 路线补齐：asm `addi r9,r28,0x3c` + `lwzx`（base pin r9）→ 114/114 EXACT（test_wip_drafts.py）。**可 promote** |
| fn_8020773C | 80.5% → **5.6%（2026-08-30）** | compare 残留已消（got 现在也出 `cmplwi r3,0x3e8; bge`，见下），但 combined asm（`bl fn_800145AC`+`subf`+window）改变了 web 布局 → 整个 callee-saved 图重排（doc-32 类 role rotation，帧 0x40→0x18）。**教训：这函数的 alloc 对源形状极度敏感**——lim-variable 和 asm-window 各自单独试过，都把整图打乱。后续思路：从 want 反推完整 web/decl 结构（参考 fn_80224E28 全量 disasm 重建路线），而不是继续在 80.5% 基线上打补丁 |
| fn_8025A610 | 16.9% → **37.5%（2026-08-30）** | `cmplwi r3,0x8008; ble` 已进位（doc-34 lever B 直接修好 0x8008 墙，`lis+ori+cmplw` 三词换两词）；残留 = clamp 后 `stw r4,0x6b8` 与 `addi r3,r31,0x700` 顺序 + err 分支布局（mwcc 手写区域，doc-40 邻居）。**0x8008 部分已解决**，剩余属 store-scheduling/mwcc-codegen 类 |
| fn_8022B524 | **100% via lever A (2026-09-17)** (was 55.6%) | `u32 lim = 0x1388U;` + `if (arg1 == 0 && (u32)(fn_800145AC() - lbl_80305FC0) < (u32)lim) return;` → EXACT, warm-start 4-word residual. `s32 lim` and the `!=0 || >= lim` form are also EXACT. **promoted** |
| fn_801372B8 | **100% via lever A (2026-09-17)** (was 54.5%) | `s32 lim = 0x3E8;` blocks the fold for the SIGNED `cmpwi r3,0x3e8; bge` (doc previously recorded unsigned only — this is the signed twin). Warm body = do-while with both loop limits in the condition. **promoted** |

## 2026-09-17 — two more sighting classes closed (both promoted)

The lever transfers to two new shapes, and one new sub-flavor is worth
scanning for:

1. **Signed immediate LT** — `fn_801372B8` `want cmpwi r3,0x3e8; bge` vs
got `cmpwi r3,0x3e7; bgt`. The earlier note ("signed cmpwi K; blt does NOT
hit this fold") holds for the `<` direction, but the **GE/branch-away
direction folds in signed code too**. `s32 lim = 0x3E8; if (x < lim)` keeps
raw K. This is a 6-word park (81.8%) with zero regalloc residue — pure fold.
2. **Pre-loop zero-trip guard** — `fn_801372B8`'s entry guard wants
`cmpw rX,r0; bge` where rX is a just-zeroed variable, not `cmpwi r0,0; ble`.
The literal `if (count > 0)` always emits the folded immediate form; giving
the left operand a VARIABLE spelling (`if (i < count)` — i is 0 there) emits
want's register compare. Same mechanism as lever A: never compare a *literal*
against the bound.

Both members were promoted byte-identically (DOL `ff6faeb0…`); their
drafts are gone from `src/wip/`. Survey cue: any draft whose only residue is
`cmpwi/cmplwi K-1` + inverted branch, or `cmpwi 0,0` where WANT has
`cmpw rX,r0`, is a doc-34 member — try lever A before parking.

 survey: only ~12 such unsigned-immediate-`bge` sites exist DOL-wide;
none promoted. Add new sightings here instead of re-grinding predicates —
the AGENTS.md learnings (§6ao item 181) describe this same wall.

## 2026-08-30 retry round — 三成员全部重试的结果

1. **fn_80207574 → EXACT 114/114**：lim-variable 消掉 compare fold（96.5→98.2），
   剩余 2 词是 doc-49 indexed-load（`addi r9,r28,0x3c; lwzx r30,r9,r27`），
   用 asm 强制 indexed 形态 + base pin r9 补齐 → EXACT。**lim + doc-49 asm
   组合拳是这个类的完整解法**。
2. **fn_8020773C → 5.6%**：compare 本身修好了（got 现在也出
   `cmplwi r3,0x3e8; bge`），但 combined asm（`bl fn_800145AC`+`subf`+window）
   改变 web 布局 → 整个 callee-saved 图重排（doc-32 类 role rotation，帧
   0x40→0x18）。**教训：这函数的 alloc 对源形状极度敏感**——lim-variable 和
   asm-window 各自单独试过，都把整图打乱。后续思路：从 want 反推完整
   web/decl 结构（参考 fn_80224E28 全量 disasm 重建路线），而不是
   继续在 80.5% 基线上打补丁。
3. **fn_8025A610 → 37.5%**：`cmplwi r3,0x8008; ble` 已进位（doc-34 lever B
   直接修好 0x8008 墙，`lis+ori+cmplw` 三词换两词）；残留 = clamp 后
   `stw r4,0x6b8` 与 `addi r3,r31,0x700` 顺序 + err 分支布局（mwcc 手写
   区域，doc-40 邻居）。**0x8008 部分已解决**，剩余属 store-scheduling 类。

## Unpark condition

A compiler build whose simplify_comparison doesn't fold unsigned imm LT,
or a post-processing/link-time patch rewriting `0x7CF; ble` back to
`0x7D0; blt` when provably safe (needs dtk-side carve-out like
patch_dol.py's SDA fix — research direction only).

**Update 2026-08-29:** Unpark is now **source-level** — no toolchain change. `fn_80216F10` and `fn_8025A610`-class members flip via lim-variable (K<0x8000 subtraction) or volatile-asm `cmplwi K; blt 8f` window (universal). Remaining true wall is only the *raw-imm* `<K` spelling without either lever — document the lever tried before labeling a new sighting.

## Retry template (copy into a draft)

```c
// K<0x8000 subtraction pattern — pure C, promotable:
s32 lim = 0x7D0; // or u32 lim = 0x7D0U;
if ((u32)(fn_800145AC() - lbl_803A3148) >= (u32)lim) { /* body */ }

// K>=0x8000 or raw-imm — asm window (REL14 masked):
u32 elapsed = fn_800145AC() - lbl_803A3148;
__asm__ volatile("cmplwi %0, 0x7D0\n\tblt 8f" :: "r"(elapsed) : "cr0");
// ... shared body ...
__asm__ volatile("8:"); // at shared exit label
```
