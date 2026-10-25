# 22 — MSL C runtime: it's SN ProDG newlib, mostly wired

**Status: 14 of 17 live functions wired/solved (2026-08-26).** memset,
memmove and strncmp are **byte-exact at 100%** via the sources below
(plain ngccc flags); **strcasecmp SOLVED 2026-08-26 ** — the last
word fell to a one-line fix (see its section). **Promotion note (2026-08-26
audit, moved 2026-09-09):** all three were promoted directly as `src/fn_8026AFB8.c` /
`src/fn_8026AECC.c` / `src/fn_8026B3A4.c` (`[x]` complete in PROGRESS.md) —
NOT copied into `libs/runtime/src/` as this doc originally instructed; the
winning C below is kept for reference. The named-libc `src/` matches
(`vprintf`/`memmove`/`memset`/`strcasecmp`/`strncmp` + `fn_8026D1B4` /
`fn_8026E5B8`) have since been moved to `libs/runtime/src/` (the five named
ones under their real filenames `vprintf.c`/`memmove.c`/`memset.c`/
`strcasecmp.c`/`strncmp.c`, the two anonymous ones kept as `fn_*.c` —
runtime lib owns the `Object`; same bytes, DOL still byte-identical) — see
`libs/runtime/README.md`. Second wave (2026-09-09): `atoff`/`rand`/`free`/
`isdigit`/`isspace`/`__getreent`/`floor` identified the same way (crashwoc
`rand.c`/`vprintf.c`/`strtol.c` semantics verbatim + newlib ctype/fdlibm
ABI) and moved to `libs/runtime/src/` under real names; `lbl_803CA420` is
newlib's `_impure_ptr`, not MSL state. `rand`/`__getreent` trip the known
M4.11 r13-asm objdiff undercount (PROGRESS `- [ ]`, DOL-identical).

## 2026-08-23 solutions

Three NEW generalizable recipes cracked the previously "compiler-
configuration-blocked" functions — no version/flag changes needed:

1. **Empty `__asm__ volatile("");` as a position barrier.** Between statement
   groups it forbids the scheduler moving anything across that point while
   emitting zero bytes. Kills the memset guard-hoist class ("compare scheduled
   into a latency slot") that doc-22 previously declared unreachable.
   `"memory"`/`"cc"` clobbers work identically here.
2. **Explicit counter-copy locals.** When WANT shows a value copied to a second
   register at entry (`mr r10,r5`) or a count temp before a test (`mr r0,r5`),
   declare a REAL second variable in C (`size_t n2 = n;`, `t = n--;`). GCC
   collapses implicit copies but honors source-level ones — this alone flipped
   memmove and strncmp.
3. **`register T x __asm__("rN")` pins extend to libc-style code** (fill→r0,
   s1/s2→r3/r4) — but never pin a value that must RECEIVE an incoming arg
   (corrupts param delivery); pin only post-prologue webs.

### memset 0x8026AFB8 — 100.0% (37/37)

```c
typedef unsigned int size_t;

void* memset(void* dest, int c, size_t count)
{
    register unsigned long fill __asm__("r0");
    unsigned char* p;
    unsigned long* aligned_p;

    p = (unsigned char*)dest;

    if (count > 3 && (((unsigned long)dest & 3) == 0)) {
        c &= 0xFF;
        aligned_p = (unsigned long*)dest;
        fill = (c << 8) | c;
        fill |= fill << 16;
        __asm__ volatile("" ::: "memory");

        if (count > 15) {
            do {
                *aligned_p = fill;
                count -= 16;
                *++aligned_p = fill;
                *++aligned_p = fill;
                *++aligned_p = fill;
                aligned_p++;
            } while (count > 15);
        }

        while (count > 3) {
            *aligned_p++ = fill;
            count -= 4;
        }

        p = (unsigned char*)aligned_p;
    }

    while (count-- != 0) {
        *p++ = c;
    }

    return dest;
}
```

The two levers: `register unsigned long fill asm("r0")` pins fill in r0
(retail keeps p in r9; plain decls coalesce fill into the dead-p reg), and the
empty volatile asm between the fill chain and `if (count > 15)` blocks sched2
from hoisting `cmplwi r5,0xf` into the slwi→or latency slot.

### memmove 0x8026AECC — 100.0% (59/59)

crashwoc structure plus ONE line: `size_t n2 = n;` at top; overlap test,
backward loop, forward do-while and both tails count on `n2`; only the forward
`n2 > 15` guard tests original `n`. That reproduces retail's `mr r10,r5` web
split; the documented 5-insn overlap-setup order mismatch disappears on its own
(it was downstream of the missing copy).

```c
typedef unsigned int size_t;

void* memmove(void* dst_void, const void* src_void, size_t n)
{
    char* dst = dst_void;
    const char* src = src_void;
    unsigned long* aligned_dst;
    const unsigned long* aligned_src;
    size_t n2 = n;

    if (src < dst && dst < src + n2)
    {
        src += n2;
        dst += n2;
        while (n2--)
            *--dst = *--src;
    }
    else
    {
        if (n > 15 && ((((unsigned long)src) | ((unsigned long)dst)) & 3) == 0)
        {
            aligned_dst = (unsigned long*)dst;
            aligned_src = (const unsigned long*)src;

            do {
                *aligned_dst = *aligned_src;
                n2 -= 16;
                *++aligned_dst = *++aligned_src;
                *++aligned_dst = *++aligned_src;
                *++aligned_dst = *++aligned_src;
                aligned_dst++;
                aligned_src++;
            } while (n2 > 15);

            while (n2 > 3)
            {
                *aligned_dst++ = *aligned_src++;
                n2 -= 4;
            }

            dst = (char*)aligned_dst;
            src = (const char*)aligned_src;
        }

        while (n2--)
            *dst++ = *src++;
    }

    return dst_void;
}
```

### strncmp 0x8026B3A4 — 100.0% (56/56)

Canonical newlib body except the byte loop enters through an explicit temp:
`t = n--; if (t == 0) break;` — prevents GCC collapsing retail's `mr r0,r5`
pre-test temp; yields the rotated lbzu loop + shared exit verbatim.

```c
typedef unsigned int size_t;

#define UNALIGNED(X, Y) \
    ((((long)(X)) & (sizeof(long) - 1)) | (((long)(Y)) & (sizeof(long) - 1)))
#define DETECTNULL(X) (((X) - 0x01010101) & ~(X) & 0x80808080)

int strncmp(const char* s1, const char* s2, size_t n)
{
    unsigned long* a1;
    unsigned long* a2;
    int t;

    if (n == 0)
        return 0;

    if (!UNALIGNED(s1, s2))
    {
        a1 = (unsigned long*)s1;
        a2 = (unsigned long*)s2;
        while (n >= sizeof(unsigned long) && *a1 == *a2)
        {
            n -= sizeof(unsigned long);
            if (n == 0 || DETECTNULL(*a1))
                return 0;
            a1++;
            a2++;
        }
        s1 = (char*)a1;
        s2 = (char*)a2;
    }

    while (1)
    {
        t = n--;
        if (t == 0)
            break;
        if (*(const unsigned char*)s1 != *(const unsigned char*)s2)
            break;
        if (n == 0 || *s1 == '\0')
            return 0;
        s1++;
        s2++;
    }

    return (*(const unsigned char*)s1 - *(const unsigned char*)s2);
}
```

### strcasecmp 0x8026B04C — **SOLVED 2026-08-26, EXACT 37/37**

The final word was a one-line deletion: the `register int rc1
__asm__("r3")` return-pin that the 97.30% attempt added was SUPPRESSING the
zero-extract. **A hard-reg pin on the return web blocks ngccc's zero_extract
pattern** — with `rc1` as a plain local, GCC emits the tail's
`clrlwi r3,r7,0x18` naturally (the "redundant" mask want keeps is exactly
what a plain local produces; the pin forced the already-masked value to be
copied instead). Recipe: when want shows a clrlwi your pinned draft emits as
a bare `mr`, DROP the pin before trying wedges. s1/s2 pins stay. Draft:
`src/wip/fn_8026B04C.c` (EXACT, awaiting promotion).

Historical 97.30% state: loop byte-exact incl. the `b/addi/addi` rotation
artifact and extsb handling via local register pins (`s1→r3`, `s2→r4`). Last
diff was w24 want `clrlwi r3,r7,0x18` vs got `mr r3,r7`. Resisted back then:
opaque-asm tails, raw-var pinning, signed-snapshot forms, `&=0xFF`, all
schedule/CSE flags, and `#pragma peephole off` (accepted silently by ngccc
3.9.3 but A/B verified byte-identical .text on game-mode `-O2 -G0` — NOT a
lever).

---

# ORIGINAL ANALYSIS (historical)

**Status: MOSTLY WIRED (2026-08-19).** The DOL's runtime zone
(`0x80269EB0..0x80274A78`) is **not MSL** — it is the **SN Systems ProDG
newlib** (the EA/Neversoft libc), compiled with the game's ngccc (GCC 2.95.2,
ProDG 3.9.3), **not** with mwcc. **10 functions are wired byte-exact** (lib
`runtime`, `libs/runtime/src/`, ngccc `-O2 -G0`): `memcmp`, `memcpy`,
`strlen`, `memchr`, `strchr`, `strcmp`, `strcpy`, `strncpy`, `strcat`,
`tolower`. The rest of the zone (`memset`, `memmove`, `strncmp`,
`strcasecmp`, the printf family) stays auto-asm for the reasons below.

## What's in the DOL zone (live functions, ~call sites in whole .text)

| addr | identity | size | status |
|---|---|---|---|
| 0x80269F30 | `tolower` | 0x1C | **WIRED** |
| 0x80269F4C | varargs/`__va_arg` helper | 0xD8 | auto-asm |
| 0x8026A024 | `vprintf` (stream wrapper → fn_8026BC98) | 0x34 | **EXACT-masked-SDA** (needs manual `Object(extra_cflags=["-msdata=eabi","-G4"])` like fn_80252C3C — m2c phantom 4th arg removed, callee is 3-arg) |
| 0x8026A058 | `atoff` (`strtof(s, NULL)` wrapper, newlib atoff.c verbatim) | 0x24 | **WIRED** (`libs/runtime/src/atoff.c`) |
| 0x8026A07C | `qsort` (Bentley/McIlroy — algorithm map verified, still parked) | 0x98C | auto-asm (structural rebuild parked: big-function allocator wall, want stmw r17/frame 0x48 vs ~4 saved regs reachable; block/register maps in wip header) |
| 0x8026AA08 | `rand` (newlib LCG over `_rand_next`@0x58; crashwoc `rand.c` verbatim) | 0x24 | **WIRED** (`libs/runtime/src/rand.c`; objdiff undercounts — r13-asm artifact) |
| 0x8026AA2C | `free` (heapless stub → OSPanic `*** Library error *** ... 'free'`) | 0x3C | **WIRED** (`libs/runtime/src/free.c`) |
| 0x8026AA68 | `strtof` (simple float engine; uses `isspace`/`isdigit`, `ERANGE` via `__getreent`) | 0x330 | auto-asm (hand rewrite parked 2026-09-09 at 66/205: dead-`mr` cap + combine/sched walls, see draft header; rename to `strtof` on promotion) |
| 0x8026AD98 | `memcmp` | 0x90 | **WIRED** |
| 0x8026AE28 | `memcpy` | 0xA4 | **WIRED** |
| 0x8026AECC | `memmove` | 0xEC | auto-asm |
| 0x8026AFB8 | `memset` | 0x94 | auto-asm (4-diff coin flip) |
| 0x8026B04C | `strcasecmp` | 0x94 | **SOLVED ** (drop the rc1 r3 pin → clrlwi falls out; EXACT draft in src/wip) |
| 0x8026B0E0 | `strcat` | 0x90 | **WIRED** |
| 0x8026B170 | `strchr` | 0x9C | **WIRED** |
| 0x8026B20C | `strcmp` | 0xA8 | **WIRED** |
| 0x8026B2B4 | `strcpy` | 0x84 | **WIRED** |
| 0x8026B338 | `strlen` | 0x6C | **WIRED** |
| 0x8026B3A4 | `strncmp` | 0xE0 | auto-asm (1-insn diff) |
| 0x8026B484 | `strncpy` | 0xCC | **WIRED** |
| 0x8026B550 | `strstr` | 0x68 | auto-asm (park 92.9%: ngccc duplicates the `[mr r3,r10;blr]` tail — doc-31 class; all want bytes verbatim otherwise) |
| 0x8026B5B8 | decimal-string increment (rounding helper for the float→ASCII core) | 0x5C | **WIRED** as `src/fn_8026B5B8.c` (no standard name — not renamed) |
| 0x8026B614 | in-place string reverse (called by `itoa`) | 0x4C | **WIRED** as `src/fn_8026B614.c` (`strrev` candidate, spelling unproven — not renamed) |
| 0x8026B660 | `itoa`-class (digit table + base param + reverse; parked) | 0x7C | auto-asm (park 83.9%, doc-15 tie-break) |
| 0x8026B6DC | float→ASCII core (`ecvt`-class worker; calls `floor`/`fmod`/increment/`itoa`; parked) | 0x4E8 | auto-asm (doc-14 + doc-28 walls) |
| 0x8026BBC4 | buffered stdout/stderr writer twin (flushes via EXI `fn_8028DFE8`; parked) | 0xD4 | auto-asm |
| 0x8026D1B4 | buffered stdout/stderr writer twin | 0xD4 | **WIRED** as `libs/runtime/src/fn_8026D1B4.c` (direction unproven — not renamed) |
| 0x8026E57C | `isdigit` (`(_ctype_+1)[c] & _N(4)`) | 0x14 | **WIRED** (`libs/runtime/src/isdigit.c`) |
| 0x8026E590 | `isspace` (`(_ctype_+1)[c] & _S(8)`) | 0x14 | **WIRED** (`libs/runtime/src/isspace.c`) |
| 0x8026E5A4 | `__getreent` (returns `_impure_ptr`) | 0x8 | **WIRED** (`libs/runtime/src/__getreent.c`; objdiff undercounts — r13-asm artifact) |
| 0x8026E5AC | rodata-table getter (`lbl_802B218C`; purpose unknown) | 0xC | **WIRED** as `src/fn_8026E5AC.c` (not renamed) |
| 0x8026E5B8 | wrapper forwarding `_impure_ptr` to the above | 0x24 | **WIRED** as `libs/runtime/src/fn_8026E5B8.c` (not renamed) |
| 0x8026E5DC | `floor` (fdlibm; rodata2 doubles) | 0x174 | **WIRED** (`libs/runtime/src/floor.c`; second copy at `src/fn_80270290.c`) |
| 0x8026F20C | `memchr` | 0xC0 | **WIRED** |

(Dead-linked after 0x8026B5B8: MSL double libm + strtod family, 0 callers —
`docs/neversoft-math-lib.md` §2. The Neversoft float lib 0x8027052C..0x80272044
is the game's own code, also not MSL.)

## Discovery: newlib, not MSL (and not mwcc)

- The word-at-a-time bit-trick algorithms (`0x80808080` / `0xFEFEFEFF`) are
  **newlib's**, not MSL's. Writing newlib's canonical `strlen` and compiling
  with **ngccc** reproduces the DOL's exact algorithm (ProDG GCC, not mwcc —
  mwcc's byte loops use `lwz+clrlwi`; the DOL uses `lbz`).
- **The original source tree exists**: the crashwoc decomp's
  `src/runtime/libc/` is the exact SN ProDG newlib revision. All 10 wired
  functions are the **original crashwoc sources** (with `#include "string.h"`
  swapped for the self-contained `types.h` + `size_t` typedef),
  byte-exact against the THUG2 DOL. Do not hand-write these — copy them.
- The retained `libs/PowerPC_EABI_Support/MSL` files are only the small header
  closure needed by the wired Dolphin sources. The MSL implementation sources
  were pruned because they are not part of THUG2's configured link and are not
  the DOL's runtime; do not attempt to wire the retained headers as a runtime.

## What matched and how

Ten functions wired byte-exact (`libs/runtime/src/`, ngccc `-O2 -G0`,
ProDG 3.9.3 = `cflags_game`):

- **memcpy** (0x8026AE28): 16-byte-unrolled word copy + 4-byte tail + byte
  tail. Key forms: the byte tail is `while (r5-- != 0)` (pre-decrement test),
  and the 16-byte loop stores via pointer-increment (`stwu`) — array-index
  stores (`ws[0..3]` + `ws += 4`) compile to plain `stw`+`addi` and do NOT match.
- **strlen** (0x8026B338): word scan with the `0x01010101`/`0x80808080`
  bit-trick, then byte scan. Iterating an `unsigned long *` (newlib style)
  is what pins the `andc`/`and.` destination registers — the plain `char*`
  version flips them.
- **memcmp** (0x8026AD98): alignment check, word loop with peeled entry
  compare, byte tail. The `u1/u2/p/l1/l2` variable split pins the entry
  compare to `lwz r0,0(r4); lwz r9,0(r3); cmpw r9,r0` — the m2c goto form
  instead loads `*s1` from the p copy (r9) and misses by 6 bytes.
- **strcmp/strncpy/strcpy/memchr/strchr/strcat** (0x8026B20C/0x8026B484/
  0x8026B2B4/0x8026F20C/0x8026B170/0x8026B0E0): original crashwoc newlib
  sources, byte-exact. The 14 already-matched callers now call the real
  `strcpy` symbol through exact-arity declarations, preserving their retail
  instruction scheduling; `strcat` calls `strcpy` directly.
- **tolower** (0x80269F30): indexes `_ctype_ + 1` — the `_ctype_` symbol was
  added to symbols.txt at 0x802B1D04 (the 0x101-byte newlib ctype table; the
  auto-detected `lbl_802B1D05`/`lbl_802B1D08` labels inside it were removed
  and the string region relabeled `lbl_802B1E08`).

General lesson (doc-10 class): the m2c drafts (s32/goto style) do NOT compile
back byte-exact; the **canonical newlib source with distinct pointer
variables** does. Copy the real source, don't reconstruct the decompiled shape.
When renaming a shared callee, preserve legacy caller codegen with exact
arity declarations rather than an old-style empty prototype; the `strcpy`
callers are the worked example.

## What's still parked and why

> **2026-08-26 audit:** the memset / memmove / strncmp entries below are
> HISTORICAL — all three are promoted byte-exact (see the 2026-08-23
> solutions at top). Still genuinely parked: **strcasecmp** (97.30%), and
> the **printf family**. `strstr` (0x8026B550) also remains auto-asm.

- **memset** (0x8026AFB8): re-attacked 2026-08-19 with a relocation-aware
  instruction comparer (ngccc `.o` files carry REL14/REL24 relocs whose
  addends differ from the raw displacement fields; naive byte diffs were
  misleading). The do-while source `if (n > 0xF) { do { *ws++ = word; ×4;
  n -= 0x10; } while (n > 0xF); }` + `*ws++` 4-byte tail (m1 form) pins the
  retail allocation — word in r0, ws in r11, loop body and byte tail
  **byte-exact** — leaving exactly **4 instruction diffs, all one block**: the
  `if (n > 0xF)` guard's `cmplwi r5,0xf` is scheduled into the slwi→or
  latency slot of the word chain (GOT) vs after the chain (DOL). This hoist
  is robust across every lever tested: all 5 in-tree ngccc versions
  (3.5/3.5b140/3.7/3.8.1/3.9.3), every `-mcpu` model (750-family hoists;
  603/602-family leaves the position but wrecks regalloc — word/ws merge into
  r9, byte loop restructures to 36 insns), `-O1/-O2/-O3/-Os`, and each
  scheduling flag alone (`-fno-schedule-insns` and `-fno-schedule-insns2`
  each still hoist — the other pass compensates; the earlier doc claim that
  `-fno-schedule-insns` fixes the position was disproven with the corrected
  comparer). Only `-fno-schedule-insns -fno-schedule-insns2` together fix the
  entry, but they deschedule the loops (9 diffs). The retail build scheduled
  the loop body but not the entry compare — a compiler configuration none of
  our tools reproduce. While/for loop forms additionally break word→r0 (r9).
  Do not attempt `-fno-schedule-insns` zone-wide — it also breaks the three
  wired functions.
- **memmove** (0x8026AECC): the DOL is newlib's memmove with a backward
  byte-only path (`src < dst && dst < src+n`, `lbzu -1`/`stbu -1` loops) and a
  forward word-unrolled path guarded on `n` but looping on an `n2` copy.
  A 2026-08-20 source-only reconstruction reached the exact 0xEC-byte size
  and matched the full forward path, byte tail, and backward loop. It remains
  five instructions short of byte-exact: the overlap setup schedules
  `add r11,r3,r10; cmpwi r10,0; mr r4,r0; addi r10,-1; beqlr` while ngccc
  emits the same instructions in a different order. `-fno-schedule-insns2`
  changes register allocation and `-fno-schedule-insns` does not solve it.
  The candidate was rolled back; crashwoc's memmove.c is a placeholder.
- **strncmp** (0x8026B3A4): crashwoc's strncmp compiles to 220B vs DOL's
  224B — the DOL's byte loop uses the `lbzu` post-increment form while GCC
  emits a different loop shape (1 insn short + entry `mr r9,r3` diff). A
  2026-08-20 source-only attack reconstructed the full 224B word/byte shape,
  including `lbzu`, but ProDG still collapsed the retail `mr r0,r5` count
  temporary and chose different byte-register allocation; its best objdiff
  result was 83.57% and was rolled back. No partial C unit is registered.
- **strcasecmp** (0x8026B04C): crashwoc's canonical source remains parked. The
  original DOL is 0x94 bytes and begins with `b; addi r3,r3,1; addi r4,r4,1`,
  then loads the first pair as `lbz r0,0(r3); lbz r8,0(r4); mr r7,r0;
  extsb r0,r0`. Source-only attempts using the canonical newlib body,
  `-fno-schedule-insns`, explicit do/goto loop forms, signed-byte temporaries,
  and source-level pointer register hints reproduced the broad control flow
  but not that raw-byte/`extsb` allocation. The closest non-asm form still
  differed in the first temporary and was rolled back; no partial C unit is
  registered.
- **printf family** (fn_8026A07C → fn_8026BC98): crashwoc's printf/vfprintf/
  sprintf are placeholders — the real SN newlib stdio revision isn't in any
  sibling repo yet. Large formatter — parked.

## Caller naming sweep (2026-08-20)

The remaining WIP callers of the linked runtime zone were swept with
`tools/apply_wip_names.py`: all stale `fn_8026B0E0/B170/B20C/B2B4/B338/B484`
tokens in `src/wip/` now use their real names (`strcat`, `strchr`, `strcmp`,
`strcpy`, `strlen`, and `strncpy`). This is metadata-only because WIP drafts
are inert and not registered in `splits.txt`.

Second pass (2026-08-20): `fn_8026B04C` → `strcasecmp` and `fn_8026B550` →
`strstr` were renamed in `symbols.txt` (auto-asm names propagate via `dtk dol
split`; no scope:global needed) and all 53 call-site tokens in `src/wip/`
were swept. The 2 compiled callers of `strcasecmp` (`src/fn_8018E520.c`,
`src/fn_8020A808.c`) got local prototypes + call sites renamed. `strstr` is
the last live function before the dead-linked zone; it was missing from the
wiring table entirely (identified here by shape: naive substring search
returning a pointer). The 4 stale `src/wip` bodies whose *filenames* were
already real names (`__GXShutdown.c`, `__GXDefaultTlutRegionCallback.c`,
`__GXDefaultTexRegionCallback.c`, `fn_80003100.c`/`__start`) were fixed to
match — `apply_wip_names.py` misses them because it only globs `fn_*.c`
(and `__start` is in `.init`, not `.text`).

One corrected caller, `0x80137774`, had been generated with a spurious third
`strcpy` argument. Retail disassembly shows the call uses `r3 = arg0 +
offset` and `r4 = arg2`; after fixing it to two arguments, the draft compiled
`EXACT`, was promoted to `src/fn_80137774.c`, and the rebuilt DOL remained
byte-identical. Other repaired WIP callers compile but are still non-matching;
they remain parked rather than being promoted.

## To unblock

1. **strcasecmp**: one combine-level decision short (97.30%, see the solved
   recipe block above for the current best body and the resisted levers).
2. **printf family**: obtain the ProDG newlib `stdio` revision matching
   fn_8026A07C (nfsmw's SN tree or a later EA ProDG-era repo).
3. **strstr** (0x8026B550): naive substring search, last live fn before the
   dead zone — never attacked with the 2026-08-23 recipes; try the crashwoc
   newlib-source route first.

(memset/memmove/strncmp are DONE — promoted as `src/fn_*.c`, see top.)
