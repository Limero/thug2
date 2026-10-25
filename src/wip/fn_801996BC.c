// WIP DRAFT (non-matching) — hand-rebuilt from disasm (two-phase checker)
// family=m2c range=0x801996BC-0x80199848 size=396B
// PARKED 64.6%: two-phase checker hand-rebuilt from disasm; enum-phase
// register map (r26 op/r27 arr/r28 arg0/r29 mgr/r30 node/r31 iw) matches,
// D454/D4E8/98B10 arities audited, unprototyped fn_8026AFB8 keeps WANT's
// crclr, all-pass store kept via post-store memory fence. Remaining diffs
// are doc-15-class: (a) prologue micro-weave ([addi r30/lwz r29],
// [addi r11lo/addi r3], mr-r27 float) — expand_call/scheduler artifacts;
// (b) GCC places the two ret1 tail-blocks AFTER the walk phase where WANT
// keeps them between check-loop and walk (ProDG linear block order);
// resisted: pp-pin/unpin/op-barrier, volatile fences, atomic-asm anchors
// (r9-pin asm hits cc1 "inconsistent operand constraints"), void* proto
// flips on D454/D4E8, -fno-schedule-insns(2), __builtin_expect, else-form.
// 2026-10-17 re-triage: head is now char* (base needs no cast) and the walk
// pointer is CStruct* instead of s32 — same 64.6% size-exact, so adopted as
// the more honest spelling. Stripping the register pins and barriers drops
// to 12.5% at 384B, so they stay as load-bearing coloring.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// FLAG: -fno-expensive-optimizations
#include "types.h"
#include "structs.h"
extern void *lbl_80305EAC;
extern s32 lbl_80305EC0;
extern s32 lbl_80305F9C;
extern char lbl_802A83F8[];
extern s32 fn_80198B10(s32 arg0);
extern void *fn_8021D454(s32 arg0, CStruct * arg1, s32 arg2);
extern void *fn_8021D4E8(s32 arg0, CStruct * arg1, s32 arg2);
extern s32 fn_801403CC(void *arg0);
extern s32 fn_801813F0(CStruct * arg0);
extern s32 fn_801746A4(void *arg0, s32 arg1);
typedef struct {
    s32 v[4];
} accum_t;

s32 fn_801996BC(void *arg0) {
    struct out_s {
        s32 _0;
        s32 _4;
        s32 _8;
        s32 _c;
    } out;
    register void *a0 __asm__("r28");
    register char *head __asm__("r31");
    register s32 *abase __asm__("r27");
    register struct out_s *op __asm__("r26");
    register s32 mgr __asm__("r29");
    s32 arr[4];
    CScript *node;

    a0 = arg0;
    head = lbl_80305EAC;
    if (fn_80198B10(*(s32 *)&lbl_80305EC0) != 0) {
        register struct out_s *pp __asm__("r30");
        register s32 *ap __asm__("r3");

        mgr = *(s32 *)&lbl_80305F9C;
        pp = &out;
        pp->_4 = 0;
        pp->_8 = (s32)lbl_802A83F8;
        ap = arr;
        abase = ap;
        memset(ap, 0, 0x10);
        op = pp;
        __asm__ volatile("" : "+r"(op));
        node = fn_8021D454(mgr, pp, 0);
        if (node != NULL) {
            do {
                register accum_t *iw __asm__("r31");
                s32 v;
                s32 idx;
                iw = (accum_t *)abase;
                __asm__ volatile("" ::: "memory");
                v = fn_801813F0(fn_801403CC(*((void * *)&node->unk0x18)));
                idx = node->unk0x34;
                iw->v[idx] += v;
                node = fn_8021D4E8(mgr, &out, 0);
            } while (node != NULL);
        }
        {
            register s32 *q __asm__("r3");
            register s32 thr __asm__("r9");
            u32 n;
            q = abase;
            thr = ((Unk_9994C3F5 *)a0)->unk0x8;
            n = 4U;
            do {
                s32 cur = *q;
                q += 1;
                if (cur >= thr) {
                    op->_8 = (s32)lbl_802A83F8;
                    return 1;
                }
            } while (n-- > 1U);
        }
        op->_8 = (s32)lbl_802A83F8;
        __asm__ volatile("" ::: "memory");
        return 0;
    }
    {
        register char *base __asm__("r29");
        register u32 i __asm__("r30");
        register u32 cnt __asm__("r11");
        register CStruct *p __asm__("r9");

        i = 0U;
        base = head + 0x2C;
    again:
        p = ((Unk_1D62F22E_2 *)base)->unk0xC;
        cnt = 0U;
        goto chk;
        do {
            p = ((CStruct *)p)->unk0xC;
            cnt += 1U;
        chk:;
            if (((CStruct *)p)->unk0x4 == -1) {
                p = 0;
            }
        } while (p != NULL);
        __asm__("" : "+r"(p));
        if (i < cnt) {
            if (fn_801813F0(fn_801403CC(
                    (void *)fn_801746A4(head, (s32)i))) >= ((Unk_9994C3F5 *)a0)->unk0x8) {
                return 1;
            }
            i += 1U;
            goto again;
        }
    }
    return 0;
}
