# 65 — Map-merged second entry point (a `type:label` inside a `type:function` range is a real function)

**Status: SOLVED / RECIPE (2026-09-19).** Exemplar `fn_80274B10` +
`lbl_80274B20` (region 0x80274B10–0x80274B4C, 60B) promoted byte-exact,
DOL identical.

## Symptom

`symbols.txt` declares a function whose size covers code that is *really two
functions*, and the second entry point appears as a `type:label` inside it:

```
fn_80274B10 = .text:0x80274B10; // type:function size:0x3C
lbl_80274B20 = .text:0x80274B20; // type:label          <- a real entry point
```

Retail bytes: the first entry opens with its own 8-byte frame and link-register save, then calls abort with no epilogue (the link register is never restored). The second entry at 0x80274B20 is a separate function with its own frame and link save; it materialises a global address, loads the indirect target, moves it to the link register, performs the indirect branch, then restores the link register, tears down its 8-byte frame, and returns. Two complete prologues and only ONE epilogue — impossible for one function (the
stack would leak 8 bytes per call), which is the tell.

## Why it happens

`abort()` is `noreturn`. CW still emits the LR-save prologue for the call, then
deletes the unreachable epilogue, so the next function's own prologue follows
immediately with no padding and no branch. The map's function size is just the
distance to the next *function* symbol, so the second entry point shows up as a
label **inside** the first function. Note the later sibling `fn_802740DC`
contains a plain `bl 0x80274B20` — the decisive evidence that the label is an
entry point, findable with a DOL-wide branch-target scan (or simply by grepping
`src/` for the address, since the caller is usually already matched).

## Recipe

1. Confirm the label is a **call target** (`bl`/`bc` from another function, or an
   entry in a `.data` fn-pointer table) — not a loop/branch target of the same
   function. In-function branch targets are normal (`_savegpr_15`, `getTiming`'s
   case labels) and must NOT be split out.
2. Write **two objects**, one per entry point, each with its own split range:
   - `src/fn_80274B10.c` — `void fn_80274B10(void) { abort(); }`, range
     `0x80274B10-0x80274B20` (16B).
   - `src/lbl_80274B20.c` — the tail function, range `0x80274B20-0x80274B4C`
     (44B).
   The noreturn first half compiles to exactly 16B (prologue + `bl`, no
   epilogue); nothing has to be forced.
3. Fix `symbols.txt` so the two ranges are disjoint — the old size overlapped:
   `fn_80274B10 ... size:0x10` and `lbl_80274B20 ... type:function size:0x2C`.
   dtk **refuses to configure** otherwise:
   `Split fn_80274B10.c .text (0x80274B10..0x80274B20) ends within symbol
   'fn_80274B10' (0x80274B10..0x80274B4C)` /
   `Symbol fn_80274B10 overlaps with symbol lbl_80274B20`.
4. Register the second file by hand — `tools/add_gen_leaves.py` only globs
   `src/fn_*.c`, so a `lbl_*.c`/non-`fn_` name is never auto-added: append the
   `lbl_80274B20.c:` block to `splits.txt` (keep it adjacent to its neighbour)
   and an `Object(Matching, "lbl_80274B20.c"),` line to `configure.py`.
5. Reconfigure, rebuild, `cmp` the DOL. Both halves then report 100%.

## Gotcha: do NOT keep both functions in one object

The single-object form (one file, two function definitions, one split covering
both) links byte-identically, but objdiff scores it **26.67%** (4/15 words:
prologue + the second prologue) and it counts as *unmatched*: objdiff resolves
relocations only for functions inside the unit's own range/mapping, so the
symbols of the second half keep their unrelocated placeholders (`48000001`,
`3d200000`). Two units → 100% each, and the function count goes up by two
(`fn_80274B10` 16B + `lbl_80274B20` 44B) instead of one 60B function.

## Scope

Search pattern for more candidates:

```python
# symbols.txt: functions whose range contains a type:label
# (59 hits; all others are in-function branch targets -> NOT splittable)
```

Siblings that are *not* members: `getTiming`, `VIGetTvFormat`, `SIEnablePollingInterrupt`
(their internal labels are `switch`/branch targets of the same function),
`__save_gpr`/`__restore_gpr` (`_savegpr_14..31`, a jump-in table — doc 45), and
`OSExceptionVector` (`__DBVECTOR`/`__OSEVSetNumber`, asm blob — doc 40).
