// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012F360-0x8012F4DC (380B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

// 0x2C-stride table element (fn_80132140 walks the same table: f0/f4/f14)
typedef struct S_360_E {
    s32 f0;
    s32 f4;
    char _p8[0x24];
} S_360_E;

typedef struct S_360_O {
    char _p00[0xC];
    s32 f0C;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    char _p20[0x14];
    S_360_E *f34;
    s32 cnt;
    char _p3C[0x58];
    S_360_E *tbl;
    s32 f98;
    char _p9C[0x8];
    s32 fA4;
    s32 fA8;
    s32 fAC;
    char _pB0[0x4];
    s32 fB4;
    char _pB8[0x4];
    CStruct *fBC;
    char _pC0[0x8];
    s32 fC8;
} S_360_O;

extern s32 lbl_8030342C;
void Mem_Free_3(s32);
void CStruct_delete(CStruct *, s32);
void CObject_RemoveRefLink(CStruct *, CStruct *);
void fn_80132140(S_360_O *);
void fn_801347CC(CScript *, s32);

void fn_8012F360(S_360_O *arg0) {
    S_360_E *def_3C;
    S_360_E *def_20;
    CStruct *link;
    CScript *g;
    s32 i;
    s32 off;
    register s32 z __asm__("r26");

    fn_80132140(arg0);
    if (arg0->f0C != 0) {
        Mem_Free_3(arg0->f0C);
        arg0->f0C = 0;
    }
    g = (CScript *)lbl_8030342C;
    if (arg0->f10 != 0) {
        fn_801347CC(g, arg0->fC8);
    }
    arg0->f10 = 0;
    if (arg0->f18 != 0) {
        CStruct_delete(arg0->f18, 3);
        arg0->f18 = 0;
    }
    if (arg0->f14 != 0) {
        CStruct_delete(arg0->f14, 3);
        arg0->f14 = 0;
    }
    def_3C = (S_360_E *)((char *)arg0 + 0x3C);
    def_20 = (S_360_E *)((char *)arg0 + 0x20);
    link = (CStruct *)((char *)arg0 + 0xBC);
    i = 0;
    if (i < arg0->cnt) {
        z = 0;
        off = 0;
        // Element address written out 3x, and as `off + base` (not `base +
        // off`): a named `E *e` makes the address a pseudo live across both
        // calls (callee-saved r30, +1 stmw slot, 12B over); spelled out, each
        // MEM gets its own short-lived address reload, and the offset-0 one
        // folds into the indexed form `lwzx`.
        do {
            fn_801347CC(g, *(s32 *)(off + (s32)arg0->tbl));
            if (*(s32 *)(off + (s32)arg0->tbl + 4) != 0) {
                CStruct_delete(*(s32 *)(off + (s32)arg0->tbl + 4), 3);
                *(s32 *)(off + (s32)arg0->tbl + 4) = z;
            }
            i++;
            off += 0x2C;
        } while (i < arg0->cnt);
    }
    arg0->cnt = 0;
    if (arg0->tbl != def_3C) {
        Mem_Free_3((s32)arg0->tbl);
    }
    arg0->tbl = def_3C;
    arg0->f1C = 0;
    if (arg0->f34 != def_20) {
        Mem_Free_3((s32)arg0->f34);
    }
    arg0->f34 = def_20;
    arg0->f98 = 0;
    arg0->fA4 = 0;
    arg0->fAC = 0;
    arg0->fA8 = 0;
    if (arg0->fBC != 0) {
        CObject_RemoveRefLink(arg0->fBC, link);
        arg0->fBC = 0;
    }
    arg0->fBC = 0;
    arg0->fC8 = 0;   // NB: sched2 emits these two `= 0` stores in REVERSE
    arg0->fB4 = arg0->fB4 & QB_UNKNOWN_0x3FFFFFFF;   // source order — the other
}                                                      // way round is a 2-word DIFF
