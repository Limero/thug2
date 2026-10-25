// WIP DRAFT (non-matching) — hand-rebuilt from disasm.
// family=m2c range=0x800A473C-0x800A49EC size=688B
// PARKED 2026-10-06 (the worker pool was disabled before this
// slice ran — body left as the current best, not re-measured).
// Blocker: 688B integer script-command body (22 calls / 4 branches, no FPR/PS);
// the m2c draft is a DIFF husk. Next: rebuild the guard chain + CStruct_*/
// Script_SpawnScript call shapes from tmp_bundles/800A473C.md.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct {
    s32 unk0x0;
    s32 unk0x4;
    s32 unk0x8;
    s32 unk0xC;
    u32 unk0x10;
} ElemA473C;

typedef struct {
    ElemA473C *unk0x0;
    s32 unk0x4;
    s32 unk0x8;
    s32 unk0xC;
    s32 unk0x10;
} ArrA473C;

typedef struct {
    s32 unk0x0;
    char pad0x4[0xC];
    s32 unk0x10;
} Arg1A473C;

typedef struct {
    char pad0x0[0xC];
    s32 unk0xC;
} FlagA473C;

typedef struct {
    char pad0x0[0xBC];
    FlagA473C *unk0xBC;
} CtxA473C;

s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void CStruct_delete(s32, s32);
void fn_80126F88(s32, s32);
void fn_80127E70(void *, s32, s32, s32);
s32 fn_801320F4(void *);
void fn_801320EC(void *, s32);
void fn_8012F8E8(void *, s32, s32);
void fn_8012F260(void *, s32, s32, void *);
s32 fn_801309EC(void *);
s32 Script_SpawnScript(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void CObject_RemoveRefLink(void *, void *);
void CObject_AddRefLink(void *, void *);
void fn_800A3B90(void *, s32, s32);
void fn_800A3D8C(void *, s32);

void fn_800A473C(ArrA473C *arg0, Arg1A473C *arg1, CtxA473C *arg2) {
    s32 saved;
    s32 cnt;
    ElemA473C *elem;
    s32 v25;
    s32 v29;
    s32 v30;
    u32 bit;

    cnt = 0;
    saved = arg0->unk0xC;
    arg0->unk0xC = 0;
    arg0->unk0x10 = arg0->unk0x10 + 1;
    elem = arg0->unk0x0;
    if (cnt < arg0->unk0x4) {
        do {
            if ((elem->unk0x0 == arg1->unk0x0) && (elem->unk0x4 != -QB_UNKNOWN_0x3C883A8E)) {
                v25 = 0;
                if (arg1->unk0x10 != 0) {
                    v25 = CStruct_ctor(CStruct_new(8));
                    if (elem->unk0xC != 0) {
                        fn_80126F88(v25, elem->unk0xC);
                    }
                    v29 = v25;
                    fn_80126F88(v25, arg1->unk0x10);
                } else {
                    v29 = elem->unk0xC;
                }
                bit = elem->unk0x10 >> 31;
                if (bit != 0) {
                    if (fn_801320F4(arg2) != 0) {
                        s32 obj2;
                        obj2 = CStruct_ctor(CStruct_new(8));
                        fn_80127E70(obj2, 0, 0xD, elem->unk0x10 >> 31);
                        v30 = fn_801320F4(arg2);
                        fn_801320EC(arg2, 0);
                        fn_8012F8E8(arg2, v30, obj2);
                        if (obj2 != 0) {
                            CStruct_delete(obj2, 3);
                        }
                    }
                    if (elem->unk0x4 != -QB_UNKNOWN_0x3C883A8E) {
                        fn_8012F260(arg2, elem->unk0x4, v29, arg2->unk0xBC);
                        fn_801309EC(arg2);
                    }
                } else {
                    if ((arg2->unk0xBC != 0) && ((arg2->unk0xBC->unk0xC & 0x10000) != 0)) {
                        s32 scr;
                        s32 *link;
                        scr = Script_SpawnScript(elem->unk0x4, v29, 0, 0, 0, 0, 0, 0, bit, bit);
                        link = (s32 *)((char *)scr + 0xBC);
                        if (*link != 0) {
                            CObject_RemoveRefLink((void *)*link, link);
                            *link = bit;
                        }
                        *link = (s32)arg2->unk0xBC;
                        if (*link != 0) {
                            CObject_AddRefLink((void *)*link, link);
                        }
                        fn_801309EC((void *)scr);
                    } else {
                        fn_8012F8E8(arg2, elem->unk0x4, v29);
                    }
                }
                if (v25 != 0) {
                    CStruct_delete(v25, 3);
                }
                fn_800A3B90(arg1, 0, elem->unk0x4);
            }
            elem++;
            if (arg0->unk0x8 == 0) {
                s32 t;
                t = arg0->unk0x10 - 1;
                arg0->unk0x10 = t;
                if ((t == 0) && (arg0 != 0)) {
                    fn_800A3D8C(arg0, 3);
                }
                break;
            }
            if (arg0->unk0xC != 0) {
                break;
            }
            cnt++;
        } while (cnt < arg0->unk0x4);
    }
    arg0->unk0xC = ((arg0->unk0xC != 0) || (saved != 0));
    arg0->unk0x10 = arg0->unk0x10 - 1;
}

// NOTE (2026-10-06): reconstructed from the WANT disassembly.
// Fixes vs the m2c body: (1) `bit` = logical (srwi) shift of the u32 elem->unk0x10
// (m2c cast to s32 first -> srawi); (2) fn_80127E70 gets a real prototype so the
// spurious `crclr cr1eq` before its bl disappears; (3) the `head`/`link`/`obj`/`scr`/
// `tmp`/`flag` temporaries are inlined/block-scoped so the callee-saved save set is
// WANT's r21..r31 (11 regs, `stmw r21`) rather than the draft's r20..r31 (stmw r20);
// (4) the tail flag is assigned directly from the (a!=0)||(saved!=0) test instead of
// a `flag` local. Body order follows WANT's statement order.
