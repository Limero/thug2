// WIP DRAFT (non-matching) — C body reconstructed from want disassembly.
// family=m2c range=0x8007F980-0x8007FBE8 size=616B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// UPDATED 2026-09-15 (e): 6.4% -> 6.5%. raw address literal -> registered lbl_ symbol: MWCC emits lis+ori for a literal constant but lis+addi for a symbol address (fn_8006A8C0 recipe). tools/raw_sym_scan.py automated the A/B; keep the best body.
// UPDATED 2026-09-15 (h): 6.5% -> 7.1%. doc-56 missing-prototype
// call: the draft called `fn_800994C8` with no declaration in scope, so ngccc
// emitted a `crclr cr1eq` (one extra word, whole tail shifted).
// Declaring it removes the word. tools/proto_undeclared_scan.py.
// UPDATED 2026-09-21: recorded FLAG line was stale and harmful (6.6% with it); dropping
// the flag leaves this body at 7.1% (tools/flagdrop_scan.py).
// REWRITTEN 2026-10-06 — the old m2c body branched
// on the element COUNT (`if (n == 0)`) instead of on arg1, freed the wrong
// pointers (`Mem_Free2(arg0)` where want frees `q->unk0x58`, and
// `Mem_Free2(arg0, buf)` where want frees `buf`), left three callees
// unprototyped (fn_800963F8 / fn_8007E8F8 / fn_8007ED94 → spurious
// `crclr cr1eq` words) and typed the two lists as untyped s32 without the
// u16 count.  The body below is rebuilt from the want:
//   * `cmpwi cr4, r27, 0` … `bne cr4, 0x8007fb1c` ⇒ the real branch is
//     `if (arg1 == 0) { ...element-list path... } else { ...matrix path... }`;
//     the element-copy loop is COMMON code placed before the branch.
//   * the -0x68 frame / `stmw r26` / `mflr`+`mfcr`+`stw r12,0x4c` prologue is
//     the one GCC emits when the arg1 test lives in CR4 across the loop calls
//     (hence the CR save) — reproduced by keeping the `if (arg1 == 0)` outside
//     the loop, after it.
//   * arg0 = {+0x18 ptr, +0x20 s32* list, +0x24 u32 count}; the new object
//     p = fn_8007E8F8() = {+0x18 ptr, +0x20 s32* list, +0x24 u32 count,
//     +0x30 s32*}; q = fn_8007DF14(arg2) = {+0x58 s32* list, +0x5c u16 count}.
//   * the matrix path clears the new object's +0x18 and ORs bit 0 of
//     fn_80093E4C's result (`*t |= 1`).
#include "types.h"
#include "structs.h"

extern char lbl_80296268[]; /* 1.0f: identity-matrix diagonal */
extern char lbl_8029626C[]; /* 0.0f: identity-matrix off-diagonal */

void  *Mem_NewZero(s32);
void  *Mem_Alloc(s32);
void  *Mem_Alloc2(s32);
void   Mem_Free2(void *);
void  *fn_8007E8F8(void *);
s32    fn_800963F8(s32, s32);
void   fn_8005F1F0(void *, s32);
void  *fn_8007DF14(void *);
void   fn_8009950C(void *, u32, s32 *);
s32    fn_8009951C(void *);
void   fn_800994C8(void *, u32, s32 *);
s32    fn_800997BC(void *);
s32    fn_8007ED94(void *);
void  *fn_80093E4C(void *, void *, f32 *, s32, s32);

typedef struct {
    char  pad0x00[0x18];
    void *unk0x18;
    s32  *unk0x20;
    u32   unk0x24;
    s32  *unk0x30;
} Node_7F980;

typedef struct {
    char  pad0x00[0x58];
    s32  *unk0x58;
    u16   unk0x5c;
} Sub_7F980;

void *fn_8007F980(Node_7F980 *arg0, s32 arg1, void *arg2) {
    Node_7F980 *p;
    Sub_7F980 *q;
    s32 *buf;
    u16 count;
    u32 i;
    s32 j;
    void *obj;
    s32 *t;
    f32 mtx[16];
    f32 zero;
    f32 one;

    p = fn_8007E8F8(Mem_NewZero(0x58));
    p->unk0x18 = arg0->unk0x18;
    if (arg0->unk0x24 != 0) {
        p->unk0x20 = (s32 *) Mem_Alloc((s32) arg0->unk0x24 * 4);
    } else {
        p->unk0x20 = 0;
    }
    p->unk0x24 = arg0->unk0x24;

    for (i = 0; i < p->unk0x24; i++) {
        p->unk0x20[i] = fn_800963F8(arg0->unk0x20[i], arg1);
    }

    if (arg1 == 0) {
        fn_8005F1F0(p, 1);
        q = (Sub_7F980 *) fn_8007DF14(arg2);
        count = q->unk0x5c;
        if (count != 0) {
            buf = (s32 *) Mem_Alloc((s32) count * 4);
        } else {
            buf = 0;
        }
        p->unk0x18 = arg2;
        for (j = 0; j < q->unk0x5c; j++) {
            buf[j] = q->unk0x58[j];
        }
        count = q->unk0x5c;
        if (q->unk0x58 != 0) {
            Mem_Free2(q->unk0x58);
        }
        q->unk0x58 = 0;
        fn_8009950C(q, arg0->unk0x24, arg0->unk0x20);
        fn_8009951C(q);
        if (count != 0) {
            for (j = 0; j < (s32) count; j++) {
                q->unk0x58[j] = buf[j];
            }
        }
        if (buf != 0) {
            Mem_Free2(buf);
        }
        fn_800994C8(q, p->unk0x24, p->unk0x20);
        fn_800997BC(q);
    } else {
        obj = (void *) fn_8007ED94(p);
        fn_8005F1F0(p, 1);
        zero = *(f32 *) lbl_8029626C;
        one = *(f32 *) lbl_80296268;
        mtx[0] = one;
        mtx[1] = zero;
        mtx[2] = zero;
        mtx[3] = zero;
        mtx[4] = zero;
        mtx[5] = one;
        mtx[6] = zero;
        mtx[7] = zero;
        mtx[8] = zero;
        mtx[9] = zero;
        mtx[10] = one;
        mtx[11] = zero;
        mtx[12] = zero;
        mtx[13] = zero;
        mtx[14] = zero;
        mtx[15] = one;
        t = (s32 *) fn_80093E4C(Mem_Alloc2(0x70), obj, mtx, 1, 0);
        *t |= 1;
        p->unk0x30 = t;
        p->unk0x18 = 0;
    }
    return p;
}

// PARKED 2026-10-06: the semantic reconstruction
// above replaces a body that branched on the wrong value and freed the wrong
// pointers (old score 7.79%, 142/154 words diff).  Root blocker for an exact
// match: path B (arg1 != 0) contains a 4-iteration empty CTR spin
// (`li r0,4; mtctr r0; bdnz .`), which has no C spelling and is unmodelled
// here, and the 16 identity-matrix stores are emitted by want in the order
// [1][0][2][14][15][3..13] (a scheduler reorder of the natural ascending
// source order used above).  Everything else — prologue (frame 0x68, stmw r26,
// mflr/mfcr, stw r12,0x4c), the common element-copy loop, arg1→CR4 across the
// loop calls, both `Mem_Alloc`/`Mem_Free2` targets, the callee protos, and the
// `fn_80093E4C(Mem_Alloc2(0x70), obj, mtx, 1, 0)` arg order — is now modelled.
// WANT vs GOT residual is expected in: the CR4 compare placement, the matrix
// store order, and the unmodelled CTR spin.  Best body above; not promoted.
