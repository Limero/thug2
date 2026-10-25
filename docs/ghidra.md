# Ghidra for THUG2 (G2TE52) — headless decompiler

This doc covers the flatpak Ghidra install at
`/var/lib/flatpak/exports/bin/org.ghidra_sre.Ghidra` (GUI won't work in this
sandbox, but headless does).

## Why headless is niche here

The project's matching pipeline is compiler-locked:

* `m2c` (`tools/fill_wip_drafts.py`) → `ngccc -O2 -G0` (`configure.py:cflags_game`) → `mwld GC/1.3.2` → byte-identical `main.dol` (`ff6faeb0…`) — verified via `tools/sda_verify.py`/`gen_leaves.compile_fn` masked `REL14/REL24/SDA21`.

Ghidra's decompiler (`PowerPC:BE:32:default`, `e500:default` for ELF) is
type-recovery focused, not `ngccc`-idiomatic. Its C will **not** compile to
the same bytes without manual porting — same work as porting `m2c` output,
without `m2c`'s `ppc-mwcc-c` fixes (`->unkN` byte casts, `saved_reg_r13`,
`Warning:` stripping). It also mishandles the game's `SDA21 r13` and
Gekko `psq`/`paired-single` (as with `capstone`), so `SDA`/`PS` functions
decompile to `return;` or stubs.

Where it **does** help:

* `05-m2c-corrupt` (`docs/parkings/05-m2c-corrupt-draft.md` `0x8008076C` `94%`): Ghidra recovered the 2.5 KB `local_4e40[2500]` loop + `auStack_2730` spill that `m2c` truncated.
* Large `fdlibm` hand-rebuilds (`docs/parkings/44-math-entry-staging-homing-wall.md` `__ieee754_log` `0x8026EAAC` `82` lines, `SDA21` pool `0x43300000` dance as `CONCAT44`) — cleaner control-flow than `m2c`'s `sp8`/`temp_f*`/`unkspC` phantom.
* `41-handwritten-asm-texture-upload` and Dolphin SDK `libs/dolphin` revert work where you need CFG/struct recovery, not byte-exact.

Keep `m2c`+`gen_leaves` primary; use Ghidra as secondary for those 3 parked classes.

## Flatpak workaround (`/tmp` wipe-safe)

Flatpak ships `files/lib/ghidra/support/launch.properties -> /var/config/ghidra.properties`
(a dangling symlink outside the sandbox) + bundled `files/jdk 21.0.12.1`. Running
`files/lib/ghidra/support/analyzeHeadless` directly fails with `Cannot launch
from repo because Ghidra has not been compiled`.

`tools/ghidra_decompile.py` works around it on every invocation (so `/tmp` wipe
does not break it):

1. `find_ghidra()` globs `/var/lib/flatpak/app/org.ghidra_sre.Ghidra/x86_64/stable/*/files/lib/ghidra` (`files/lib/ghidra/support/analyzeHeadless:1`, `files/jdk/bin/java:1`).
2. `prepare_headless()` copies `support/` to a `mkdtemp` (`ghidra_headless_*`) with `ignore_dangling_symlinks=True`, replaces `launch.properties` with `launch.properties.orig:1` (real file), and symlinks `Ghidra->.../files/lib/ghidra/Ghidra:1` for `INSTALL_DIR/Ghidra/Framework/...`.
3. Writes `DumpOne.java`/`DumpBatch.java` (embedded `DecompInterface` batch, `toAddr`+`getFunctionAt`+`decompileFunction`) to a temp `scriptPath`.
4. Runs `analyzeHeadless <tmp_proj> THUG2 -import build/G2TE52/main.elf -processor PowerPC:BE:32:default -scriptPath <tmp> -postScript DumpBatch.java 0x... -deleteProject` with `PATH=<jdk>/bin:$PATH` and `XDG_RUNTIME_DIR=/tmp`.

No persistent `/tmp/ghidra_test` needed — the tool recreates the fix each run.

## Usage

```sh
# single function (prints + writes /tmp/ghidra_8026EAAC.c)
tools/venv/bin/python tools/ghidra_decompile.py 0x8026EAAC

# batch (one headless run, ~70s import+analysis, subsequent decompiles fast)
tools/venv/bin/python tools/ghidra_decompile.py 0x8008076C 0x8026FD2C 0x80271444

# explicit ELF/DOL, custom out dir, keep project, longer timeout
tools/venv/bin/python tools/ghidra_decompile.py 0x8026FF40 --elf orig/G2TE52/sys/main.dol --out-dir /tmp/ghidra_out --timeout 300 --keep-project
```

Output files are always `/tmp/ghidra_<hex>.c` (also printed to stdout, truncated `2000` chars in log). Batch writes one file per address. The script also handles `getFunctionContaining` fallback when the entry point is not a function start (common for `auto_*` gap functions).

Import uses `build/G2TE52/main.elf` by default (correct `PowerPC:BE:32:e500:default`, `_SDA_BASE 0x803D2280`, `_SDA2_BASE 0x803D2F80` detected). `orig/G2TE52/sys/main.dol` import falls back to `Raw Binary` loader (no `DOL` loader in Ghidra) — use ELF.

Time: first ELF import+`AutoAnalysisManager` `~65-68s` (`Disassemble Entry Points 16s`, `PowerPC Constant Reference 14s`, `Stack 15s`), then `DumpBatch.java` `~1s` per function.

## When to use vs `m2c`

| Situation | Use |
|---|---|
| Leaf / small GPR-only / `gen_dispatch` | `tools/gen_leaves.py` (already auto-matched) |
| `src/wip` `m2c` draft `>50%` `NEAR` | `tools/test_wip_drafts.py` + `tools/flagdiff.py`/`ps_diff.py`/`sda_verify.py` (byte-exact is the arbiter) |
| `src/wip` `stub` where `m2c` produced nothing useful, or `05`/`44`/`41` where `m2c` structure is lost | `tools/ghidra_decompile.py` for CFG/types, then hand-port to `ngccc` idioms (`volatile double _dummy`, `hi:r9 lo:r10` pins, `fr0` staging, `__ps_t` + `-mps-float`) |

Do not promote Ghidra C verbatim — port it like `m2c` output, then verify via `gen_leaves.compile_fn` masked compare and `tools/sda_verify.py` for `SDA` before `promote`.

## References

* Flatpak: `/var/lib/flatpak/app/org.ghidra_sre.Ghidra/.../files/lib/ghidra/support/analyzeHeadless:1`, `files/jdk/bin/java:1` (`openjdk 21.0.12.1`), `support/launch.sh:1` (`INSTALL_DIR` logic).
* Language: `ppc.ldefs:1` `PowerPC:BE:32:default` (also `BE:64`, `4xx`).
* Scripts: `DumpOne.java`/`DumpBatch.java` embedded in `tools/ghidra_decompile.py:1` (`DecompInterface`, `toAddr`, `getFunctionAt`).
* Example outputs: `/tmp/ghidra_8026EAAC.c` (`82` lines, `CONCAT44(0x43300000,uVar3 ^0x80000000)-lbl_802B2220`), `/tmp/ghidra_8008076C.c` (`2500`+`10032` stacks) vs `src/wip/fn_8008076C.c:1` (`94%`).
