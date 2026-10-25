# odemuexi2

Metrowerks debug (EXI/UART) module, matching the retail build. Built with mwcc
`GC/1.2.5n` and `cflags_odemuexi2` (not the ngccc game toolchain). Reference
source: `../tww/src/OdemuExi2/DebuggerDriver.c`.

## Wired (matching)

- [x] `DBGFlushBuffer` (0x8028D340, 0x2C) — static helper, no attested name
- [x] `fn_8028D464` (0x8028D464, 0x30) — fn-ptr dispatch through `lbl_803CAF1C`
- [x] `DBClose` (0x8028D494) — 4B no-op
- [x] `DBOpen` (0x8028D498) — 4B no-op
- [x] `DBWrite` (0x8028D49C, 0x260) — `_DBGReadStatus`/`DBGWriteMailbox` inlined
- [x] `DBRead` (0x8028D6FC, 0x8C)
- [x] `DBQueryData` (0x8028D788, 0x9C) — CheckMailBox inlined
- [x] `DBInitInterrupts` (0x8028D824, 0x54)
- [x] `DBInitComm` (0x8028D878, 0x78)
- [x] `DBGHandler` (0x8028D8F0, 0x40)
- [x] `MWCallback` (0x8028D930, 0x3C)
- [x] `_DBGReadStatus` (0x8028D96C, 0xAC)
- [x] `DBGWrite` (0x8028DA18, 0xDC)
- [x] `DBGRead` (0x8028DAF4, 0xDC)
- [x] `DBGReadMailbox` (0x8028DBD0, 0xAC)
- [x] `DBGEXIImm` (0x8028DC7C, 0x298) — thug2 inlines `DBGEXISync` here (AGENTS.md #219)
- [x] `Vtable0x803089D0.c` — dispatch-table thunks m0–m6
  (0x8028DF14–0x8028DF3C, one TU; gen-leaf match, attested names)

All of the above are verified EXACT with `tools/mwcc_verify.py` and linked at
their retail addresses (DOL byte-identical). `DBGEXISelect`/`Deselect`/`Sync`
are inlined at each call site; `DBGEXIImm` is the one shared out-of-line helper,
referenced as extern. Shared small data (`lbl_803CAA58` SendCount etc.) comes
from the auto-stub data objects.

## Remaining

### Parked drafts exist (wip, not yet promotable)

- [ ] `fn_8028D36C` — zero-padder, 93.7%; tail (x8 CTR unroll + `andi.`
  remainder) understood and matched, but the 7-word head block
  (`cmplwi r0,0x20 / subfic r3 / li r6 / bgelr`) resists ~25 spellings (see
  park note in `src/wip/fn_8028D36C.c`)

### No draft at all (auto-stubbed, keep original DOL bytes)

- [ ] `fn_8028DF3C` (0x5C)
- [ ] `fn_8028DF98` (0x50) — 3-way dispatch redraft in `src/wip/`, unverified

### NonMatching placeholder

- [ ] `DebuggerDriver.c` — not linked (no exact split range left); provides the
  reference layout only. Its former D494–D6FC range is now covered by the
  DBClose/DBOpen/DBWrite matching units.

Note: mwcc-verified drafts must go through this lib module — registering them
in the ngccc game module shifts layout by +4 and breaks the DOL (WIP.md).
