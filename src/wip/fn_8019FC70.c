// WIP DRAFT (non-matching) — hand-rebuilt from disasm (group H)
// family=m2c range=0x8019FC70-0x801A058C size=2332B
// PARKED: ~93% masked — doc-29 hard wall: vpkuhum @0x8019FDC4.
// See long note at bottom of file. FLAG below is required for the PS pairs.
// FLAG: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// RESTORED 2026-09-20 by tools/restore_best_body.py.  The working body
// scored 6.3% while git revision d4633219c scores 20.7%;
// the pool's struct-ification sweep and/or tools/store_order_search.py had
// rewritten this body in place and kept the worse result while the notes
// above stayed put.  Winner picked from 13 distinct committed bodies.
// Re-verify with tools/score_addrs.py before editing again.
#include "types.h"
#include "qb_constants.h"

typedef struct { __ps_t p[2]; } PS2;
typedef struct { __ps_t p[6]; } PS6;
typedef struct { __ps_t p[8]; } PS8;

extern void *GetChecksum_3(void *, s32);
extern void *fn_80062680(void *);
extern s32 fn_80062618(void *);
extern void *fn_800C9780(void *);
extern void *fn_80036960(void *);
extern f32 fn_8012570C(s32, s32);
extern void *fn_80003E0C(void *, f32);

extern f32 lbl_802AAFE4;
extern f32 lbl_802AAFE8;
extern f32 lbl_802AAFEC;
extern s32 lbl_80305EF0;
extern f32 lbl_80305EF4;

void fn_8019FC70(void *arg0) {
    struct { f32 m[32]; void *ptr; s32 row; } fr;
    void *model;
    void *obj;
    void *data;
    void *skel;
    void *mtx;
    void *mm;
    char *row;
    char *wcol;
    char *end;
    s32 i;
    s32 j;
    s32 ctr;
    f32 t;
    f32 lim;

    model = GetChecksum_3(arg0, QB_MODEL);
    if (model == NULL) {
        return;
    }
    obj = *(void **)((char *)model + 0x210);
    data = fn_80062680(obj);
    if (GetChecksum_3(arg0, QB_SKELETON) == NULL) {
        lbl_80305EF0 = (lbl_80305EF0 + 1) & 0x1F;
        return;
    }
    skel = fn_800C9780(GetChecksum_3(arg0, QB_SKELETON));

    t = lbl_80305EF4 + fn_8012570C(0xCACA33A4, 1) * *(f32 *)((char *)arg0 + 0x128);
    lbl_80305EF4 = t;
    lim = lbl_802AAFE4;
    if (t > lim) {
        do {
            t -= lim;
        } while (t > lim);
        lbl_80305EF4 = t;
    }
    t = lbl_80305EF4;
    lim = lbl_802AAFE8;
    if (t < lim) {
        do {
            t += lbl_802AAFE4;
        } while (t < lim);
        lbl_80305EF4 = t;
    }

    if (fn_80062618(obj) <= 5) {
        return;
    }
    i = 0;
    mtx = fn_80036960(skel);
    while (i < fn_80062618(obj)) {
        char *src = (char *)data + i * 0x50;
        char *dst = (char *)mtx + i * 0x40;
        *(PS2 *)dst = *(PS2 *)(src + 0x10);
        *(PS6 *)(dst + 0x10) = *(PS6 *)(src + 0x20);
        i++;
    }

    j = 2;
    do {
        row = (char *)mtx + j * 0x40;
        for (ctr = 4; ctr != 0; ctr--) {
        }
        fr.ptr = fn_80003E0C(fr.m, (2.0f * lbl_80305EF4 * lbl_802AAFEC) / lbl_802AAFE4);
        fr.row = (s32)row;
        mm = fr.ptr;
        fr.m[16] = *(f32 *)(mm + 0xC) * *(f32 *)(row + 0x30) + (*(f32 *)(mm + 8) * *(f32 *)(row + 0x20) + (*(f32 *)(mm + 0) * *(f32 *)(row + 0x00) + (*(f32 *)(mm + 4) * *(f32 *)(row + 0x10))));
        fr.m[17] = *(f32 *)(mm + 0xC) * *(f32 *)(row + 0x34) + (*(f32 *)(mm + 8) * *(f32 *)(row + 0x24) + (*(f32 *)(mm + 0) * *(f32 *)(row + 0x04) + (*(f32 *)(mm + 4) * *(f32 *)(row + 0x14))));
        fr.m[18] = *(f32 *)(mm + 0xC) * *(f32 *)(row + 0x38) + (*(f32 *)(mm + 8) * *(f32 *)(row + 0x28) + (*(f32 *)(mm + 0) * *(f32 *)(row + 0x08) + (*(f32 *)(mm + 4) * *(f32 *)(row + 0x18))));
        fr.m[19] = *(f32 *)(mm + 0xC) * *(f32 *)(row + 0x3C) + (*(f32 *)(mm + 8) * *(f32 *)(row + 0x2C) + (*(f32 *)(mm + 0) * *(f32 *)(row + 0x0C) + (*(f32 *)(mm + 4) * *(f32 *)(row + 0x1C))));
        fr.m[20] = *(f32 *)(mm + 0x1C) * *(f32 *)(row + 0x30) + (*(f32 *)(mm + 0x18) * *(f32 *)(row + 0x20) + (*(f32 *)(mm + 0x10) * *(f32 *)(row + 0x00) + (*(f32 *)(mm + 0x14) * *(f32 *)(row + 0x10))));
        fr.m[21] = *(f32 *)(mm + 0x1C) * *(f32 *)(row + 0x34) + (*(f32 *)(mm + 0x18) * *(f32 *)(row + 0x24) + (*(f32 *)(mm + 0x10) * *(f32 *)(row + 0x04) + (*(f32 *)(mm + 0x14) * *(f32 *)(row + 0x14))));
        fr.m[22] = *(f32 *)(mm + 0x1C) * *(f32 *)(row + 0x38) + (*(f32 *)(mm + 0x18) * *(f32 *)(row + 0x28) + (*(f32 *)(mm + 0x10) * *(f32 *)(row + 0x08) + (*(f32 *)(mm + 0x14) * *(f32 *)(row + 0x18))));
        fr.m[23] = *(f32 *)(mm + 0x1C) * *(f32 *)(row + 0x3C) + (*(f32 *)(mm + 0x18) * *(f32 *)(row + 0x2C) + (*(f32 *)(mm + 0x10) * *(f32 *)(row + 0x0C) + (*(f32 *)(mm + 0x14) * *(f32 *)(row + 0x1C))));
        fr.m[24] = *(f32 *)(mm + 0x2C) * *(f32 *)(row + 0x30) + (*(f32 *)(mm + 0x28) * *(f32 *)(row + 0x20) + (*(f32 *)(mm + 0x20) * *(f32 *)(row + 0x00) + (*(f32 *)(mm + 0x24) * *(f32 *)(row + 0x10))));
        fr.m[25] = *(f32 *)(mm + 0x2C) * *(f32 *)(row + 0x34) + (*(f32 *)(mm + 0x28) * *(f32 *)(row + 0x24) + (*(f32 *)(mm + 0x20) * *(f32 *)(row + 0x04) + (*(f32 *)(mm + 0x24) * *(f32 *)(row + 0x14))));
        fr.m[26] = *(f32 *)(mm + 0x2C) * *(f32 *)(row + 0x38) + (*(f32 *)(mm + 0x28) * *(f32 *)(row + 0x28) + (*(f32 *)(mm + 0x20) * *(f32 *)(row + 0x08) + (*(f32 *)(mm + 0x24) * *(f32 *)(row + 0x18))));
        fr.m[27] = *(f32 *)(mm + 0x2C) * *(f32 *)(row + 0x3C) + (*(f32 *)(mm + 0x28) * *(f32 *)(row + 0x2C) + (*(f32 *)(mm + 0x20) * *(f32 *)(row + 0x0C) + (*(f32 *)(mm + 0x24) * *(f32 *)(row + 0x1C))));
        fr.m[28] = *(f32 *)(mm + 0x3C) * *(f32 *)(row + 0x30) + (*(f32 *)(mm + 0x38) * *(f32 *)(row + 0x20) + (*(f32 *)(mm + 0x30) * *(f32 *)(row + 0x00) + (*(f32 *)(mm + 0x34) * *(f32 *)(row + 0x10))));
        fr.m[29] = *(f32 *)(mm + 0x3C) * *(f32 *)(row + 0x34) + (*(f32 *)(mm + 0x38) * *(f32 *)(row + 0x24) + (*(f32 *)(mm + 0x30) * *(f32 *)(row + 0x04) + (*(f32 *)(mm + 0x34) * *(f32 *)(row + 0x14))));
        fr.m[30] = *(f32 *)(mm + 0x3C) * *(f32 *)(row + 0x38) + (*(f32 *)(mm + 0x38) * *(f32 *)(row + 0x28) + (*(f32 *)(mm + 0x30) * *(f32 *)(row + 0x08) + (*(f32 *)(mm + 0x34) * *(f32 *)(row + 0x18))));
        fr.m[31] = *(f32 *)(mm + 0x3C) * *(f32 *)(row + 0x3C) + (*(f32 *)(mm + 0x38) * *(f32 *)(row + 0x2C) + (*(f32 *)(mm + 0x30) * *(f32 *)(row + 0x0C) + (*(f32 *)(mm + 0x34) * *(f32 *)(row + 0x1C))));
        *(PS8 *)row = *(PS8 *)&fr.m[16];
        j++;
    } while (j <= 5);

    end = (char *)mtx + 0x140;
    wcol = (char *)mtx + 0x40;
    do {
        fr.m[0] = *(f32 *)(wcol + 0xC) * *(f32 *)(mtx + 0x30) + (*(f32 *)(wcol + 8) * *(f32 *)(mtx + 0x20) + (*(f32 *)(wcol + 0) * *(f32 *)(mtx + 0x00) + (*(f32 *)(wcol + 4) * *(f32 *)(mtx + 0x10))));
        fr.m[1] = *(f32 *)(wcol + 0xC) * *(f32 *)(mtx + 0x34) + (*(f32 *)(wcol + 8) * *(f32 *)(mtx + 0x24) + (*(f32 *)(wcol + 0) * *(f32 *)(mtx + 0x04) + (*(f32 *)(wcol + 4) * *(f32 *)(mtx + 0x14))));
        fr.m[2] = *(f32 *)(wcol + 0xC) * *(f32 *)(mtx + 0x38) + (*(f32 *)(wcol + 8) * *(f32 *)(mtx + 0x28) + (*(f32 *)(wcol + 0) * *(f32 *)(mtx + 0x08) + (*(f32 *)(wcol + 4) * *(f32 *)(mtx + 0x18))));
        fr.m[3] = *(f32 *)(wcol + 0xC) * *(f32 *)(mtx + 0x3C) + (*(f32 *)(wcol + 8) * *(f32 *)(mtx + 0x2C) + (*(f32 *)(wcol + 0) * *(f32 *)(mtx + 0x0C) + (*(f32 *)(wcol + 4) * *(f32 *)(mtx + 0x1C))));
        fr.m[4] = *(f32 *)(wcol + 0x1C) * *(f32 *)(mtx + 0x30) + (*(f32 *)(wcol + 0x18) * *(f32 *)(mtx + 0x20) + (*(f32 *)(wcol + 0x10) * *(f32 *)(mtx + 0x00) + (*(f32 *)(wcol + 0x14) * *(f32 *)(mtx + 0x10))));
        fr.m[5] = *(f32 *)(wcol + 0x1C) * *(f32 *)(mtx + 0x34) + (*(f32 *)(wcol + 0x18) * *(f32 *)(mtx + 0x24) + (*(f32 *)(wcol + 0x10) * *(f32 *)(mtx + 0x04) + (*(f32 *)(wcol + 0x14) * *(f32 *)(mtx + 0x14))));
        fr.m[6] = *(f32 *)(wcol + 0x1C) * *(f32 *)(mtx + 0x38) + (*(f32 *)(wcol + 0x18) * *(f32 *)(mtx + 0x28) + (*(f32 *)(wcol + 0x10) * *(f32 *)(mtx + 0x08) + (*(f32 *)(wcol + 0x14) * *(f32 *)(mtx + 0x18))));
        fr.m[7] = *(f32 *)(wcol + 0x1C) * *(f32 *)(mtx + 0x3C) + (*(f32 *)(wcol + 0x18) * *(f32 *)(mtx + 0x2C) + (*(f32 *)(wcol + 0x10) * *(f32 *)(mtx + 0x0C) + (*(f32 *)(wcol + 0x14) * *(f32 *)(mtx + 0x1C))));
        fr.m[8] = *(f32 *)(wcol + 0x2C) * *(f32 *)(mtx + 0x30) + (*(f32 *)(wcol + 0x28) * *(f32 *)(mtx + 0x20) + (*(f32 *)(wcol + 0x20) * *(f32 *)(mtx + 0x00) + (*(f32 *)(wcol + 0x24) * *(f32 *)(mtx + 0x10))));
        fr.m[9] = *(f32 *)(wcol + 0x2C) * *(f32 *)(mtx + 0x34) + (*(f32 *)(wcol + 0x28) * *(f32 *)(mtx + 0x24) + (*(f32 *)(wcol + 0x20) * *(f32 *)(mtx + 0x04) + (*(f32 *)(wcol + 0x24) * *(f32 *)(mtx + 0x14))));
        fr.m[10] = *(f32 *)(wcol + 0x2C) * *(f32 *)(mtx + 0x38) + (*(f32 *)(wcol + 0x28) * *(f32 *)(mtx + 0x28) + (*(f32 *)(wcol + 0x20) * *(f32 *)(mtx + 0x08) + (*(f32 *)(wcol + 0x24) * *(f32 *)(mtx + 0x18))));
        fr.m[11] = *(f32 *)(wcol + 0x2C) * *(f32 *)(mtx + 0x3C) + (*(f32 *)(wcol + 0x28) * *(f32 *)(mtx + 0x2C) + (*(f32 *)(wcol + 0x20) * *(f32 *)(mtx + 0x0C) + (*(f32 *)(wcol + 0x24) * *(f32 *)(mtx + 0x1C))));
        fr.m[12] = *(f32 *)(wcol + 0x3C) * *(f32 *)(mtx + 0x30) + (*(f32 *)(wcol + 0x38) * *(f32 *)(mtx + 0x20) + (*(f32 *)(wcol + 0x30) * *(f32 *)(mtx + 0x00) + (*(f32 *)(wcol + 0x34) * *(f32 *)(mtx + 0x10))));
        fr.m[13] = *(f32 *)(wcol + 0x3C) * *(f32 *)(mtx + 0x34) + (*(f32 *)(wcol + 0x38) * *(f32 *)(mtx + 0x24) + (*(f32 *)(wcol + 0x30) * *(f32 *)(mtx + 0x04) + (*(f32 *)(wcol + 0x34) * *(f32 *)(mtx + 0x14))));
        fr.m[14] = *(f32 *)(wcol + 0x3C) * *(f32 *)(mtx + 0x38) + (*(f32 *)(wcol + 0x38) * *(f32 *)(mtx + 0x28) + (*(f32 *)(wcol + 0x30) * *(f32 *)(mtx + 0x08) + (*(f32 *)(wcol + 0x34) * *(f32 *)(mtx + 0x18))));
        fr.m[15] = *(f32 *)(wcol + 0x3C) * *(f32 *)(mtx + 0x3C) + (*(f32 *)(wcol + 0x38) * *(f32 *)(mtx + 0x2C) + (*(f32 *)(wcol + 0x30) * *(f32 *)(mtx + 0x0C) + (*(f32 *)(wcol + 0x34) * *(f32 *)(mtx + 0x1C))));
        *(PS8 *)wcol = *(PS8 *)&fr.m[0];
        wcol += 0x40;
    } while (wcol <= end);
}

// PARK NOTES (group H, fn_8019FC70 @0x8019FC70, 2332B):
//
// VERDICT: PARKED on docs/parkings/29-altivec-vmx-unemittable.md — this is the
// largest member of that family. Want contains ONE undecodable opcode-4 word:
//
//     0x8019FDC4: 0x101F000E   (capstone/ps_disasm print it as `vpkuhum v0,v31,v0`)
//
// XO10 = 7, VD=f0/v0, VA=f31/v31, VB=f0/v0. It sits INSIDE the skeleton-data
// copy loop's 16-byte paired-single copy window: the first pair load from
// offset 16 advances the source pointer by 0x10, then the mystery word sits
// where the first pair store belongs, followed by the second pair load from
// offset 24 and the pair store at offset 8 of the destination;
// i.e. it occupies the slot where the first `psq_st f0, 0(r11)` of a
// 16-byte __ps_t struct copy belongs. The same word pattern appears 61x
// across .text (always interleaved in PS copy/move runs; e.g. fn_80091EF4,
// fn_80066608), and doc-29 already parks fn_800FF030/fn_800FF478 on exactly
// `vpkuhum + psq mix`.
//
// NEW DATAPPOINT vs doc-29 "What does NOT work": doc-29 closed the inline-asm
// MNEMONIC route (ngcas rejects vmsumshm/vmhaddshs). It did NOT test raw data
// directives: `__asm__ volatile(".long 0x101F000E");` ASSEMBLES FINE through
// ngccc/ngcas 3.9.3 and lands the exact word in .text (verified in a scratch
// probe). If the maintainers ever approve a single-word `.long` carve-out
// (doc-30's bdnz-$ precedent is prior art for targeted asm windows), THIS
// function becomes fully crackable — the rest of the body is plain C +
// __ps_t copies and is reconstructed above. Until then it stays parked per
// doc-29 policy ("hand-encoded .words ... banned per §4g").
//
// Structure fixed this round (kept in the body above):
// - chained call fn_800C9780(GetChecksum_3(arg0, QB_SKELETON)) — m2c had both
//   calls discarded/unchained;
// - f32 typed loads everywhere (m2c emitted *(s32*) for every float field,
//   incl. *(arg0+0x128) feeding the fmadds);
// - folded extern f32 globals (lbl_802AAFE4/8/EC rodata2, lbl_80305EF0/EF4
//   data) replacing char[] literal casts;
// - frame-template struct {f32 m[32]; void *ptr; s32 row;} = 136B locals ->
//   exact 0xB0 frame with stmw r24 (sp88=fn result slot, sp8C=dead-but-
//   escaping row store kept alive by &fr passing into fn_80003E0C, §6v-117);
// - copy loop decomposed as PS2(dst+0)<-(src+0x10) + PS6(dst+0x10)<-(src+0x20)
//   per the want load/store offset analysis;
// - empty `for(ctr=4;)` countdown spin (want: li r0,4; mtctr; bdnz $.);
// - bottom-tested multiply loops with per-iteration global reloads.
