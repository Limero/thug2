// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8025B340-0x8025B554 (532B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

register unsigned int *ctx_r31 __asm__("r31");

typedef struct {
    char pad_000[0x348];
    unsigned int xer;
    char pad_34c[4];
    unsigned int ctr;
    char pad_354[0x380 - 0x354];
    unsigned int hid0;
    char pad_384[4];
    unsigned int hid1;
    char pad_38c[4];
    unsigned int hid2;
    char pad_394[4];
    unsigned int iba0u;
    char pad_39c[4];
    unsigned int iba0l;
    char pad_3a4[4];
    unsigned int iba1u;
    char pad_3ac[4];
    unsigned int iba1l;
    char pad_3b4[4];
    unsigned int iba2u;
    char pad_3bc[4];
    unsigned int iba2l;
    char pad_3c4[4];
    unsigned int iba3u;
    char pad_3cc[4];
    unsigned int iba3l;
    char pad_3d4[4];
    unsigned int dba0u;
    char pad_3dc[4];
    unsigned int dba0l;
    char pad_3e4[4];
    unsigned int dba1u;
    char pad_3ec[4];
    unsigned int dba1l;
    char pad_3f4[4];
    unsigned int dba2u;
    char pad_3fc[4];
    unsigned int dba2l;
    char pad_404[4];
    unsigned int dba3u;
    char pad_40c[4];
    unsigned int dba3l;
    char pad_414[4];
    unsigned int sprg4;
    char pad_41c[4];
    unsigned int sprg5;
    char pad_424[4];
    unsigned int sprg6;
    char pad_42c[4];
    unsigned int sprg7;
    char pad_434[4];
    unsigned int dar;
    char pad_43c[4];
    unsigned int dsisr;
    char pad_444[4];
    unsigned int spr282;
    char pad_44c[4];
    unsigned int spr1013;
    char pad_454[4];
    unsigned int spr284;
    char pad_45c[4];
    unsigned int spr285;
    char pad_464[4];
    unsigned int spr1017;
    char pad_46c[4];
    unsigned int spr22;
    char pad_474[4];
    unsigned int spr1010;
    char pad_47c[4];
    unsigned int spr953;
    char pad_484[4];
    unsigned int spr954;
    char pad_48c[4];
    unsigned int spr957;
    char pad_494[4];
    unsigned int spr958;
    char pad_49c[4];
    unsigned int spr955;
    char pad_4a4[4];
    unsigned int spr952;
    char pad_4ac[4];
    unsigned int spr956;
    char pad_4b4[4];
    unsigned int spr1016;
    char pad_4bc[4];
    unsigned int spr1018;
    char pad_4c4[4];
    unsigned int spr1020;
    char pad_4cc[4];
    unsigned int iccr;
    char pad_4d4[4];
    unsigned int spr25;
    char pad_4dc[4];
    unsigned int pvr;
    char pad_4e4[4];
    unsigned int spr922;
    char pad_4ec[4];
    unsigned int spr923;
    char pad_4f4[4];
    unsigned int spr921;
    char pad_4fc[4];
    unsigned int sr0;
    char pad_504[4];
    unsigned int sr1;
    char pad_50c[4];
    unsigned int sr2;
    char pad_514[4];
    unsigned int sr3;
    char pad_51c[4];
    unsigned int sr4;
    char pad_524[4];
    unsigned int sr5;
    char pad_52c[4];
    unsigned int sr6;
    char pad_534[4];
    unsigned int sr7;
    char pad_53c[4];
    unsigned int sr8;
    char pad_544[4];
    unsigned int sr9;
    char pad_54c[4];
    unsigned int sr10;
    char pad_554[4];
    unsigned int sr11;
    char pad_55c[4];
    unsigned int sr12;
    char pad_564[4];
    unsigned int sr13;
    char pad_56c[4];
    unsigned int sr14;
    char pad_574[4];
    unsigned int sr15;
} ctx_t;

#define SAVE_SPR(spr, field) do { __asm__ volatile("mfspr %0, " #spr : "=r"(v)); ((ctx_t *)ctx_r31)->field = v; } while (0)
#define SAVE_SR(sr, field) do { __asm__ volatile("mfsr %0, " #sr : "=r"(v)); ((ctx_t *)ctx_r31)->field = v; } while (0)
#define SAVE_REG(reg, field) do { __asm__ volatile(#reg " %0" : "=r"(v)); ((ctx_t *)ctx_r31)->field = v; } while (0)
#define SAVE_WORD(word, field) do { __asm__ volatile(".long " #word : "=r"(v)); ((ctx_t *)ctx_r31)->field = v; } while (0)

void fn_8025B340(void) {
    register unsigned int v __asm__("r5");
    __asm__ volatile("mfxer %0" : "=r"(v));
    ((ctx_t *)ctx_r31)->xer = v;
    __asm__ volatile("mfctr %0" : "=r"(v));
    ((ctx_t *)ctx_r31)->ctr = v;
    SAVE_SPR(0x3f0, hid0);
    SAVE_SPR(0x3f1, hid1);
    SAVE_SPR(0x210, iba0u);
    SAVE_SPR(0x211, iba0l);
    SAVE_SPR(0x212, iba1u);
    SAVE_SPR(0x213, iba1l);
    SAVE_SPR(0x214, iba2u);
    SAVE_SPR(0x215, iba2l);
    SAVE_SPR(0x216, iba3u);
    SAVE_SPR(0x217, iba3l);
    SAVE_SPR(0x218, dba0u);
    SAVE_SPR(0x219, dba0l);
    SAVE_SPR(0x21a, dba1u);
    SAVE_SPR(0x21b, dba1l);
    SAVE_SPR(0x21c, dba2u);
    SAVE_SPR(0x21d, dba2l);
    SAVE_SPR(0x21e, dba3u);
    SAVE_SPR(0x21f, dba3l);
    SAVE_SR(0, sr0);
    SAVE_SR(1, sr1);
    SAVE_SR(2, sr2);
    SAVE_SR(3, sr3);
    SAVE_SR(4, sr4);
    SAVE_SR(5, sr5);
    SAVE_SR(6, sr6);
    SAVE_SR(7, sr7);
    SAVE_SR(8, sr8);
    SAVE_SR(9, sr9);
    SAVE_SR(0xa, sr10);
    SAVE_SR(0xb, sr11);
    SAVE_SR(0xc, sr12);
    SAVE_SR(0xd, sr13);
    SAVE_SR(0xe, sr14);
    SAVE_SR(0xf, sr15);
    SAVE_SPR(0x110, sprg4);
    SAVE_SPR(0x111, sprg5);
    SAVE_SPR(0x112, sprg6);
    SAVE_SPR(0x113, sprg7);
    SAVE_REG(mfdar, dar);
    SAVE_REG(mfdsisr, dsisr);
    SAVE_SPR(0x11a, spr282);
    SAVE_SPR(0x3f5, spr1013);
    SAVE_SPR(0x11c, spr284);
    SAVE_SPR(0x11d, spr285);
    SAVE_SPR(0x3f9, spr1017);
    SAVE_SPR(0x16, spr22);
    SAVE_SPR(0x3f2, spr1010);
    SAVE_SPR(0x3b9, spr953);
    SAVE_SPR(0x3ba, spr954);
    SAVE_SPR(0x3bd, spr957);
    SAVE_SPR(0x3be, spr958);
    SAVE_SPR(0x3bb, spr955);
    SAVE_SPR(0x3b8, spr952);
    SAVE_SPR(0x3bc, spr956);
    SAVE_SPR(0x3fc, spr1016);
    SAVE_SPR(0x3fd, spr1018);
    SAVE_SPR(0x3fe, spr1020);
    SAVE_WORD(0x7cbbfaa6, iccr);
    SAVE_SPR(0x19, spr25);
    SAVE_REG(mfpvr, pvr);
    SAVE_SPR(0x39b, spr923);
    SAVE_SPR(0x39a, spr922);
    SAVE_SPR(0x399, spr921);
    SAVE_SPR(0x398, hid2);
}

// PARKED 2026-09-25 — POLICY-BLOCKED, despite a byte-exact standalone object.
//
// VERIFIED BODY: symbols.txt size 0x214 (532B / 133 instructions). The retail
// function starts at 0x8025B340 with `mfxer r5`, has no stack adjustment, LR
// save, argument move, or callee-saved prologue, and ends at 0x8025B550 with
// `blr`. It consists of 66 privileged reads, 66 `stw r5,off(r31)` pairs, and
// the return. XER, CTR, HID0/1/2, IBAT/DBAT, SR0-15, SPRG4-7, DAR, DSISR,
// ICCR, PVR, DMA/debug SPRs, and WPAR are saved into ctx offsets 0x348-0x578.
//
// NO-PROLOGUE / INCOMING-R31 CLAIM: CONFIRMED. At 0x8025B6F4, the context
// save path explicitly builds r31=0x803CA4A0 at 0x8025B658/0x8025B65C, uses
// r31 for the GPR, CR, and MSR stores, and calls this function with no r3
// argument setup. The paired call at 0x8025BBE4 is later in the same save
// sequence and likewise arrives with r31 as the context base. The old claim
// that a function-local r31 pin necessarily adds an entry `mr` is false: the
// file-scope `register ... __asm__("r31")` emits bare r31-relative accesses
// with no prologue, as already proven by src/fn_8025AF7C.c.
//
// BEST VERIFIED SOURCE: the body above compiles to exactly 532/532 bytes and
// scores EXACT 100.0% with `test_wip_drafts.py --addr 0x8025B340`. The 66
// stores are real C structure stores; the value web is pinned to r5. Each
// privileged read needs one inline-asm instruction. `mficcr` is not accepted
// by ngcas 1.0.25.836, so its exact `mfdar`-style opcode is emitted as one
// isolated `.long` word; this is not a whole-body asm transcription.
//
// EXACT TECHNICAL BLOCKER: 66 of 133 instructions (49.6%) are inline asm,
// exceeding both project limits (<30% and <=24 instructions; recipe 180).
// There is no ordinary C expression for these SPR/SR reads, and no smaller
// source-level route was found. Promoting this exact object would make objdiff
// report a match while roughly half the function remains transcribed asm, so
// leave it inert. Do not promote. A future shared blob split that includes the
// caller/control-flow unit could make the entire assembly region one explicit
// auto-asm owner, but this standalone pseudo-function remains parked.
