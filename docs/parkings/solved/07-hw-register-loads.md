# Issue 07 — 0xCC00 MMIO/HW-register *loads* (lis+ori vs lis+stb HA/LO split)

**Status: SOLVED — CLOSED 2026-08-26 audit.** The sole exemplar
`fn_80274ECC` (`__ARGetInterruptStatus`) is wired byte-exact via the
mwcc-routed AR module `libs/dolphin/src/ar/ar.c` (`[x] __ARGetInterruptStatus
(16B)` in PROGRESS.md). The per-object mw_version route below was executed;
nothing remains in this class.

---

**ROOT CAUSE (2026-08-23) — the parked `hwr` draft is MWCC codegen, not
ProDG.** The canonical SDK source compiled with the repo's own CRT compiler reproduces the want BYTES EXACTLY:

```
wibo build/compilers/GC/1.3.2/mwcceppc.exe -O4,p -c \
  'return (*(volatile u16*)0xCC00500A)&0x20;'
→ 3C60CC00 A003500A 540306B4 4E800020   (= want verbatim)
```

So the function belongs to the mwcc-compiled runtime zone (like the GX/OS
SDK blocks), not the ngccc game-code set — route it per-object with
`mw_version=GC/1.3.2` (project.py already drives mwcceppc for CRT objects).

**On the ProDG side** the named-extern recipes DO fix the shape now:
`extern u16 lbl_CC00500A; return lbl_CC00500A & 0x20u;` produces want's exact
`lis rX; lhz r0, disp(rX); rlwinm r3,r0,0,26,26` form (recipe-53 fold works
for MMIO loads too). The only residual is the address-base color: want r3,
ProDG picks r9 at EVERY -O level (REG_ALLOC_ORDER walks r9→r11→r8, verified
by clobber experiments); register-pins either fold away or block the @l fold
(extra addi, 20B); clobbering arg regs triggers a framed callee-saved form;
file-scope `register ... __asm__("r3")` is rejected by cc1.

**NEW generalizable triage rule:** before parking ANY "regalloc coin-flip",
compile the draft's logic with mwcceppc -O4,p — byte-exact ⇒ it's an
SDK-runtime object (park permanently or re-route via mw_version). Likely
re-classifies other SDK-zone parks.

---

# ORIGINAL ANALYSIS (historical)

**Status:** PARKED (as of M4.9x; park set is a moving target — re-verify before trusting) (loads only; the *store* family `hws` matches)

## The problem

Gekko memory-mapped I/O registers live at 0xCC000000 (audio DSP, serial,
etc.). Leaf functions that touch them compile differently for **stores vs
loads**:

- **Stores match** (`hws` family, 11 matched): `*(volatile u8/u16/u32 *)
  0xCC00XXXX = v;` reproduces the game's `lis rX,HA; stb/sth/stw rD,LO(rX)`.
- **Loads do not** (`hwr`, 1 parked): the game emits `lis; lwz/lhz` with a
  specific HA/LO split, but ngccc materializes `lis+ori` (loading the full
  32-bit address into a register first) with a **different HA/LO split**.

Original pattern (game): the high half 0xCC00 is loaded into a base register, then the MMIO word is loaded directly with the low half as displacement in the same load.

ngccc compiled: the high half 0xCC00 is loaded into a base register, then ORed with the low half to materialize the full 32-bit address as an extra instruction, and the MMIO word is loaded with zero displacement through the materialized register.

— or the HA/LO split of the `lis` differs because GCC 2.95.2's
`gen_movsi`/constant handling computes `-0x3400...`-style negated addresses
differently. The result is an instruction-count and/or immediate-field
difference that no C shape fixes (this is the same "lis+ori vs lis+stb with a
different HA/LO split" class documented in AGENTS.md §4f for 0xCC00 loads).

## Why it's parked

- ngccc's address materialization for a 32-bit literal differs from the
  game compiler's for *loads* (while agreeing for *stores* — the store form
  `*(volatile T*)ADDR = v` uses a different RTL path).
- The 1 affected draft (`hwr` family) stays parked.

## What was tried

- `volatile` loads of every width, pointer-cast loads, `__attribute__`
  tricks, all ngccc builds/flags.

## Research directions for an external AI

1. In GCC 2.95.2's PowerPC backend, compare the RTL emitted for
   `*(volatile u32*)0xCC00XXXX` **stores** (which match) vs **loads** (which
   don't). The difference is likely in `legitimize_address`/`rs6000_legitimize`
   handling of a `volatile` MEM as an *operand* vs *destination*.
2. If the game used `lis;lwz` with a hand-written HA/LO, the fix may be an
   inline-asm leaf (see Issue 06 discussion) or a `#define` that forces
   `__asm__("lwz %0, LO(rX)")`-style access.
3. Check the GameCube SDK headers: the canonical MMIO access pattern is
   `*(volatile u32*)0xCC00...` — the game's compiler split the address
   directly into the load's d-form. A ProDG/GCC build with
   `-mno-sdata`/different `-G` might reproduce it.

## Store-side update (M7.05) — named-extern form is the store recipe

fn_8001DC14 (three byte stores to 0xCC008000) promoted M7.05 via
`(volatile u8 *)&lbl_CC008000` — a **named extern `lbl_CC008000[]`**, NOT
the literal `0xCC008000`. The literal form makes ngccc pick a different
HA/LO split (`lis 0xCC00` + `ori` or merged stores); referencing the named
symbol lets the linker choose the game's split (`lis r9, -0x33ff` /
`stb rX, -0x8000(r9)`, i.e. HA=0xCC01 LO=-0x8000). `volatile` is still
required or the three consecutive stores collapse into one. So the store
family's full recipe is: named extern + volatile (AGENTS.md §6g #36).

## Where to look

- WIP family table (`WIP.md`): `hws` (12, matched stores incl. 8001DC14)
  vs `hwr` (1, parked load).
- History: `AGENTS.md` §4f ("0xCC00 HW-register *loads* remain
  unmatchable… lis+ori where the game used lis+stb with a different HA/LO
  split").
