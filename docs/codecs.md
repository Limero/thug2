# Codecs: audio, FMV, and stream containers

Status of the investigation into the audio/video codecs inside the G2TE52 DOL
and on the game disc. Findings 2026-08-14; earlier reverse engineering
2026-08-14; full-disc codec-signature verification pass 2026-10-04 (see
"Full-disc codec verification (2026-10-04)" below).

## Conclusions

- **No Rad Game Tools in this game.** No Bink video, no Bink audio, no
  `radlib`/`rrdecode`. Verified against the *decompressed* disc, not just by
  strings — see the 2026-10-04 section for why a DOL string scan cannot
  settle this either way.
- **FMV is not THP.** The THP-looking strings in the DOL (`THPS4`,
  `GetMaxTHPS4FilesAllowed`) are THUG's **save-file** format name, not the
  Nintendo THP video format. The `THP\0` container magic appears **0 times** in
  the DOL and exactly **1 time** on the disc, and that single hit is
  spurious: it sits inside a Gekko instruction stream (neighbouring bytes read
  as `TX`/`B`/`@` opcodes) and a THP header parse of it yields nonsense
  (`width=16384`). There are no `.thp` files on the disc (0 occurrences).
- Disc audio is **raw Vorbis** (packet format, no Ogg framing) inside an
  in-house Neversoft container (magic `VID1`, chunks `HEAD`/`VIDH`/`AUDH`/
  `VAUD`).
- The Vorbis decoder in the DOL is **custom (in-house, "AUDSimple")**, not
  stock Xiph Tremor and not stock libvorbis:
  - No Tremor lookup tables (any era) present as constants in the DOL.
  - No libvorbis float tables (`FLOOR1_fromdB`, MDCT sine window) present.
  - Decoder engine (0x80252000-0x80258000) is integer/fixed-point: only a
    handful of FPU ops per 4K block, and those are permutation/bit
    manipulation, not audio math.
  - Bit reader at 0x80257E48 is **MSB-first**; Tremor's oggpack reader is
    LSB-first. Strong evidence of a custom implementation.
  - No `OggS` framing and no Ogg page structure anywhere on disc.
- FMV (`streams`/movie files) are **MPEG-1 video with AC-3 audio**, in the
  same `VID1` container. MPEG-1 and AC-3 signatures occupy the *same* disc
  regions (0-64 MB, 256-304 MB), while Vorbis/music lives in 736-992 MB, so
  the two roles are cleanly separated by region. The remaining open item is
  the *code-side* mode-8 dispatch, not the disc-side correlation.

## DOL module map (codec-related)

All addresses are DOL virtual addresses (section 1 = .text 0x800034A0-0x8028E040).

| Range | Purpose |
| --- | --- |
| 0x80120000-0x80137000 | Music player / AUDSimple API (Neversoft `p_music.cpp`) |
| 0x80240000-0x8024A700 | Audio codec module (vorbis) |
| 0x8024A700-0x8024D000 | Movie player / M4 MPEG-1 decoder |
| 0x8024D000-0x8024F400 | Shared stream/demux/ring-buffer machinery |
| 0x8024F400-0x80252000 | MPEG decode kernels (M4/movie) |
| 0x80252000-0x80258000 | **Audio decode engine** (vorbis: packet splitter, dispatch loop, bit reader) |

### Music player / AUDSimple API

Single global player object at **bss 0x8039D940** (size 0x194 bytes), built
as `lis r9,-0x7fc6; addi r9,r9,-0x26c0`.

Function map:

| Address | Purpose |
| --- | --- |
| 0x80120880+ | AUDSimple init: ctor (strings at 0x801205D0/0x8012063C), then init decoder with `music/ogg/` base path (string at 0x80302F30), clears player fields 0xc4/0xc8 |
| 0x80136234 | Player constructor (memset 0x194 via bl 0x8026afb8) |
| 0x80136be4 | Decoder init: resolve stream name (0x802456ac, -1 = fail), info lookup 0x802459a0 (flag bit test), create stream player 0x80245a38 (queue at 0x8039dae0, capacity 0x20, callback 0x80136888, count 2); name copied to +0x44, flag set at +0xc0 |
| 0x80136d30 | Player tick: walks circular list of 10 chunk entries (table +0xf8, index +0xe8, mod-10 via 0xcccccccd), scans for `AUDD` (0x41554444) `[tag:4][size:4]` chunks, submits via 0x80135c80 |
| 0x80120924 | Player tick/update; fields 0xac/0xb0/0xb4/0xbc/0xc0/0x190 |
| 0x801367d8, 0x80136cac | Playback state loops |
| 0x801365b0 | Teardown; calls decoder close 0x8024ea94 |
| 0x80135afc | Output stage: MSR save/restore via 0x80264768, interleaves into double-buffered 0x400-halfword-per-channel blocks; ring positions at r13 -0x2b14/-0x2b10/-0x2b0c/-0x2b18/-0x2b1c, channel count at -0x2b0c |

Error strings (all in section 8 data):

| Address | String |
| --- | --- |
| 0x8029d778 | `c:/nxcommon_skate6/code/gel/music/NGC/p_music.cpp` |
| 0x8029d7ac | `*** AUDSimpleAllocDVDBuffers failed!` |
| 0x8029d7d4 | `*** AUDSimpleCreateDecoder failed!` |
| 0x8029d7f8 | `*** AUDSimpleInitAudioDecoder failed!` |
| 0x8029d830 | `streams/streamsn.wad` |

Direct code xrefs to these strings have not been found by lis/addi scans, and
section 9 holds no pointer constants to the driver functions
(0x8024eec0/0x8024ead4/0x80252d7c/0x8024ea94) or any `vorbis` literals; they
are probably referenced through .data assert tables or r13 (SDA). The strings
confirm the module is Neversoft's own code
(`c:/nxcommon_skate6/...`, real path on the dev machines).

The script/stream system also has a cue table (`LevelEvents/...`, `Story/...`
strings at 0x8029d874-0x8029db44) used by a script cue executor near
0x8011fc98.

## Decoder module (0x8024xxxx)

Called from the player. Round-2 reversal corrected the earlier map: 0x802456ac
is NOT a decoder create; it resolves a stream name against a table.

| Address | Purpose |
| --- | --- |
| 0x802456ac | **Stream-table path resolver**: parses `/`, `.`, `..` against a 12-byte-entry stream table at r13-0x781c (SDA references at 0x80245680/0x80245694/0x802456a4), name compare via 0x80269f30; returns entry ID or -1 |
| 0x802459a0 | Stream info lookup (flag bit test) after name resolution |
| 0x80245a38 | Create stream player; destroy = 0x80245a14 |
| 0x80248074 | Decoder state machine/update. Callers: 0x80121d0c, 0x80136814, 0x80245a20 |
| 0x8024ea94 | Decoder close/free. Callers: 0x80136594, 0x801365cc, 0x80249918, 0x8024996c |

Stream/demux machinery:

| Address | Purpose |
| --- | --- |
| 0x8024e9d0-0x8024f400 | Registry layer: 0x8024ea14 registers callbacks into r13 SDA (-0x7f3c/-0x7f38/-0x7f40); 0x8024ead4 submit (thin wrapper: bl 0x80252d7c); 0x8024ebd8 free; 0x8024ee00 ring alloc (size rounded up +0x10 words, -1 sentinel); 0x8024ee6c ring free; 0x8024eec0 dispatches the -0x7f40 callback; 0x80249a00 registers 3 fns (-0x7f60/-0x7f5c/-0x7f58) |
| 0x8024e114 | Video buffer get, used 13x by the movie decoder (0x8024a724-0x8024ae2c) |

Audio submission chain: player tick 0x80136d30 finds `AUDD` chunks →
0x80135c80 → 0x8024ead4 (submit) → 0x80252d7c (decode driver) with **mode 3**
(music). Movie path (0x802499cc) uses **mode 8**; mode 0 → -1.

## Audio decode engine (0x80252000-0x80258000)

Integer/fixed-point vorbis engine:

| Address | Purpose |
| --- | --- |
| 0x80252c3c / 0x80252c90 | Engine client-object init / free |
| 0x80252d7c | Main decode driver: mode dispatch (3 = music; 8 = movie, caller 0x802499cc; 0 → -1); `mtspr 0x396, 0x0f070f07` (disables FP exceptions) |
| 0x80252ec8 | Packet splitter / header parser |
| 0x8025302c / 0x80253054 | Queue init |
| 0x802533b0, 0x80253dbc, 0x80253ea0, 0x80253ef0, 0x80253fb8, 0x80253ff4 | Queue ops; 0x80253ef0 is the dispatch loop using `mtlr/blrl` callbacks (music callback 0x80135afc) |
| 0x80254000 | Buffer-list dispatch |
| 0x80254720 / 0x80254764 | Decode init |
| 0x80257cc4 | memset helper |
| 0x80257e48 | **Bit reader, MSB-first** (Tremor's oggpack is LSB-first) |

Float constants for the degree→radian rotation (not an MDCT) live in section
8 at 0x802b1330-0x802b1348: 176.0, 0.0, 1.0, 0.5, pi, 180.0, 120.0. Used by
0x802445e8 (only caller 0x8024548c), which rotates via sin/cos
(0x80271070/0x80271170).

Needs work: function boundaries, the packet demux (type dispatch on the
vorbis packet header byte 1/3/5 = ID/comment/setup, 0 = audio), the
codebook/floor/residue readers inside 0x80252xxx, and the mode-dispatch
target table (what mode 3 vs 8 select).

## Vorbis decoder provenance

Searched the whole DOL (all sections, big-endian u32 comparisons) for Xiph
Tremor and libvorbis tables:

| Table (source) | First values | Found? |
| --- | --- | --- |
| Tremor `sincos_lookup0[1026]` (mdct_lookup.h) | 0x00000000, 0x7fffffff, 0x003243f5, 0x7ffff621 | no |
| Tremor `FROMdB_LOOKUP[35]` (lsp_lookup.h) | 0x003fffff, 0x0028619b, 0x00197a96, 0x0010137a | no |
| Tremor `FROMdB2_LOOKUP[32]` | 0x000001fc, ... | no |
| Tremor `COS_LOOKUP_I[129]` | 16384, 16379, 16364, 16340, 16305, 16261, 16207, 16143 | no |
| Tremor `INVSQ_LOOKUP_I` (floor0.c) | 92682, 91966, 91267, 90583, 89915, 89261, 88621, 87995 | no |
| libvorbis `FLOOR1_fromdB` floats | 1.0649863e-07, 1.1341951e-07, ... | no |
| libvorbis `mdct_sine_window_1024/2048` | (not yet searched) | ? |

Tremor reference: `<scratch> (gitlab.xiph.org/xiph/tremor,
commit bbef83c, 2002-10-16, THUG2-era).

Supporting evidence :

- FPU-density scan over the codec range: the float-heavy blocks are
  0x80241000 (267 FPU/4K) and 0x80242000 (280/4K) = **3D matrix math**
  (0x80241000 is a matrix-vector multiply via bl 0x80003eb0), not audio.
  The decode engine 0x80252000-0x80258000 is essentially integer-only.
- 0x80253e/0x80254/0x80255 float spots are permutation/bit-reversal builders
  (0x80255000 builds a perm table), not MDCT kernels.
- Bit reader 0x80257e48 reads MSB-first; Tremor's oggpack_reader is LSB-first
  (`oggpack_look` on little-endian bit order). Same decoder cannot be both.

Verdict: not stock Tremor, not stock libvorbis. Custom fixed-point decoder
with custom (or runtime-computed) tables.

## Movie decoder (M4 / MPEG-1)

- Strings: `M4Decoder.cpp` at 0x802b1448 (assert file), `Invalid B-frame
  type` at 0x802b1458; assert site at 0x8024ae88 (`M4Decoder.cpp` line
  offset +0x392).
- Float/IDCT kernel at **0x8024ef18**: prologue saves 18 doubles
  (`stfd f14-f31`), FPSCR setup (`mtspr 0x397`), float constants from a pool
  at 0x8023f284; called only from 0x8024b19c, 0x8024b63c, 0x8024ba14,
  0x8024c07c (all in the movie region).
- **VMX anomaly**: at 0x8024eff8+ raw bytes decode to genuine Altivec
  (`vmhaddshs`, opcode 4, XO 0x210). Gekko has no VMX; this kernel is
  probably dead code on GC (or a never-taken port). Unresolved.
- Movie decode kernels sit after 0x8024f400 (e.g. bl 0x802518d8 used by
  movie decoder functions).
- Movie audio path enters the same decode engine as music but with
  **mode 8** via 0x802499cc (vs mode 3 for music). Whether the payload is
  AC-3 or vorbis at this point is still open.

## Disc image findings

Source: rebuilt `<scratch> from the RVZ (2026-10-04 pass also
used a second rebuild at `<scratch>, 1,459,978,240 bytes,
validated by volume descriptor: `G2TE52` at 0x0, "Tony Hawk's Unde..." at
0x20).

- FST offsets from boot.bin (ISO offset 0x424) did not resolve; FST
  entry parsing is incomplete/unreliable.
- Signature counts over the whole disc:
  - MPEG-1 sequence header `00 00 01 b3`: 1782 (FMV region 0-64 MB, plus
    256-304 MB; nothing past 304 MB except stray singles)
  - AC-3 sync word `0b 77`: 12988; dense in 0-64 MB and 256-304 MB (same
    region as MPEG-1), spurious matches spread everywhere else
  - Vorbis ID header `01 vorbis`: 187, all in 736-992 MB (music files)
  - `OggS`: 0 (no Ogg framing anywhere)
- Vorbis stream bytes (first found at ISO 0x128fe792):
  `0d 0a 56 49 44 31 <u32 len> ... 48 45 41 44` (`\r\n` + `VID1` + length,
  then `HEAD` chunk), then `VIDH` (video header, u32 len), `AUDH` (audio
  header, len 0x1080), `VAUD` (audio data, len 0xbb80 = 48000), payload =
  raw vorbis packets back-to-back: `01 vorbis` ID header, `03 vorbis`
  comment with vendor `BCV`, `05 vorbis` setup (all 0xBB80 = 48 kHz
  signatures). Movie region carries the same HEAD/VIDH/AUDH/VAUD chunks.

## Full-disc codec verification (2026-10-04)

The RVZ was converted to a raw ISO and **every byte of the 1.46 GB image was
scanned** for codec magics. This was done because a DOL string scan cannot
answer the question: a statically linked library such as Bink ships as
`.text` + `.data` only, its version/copyright banners are referenced by no
code path, and the game never opens a `.bik`, so no extension string is ever
linked in. **Absence of strings is the expected state whether Bink is
present or not** and carries no information either way.

Raw counts over the whole image:

| Signature | Count | Verdict |
| --- | --- | --- |
| `BIKF` | 3 | **spurious** |
| `BIKS` | 1 | **spurious** |
| `BIKi` / `BIKE` | 0 | absent |
| `THP\0` | 1 | **spurious** |
| `.thp` / `.bik` extension | 0 / 0 | absent |
| MPEG-1 sequence header `00 00 01 b3` | 1782 | real |
| MPEG-1 GOP `00 00 01 b8` | 2567 | real |
| AC-3 sync `0b 77` | 13379 | real |
| `VID1` / `AUDH` / `VAUD` | 188 / 191 / 197 | real |
| `vorbis` (ASCII) | 374 | real |
| `OggS` | 0 | real (no Ogg framing) |

The MPEG-1 sequence-header count reproduces exactly (1782 in both passes),
which cross-validates the two scans. The AC-3 count differs (12988 above vs
13379 here) because the earlier pass appears to have counted only pairs that
pass a basic sync-word plausibility check, whereas 13379 is a raw `0b 77`
byte-pair count and so includes spurious pairs in non-AC-3 data — the
original note "spurious matches spread everywhere else" still applies. Treat
AC-3 counts as approximate and region-based, not exact. Likewise the 187
`01 vorbis` ID headers above and the 374 raw ASCII `vorbis` occurrences here
count different things (per-file ID headers vs every occurrence of the
substring, of which each Vorbis stream has several).

The three `BIKF` and one `BIKS` hits are **false positives**, not containers:

- Parsing the `BIKF` header at those offsets yields nonsense
  (`width=1094073155`, `height=1162299461`, `size=1,195,262,779`).
- The bytes immediately following the magic are ASCII text
  (`G>C;A6;CEGHEF`), not a header.
- All three `BIKF` hits have **byte-identical surrounding context** — they are
  coincidental sequences inside repeated asset data.

Do not cite these as evidence of Bink. Re-verify with the header parse before
reaching for the string again. The lone `THP\0` hit is spurious by the same
test — it lands in a Gekko instruction stream and its header parse is
nonsense.

### Two DOL-side artifacts that are easy to misread

- **Zigzag table at 0x80306C98.** A byte-exact 64-byte MPEG-1 zigzag
  (`0,1,8,16,9,2,3,10,...`) followed by the complementary 2x2 block-order
  table. It looks like strong evidence of a live MPEG decoder, but it is
  **unreferenced**: zero 32-bit pointers in any loaded section, and zero
  instruction displacements (`lis`/`addi`/`ori`, or any base+offset) reaching
  it. It sits amid `"Disk #"`, `"Game version"`, `"Streaming %s"` strings and
  character-ramp tables in section 9. Treat as dead/incidental data; the MPEG
  identification rests on the disc evidence, not on this table.
- **`THPS4` / `GetMaxTHPS4FilesAllowed`.** THUG's **save** format. Not a video
  container marker — see Conclusions.

### Why code-side magic searches come up empty

None of `VID1`, `AUDH`, `VAUD`, `THP\0`, or any Bink magic (`BIKF`/`BIKi`/
`BIKS`) appear as constants in the DOL (0 hits in every loaded section). This
is expected and is
why the container cannot be identified by scanning `.text`/`.data`: the parser
matches chunk tags at runtime against bytes read from media, so no literal is
embedded. The same caveat applies to the unresolved AUDSimple string xrefs
below.

## Open items

- [x] Identify the float block at 0x802444a0: resolved - it is a degree→radian
      sin/cos rotation (float pool 176.0/180.0/120.0/pi at 0x802b1330,
      sec 8), called only from 0x8024548c. Not a vorbis or AC-3 MDCT.
- [x] Bit reader: found at 0x80257e48, MSB-first - inconsistent with Tremor.
- [ ] Full reverse of the decode engine 0x80252xxx: packet demux (type
      dispatch on vorbis packet header byte 1/3/5 = ID/comment/setup,
      0 = audio), codebook/floor/residue readers vs Tremor structure.
- [ ] Mode-dispatch target table in 0x80252d7c (what mode 3 = music vs 8 =
      movie select), and trace the -0x7f40 callback resolution at 0x8024eec0.
- [ ] Movie path (0x802499cc, mode 8): confirm the code-side payload is AC-3.
      Disc-side correlation is **done** (2026-10-04): MPEG-1 and AC-3 share
      the FMV regions 0-64 MB and 256-304 MB, Vorbis/music is 736-992 MB, so
      FMV = MPEG-1 + AC-3. What remains is proving mode 8 selects the AC-3
      decoder rather than the Vorbis one inside the DOL.
- [ ] Resolve the VMX kernel at 0x8024eff8 (dead code on Gekko?).
- [ ] Find xrefs to the AUDSimple fail strings (scan section 9 .data for
      pointer constants 0x8029d7ac/0x8029d7d4/0x8029d7f8/0x8029d778/
      0x8029d830 and 0x80302f30).
- [ ] Finalize FST parsing to map files to regions (music/ogg vs movies).
      Status 2026-10-04: still unresolved. The GC ISO root-directory record at
      0x4400 did not decode with standard ISO-9660 field offsets (both-endian
      extent/data-length at 2 and 0x1A); a corrected parse is needed to get
      FMV filenames. Signatures above are region-based, not file-based.
- [x] Is Rad Game Tools / Bink linked? **No** — verified against the full
      decompressed disc, 2026-10-04. See the verification section.
- [ ] Identify the movie/M4 wrapper at 0x8024f400-0x80252000 by control-flow
      shape (the codec is certain; the in-house wrapper is not characterised).