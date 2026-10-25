// WIP DRAFT (non-matching) — hand-rebuild from the want disassembly
// family=m2c range=0x80122C40-0x801232EC size=1708B
// PARKED 2026-10-03 (b04): DIFF, masked 23/427 words = 5.4%; object .text
// 1608B vs want 1708B (25 instructions short).  Baseline was FAIL (the m2c
// draft did not compile: 7-arg memset).  Reproduce with
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x80122C40
// (use <scratch> for a MASKED word diff + pct; want_vs_got.py
// compares RAW words and lies about every lis/lfs).
//
// WHAT IS ALREADY EXACT (verified instruction-for-instruction):
//   * prologue/epilogue: stwu r1,-0xd0(r1); mflr; stmw r22,0xa8(r1); stw r0,0xd4(r1)
//     and the matching lmw/la/blr — frame 0xd0, r22-r31 saved.
//   * frame layout byte-for-byte: mix[2]@0x08 (0x48 slot), src@0x50 (14B),
//     addr@0x60 (16B), adpcm@0x70 (0x28), ve@0x98 (4B), shared f64 temp@0xa0.
//   * 154/427 instructions are byte-identical (whole float conversion blocks,
//     the do-while 0x800 ramp, the memset/DCFluash/AX call sequence, stores).
//   * the switch shape (`if NONE return 0` + if/else-if chain + `!= MCPA`
//     -> OSPanic) reproduces the want's compare chain exactly.
//
// KEY FINDINGS (reusable):
//   1. A 36-byte struct local gets a 0x28 frame slot (ngccc pads aggregates
//      to 8).  Two of them therefore CANNOT be the want's layout — the want
//      has them 0x24 apart.  `AXPBMIX mix[2]` (array) gives one 0x48 slot with
//      0x24 stride, which is what reproduces sp+0x08 / sp+0x2C.  Measured:
//      2 separate locals -> mixL@0x08 mixR@0x30 (wrong); mix[2] -> correct.
//   2. float->int needs the recipes-112 manual dodge, NOT a plain `(s32)f`:
//        if (!(f >= K_d)) a = (s32)f; else { a = (s32)(f - K_d); a ^= 0x80000000; }
//      with `extern f64 lbl_8029E2B8;` (= 2^31) as the real rodata2 pool.
//      A bare `(s32)f` emits a bare `fctiwz` with no cror/bso guard and no
//      xoris.  Inside this function the guard DOES come out as `cror
//      cr0un,cr0eq,cr0gt` + `bso` (BO=3); in isolated micro-tests GCC emits
//      the same cror with BO=12 (`bge`), so do not trust micro-tests here.
//   3. `extern s32 fn_XXXX;` (a VARIABLE) makes `*(s32*)p = (s32)fn_XXXX`
//      compile to `lwz` (a READ of the function's first instruction — wrong);
//      declare them `extern void fn_XXXX(void);` to get lis+addi.
//   4. `u32 a; ... a >> 16` gives `srwi` (want); `s32 a` gives `srawi`.
//   5. int->f64 casts: the object still carries an 8-byte private .rodata
//      (GCC's own 0x4330000000000000) instead of the game's lbl_8029E2A8.
//      Hand-writing the union dance against `extern f64 lbl_8029E2A8` removes
//      the private rodata but gives `d` its OWN 8-byte slot, pushing the fctiwz
//      temp off sp+0xa0 to sp+0xb0 and the whole frame out of shape (tried,
//      reverted).  This is a genuine promotion blocker to solve.
//
// REMAINING DIFF / Ruled out:
//   * 25 instructions short.  The bulk is GCC duplicating `lis` per global in
//     two regions where it shares instead: the 6 zero-stores at 0x80122F30-74
//     (want emits 7 `lis` + 2 `li`, got emits 4) and the `addi r10,r9,-0x41a4`
//     address-in-a-register + `mr r9,r11` dead insn in each switch arm.
//     Both are register-allocation / reload choices, not source shape.
//   * ROUNDED OUT: plain `(s32)f` (loses cror/bso+xoris, 3 words per site);
//     separate AXPBMIX locals (wrong frame); absolute literals instead of
//     lbl_ symbols (verified in an isolated test: literals give
//     `lis HI; lfs 0(r)` while symbols give `lis @ha; lfs @l(r)` — but both
//     reloc types 4/6 ARE masked, so this is a wash; don't bother).
//   * MOST PROMISING NEXT IDEA: chase the 6-zero-store `lis` duplication with
//     explicit `s32 *`-typed locals for the six globals (they are separate
//     lbl_ objects, so giving each a named pointer forces one base reg each),
//     then re-check whether the two switch arms' extra `addi`/`mr` appear.
//     UPDATE 2026-10-11 (rand3): block-scoped `s32 *pXX` locals for the six
//     zero-stores measured - object comes out 100B SHORT (region collapses),
//     so the idea fails in this form; reverted. Do NOT chase register numbers directly — 23 of the 404 masked diffs are
//     r6-vs-r31 style base-register roulette that the positional scorer cannot
//     reward until the counts line up.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// 2026-10-03 b04: hand-rebuild from the want (m2c draft did not compile —
// 7-arg memset).  Structs re-derived from the AX param-buffer layout:
// 0x24 mix, 14-byte src, 16-byte addr (u32 addrs), 0x28 adpcm, 4-byte ve.
#include "types.h"

extern char lbl_8029DEB4[];
extern char lbl_8029E248[];
extern char lbl_8029E260[];
extern char lbl_8029E284[];
extern f32 lbl_8029E2B0;
extern f64 lbl_8029E2B8;
extern f32 lbl_8029E2C0;
extern f32 lbl_8029E2C4;
extern f32 lbl_8029E2C8;
extern f32 lbl_8029E2CC;
extern f32 lbl_8029E2D0;
extern char lbl_8037B5E8[];
extern f32 lbl_8039BAF4;
extern char lbl_8039BA58[];
extern char lbl_8039BB00[];
extern char lbl_8039BE58[];
extern char lbl_8039BE5C[];
extern char lbl_8039BE60[];
extern char lbl_8039BE64[];
extern char lbl_8039BE68[];
extern char lbl_8039BE6C[];
extern char lbl_8039BE78[];
extern char lbl_8039BE7C[];
extern char lbl_8039BE80[];
extern char lbl_8039BE84[];
extern char lbl_8039BE88[];
extern char lbl_8039BE8C[];
extern char lbl_8039BE90[];
extern char lbl_8039BE94[];
extern char lbl_8039BE98[];
extern char lbl_8039BE9C[];
extern char lbl_8039C2A4[];
extern char lbl_8039C2A8[];
extern f32 lbl_8039C2AC;
extern char lbl_8039C2B0[];
extern char lbl_8039C2B4[];
extern void fn_80123408(void);
extern void fn_8012355C(void);
extern void fn_80123570(void);
extern void fn_80123584(void);
extern void fn_80123668(void);
extern void fn_8012367C(void);
extern void fn_80123BE0(void);

void memset(void *, s32, u32);
void DCFlushRange(void *, u32);
s32 OSDisableInterrupts(void);
void OSRestoreInterrupts(s32);
void OSPanic(char *, s32, char *);

typedef struct {
    u16 vL;
    u16 vDeltaL;
    u16 vR;
    u16 vDeltaR;
    u16 vAuxAL;
    u16 vDeltaAuxAL;
    u16 vAuxAR;
    u16 vDeltaAuxAR;
    u16 vAuxBL;
    u16 vDeltaAuxBL;
    u16 vAuxBR;
    u16 vDeltaAuxBR;
    u16 vAuxBS;
    u16 vDeltaAuxBS;
    u16 vS;
    u16 vDeltaS;
    u16 vAuxAS;
    u16 vDeltaAuxAS;
} AXPBMIX;

typedef struct {
    u16 ratioHi;
    u16 ratioLo;
    u16 currentAddressFrac;
    u16 last[4];
} AXPBSRC;

typedef struct {
    u16 loopFlag;
    u16 format;
    u32 loopAddress;
    u32 endAddress;
    u32 currentAddress;
} AXPBADDR;

typedef struct {
    u16 coef[16];
    u16 gain;
    u16 predScale;
    u16 yn1;
    u16 yn2;
} AXPBADPCM;

typedef struct {
    u16 currentVolume;
    s16 currentDelta;
} AXPBVE;

s32 AXAcquireVoice(s32, s32, s32);
void AXSetVoiceMix(void *, AXPBMIX *);
void AXSetVoiceVe(void *, AXPBVE *);
void AXSetVoiceSrcType(void *, s32);
void AXSetVoiceSrc(void *, AXPBSRC *);
void AXSetVoiceAddr(void *, AXPBADDR *);
void AXSetVoiceAdpcm(void *, AXPBADPCM *);
void AXSetVoiceType(void *, s32);
void AXRegisterCallback(s32);

typedef struct {
    s32 (*unk0)(s32);
    char pad4[0x98];
    f32 unk9C;
    s32 unkA0;
    u32 unkA4;
    u8 unkA8;
} CB_t;

s32 fn_80122C40(void) {
    AXPBMIX mix[2];
    AXPBSRC src;
    AXPBADDR addr;
    AXPBADPCM adpcm;
    AXPBVE ve;
    CB_t *cb = (CB_t *)lbl_8039BA58;
    void **vp;
    s32 *p;
    s32 p0;
    s32 p1;
    s32 intr;
    s32 i;
    u32 a;
    f32 f1;

    if (cb->unkA0 == 0x4E4F4E45) {
        return 0;
    }
    if (cb->unkA0 == 0x56415544) {
        f1 = (f32)(f64)cb->unkA4 * lbl_8029E2B0 / cb->unk9C;
        if (!(f1 >= lbl_8029E2B8)) {
            a = (s32)f1;
        } else {
            a = (s32)(f1 - lbl_8029E2B8);
            a ^= (s32)0x80000000;
        }
        *(s32 *)lbl_8039BE5C = a;
        i = *(u8 *)lbl_8039BB00;
        if (i > 2U) {
            i = 2;
        }
        *(u8 *)lbl_8039BE68 = (u8)i;
        *(s32 *)lbl_8039BE84 = (s32)(void *)fn_80123584;
        *(s32 *)lbl_8039BE88 = (s32)(void *)fn_80123668;
        *(s32 *)lbl_8039BE8C = (s32)(void *)fn_8012367C;
    } else if (cb->unkA0 == 0x50433136) {
        f1 = (f32)(f64)cb->unkA4 * lbl_8029E2B0 / cb->unk9C;
        if (!(f1 >= lbl_8029E2B8)) {
            a = (s32)f1;
        } else {
            a = (s32)(f1 - lbl_8029E2B8);
            a ^= (s32)0x80000000;
        }
        *(s32 *)lbl_8039BE5C = a;
        i = *(u8 *)lbl_8039BB00;
        if (i > 2U) {
            i = 2;
        }
        *(u8 *)lbl_8039BE68 = (u8)i;
        *(s32 *)lbl_8039BE84 = (s32)(void *)fn_80123408;
        *(s32 *)lbl_8039BE88 = (s32)(void *)fn_8012355C;
        *(s32 *)lbl_8039BE8C = (s32)(void *)fn_80123570;
    } else if (cb->unkA0 != 0x4150434D) {
        OSPanic(lbl_8029DEB4, 0x59D, lbl_8029E248);
    }

    p0 = ((s32 (*)(s32))cb->unk0)(*(s32 *)lbl_8039BE5C * (cb->unkA8 * 2));
    *(s32 *)lbl_8039BE58 = p0;
    if (p0 == 0) {
        return 1;
    }
    *(u32 *)lbl_8039BE78 = cb->unkA4;
    *(s32 *)lbl_8039BE60 = 0;
    *(s32 *)lbl_8039BE64 = 0;
    p1 = ((s32 (*)(s32))cb->unk0)(0x1000);
    *(s32 *)lbl_8039BE6C = p1;
    if (p1 == 0) {
        return 1;
    }

    p = (s32 *)lbl_8039BE6C + 1;
    i = 1;
    do {
        i += 1;
        p[0] = p[-1] + 0x800;
        p += 1;
    } while (i <= 1);

    *(s32 *)lbl_8039BE7C = 0;
    *(s32 *)lbl_8039BE98 = 2;
    *(s32 *)lbl_8039BE8C = 0;
    *(s32 *)lbl_8039BE80 = 0;
    *(s32 *)lbl_8039BE90 = 0;
    *(s32 *)lbl_8039BE94 = 0;
    memset((void *)p1, 0, 0x1000);
    DCFlushRange((void *)p1, 0x1000);
    intr = OSDisableInterrupts();
    vp = (void **)lbl_8039BE9C;
    vp[0] = (void *)AXAcquireVoice(0x1F, 0, 0);
    if (vp[0] == 0) {
        OSPanic(lbl_8029DEB4, 0x5C9, lbl_8029E260);
    }
    vp[1] = (void *)AXAcquireVoice(0x1F, 0, 0);
    if (vp[1] == 0) {
        OSPanic(lbl_8029DEB4, 0x5CB, lbl_8029E284);
    }
    memset(&mix[0], 0, 0x24);
    mix[0].vL = 0x7FFF;
    memset(&mix[1], 0, 0x24);
    mix[1].vR = 0x7FFF;
    AXSetVoiceMix(vp[0], &mix[0]);
    AXSetVoiceMix(vp[1], &mix[1]);
    ve.currentVolume = 0x7FFF;
    ve.currentDelta = 0;
    AXSetVoiceVe(vp[0], &ve);
    AXSetVoiceVe(vp[1], &ve);
    memset(&src, 0, 0xE);
    f1 = (f32)(f64)*(u32 *)lbl_8039BE78 * lbl_8029E2C0 / lbl_8029E2C4;
    if (!(f1 >= lbl_8029E2B8)) {
        a = (s32)f1;
    } else {
        a = (s32)(f1 - lbl_8029E2B8);
        a ^= (s32)0x80000000;
    }
    src.ratioHi = (u16)(a >> 0x10U);
    src.ratioLo = (u16)a;
    *(f32 *)&lbl_8039C2AC = (f32)(f64)*(u32 *)lbl_8039BE78;
    f1 = (f32)(f64)*(u32 *)lbl_8039BE78 * lbl_8029E2CC * (lbl_8029E2C8 / lbl_8039BAF4) *
         lbl_8029E2D0;
    if (!(f1 >= lbl_8029E2B8)) {
        a = (s32)f1;
    } else {
        a = (s32)(f1 - lbl_8029E2B8);
        a ^= (s32)0x80000000;
    }
    *(s32 *)lbl_8039C2B0 = a;
    AXSetVoiceSrcType(vp[0], 4);
    AXSetVoiceSrc(vp[0], &src);
    AXSetVoiceSrcType(vp[1], 4);
    AXSetVoiceSrc(vp[1], &src);

    addr.loopAddress = *(u32 *)(lbl_8037B5E8 + 0x198) >> 1U;
    addr.endAddress = addr.loopAddress + 0x3FF;
    addr.currentAddress = addr.loopAddress;
    addr.loopFlag = 1;
    addr.format = 10;
    AXSetVoiceAddr(vp[0], &addr);
    addr.currentAddress = (*(u32 *)(lbl_8037B5E8 + 0x198) >> 1U) + 0x400;
    addr.loopAddress = (*(u32 *)(lbl_8037B5E8 + 0x198) >> 1U) + 0x400;
    addr.endAddress = (*(u32 *)(lbl_8037B5E8 + 0x198) >> 1U) + 0x7FF;
    AXSetVoiceAddr(vp[1], &addr);

    memset(&adpcm, 0, 0x28);
    adpcm.gain = 0x800;
    AXSetVoiceAdpcm(vp[0], &adpcm);
    AXSetVoiceAdpcm(vp[1], &adpcm);
    AXSetVoiceType(vp[0], 1);
    AXSetVoiceType(vp[1], 1);
    AXRegisterCallback((s32)fn_80123BE0);
    *(u32 *)lbl_8039C2A4 = *(u32 *)(lbl_8037B5E8 + 0x198) >> 1U;
    *(s32 *)lbl_8039C2A8 = 0x400;
    *(s32 *)lbl_8039C2B4 = 0;
    OSRestoreInterrupts(intr);
    return 0;
}