// WIP DRAFT (non-matching) — hand reconstruction of the want instruction stream
// family=m2c range=0x8003F360-0x8003F608 size=680B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 1.8% ([11]asc->1.8%).
// UPDATED 2026-09-15 (e): 1.8% -> 1.8%. raw address literal -> registered lbl_ symbol: MWCC emits lis+ori for a literal constant but lis+addi for a symbol address (fn_8006A8C0 recipe). tools/raw_sym_scan.py automated the A/B; keep the best body.
#include "types.h"

void CObject_RemoveRefLink(void *pObject, void *pLinkCell);
void fn_8009E004(void *pThis);

extern char lbl_80292408[]; /* vtable installed at +0x08 (lis/addi -> 0x80292408) */
extern char lbl_802922FC[]; /* .rodata2 float, == 1.0f */
extern char lbl_80292300[]; /* .rodata2 float, == 0.0f */

/* One CObject reference cell: { object, two bookkeeping words }. */
typedef struct {
    void *m_pObject; /* +0x00 */
    s32 m_nUnk04;    /* +0x04 */
    s32 m_nUnk08;    /* +0x08 */
} T2RefLink;         /* 0xC */

typedef struct {
    f32 f[2];
} T2Pair; /* 8B — copied as one paired-single 8-byte move in the want */

typedef struct {
    T2Pair a;
    T2Pair b;
} T2Quad; /* 16B stack temporary */

/* State block at +0x88 / +0x128 (0x48B).  +0x00 and +0x08/+0x10 are the
   "identity" head, +0x18..+0x3C is the 10-float body, +0x40 the packed
   colour, +0x44 an unset trailing word. */
typedef struct {
    f32 m_f00;        /* +0x00  1.0f */
    u32 m_u04;        /* +0x04  (set by fn_8009E004) */
    T2Pair m_pair08;  /* +0x08  {0.0f, 0.0f} */
    T2Pair m_pair10;  /* +0x10  {0.0f, 1.0f} */
    f32 m_f18;        /* +0x18  0.0f */
    f32 m_f1C;        /* +0x1C  0.0f */
    u32 m_u20;        /* +0x20  (set by fn_8009E004) */
    f32 m_f24;        /* +0x24  (set by fn_8009E004) */
    f32 m_f28;        /* +0x28  (set by fn_8009E004) */
    f32 m_f2C;        /* +0x2C  1.0f */
    f32 m_f30;        /* +0x30  1.0f */
    f32 m_f34;        /* +0x34  1.0f */
    f32 m_f38;        /* +0x38  1.0f */
    f32 m_f3C;        /* +0x3C  0.0f */
    u8 m_col40[4];    /* +0x40  0x80 x4 */
    u32 m_u44;        /* +0x44  */
} T2State;            /* 0x48 */

/* The +0xD0 block is the same state with 0x10 bytes past it. */
typedef struct {
    T2State m_state;   /* +0x00 */
    u8 m_pad48[4];     /* +0x48 */
    s32 m_n4C;         /* +0x4C  0 */
    u8 m_pad50[8];     /* +0x50 */
} T2StateB;            /* 0x58 */

/* Tail block at +0x170. */
typedef struct {
    u32 m_u00;       /* +0x00 */
    u32 m_u04;       /* +0x04 */
    f32 m_f08;       /* +0x08  0.0f */
    f32 m_f0C;       /* +0x0C  0.0f */
    u8 m_col10[4];   /* +0x10  0x80 x4 */
    f32 m_f14;       /* +0x14  0.0f */
    f32 m_f18;       /* +0x18  1.0f */
    s32 m_n1C;       /* +0x1C  0 */
} T2Tail;            /* 0x20 */

typedef struct {
    u8 m_pad00[8];        /* +0x00 */
    void *m_pVtable;      /* +0x08 */
    u32 m_nFlags;         /* +0x0C */
    u8 m_pad10[0x48];     /* +0x10 .. +0x57 */
    T2RefLink m_ref58;    /* +0x58 */
    T2RefLink m_ref64;    /* +0x64 */
    T2RefLink m_ref70;    /* +0x70 */
    T2RefLink m_ref7C;    /* +0x7C */
    T2State m_A;          /* +0x88 */
    T2StateB m_B;         /* +0xD0 */
    T2State m_C;          /* +0x128 */
    T2Tail m_tail;        /* +0x170 */
} T2Self;

void *fn_8003F360(T2Self *pSelf) {
    union {
        u8 b[4];
        u32 w;
    } col;
    T2Quad quad;
    f32 zero;
    f32 one;
    f32 f13;

    fn_8009E004(pSelf);
    pSelf->m_pVtable = lbl_80292408;

    /* --- clear the four CObject reference cells (member order a4/a8/object) --- */
    pSelf->m_ref58.m_nUnk04 = 0;
    pSelf->m_ref58.m_nUnk08 = 0;
    pSelf->m_ref58.m_pObject = NULL;
    pSelf->m_ref64.m_nUnk04 = 0;
    pSelf->m_ref64.m_nUnk08 = 0;
    pSelf->m_ref64.m_pObject = NULL;
    pSelf->m_ref70.m_nUnk04 = 0;
    pSelf->m_ref70.m_nUnk08 = 0;
    pSelf->m_ref70.m_pObject = NULL;
    pSelf->m_ref7C.m_nUnk04 = 0;
    pSelf->m_ref7C.m_nUnk08 = 0;
    pSelf->m_ref7C.m_pObject = NULL;
    pSelf->m_B.m_n4C = 0;

    /* --- release whatever the base ctor left in those cells.  Each of the
       four slots is guarded *and* cleared unconditionally afterwards, which
       is why the want carries two `stw r28,<slot>` for every slot. --- */
    if (pSelf->m_ref58.m_pObject != NULL) {
        CObject_RemoveRefLink(pSelf->m_ref58.m_pObject, &pSelf->m_ref58);
        pSelf->m_ref58.m_pObject = NULL;
    }
    pSelf->m_ref58.m_pObject = NULL;
    if (pSelf->m_ref64.m_pObject != NULL) {
        CObject_RemoveRefLink(pSelf->m_ref64.m_pObject, &pSelf->m_ref64);
        pSelf->m_ref64.m_pObject = NULL;
    }
    pSelf->m_ref64.m_pObject = NULL;
    if (pSelf->m_ref7C.m_pObject != NULL) {
        CObject_RemoveRefLink(pSelf->m_ref7C.m_pObject, &pSelf->m_ref7C);
        pSelf->m_ref7C.m_pObject = NULL;
    }
    pSelf->m_ref7C.m_pObject = NULL;
    if (pSelf->m_ref70.m_pObject != NULL) {
        CObject_RemoveRefLink(pSelf->m_ref70.m_pObject, &pSelf->m_ref70);
        pSelf->m_ref70.m_pObject = NULL;
    }
    pSelf->m_ref70.m_pObject = NULL;

    zero = *(f32 *)lbl_80292300;
    one = *(f32 *)lbl_802922FC;

    /* --- build the identity state block ------------------------------------ */
    pSelf->m_A.m_f18 = zero;
    pSelf->m_A.m_f2C = one;
    pSelf->m_A.m_f30 = one;
    pSelf->m_A.m_f34 = one;
    pSelf->m_A.m_f38 = one;
    pSelf->m_A.m_f1C = zero;
    pSelf->m_A.m_f3C = zero;

    quad.a.f[0] = zero;
    quad.b.f[0] = zero;
    quad.b.f[1] = one;
    quad.a.f[1] = zero;

    pSelf->m_A.m_pair10 = quad.b;
    pSelf->m_A.m_pair08 = quad.a;

    col.b[0] = 0x80;
    col.b[1] = 0x80;
    col.b[2] = 0x80;
    col.b[3] = 0x80;
    pSelf->m_A.m_col40[0] = (u8)(col.w >> 24);
    pSelf->m_A.m_col40[1] = (u8)(col.w >> 16);
    pSelf->m_A.m_col40[2] = (u8)(col.w >> 8);
    pSelf->m_A.m_col40[3] = (u8)col.w;

    pSelf->m_A.m_f00 = one;

    /* --- two identical copies of that state (member-wise: the want copies
       floats with lfs/stfs and only the +0x20/+0x40/+0x44 words with
       lwz/stw, so this is not a block move) -------------------------------- */
    pSelf->m_B.m_state.m_f00 = pSelf->m_A.m_f00;
    pSelf->m_B.m_state.m_pair08 = pSelf->m_A.m_pair08;
    pSelf->m_B.m_state.m_pair10 = pSelf->m_A.m_pair10;
    pSelf->m_B.m_state.m_f18 = pSelf->m_A.m_f18;
    pSelf->m_B.m_state.m_f1C = pSelf->m_A.m_f1C;
    pSelf->m_B.m_state.m_u20 = pSelf->m_A.m_u20;
    pSelf->m_B.m_state.m_f24 = pSelf->m_A.m_f24;
    pSelf->m_B.m_state.m_f28 = pSelf->m_A.m_f28;
    pSelf->m_B.m_state.m_f2C = pSelf->m_A.m_f2C;
    pSelf->m_B.m_state.m_f30 = pSelf->m_A.m_f30;
    pSelf->m_B.m_state.m_f34 = pSelf->m_A.m_f34;
    pSelf->m_B.m_state.m_f38 = pSelf->m_A.m_f38;
    pSelf->m_B.m_state.m_f3C = pSelf->m_A.m_f3C;
    pSelf->m_B.m_state.m_col40[0] = pSelf->m_A.m_col40[0];
    pSelf->m_B.m_state.m_col40[1] = pSelf->m_A.m_col40[1];
    pSelf->m_B.m_state.m_col40[2] = pSelf->m_A.m_col40[2];
    pSelf->m_B.m_state.m_col40[3] = pSelf->m_A.m_col40[3];
    pSelf->m_B.m_state.m_u44 = pSelf->m_A.m_u44;

    f13 = pSelf->m_A.m_f00;
    pSelf->m_C.m_pair08 = pSelf->m_A.m_pair08;
    pSelf->m_C.m_f00 = f13;
    pSelf->m_C.m_pair10 = pSelf->m_A.m_pair10;
    pSelf->m_C.m_f18 = pSelf->m_A.m_f18;
    pSelf->m_C.m_f1C = pSelf->m_A.m_f1C;
    pSelf->m_C.m_u20 = pSelf->m_A.m_u20;
    pSelf->m_C.m_f24 = pSelf->m_A.m_f24;
    pSelf->m_C.m_f28 = pSelf->m_A.m_f28;
    pSelf->m_C.m_f2C = pSelf->m_A.m_f2C;
    pSelf->m_C.m_f30 = pSelf->m_A.m_f30;
    pSelf->m_C.m_f34 = pSelf->m_A.m_f34;
    pSelf->m_C.m_f38 = pSelf->m_A.m_f38;
    pSelf->m_C.m_f3C = pSelf->m_A.m_f3C;
    pSelf->m_C.m_col40[0] = pSelf->m_A.m_col40[0];
    pSelf->m_C.m_col40[1] = pSelf->m_A.m_col40[1];
    pSelf->m_C.m_col40[2] = pSelf->m_A.m_col40[2];
    pSelf->m_C.m_col40[3] = pSelf->m_A.m_col40[3];
    pSelf->m_C.m_u44 = pSelf->m_A.m_u44;

    /* --- tail block + flag bits -------------------------------------------- */
    pSelf->m_tail.m_col10[3] = 0x80;
    pSelf->m_tail.m_n1C = 0;
    pSelf->m_tail.m_f14 = zero;
    pSelf->m_tail.m_f18 = one;
    pSelf->m_tail.m_f08 = zero;
    pSelf->m_tail.m_f0C = zero;
    pSelf->m_tail.m_col10[0] = 0x80;
    pSelf->m_tail.m_col10[1] = 0x80;
    pSelf->m_tail.m_col10[2] = 0x80;
    pSelf->m_nFlags |= 0x10400;

    return pSelf;
}

// PARKED 2026-10-06: structural reconstruction, not yet byte-verified.
// The want is a CObject-derived *constructor/destructor pair* body:
//   * `fn_8009E004(this)` is the base ctor; vtable lbl_80292408 -> +0x08;
//   * four 0xC-byte CObject reference cells at +0x58/+0x64/+0x70/+0x7C are
//     zeroed (member order a4/a8/object) and then released with the
//     CObject_RemoveRefLink(cell.object, &cell) idiom in the source order
//     0x58, 0x64, 0x7C, 0x70 -- note the non-monotonic order (not an array
//     loop), and that each guard is followed by an *unconditional* second
//     `cell.object = NULL` (hence two stores per cell in the want);
//   * a 0x48-byte identity state block at +0x88 (1.0f head, {0,0}/{0,1}
//     pair vector, 0.0f/1.0f body, packed 0x80 colour) is then copied
//     verbatim into +0xD0 (0x58-byte variant, extra word at +0x4C) and
//     +0x128, and a 0x20-byte tail at +0x170 gets 0.0f/1.0f + 0x80 colour;
//   * flags at +0x0C get `|= 0x10400` (ori 0x400 + oris 1).
// The two float operands are NOT literals in the original: the want loads
// them through .rodata2 symbols lbl_80292300 (0.0f) / lbl_802922FC (1.0f),
// so the body must keep the extern declarations (a literal would create a
// local pool entry and break link-level byte identity).
// REMAINING MISMATCH (why this is parked): the want moves every 8-byte pair
// with `psq_l`/`psq_st` (12 paired-single words), i.e. this translation unit
// was compiled with paired-single enabled, while the project's default flag
// set (no -mps-float) can only emit two 32-bit moves for those.  Reproducing
// them needs per-object `-mps-float` (`// FLAG: -mps-float`, `// extra_cflags:
// -mps-float`) plus the `__ps_t` idiom -- but -mps-float rewrites the whole
// unit's FP frame/allocator, so the flag variant must be A/B'd, not assumed.
// Secondary residuals are pure schedule/regalloc: GCC 2.95 sinks the
// `m_A.m_f00 = 1.0f` store to just before the +0xD0 copy and interleaves the
// two independent `stw 0x11c` / flag read-modify-writes differently from the
// statement order above.  Re-measure with tools/test_wip_drafts.py --addr
// 0x8003F360 (and tools/want_got.py for the word diff) before editing again.
