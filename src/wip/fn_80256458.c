// WIP DRAFT (non-matching) — hand-rebuilt from disasm 2026-08-26
// family=m2c range=0x80256458-0x802566E0 size=648B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "structs.h"

extern s32 fn_80253C60(Unk_C7387A53 * pool, s32 size);
extern s32 fn_80258840(s32 a, s32 b);

// PARKED ~6% (byte-score; structurally complete rebuild): ALLOCA+allocator wall.
// Body is a full hand-reconstruction of want's block graph (goto-web mirroring
// every label): fill-loop -> plane/mid/copy-A/block22/loopB/block25/mid_next.
// What matched: __builtin_alloca(arg3*4) reproduces want's exact
// [slwi][addi 0xe][rlwinm &~7][neg][stwux] expansion (plain VLA decl emits a
// FUSED rlwinm mask instead -- use builtin, not `s32 va[n]`).
// What resists: (1) register map - want homes arg1->r20/arg3->r21 EARLY,
// t1 in VOLATILE r8 spilled to 0x1c(fp) around calls, t2=r14, quot=r15,
// arrbase=r17, plane=r16, k=r30, koff-walker=r29, rowoff recycled into r28;
// pins applied so far shift neighbors without converging (stmw span/frame
// 0x70 vs 0x58). (2) want interleaves VLA-size calc INTO the prologue loads;
// explicit builtin moves it but scheduler still reorders vs want.
// Retry hints: apply FULL-WEB pin set from want's map first
// (m14-style, see fn_802566E0.c), incl. s32 alias pin for t1->r8; then
// variable-0 guards via asm-birth li; then block24 latch polarity
// [bge exit][blt continue] needs fallthrough-to-block25 layout.
// MATCH @ 0x80256458 size=0x288
s32 fn_80256458(s32 arg0, Unk_C8FEE62D *arg1, s32 arg2, s32 arg3, s32 (*arg4)(s32, s32, s32, s32)) {
    CStruct *t1;
    s32 t2;
    s32 quot;
    s32 sp14;
    s32 plane;
    s32 dataoff;
    s32 destoff;
    s32 row;
    s32 rowoff2;
    s32 dof;
    s32 k;
    s32 cntn;
    s32 *arr;
    s32 c3;
    s32 *pp;
    register s32 a1s __asm__("r20");
    register s32 a3s __asm__("r21");

    a1s = (s32)arg1;
    a3s = arg3;
    t1 = *(s32 *)a1s;
    t2 = t1->unk0x8;
    quot = (t1->unk0x4 - *(s32 *)((char *)t1)) / t2;
    sp14 = **((s32 * *)&arg1->unk0x10);
    arr = __builtin_alloca(arg3 * 4);
        cntn = (quot + sp14 - 1) / sp14;
        c3 = arg3;
        pp = arr;
        if (c3 > 0) {
            do {
                *pp = fn_80253C60(arg0, cntn * 4);
                pp += 1;
                c3 -= 1;
            } while (c3 != 0);
        }

        plane = 0;
        if (plane >= arg1->unk0x8) {
            return 0;
        }
        dataoff = 0;
        goto mid_test;
mid_head:
        row = 0;
        if (!(row < quot)) {
            goto mid_next;
        }
        destoff = 0;
        /* inner_test */
        if (plane != 0) {
            goto block22;
        }
        __asm__("li %0,0" : "=r"(k));
        if (!(plane < arg3)) {
            goto block22;
        }
        {
            s32 ko = 0;

            do {
                s32 idx;

                idx = fn_80258840(arg1->unk0x10, arg0 + 4);
                if (idx == -1) {
                    return 0;
                }
                *(s32 *)((char *)(destoff + arr[ko])) = *(s32 *)((char *)arg1->unk0x1C + (idx << 2));
                if (*(s32 *)((char *)(destoff + arr[ko])) == 0) {
                    return 0;
                }
                ko += 1;
            } while (ko < arg3);
        }
        goto block22;
block22:
        {
            s32 row22 = 0;

            if (!(row22 < sp14 && row < quot)) {
                goto block25;
            }
            rowoff2 = row * t2;
            dof = 0;
            goto pass_head;
L_block24:
            row22 += 1;
            dof += 4;
            rowoff2 += t2;
            row += 1;
            if (!(row22 < sp14)) {
                goto block25;
            }
            if (row < quot) {
                goto pass_head;
            }
            goto block25;
pass_head:
            __asm__("li %0,0" : "=r"(k));
            if (!(k < arg3)) {
                goto L_block24;
            }
            {
                s32 wo = rowoff2;
                s32 wd = destoff;
                s32 w18 = dof;
                s32 *wm = (s32 *)((char *)t1 + 0x14);
                s32 w12 = dataoff;
                s32 kw = 0;

                do {
                    s32 v = *(s32 *)((char *)arr + kw);
                    s32 d1 = *(s32 *)((char *)(w18 + v));
                    s32 sh = (*(s32 *)((char *)wd + d1)) << 2;
                    s32 mw = *(s32 *)((char *)wm + sh);

                    if (((mw >> plane) & 1) != 0) {
                        s32 mo = *(s32 *)((char *)arg1->unk0x14 + sh);
                        s32 d2 = *(s32 *)((char *)(w12 + mo));

                        if (d2 != 0) {
                            if (arg4(d2, *(s32 *)((char *)arg2 + kw) + (((t1->unk0x0) + wo) << 2), arg0 + 4, t2) == -1) {
                                return 0;
                            }
                        }
                    }
                    kw += 1;
                } while (kw < arg3);
            }
            goto L_block24;
        }
block25:
        destoff += 4;
        if (!(row < quot)) {
            goto mid_next;
        }
        goto mid_head;
mid_next:
        plane += 1;
        dataoff += 4;
mid_test:
        if (plane < arg1->unk0x8) {
            goto mid_head;
        }
        return 0;
}
// RE-TRIAGE 2026-10-12: ALLOCA+allocator wall stands (~6%); no body change.
