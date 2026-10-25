// WIP DRAFT (non-matching) — C body rewritten by hand from the DOL disassembly.
// family=m2c range=0x8004B798-0x8004BB0C size=884B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// FLAG: -Os
#include "types.h"
extern char lbl_80301A78[];

// object reached through a link node; field 0x18 is copied into the out param
typedef struct Unk_Obj {
    char pad0x0[0x18];
    s32 unk0x18;
} Unk_Obj;

// 16-byte link node: payload + two link pointers + pad
typedef struct Unk_Link {
    Unk_Obj *unk0x0;
    void *unk0x4;
    void *unk0x8;
    void *unk0xC;
} Unk_Link;

typedef struct Unk_Self {
    char pad0x0[0x58];
    Unk_Link unk0x58;
} Unk_Self;

s32 GetStructure_2(s32, s32, s32 *, s32);
s32 GetChecksum_2(s32, s32, s32 *, s32);
s32 GetInteger(s32, s32, s32 *, s32);
void GetElement_2(Unk_Link *, Unk_Self *, s32, s32);
void fn_8004BEB0(Unk_Link *, Unk_Self *, Unk_Link *, s32);
Unk_Obj *fn_8003FF64(Unk_Obj *, s32);
Unk_Obj *fn_800A5360(s32, s32);
void CObject_AddRefLink(void *, void *);
void CObject_RemoveRefLink(void *, void *);

s32 ResolveComplexID(Unk_Self *arg0, s32 arg1, s32 arg2, s32 *arg3) {
    Unk_Link sp8;
    s32 sp18 = 0;
    s32 sp1C;
    s32 sp20;
    s32 sp24 = 0;
    s32 sp28 = -1;
    Unk_Obj *res;

    if (GetStructure_2(arg1, arg2, &sp18, 0) != 0) {
        sp1C = 0;
        GetChecksum_2(sp18, 0, &sp1C, 0);
        sp20 = -1;
        GetInteger(sp18, 0, &sp20, 0);
        if (sp1C != 0) {
            if (arg0->unk0x58.unk0x0 == 0) {
                GetElement_2(&sp8, arg0, sp1C, 0);
            } else {
                fn_8004BEB0(&sp8, arg0, &arg0->unk0x58, sp1C);
            }
            if (arg0->unk0x58.unk0x0 != 0) {
                CObject_RemoveRefLink(arg0->unk0x58.unk0x0, &arg0->unk0x58);
                arg0->unk0x58.unk0x0 = 0;
            }
            arg0->unk0x58.unk0x0 = sp8.unk0x0;
            if (sp8.unk0x0 != 0) {
                CObject_AddRefLink(sp8.unk0x0, &arg0->unk0x58);
            }
            if (sp8.unk0x0 != 0) {
                CObject_RemoveRefLink(sp8.unk0x0, &sp8);
                sp8.unk0x0 = 0;
            }
            if (arg0->unk0x58.unk0x0 == 0) {
                return 0;
            }
        } else if (sp20 != -1) {
            res = fn_8003FF64(arg0->unk0x58.unk0x0, sp20);
            if (arg0->unk0x58.unk0x0 != 0) {
                CObject_RemoveRefLink(arg0->unk0x58.unk0x0, &arg0->unk0x58);
                arg0->unk0x58.unk0x0 = (Unk_Obj *)sp1C;
            }
            arg0->unk0x58.unk0x0 = res;
            if (res != 0) {
                CObject_AddRefLink(res, &arg0->unk0x58);
            }
            if (arg0->unk0x58.unk0x0 == 0) {
                return 0;
            }
        }
        res = (Unk_Obj *)ResolveComplexID(arg0, sp18, 0xDD4CABD6, arg3);
        if (arg0->unk0x58.unk0x0 != 0) {
            CObject_RemoveRefLink(arg0->unk0x58.unk0x0, &arg0->unk0x58);
            arg0->unk0x58.unk0x0 = 0;
        }
        arg0->unk0x58.unk0x0 = 0;
        return (s32)res;
    } else if (GetChecksum_2(arg1, arg2, &sp24, 0) != 0) {
        if (arg0->unk0x58.unk0x0 != 0) {
            fn_8004BEB0(&sp8, arg0, &arg0->unk0x58, sp24);
            if (arg0->unk0x58.unk0x0 != 0) {
                CObject_RemoveRefLink(arg0->unk0x58.unk0x0, &arg0->unk0x58);
                arg0->unk0x58.unk0x0 = 0;
            }
            arg0->unk0x58.unk0x0 = sp8.unk0x0;
            if (sp8.unk0x0 != 0) {
                CObject_AddRefLink(sp8.unk0x0, &arg0->unk0x58);
            }
            if (sp8.unk0x0 != 0) {
                CObject_RemoveRefLink(sp8.unk0x0, &sp8);
                sp8.unk0x0 = 0;
            }
            if (arg0->unk0x58.unk0x0 == 0) {
                return 0;
            }
            sp24 = arg0->unk0x58.unk0x0->unk0x18;
        } else {
            res = fn_800A5360(*(s32 *)lbl_80301A78, sp24);
            if (res != 0) {
                sp24 = res->unk0x18;
            }
        }
        if (arg0->unk0x58.unk0x0 != 0) {
            CObject_RemoveRefLink(arg0->unk0x58.unk0x0, &arg0->unk0x58);
            arg0->unk0x58.unk0x0 = 0;
        }
        arg0->unk0x58.unk0x0 = 0;
        *arg3 = sp24;
        return 1;
    } else if (GetInteger(arg1, arg2, &sp28, 0) != 0) {
        sp8.unk0x4 = (void *)-1;
        sp8.unk0x8 = (void *)-1;
        sp8.unk0x0 = fn_8003FF64(arg0->unk0x58.unk0x0, sp28);
        if (sp8.unk0x0 != 0) {
            CObject_AddRefLink(sp8.unk0x0, &sp8);
        }
        if (arg0->unk0x58.unk0x0 != 0) {
            CObject_RemoveRefLink(arg0->unk0x58.unk0x0, &arg0->unk0x58);
            arg0->unk0x58.unk0x0 = (Unk_Obj *)-1;
        }
        arg0->unk0x58.unk0x0 = (Unk_Obj *)-1;
        if (sp8.unk0x0 == 0) {
            return 0;
        }
        *arg3 = sp8.unk0x0->unk0x18;
        CObject_RemoveRefLink(sp8.unk0x0, &sp8);
        sp8.unk0x0 = (Unk_Obj *)-1;
        return 1;
    } else {
        if (arg0->unk0x58.unk0x0 != 0) {
            CObject_RemoveRefLink(arg0->unk0x58.unk0x0, &arg0->unk0x58);
            arg0->unk0x58.unk0x0 = 0;
        }
        arg0->unk0x58.unk0x0 = 0;
        return 0;
    }
}
// HAND-REWRITE (2026-10-03): the m2c body was structurally wrong; the
// whole control flow, frame and call sequence were re-derived from the DOL.
// Now compiles to EXACTLY 884B (== symbol) with the correct 0x50 frame,
// stmw r25/0x34, stw lr/0x54, and all 20 call sites in the right order.
// Key corrections vs m2c: (1) arg0->0x58 is a 12-byte link node (payload +
// 2 link words), not a plain pointer, so &arg0->unk0x58 is the link arg;
// (2) the m2c "block_19" is NOT reached from the sp1C!=0 path — it is the
// `else` of `if (sp1C)`, and both that block and the sp1C block fall into a
// SHARED tail (0x8004B914) which re-enters ResolveComplexID recursively with
// the literal checksum constant 0xDD4CABD6 (lis -0x22b4 / ori 0xabd6);
// (3) the GetElement_2 prototype is (link*, self, id, flag) — 4 args, not 5;
// (4) sp1C/sp20 are NOT initialised at declaration (the -1/0 stores sit right
// before their GetInteger/GetChecksum_2 calls); (5) the 3rd branch stores -1
// (not 0) into sp8.unk0x4/unk0x8 and into arg0->unk0x58.
// Residual: register allocation + instruction scheduling only (no structural
// divergence left). See the PARKED note at the end of the file.
// PARKED 2026-10-03: 29.86% masked, object 884B == symbol 884B.
// Everything structural now matches (frame, offsets 0x8/0x18..0x28, all 20 call
// targets in order, both if/else-if chains, the shared recursive tail, the -1
// stores, the `return 0`/`return 1` merge points). What is left is 155 differing
// words that are ALL pure register-allocation / scheduling noise:
//  (a) the two constants swap registers (want: 0 in r27, -1 in r28; got: 0 in
//      r28, -1 in r27) — every `stw r27/r28, 0x58(r31)` inherits this;
//  (b) the want keeps `&arg0->unk0x58` in a callee-saved register live across
//      the join (re-materialised as `addi r28,r31,0x58` on the two incoming
//      edges), while cc1 rematerialises it at each call site (`addi r4,r31,0x58`);
//  (c) sp1C lives in r29 in the want (kept in a callee-saved reg across calls)
//      but stays memory-resident with a volatile r5 copy in the got;
//  (d) cc1 re-materialises the literal 0 (`li r0,0`) before each store where the
//      want CSEs one constant register (li r29,0 / li r30,0) shared by 2 stores.
// PROVEN not fixable by source shape: adding ANY further local variable makes it
// strictly worse (measured) because cc1 2.95's reg_alloc_order then shifts —
// p58=&arg0->unk0x58 per block 14.48%, p8=&sp8 in branch D 20.81%, separate
// block-scoped result vars 22.83% + 8B size loss, a shared s32 t1 for the three
// GetX results 11.76%, an explicit `o = sp8.unk0x0` preload 12.22%, splitting
// the fn_8003FF64 call from the link stores 15.84%, literal-0 variable `z1`
// 7.80% + 12B size loss, `if`/`else if` split into two `if`s 23.64% - 4B.
// The original therefore uses the minimal local set (sp8 link node + sp18/sp1C/
// sp20/sp24/sp28 + one shared result pointer) with LITERAL 0/-1 stores, which is
// what this draft keeps; the residual needs per-function register pinning (the
// `register s32 x __asm__("rN")` trick used by the matched src/fn_8004BB2C.c) or
// a statement-order/flag sweep, not a semantic fix.
