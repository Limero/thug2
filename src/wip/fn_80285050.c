// PARKED 2026-10-10: the FAIL from tools/test_wip_drafts.py is
// STRUCTURAL, not a draft bug — no C edit can ever make it EXACT there.
// 0x80285050 is Dolphin-SDK code, compiled by mwcc GC/1.2.5n (configure.py
// DolphinLib: src_dir libs/dolphin, mw_version "GC/1.2.5n", cflags_dolphin),
// NOT ProDG/ngccc game code. The ngccc sweep compiles every draft with
// `-I include` only, so it cannot even see the SDK headers:
//   "dolphin/base/PPCArch.h: No such file or directory" (x5 headers)
// The metric that actually applies is the mwcc harness (GC/1.2.5n,
// cflags_dolphin, #pragma peephole off):
//   tools/venv/bin/python tools/mwcc_verify.py 0x80285050 src/wip/fn_80285050.c
//   -> DIFF 320/548 words (41.6% matched) size want=2192 got=2192  [SIZE-EXACT]
// RE-VERIFIED 2026-10-16: identical DIFF 320/548, size-exact. No C edit
// attempted (mwcc allocator-rename wall per the analysis below); body kept.
// REVIEWED 2026-10-18 (random triage): wall unchanged — retail IRO roles in
// the three loops remain unreachable from C; no new lever. Body untouched.
// Object .text SHA-1: 933c09c1afcd001a32909bb0a4b92f90f8fe0701.
//
// WIP DRAFT (non-matching) — hand reconstruction of thug2's Feb-7-2003 GXInit
// (Dolphin SDK/mwcc file, NOT game code). SMS donor + thug2 deltas; full
// derivation in docs/parkings/21-gxinit.md (attacks 1-6).
// family=hand range=0x80285050-0x802858E0 size=2192B
//
// 2026-10-10 IMPROVEMENT (320 bad, down from 364):
// The suTs body now carries source-like byte-offset and register-value
// inductions (`off`, `v0`, `v1`) and reuses one t0/t1 pair for all four
// coordinates. This is size-exact and improves the full-function masked score
// by 44 words. An exhaustive 120-permutation sweep of the five local
// declarations produced no further score change; moving declarations into
// narrower scopes, changing signedness, padding/frame forms, and retail-like
// running vat forms were also neutral or worse.
//
// PRIOR PASS (measured on the former best, 364 bad):
// 1. Bad-word clustering: 0x0144-0x0408 = 174 words (tevc loop 0x144-0x2D4 +
//    suTs loop 0x2D4-0x408), 0x044C-0x065C = 131 (vat preheader+loop), every
//    other region = 59. 305 of the 364 bad words live in the three loops.
// 2. The loops are NOT "shape" problems any more — they are pure register
//    renames. tevc is instruction-for-instruction identical to retail across
//    its whole 86-word body (checked word-by-word at +0x144..+0x1E8: every
//    mnemonic, order and offset matches; only r3/r4/r5... vs r4/r5/r6...),
//    and this draft's vat per-coord statement order ALREADY matches retail's
//    IRO temp-creation order (+0x518..+0x588 = vatA SET, vatB SET, U8(8),
//    U8(v), U32(vatB)). The six previous sessions' loop-shape work is done;
//    do NOT re-try body forms.
// 3. Prologue quantified. Both sides emit `stwu r1,-0x50(r1)`; `stmw rN`
//    saves rN..r31, so want's `stmw r25,0x34(r1)` = 28B saved + 52B of locals
//    and ours `stmw r23,0x2c(r1)` = 36B saved + 44B of locals: retail spills
//    exactly 8B (one slot) MORE while using 2 FEWER callee-saved regs. The
//    whole prologue/epilogue gap is 4 words (stmw, mr r27, mr r25, lmw).
// 4. NEW — the vat loop's 1-word preheader deficit, localised. Retail's
//    preheader is 7 words and holds `li r5, 8` (+0x50C) BETWEEN `mtctr` and
//    the two dead `b .+4`, used 4x in the body as `stb r5,-0x8000(r31)`.
//    Ours is 6 words and re-materialises `li r0, 8` inside the body. That one
//    missing word puts our vat loop head at +0x510 instead of +0x518 and is
//    the direct cause of the 131-word bad block 0x044C-0x065C. It is an mwcc
//    hoist-vs-rematerialise decision, not a source-semantics difference.
// 5. Retail materialises constant zero ONCE into saved r29 (+0x44C) and that
//    same register then BECOMES the vat counter induction: `mr r7,r29` seeds
//    the byte offset (+0x4FC), `ori r4,r29,0x80` builds v, `addi r29,r29,1`
//    counts — one long-lived saved register serving zero + counter + value.
//    We materialise zero twice (`li r29,0` for the dirtyState/dirtyVAT
//    stores, `li r10,0` for the vat offset seed) and hand the saved register
//    to the byte offset instead of the counter. A role swap not reachable
//    from C source.
//
// RULED OUT THIS PASS:
// - Hoisting the CP-command byte by hand: `u32 vatcmd = GX_LOAD_CP_REG;`
//   assigned before the vat loop and used by all four `GX_WRITE_U8(vatcmd)`.
//   -> DIFF 367/548 (33.0%), still size-exact, +1 bad in the prologue bucket
//   and +2 in the epilogue (the extra local shifts the `stmw` start). mwcc
//   does NOT keep it in a register across the loop: it still uses r0 inside
//   the body and now burns another local. Rejected; file left unchanged.
// - (disasm-only, no compile) Treating 8 / 0xff as named variables: see 4
//   and 5 — retail's single-materialisation points are allocator/scheduler
//   artifacts of retail's IRO, not source-level constants.
//
// PRIOR NOTES (2026-09-26): 364/548 via tools/mwcc_verify.py; object 548/548
// words (0x890 want, size-EXACT so vat/tex/tlut/tail align). suTs is k-form
// with per-iter byte base b=(k<<2) + one shared sequential temp t for all
// offsets/addresses (Agent A: +29 over stock); tail loop compares cast to
// (u32)j for retail cmplwi; tevc and suTs bdnz 0x408 exact.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress.
// MWCC-ONLY: the ngccc game-code sweep (tools/test_wip_drafts.py) CANNOT
// compile this file (SDK headers, peephole pragma) — its FAIL there is
// expected; do NOT "fix" it as game code. Do NOT refill with m2c
// (family=hand is skipped by fill_wip_drafts.py --force).
#include <dolphin/base/PPCArch.h>
#include <dolphin/gx.h>
#include <dolphin/gx/GX.h>
#include <dolphin/gx/GXInit.h>
#include <dolphin/os.h>

// thug2 GX.h already provides SET_REG_FIELD (4-arg plain-C form),
// PPCWGPipe + GXFIFO, GX_WRITE_U8/U32/XF_REG/RAS_REG, and GX_LOAD_BP_REG;
// only the CP/XF FIFO command bytes (0x08/0x10, confirmed against the
// retail disasm which writes raw 8 and 0x10) are local.
#define GX_LOAD_CP_REG 0x08
#define GX_LOAD_XF_REG 0x10

// Same-TU statics (prologue-hoist fix); FifoObj follows gxData at +0x4F8.
static GXData gxData;
static GXFifoObj FifoObj;
GXData* const gx = &gxData;

// Retail prologue externs (stay in auto-asm in the real build; declared
// here only so the standalone probe compiles).
extern char* __GXVersion;
extern u32 resetFuncRegistered;
extern OSResetFunctionInfo GXResetFuncInfo;

#pragma peephole off

GXFifoObj* GXInit(void* base, u32 size)
{
	u32 i;
	int k;
	int m;
	int j;
	u32 v;
	u32 reg;
	u32 freqBase;
	char stack_padding[8];

	OSRegisterVersion(__GXVersion);

	gx->inDispList    = FALSE;
	gx->dlSaveContext = TRUE;
	gx->abtWaitPECopy = TRUE;

	gx->tcsManEnab = FALSE;
	gx->tevTcEnab  = FALSE;
	GXSetMisc(GX_MT_XF_FLUSH, 0);
	__piReg  = OSPhysicalToUncached(0xC003000);
	__cpReg  = OSPhysicalToUncached(0xC000000);
	__peReg  = OSPhysicalToUncached(0xC001000);
	__memReg = OSPhysicalToUncached(0xC004000);
	__GXFifoInit();
	GXInitFifoBase(&FifoObj, base, size);
	GXSetCPUFifo(&FifoObj);
	GXSetGPFifo(&FifoObj);
	if (resetFuncRegistered == FALSE) {
		OSRegisterResetFunction(&GXResetFuncInfo);
		resetFuncRegistered = TRUE;
	}
	__GXPEInit();

	{
		u32 hid2 = PPCMfhid2();

		PPCMtwpar(0x0C008000);
		hid2 |= 0x40000000;
		PPCMthid2(hid2);
	}

	gx->genMode = 0;
	SET_REG_FIELD(gx->genMode, 8, 24, 0);
	gx->bpMask = 255;
	SET_REG_FIELD(gx->bpMask, 8, 24, 0x0F);
	gx->lpSize = 0;
	SET_REG_FIELD(gx->lpSize, 8, 24, 0x22);
	for (i = 0; i < 16; ++i) {
		gx->tevc[i]     = 0;
		gx->teva[i]     = 0;
		gx->tref[i / 2] = 0;
		gx->texmapId[i] = GX_TEXMAP_NULL;
		SET_REG_FIELD(gx->tevc[i], 8, 24, 0xC0 + i * 2);
		SET_REG_FIELD(gx->teva[i], 8, 24, 0xC1 + i * 2);
		SET_REG_FIELD(gx->tevKsel[i / 2], 8, 24, 0xF6 + i / 2);
		SET_REG_FIELD(gx->tref[i / 2], 8, 24, 0x28 + i / 2);
	}
	gx->iref = 0;
	SET_REG_FIELD(gx->iref, 8, 24, 0x27);
	{
		u32 t0;
		u32 t1;
		u32 off = 0;
		u32 v0 = 0x30;
		u32 v1 = 0x31;
		for (k = 0; k < GX_MAXCOORD; k += 4) {
			t0 = off + 0xB8;
			t1 = off + 0xD8;
			*(u32*)((char*)gx + t0) = 0;
			*(u32*)((char*)gx + t1) = 0;
			SET_REG_FIELD(*(u32*)((char*)gx + t0), 8, 24, v0);
			SET_REG_FIELD(*(u32*)((char*)gx + t1), 8, 24, v1);
			off += 4;
			v0 += 2;
			v1 += 2;
			t0 = off + 0xB8;
			t1 = off + 0xD8;
			*(u32*)((char*)gx + t0) = 0;
			*(u32*)((char*)gx + t1) = 0;
			SET_REG_FIELD(*(u32*)((char*)gx + t0), 8, 24, v0);
			SET_REG_FIELD(*(u32*)((char*)gx + t1), 8, 24, v1);
			off += 4;
			v0 += 2;
			v1 += 2;
			t0 = off + 0xB8;
			t1 = off + 0xD8;
			*(u32*)((char*)gx + t0) = 0;
			*(u32*)((char*)gx + t1) = 0;
			SET_REG_FIELD(*(u32*)((char*)gx + t0), 8, 24, v0);
			SET_REG_FIELD(*(u32*)((char*)gx + t1), 8, 24, v1);
			off += 4;
			v0 += 2;
			v1 += 2;
			t0 = off + 0xB8;
			t1 = off + 0xD8;
			*(u32*)((char*)gx + t0) = 0;
			*(u32*)((char*)gx + t1) = 0;
			SET_REG_FIELD(*(u32*)((char*)gx + t0), 8, 24, v0);
			SET_REG_FIELD(*(u32*)((char*)gx + t1), 8, 24, v1);
			off += 4;
			v0 += 2;
			v1 += 2;
		}
	}
	SET_REG_FIELD(gx->suScis0, 8, 24, 0x20);
	SET_REG_FIELD(gx->suScis1, 8, 24, 0x21);
	SET_REG_FIELD(gx->cmode0, 8, 24, 0x41);
	SET_REG_FIELD(gx->cmode1, 8, 24, 0x42);
	SET_REG_FIELD(gx->zmode, 8, 24, 0x40);
	SET_REG_FIELD(gx->peCtrl, 8, 24, 0x43);
	SET_REG_FIELD(gx->cpTex, 2, 7, 0);
	gx->dirtyState = 0;
	gx->dirtyVAT   = FALSE;

	freqBase = __OSBusClock / 500;
	__GXFlushTextureState();
	reg = (freqBase >> 11) | 0x400 | 0x69000000;
	GX_WRITE_RAS_REG(reg);

	__GXFlushTextureState();
	reg = (freqBase / 0x1080) | 0x200 | 0x46000000;
	GX_WRITE_RAS_REG(reg);

	for (m = GX_VTXFMT0; m < GX_MAX_VTXFMT; m += 4) {
		SET_REG_FIELD(gx->vatA[m], 1, 30, 1);
		SET_REG_FIELD(gx->vatB[m], 1, 31, 1);
		GX_WRITE_U8(GX_LOAD_CP_REG);
		{ v = m | 0x80; GX_WRITE_U8(v); }
		GX_WRITE_U32(gx->vatB[m]);
		SET_REG_FIELD(gx->vatA[m + 1], 1, 30, 1);
		SET_REG_FIELD(gx->vatB[m + 1], 1, 31, 1);
		GX_WRITE_U8(GX_LOAD_CP_REG);
		{ v = (m + 1) | 0x80; GX_WRITE_U8(v); }
		GX_WRITE_U32(gx->vatB[m + 1]);
		SET_REG_FIELD(gx->vatA[m + 2], 1, 30, 1);
		SET_REG_FIELD(gx->vatB[m + 2], 1, 31, 1);
		GX_WRITE_U8(GX_LOAD_CP_REG);
		{ v = (m + 2) | 0x80; GX_WRITE_U8(v); }
		GX_WRITE_U32(gx->vatB[m + 2]);
		SET_REG_FIELD(gx->vatA[m + 3], 1, 30, 1);
		SET_REG_FIELD(gx->vatB[m + 3], 1, 31, 1);
		GX_WRITE_U8(GX_LOAD_CP_REG);
		{ v = (m + 3) | 0x80; GX_WRITE_U8(v); }
		GX_WRITE_U32(gx->vatB[m + 3]);
	}
	{
		u32 reg1 = 0;
		u32 reg2 = 0;
		SET_REG_FIELD(reg1, 1, 0, 1);
		SET_REG_FIELD(reg1, 1, 1, 1);
		SET_REG_FIELD(reg1, 1, 2, 1);
		SET_REG_FIELD(reg1, 1, 3, 1);
		SET_REG_FIELD(reg1, 1, 4, 1);
		SET_REG_FIELD(reg1, 1, 5, 1);
		GX_WRITE_XF_REG(0, reg1);
		SET_REG_FIELD(reg2, 1, 0, 1);
		GX_WRITE_XF_REG(0x12, reg2);
	}
	{
		u32 reg = 0;
		SET_REG_FIELD(reg, 1, 0, 1);
		SET_REG_FIELD(reg, 1, 1, 1);
		SET_REG_FIELD(reg, 1, 2, 1);
		SET_REG_FIELD(reg, 1, 3, 1);
		SET_REG_FIELD(reg, 8, 24, 0x58);
		GX_WRITE_RAS_REG(reg);
	}
	for (j = 0; (u32)j < 8; j++)
		GXInitTexCacheRegion(&gx->TexRegions0[j], 0, j * 0x8000, 0,
		                     0x80000 + j * 0x8000, 0);
	for (j = 0; (u32)j < 4; j++)
		GXInitTexCacheRegion(&gx->TexRegions1[j], 0, (j * 2 + 8) * 0x8000, 0,
		                     (j * 2 + 9) * 0x8000, 0);
	for (j = 0; (u32)j < 16; j++)
		GXInitTlutRegion(&gx->TlutRegions[j], 0xC0000 + j * 0x2000, 16);
	for (j = 0; (u32)j < 4; j++)
		GXInitTlutRegion(&gx->TlutRegions[j + 16], 0xE0000 + j * 0x8000, 64);
	__cpReg[3] = 0;

	{
		SET_REG_FIELD(gx->perfSel, 4, 4, 0);
		GX_WRITE_U8(GX_LOAD_CP_REG);
		GX_WRITE_U8(0x20);
		GX_WRITE_U32(gx->perfSel);
		GX_WRITE_U8(GX_LOAD_XF_REG);
		GX_WRITE_U32(0x1006);
		GX_WRITE_U32(0);
		GX_WRITE_RAS_REG(0x23000000);
		GX_WRITE_RAS_REG(0x24000000);
		GX_WRITE_RAS_REG(0x67000000);
	}

	__GXSetTmemConfig(0);
	__GXInitGX();
	return &FifoObj;
}