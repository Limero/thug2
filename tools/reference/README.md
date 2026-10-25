# tools/reference/ — preserved work artifacts

Everything here was recovered from the sandbox `/tmp` (tmpfs gets wiped on
restart) so no investigation work is lost. Files are small; the compiled `.o`
objects are gitignored (`.gitignore` has `*.o`) — the sources and docs are
tracked.

| Folder | Contents | Why it's here |
|---|---|---|
| `dtk-template-docs/` | `gs.md` (getting_started), `dtktpl_readme.md` | Upstream dtk-template workflow docs fetched during setup; canonical reference for the decomp loop and split file format (`splits.md` was a byte-identical copy of `docs/splits.md`, removed) |
| `compiler-sweeps/` | Source shapes from the M3 compiler hunt (`fs_*`, `mx_*`, `oh_*`, `ol*`, `sh_*`, `sweep_*`, `pd*`, `pv_*`, plus `sh_src.cpp`/`sh_b.txt` from the C++-mode test) | Evidence of which mwcc versions/flags/expressions were tried before discovering ProDG; the compiled `.o` objects were gitignored scratch and have been deleted, sources kept |
| `rng-match/` | `v1`–`v6` C variants + `cand.c` for `fn_800034E4` | The M4 source-shape exploration; `v2_s2n_local.c` is the winning shape (now in `src/rng.c`) |
| `bootlogs/` | `nogui_*.log`, `final_boot.log` | Dolphin boot-test evidence (0 vs 30 "Invalid read" control runs, §7 of AGENTS.md) |
| `depfile-test/` | `src/test.c`, `test.d`, `test.o` | The `-MD` depfile naming test that proved `ngccc` depfiles work with ninja `deps=gcc` |

Use this folder as a reference when matching future functions — especially
`rng-match/` (shape experimentation methodology) and `dtk-template-docs/`
(split format, workflow).
