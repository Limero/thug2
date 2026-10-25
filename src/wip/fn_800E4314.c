// WIP DRAFT (non-matching) — hand rewrite 2026-10-10.
// family=m2c range=0x800E4314-0x800E43B0 size=156B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// IMPROVED 2026-10-10: 14.3% (m2c draft, "DIFF, not matched") -> 69.2%.
//   Body is now taken from the PROMOTED TWIN FAMILY (docs/parkings/83): this
//   function is the same `Unk_F5317C5D` script-command dispatcher as
//   src/fn_800C0240.c / fn_800C9F54.c / fn_800D31A4.c / fn_800C0240.c /
//   fn_800CD724.c / fn_800D63A0.c / fn_800DE8FC.c / fn_800DB2B4.c /
//   fn_800CCAF0.c / fn_800DFABC.c (all promoted, all byte-identical), so the
//   entry-table decode is copied verbatim from src/fn_800C0240.c:
//     `s16 idx = *((s16 *)&arg1->unk0xC); void *tbl = *(void **)((char*)arg0+idx);
//      e = ((Ent_t *)((char *)tbl + t * 8))[-1];`  and
//     `off = (s16)(e.w0 >> 16) + t4;`
//   The m2c draft's real bugs were (a) the element read modelled as a SCALED
//   `s32*` index instead of a byte-offset `lwzx` table pointer, (b) the
//   `>> 16` half not extracted at all, and (c) the entry read as ONE word.
//   First 27 of 39 instructions are now byte-identical and the object is
//   size-exact (156B == symbols.txt size:0x9C).
//
// PARKED — RESIDUAL IS doc-31 (intra-function duplicate-call crossjump).
//   The function's two arms END IN AN IDENTICAL CALL, and retail merged the
//   two call sites' `blrl` into ONE shared call block:
//     In arm A retail forms the call target in r3 from r8 plus r0, loads the
//     second argument from 0(r4), moves the link address in from r7, and
//     branches to a shared call block. In arm B it forms the target in r3
//     from r8 plus r3, moves the link address in from r0, and falls into
//     that same block, which performs the indirect call and continues into
//     the epilogue.
//   ngccc emits TWO `blrl`s and cross-jumps only the EPILOGUE
//   (got arm A: ... mtlr r7 ; blrl ; b <epilogue>), so the twelve words from
//   the arm A call to the end sit one word off.  This is exactly the doc-31
//   symptom; the body below is the two-call-site spelling that reproduces
//   the per-arm argument staging (`add r3`/`lwz r4` duplicated per arm) AND
//   the `mr r8,r3` entry copy of arg0, and it is 27/27 identical up to it.
//
//   Measured source shapes (all size-checked, all on this exact body):
//     * two call sites, one in each arm (BEST, 69.23%, size-exact 156B) —
//       this file.  `return;` after the arm-A call: byte-identical, no change.
//     * ONE call after the if/else (both `fn`/`off` staged per arm): 11.4%,
//       object 140B — GCC keeps one `blrl` (right!) but the argument staging
//       folds into the join block and the `mr r8,r3` entry copy disappears,
//       so the whole middle is four words short.
//     * same, with BOTH call args (`tgt`, `a1`) staged per arm per the
//       doc-31 fn_800ABCA8 recipe: 10.8%, object 148B — staging IS duplicated
//       per arm now, but `mr r8,r3` still missing (2 words short).
//     * call duplicated in each arm with the shared `fn` declaration hoisted
//       out of the `if`: 69.23% (same as the best).
//   Conclusion: the only remaining delta is ngccc refusing to merge the two
//   `blrl` sites.  Do not re-grind shapes; re-test if a crossjump/call-merge
//   flag is ever found (doc-31 "Retry hints").
//
// Note: `Unk_F5317C5D` already types unk0x8/unk0xA as s16 and unk0xC as the
// fn-ptr member, and `Unk_E71E4713` unk0x60/unk0x64 — no local typedefs needed.
#include "types.h"
#include "structs.h"

typedef struct {
    s32 w0;
    s32 w1;
} Ent_t;

void fn_800E4314(CScript *arg0, Unk_F5317C5D *arg1) {
    s16 t = arg1->unk0xA;

    if (t != 0) {
        s32 (*fn)(void *, s32);
        s32 off;
        s16 t4;
        Ent_t e;

        if (t >= 0) {
            s16 idx = *((s16 *)&arg1->unk0xC);
            void *tbl = *(void **)((char *)arg0 + idx);
            e = ((Ent_t *)((char *)tbl + t * 8))[-1];
            fn = (s32 (*)(void *, s32))e.w1;
        } else {
            fn = (s32 (*)(void *, s32))arg1->unk0xC;
        }
        t4 = arg1->unk0x8;
        if (t >= 0) {
            off = (s16)(e.w0 >> 16) + t4;
        } else {
            off = t4;
        }
        fn((char *)arg0 + off, *(s32 *)arg1);
    } else {
        void *vt = *((void * *)&arg0->unk0x18);
        ((s32 (*)(void *, s32))(*((void * *)&((Unk_E71E4713 *)vt)->unk0x64)))(
            (char *)arg0 + ((Unk_E71E4713 *)vt)->unk0x60,
            *(s32 *)arg1);
    }
}
// 2026-10-18: shared-fn-hoisted + `register fn __asm__("r7")` probe: 160B (+4B),
// no blrl merge (69.2% shape broken). r7 pin costs a word. Unmerged-blrl stands.
// 2026-10-20: V1 (zero path via named fp0/this0/a0 locals, parallel calls)
// and V2 (explicit return after each call) both keep the same 12 tail
// diffs: ngccc emits blrl in the nonzero path + a stray b instead of
// want's mtlr-r7 + b-skip to a cross-jump-shared blrl. Retail's r7/r0
// split homes with one shared blrl need a crossjump merge our builds
// never perform (both calls void, identical epilogues). Parked.
