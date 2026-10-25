# THUG2 controller input map (identification)

Companion to `docs/neversoft-audio-engine.md` and `docs/neversoft-math-lib.md`.
This doc records the **identification** of every game-side function involved in
reading the GameCube controller (PAD layer), maintaining the game's controller
objects, and exposing input to the QB script engine in the retail `main.dol`
(`orig/G2TE52/sys/main.dol`, case `G2TE52`). All addresses are virtual. No
decomp work has been done on this stack yet - the goal is a reliable
address-level map and the game/SDK separation line.

## 1. The SDK input layer (present in the DOL, unwired in the build)

| Region | Extent | Notes |
|---|---|---|
| PAD | 0x80261B40 - 0x802623AC | `PADInit` (0x80261B40), `PADRead`, `PADReset`, `PADClamp`, `PADSetAnalogMode`, `PADControlMotor` (0x80262340), `PADRecalibrate` - all named in `symbols.txt` |
| PAD helper | fn_80268128 `ClampStick` | in the same 0x80267xxx SDK cluster as `OSGetTime` |

The PAD module is unwired in the build (tww/bfbb `libs/dolphin/pad*` when the
time comes - see `docs/dolphin-sdk.md` for the wiring audit).

Game-side PAD callers (the whole game/PAD separation line):

| Caller | PAD calls | Role |
|---|---|---|
| fn_8001CF80 | `PADInit`, `PADSetAnalogMode` | one-time input bootstrap, called from the master init fn_8001BA14 |
| fn_8001CECC | `PADRead` → 0x80312434, `PADClamp`, `PADReset` | per-frame poll wrapper (see §3) |
| fn_800181A4 | `PADRecalibrate` | teardown / soft-reset handler (audio + input shutdown) |
| fn_8000C5D8 / 8000C6A0 / 8000C79C / 8000C868 / 8000C938 | `PADControlMotor` | the five motor (rumble) control wrappers behind `ScriptVibrateController` (0x8016077C) |
| fn_8000B6F8, fn_800176B8, fn_80017700, fn_800179D0 | reads PADStatus buffer 0x80312434 directly | boot-time pad state reads |

## 2. Game-side input code: two bands

| Band | Addrs | Role |
|---|---|---|
| early | fn_8001CECC, fn_8001CF80, fn_8000C5D8-C938, fn_80017C14 (VI callback install) | raw PAD wrapper + boot wiring |
| engine | fn_8009D2B0 (checksum→index), fn_800145AC (time), fn_8014DDFC/8014DD04/8014E114/8014E1FC (pressed / debounce / wrapper / analogue), fn_8019CF2C/8019D00C (controller objects), fn_801322F8/8013237C/801323D4/8013400C (retrace hook helpers) | the game's input state + script interface |

## 3. Per-frame chain: VI retrace → PAD read → hook

Master init fn_80017C14 (OSInit, DVDInit, VIInit, ...) installs the VI
callbacks:

| Fn | Role |
|---|---|
| fn_800184D8 | pre-retrace callback: frame flip |
| fn_80018570 | **post-retrace callback**: per frame - `fn_8001CECC` (poll pads), fn_80014248 (64-bit frame counters), reset-button handshake via global 0x80300150, then dispatches the retrace hook global 0x80300144 |
| fn_800185DC | reads 0x80300144 (`lwz r0, 0x144(r9)` on the 0x80300140 base) - the retrace-hook dispatch |

`fn_8001CECC` (the poll wrapper) body: `PADRead` into the 4-pad PADStatus
buffer at **0x80312434** (0xC bytes per pad = 0x30 total), `PADClamp`, a
per-pad error loop with a dead-pad counter, then `PADReset(mask)` where the
mask is OR-ed from the per-pad table at 0x80300198 (0x80300140-base settings
region, see §7).

**Retrace hook 0x80300144** is registered from three places:
- fn_801322F8 (plus near-twin fn_8013237C / fn_801323D4)
- fn_8013400C - controller/front-end method that uses a **field** at +0x144
  (not the global; earlier attribution mistake fixed)
- fn_801ECE7C (via fn_801E72F0)

## 4. Controller objects (0x80305EE4)

| Global | Role |
|---|---|
| 0x80305EE4 | pointer to the game's input/controller object (allocated 0x19C) |
| 0x80305EE8 | reference count |

- **Ctor fn_8019CF2C**: if (0x80305EE4 == NULL && arg != 0) { `fn_800099AC(0x19C, 0, 1)` → `fn_8019D00C` → store 0x80305EE4 }, then increments 0x80305EE8. Callers: fn_80145C14 (skater setup), 0x80232B98, 0x802334D4 (park editor / front-end).
- **Release fn_8019CF94**: refcounted; decrements 0x80305EE8, frees when it hits 0.
- **fn_8019D00C** (sub-object ctor): builds the layout under the 0x19C object:
  - +0x14: static table ptr (0x802AAE90 region)
  - +0x18 / +0x1C: two 0x24-byte sub-objects with method ptrs 0x8019D9E4 and 0x8019DA3C (both end in `lmw` epilogues; 0x8019DA3C additionally parses a string buffer via fn_800168B0)
  - +0x28..+0x30: three 0x30-byte per-player pad objects (loop of 3; each gets a method ptr 0x8019D7FC and a parent backref at +0x2C)
  - +0x5C..+0x7C: 3 more 0xC-stride flag words (0/1)
- The per-player pad object method **fn_8019D7FC** reads global 0x80301A78 (a PADStatus-adjacent buffer) and calls fn_800A5AA0 - the prime candidate for the per-frame poll→state writer (§11 follow-up 2).

The wrapper fn_8014E114 (ScriptControllerPressed) reads the per-player table:
`r31 = 0x80305EE4; slot = script arg; controller = *(r31 + 0x28 + slot*4)`.

## 5. The button-checksum layer (names as QB hashes)

All button names travel as Neversoft QB hashes (see `tools/qb_hash.py`).
Two data structures tie names to the pressed state:

### 5.1 Name→index lookup fn_8009D2B0

```
li r0, 0x15 (21); base = 0x80301928; index = 1
loop: if (base[i] == name) return index; index++
return 0
```

The 21-entry checksum table (each entry = `qb_hash(button_name)`), resolved
against the disc's .prg/.qb plaintext via `tools/qb_hash.py`:

| idx | name | checksum | idx | name | checksum |
|---|---|---|---|---|---|
| 1 | Up | 0xBC6B118F | 12 | Triangle | 0x20689278 |
| 2 | Down | 0xE3006FC4 | 13 | L1 | 0x26B0C991 |
| 3 | Left | 0x85981897 | 14 | L2 | 0xBFB9982B |
| 4 | Right | 0x4B358AEB | 15 | L3 | 0xC8BEA8BD |
| 5 | UpLeft | 0xB7231A95 | 16 | R1 | 0xF2F1F64E |
| 6 | UpRight | 0xA50950C5 | 17 | R2 | 0x6BF8A7F4 |
| 7 | DownLeft | 0xD8847EFA | 18 | R3 | 0x1CFF9762 |
| 8 | DownRight | 0x786B8B68 | 19 | Black | 0x767A45D7 |
| 9 | Circle | 0x2B489A86 | 20 | White | 0xBD30325B |
| 10 | Square | 0x321C9756 | 21 | Z | 0x9D2D8850 |
| 11 | X | 0x7323E97C | | | |

The names are PS2-era button names (Triangle/Square/Circle/X = PS2 face
buttons, L1-L3/R1-R3 shoulders, Black/White = PS2 select-ish buttons, Z =
GC/DC button). Word [00] at 0x80301924 is 0x00000000 (unused sentinel; the
search starts at 0x80301928).

### 5.2 Debounce deadline table

- **fn_8014DD04** = ScriptControllerDebounce: resolves the script arg to a
  checksum (via fn_801286D0), computes `deadline = now + duration` and stores
  it at **0x8039FFB8 + idx*4** (`lis -0x7fc6; addi -0x48`), converting the
  integer time from fn_800145AC to float via the 0x4330 int→double trick.
- **fn_8014DDFC** (ControllerPressed impl) gates on it first:
  `if (deadline[idx] > now) return 0` (still cooling down).
- **fn_800145AC** = the time source: reads the 64-bit counter globals at
  0x802FFF38/0x802FFF3C and base 0x8030186C, returns a comparable integer
  time in r3 (callers convert it with the 0x4330 trick).

## 6. ControllerPressed - the button test (fn_8014DDFC)

Signature: `fn_8014DDFC(controller, name_checksum)` → 1/0.

1. Guard: `controller == NULL || *(controller+0x1C) == NULL` → return 0.
2. `idx = fn_8009D2B0(name)`; `if (debounce[idx] > now) return 0`.
3. 19-case switch on the checksum; each case loads **one byte flag** from
   the state array (`r9 = *(controller+0x1C)`) and returns (byte != 0):

| name | byte | name | byte |
|---|---|---|---|
| Right | +5 | Triangle | +9 |
| Left | +6 | Circle | +0xA |
| Up | +7 | X | +0xB |
| Down | +8 | Square | +0xC |
| UpLeft | +7 AND +6 | L1 | +0xD |
| UpRight | +7 AND +5 | R1 | +0xE |
| DownLeft | +8 AND +6 | L2 | +0xF |
| DownRight | +8 AND +5 | R2 | +0x10 |
| Black | +0x17 | White | +0x18 |
| Z | +0x19 (li r3,1 preset) | | |

D-pad diagonals require **both** axis bytes set. **L3 / R3 have table slots
(15/18) but no switch case** - `ControllerPressed("L3")` falls to the default
`return 0`; they are likely read via the analogue path instead (§10
follow-up 1).

The state array's +0x11..0x16 gap is likely stick/trigger analog bytes.

Wrapper **fn_8014E114** (ScriptControllerPressed): resolves the script args
(fn_801286D0 → name into sp8, fn_80128228 → slot into spC); if a slot arg is
present uses `controller = *(0x80305EE4 + 0x28 + slot*4)`, else iterates all
four slots at +0x28..+0x34 and returns 1 on the first match.

## 7. Globals summary

| Global | Role |
|---|---|
| 0x80312434 | PADStatus buffer (4 pads × 0xC) - the raw poll output |
| 0x80300140 + 0x04 | retrace hook global (0x80300144) |
| 0x80300150 | reset-button state |
| 0x80300180 - 0x803001B0 | settings block (pad-type info / masks): readers fn_8001B8D0, fn_8001B9C8, fn_800580A0, fn_800784E0, fn_80043A34, fn_80044088, fn_8004631C; mask table at 0x80300198 used by fn_8001CECC |
| 0x80301924 | button-checksum table (21 entries, search starts at 0x80301928) |
| 0x80301A78 | PADStatus-adjacent buffer read by the pad-object method fn_8019D7FC |
| 0x80305EE4 / 0x80305EE8 | controller object ptr / refcount |
| 0x8039FFB8 | per-button debounce deadline table (idx*4) |
| 0x802FFF38 / 0x802FFF3C / 0x8030186C | 64-bit time counters for fn_800145AC |

## 8. Script-facing entry points (named in symbols.txt)

| Script command | Addr | Notes |
|---|---|---|
| ScriptControllerPressed | 0x8014E114 | wrapper → fn_8014DDFC |
| ScriptControllerDebounce | 0x8014DD04 | sets the deadline table |
| ScriptGetAnalogueInfo | ~0x8014E1FC | reads controller sub-objects +0x1C/+0x20, stick math via fn_800AA0BC / fn_800AA1F4 |
| ScriptPadsPluggedIn | 0x80153054 | reads 0x80305EE4 |
| ScriptFirstInputReceived | 0x80160750 | |
| ScriptVibrateController | 0x8016077C | → PADControlMotor wrappers fn_8000C5D8-C938 |
| ScriptSetMenuPadMappings | 0x8019E340 | reads 0x80305EE4 |
| ScriptSetButtonEventMappings | 0x8019E3E8 | |
| ScriptSetAnalogStickActiveForMenus | 0x8019E468 | |
| ScriptSetMenuAutoRepeatTimes | 0x8019E29C | reads 0x80305EE4 |
| binds | 0x801603C0 / 0x8016043C / 0x801604EC / 0x801605AC | script-command binding glue, read 0x80305EE4 (0x80160484) |

Other 0x80305EE4 readers: 0x800ADDB4, 0x801419EC (ScriptSetViewMode /
ViewerModel), 0x80152E9C/0x80152EDC/0x80155DD0/0x80155E28, 0x8016D57C,
0x80175058, 0x801A1CBC.

## 9. Non-input interleaved neighbors (do not attribute!)

- fn_800145AC's neighbors (0x800145xx) are small settings getters, not input.
- The 0x8019D9E4 method's callees (fn_8000F2F8 / fn_8000F320, fn_8004B15C,
  fn_8019DB68) live in the skater/front-end code, not the input core.
- fn_8016D470 writes a skater/physics object (+0x344/+0x348/+0x35C), **not**
  the input settings struct (verified by disassembly).

## 10. Identification method (reproducible)

1. Find the PAD call sites: scan all `bl` targets for the SDK `PAD*` named
   symbols in `symbols.txt` → the §1 caller table.
2. Chunked capstone disassembly (64-byte slices, +4 fallback) of .text
   (0x800034A0..0x8028E040, file offset 0x4A0).
3. Resolved-memory tracker: track `lis`/`addi`/`addis`/`mr` register copies
   to globals (the `lis` immediate is **operands[1].imm** - gotcha) to find
   every read/write of 0x80305EE4, 0x80312434, 0x80300144, 0x80301924.
4. Resolve the 0x80301924 checksums with `tools/qb_hash.py` + the disc
   .prg/.qb plaintext dict (`tools/resolve_qb_hashes.py build_dict`) - all
   21 resolve to button names; the leftover 4 were cracked by hashing
   candidate strings (UpLeft/UpRight/DownLeft/DownRight diagonals).
5. Map the fn_8014DDFC switch: each `lis+ori` pair is a case key, each `beq`
   target's `lbz N(rX)` is the state byte → the §6 table.

## 11. Follow-ups

1. **L3/R3 pressed semantics**: no switch case in fn_8014DDFC - check the
   analogue path (ScriptGetAnalogueInfo / fn_8014E1FC family) and
   `*(s32 *)(0x80305EE4 + ...)` readers for stick-press handling.
2. **State writer**: find which function fills the byte flags at
   `*(controller+0x1C) + 5..0x19` each frame. Prime candidate: the pad-object
   method fn_8019D7FC (reads 0x80301A78, calls fn_800A5AA0); trace its
   callers from fn_80018570's post-retrace path. Also confirm whether the
   flags derive from PADStatus.button or a clamped/stick-expanded form
   (the diagonals at +5..+8 suggest 4 direction bits, not raw 16-bit).
3. **Controller object layout**: exact 0x19C layout from fn_8019D00C stores
   (+0x14/+0x18/+0x1C/+0x28..+0x30/+0x5C..+0x7C) - candidates for
   symbols.txt naming once promoted (`Controller` / `PadState` / methods
   fn_8019D7FC, fn_8019D9E4, fn_8019DA3C).
4. **Settings block 0x80300180-0x803001B0**: six readers/writers identified
   (fn_8001B8D0, fn_8001B9C8, fn_80043A34, fn_80044088, fn_800580A0,
   fn_800784E0) - map the fields (0x180/0x184/0x188/0x190/0x192/0x1AA).
5. **Debounce duration constant** at 0x802A7BE8 (loaded by fn_8014DD04) and
   the 0x802A7BF8/0x802A7C00 conversion constants - read their float values
   to document the default debounce window.
6. **f32-ret / naming harvest**: rename fn_8014DDFC/fn_8014DD04/fn_8014E114
   as script-command implementations when a rename round runs
   (`rename_script_cmds.py`); they sit at 0x8014DD04-0x8014E1FC with the
   other 0x8014xxxx script commands.
