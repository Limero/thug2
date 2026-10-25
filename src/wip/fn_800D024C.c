// WIP DRAFT — rewritten 2026-10-15 (was m2c 69.8%). Current best NEAR 83.0%
// (208B, 1 word short of want 212B). See below for the size-exact 77.4% variant.
// family=m2c range=0x800D024C-0x800D0320 size=212B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// WHAT CHANGED (all measured, all type-driven, no asm, no brute force):
// - Typed table struct Tbl024C (s16 off10/off18 + s32 fn14/fn1C) replacing
//   raw *(s32*)/(s16*) casts. Same opcodes (lwz/lha) but guides scheduling.
// - Detach pointer hoisted inside the DETACH arm before the zero (p then spC)
//   fixes want's addi-r4-before-li-r30 order (was li-before-addi). 69.8->73.6%.
// - s32 fn14 temp for the 2nd vcall + p-before-spC fixes the addi/li wall:
//   73.6->77.4% size-exact (12 diffs).
// - Duplicating the final vcall into each arm with immediate 0/1 (instead of
//   one shared call via var_r4) fixes the 2nd-vcall lwz/lha + mtlr/add order:
//   prologue through final blrl now byte-exact. 77.4->83.0% but object
//   shrinks 212B->208B (cross-jump merges the two finals; the shared tail
//   falls through to li r3,1 instead of branching over default, costing the
//   one `b` word at 0x800D02FC). Single-final form keeps 212B/77.4%.
// PARKED 2026-10-15: 83.0% (208B) / 77.4% (212B exact). Residual is pure
// block layout: want splits the join (final, default li2, ret1 li1 with two
// branches) while ngccc merges to (final, ret1 fallthrough, default). No
// source shape tried places default between final and ret1 without growing
// the object. Do not retry fnptr staging (probes 2026-10-12 stand) or tbl
// caching in a local (forces r30 base, 15%). Next: tail-layout lever only.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void CObject_RemoveRefLink(CStruct *, CStruct *);
typedef struct Tbl024C {
    char pad[0x10];
    s16 off10;
    char p12[2];
    s32 fn14;
    s16 off18;
    char p1A[2];
    s32 fn1C;
} Tbl024C;
s32 fn_800D024C(CScript *arg0, s32 arg1, s32 arg2) {
    s32 var_r4;
    s32 spC;
    Unk_DB0E2BAB *t;
    char *p;

    switch (arg1) {
    case QB_ATTACH_ATTACH:
        ((s32 (*)(void *, s32))((Tbl024C *)arg0->unk0x18)->fn1C)((char *)arg0 + ((Tbl024C *)arg0->unk0x18)->off18, arg2);
        {
            s32 fn14 = ((Tbl024C *)arg0->unk0x18)->fn14;
            ((s32 (*)(void *))fn14)((char *)arg0 + ((Tbl024C *)arg0->unk0x18)->off10);
        }
        t = *((void * *)&arg0->unk0x18);
        ((s32 (*)(void *, s32))t->unk0x44)((char *)arg0 + t->unk0x40, 0);
        return 1;
    case QB_ATTACH_DETACH:
        p = (char *)arg0 + (s32)0x1C;
        spC = 0;
        if (arg0->unk0x1C != 0) {
            CObject_RemoveRefLink(*((void * *)&arg0->unk0x1C), p);
            arg0->unk0x1C = spC;
        }
        arg0->unk0x1C = spC;
        t = *((void * *)&arg0->unk0x18);
        ((s32 (*)(void *, s32))t->unk0x44)((char *)arg0 + t->unk0x40, 1);
        return 1;
    default:
        return 2;
    }
}
