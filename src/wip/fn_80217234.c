// RE-MEASURED 2026-10-07: 92.62% (was 91.28%) after deleting the single zero-code `__asm__("" : "+r"(...))` barrier
//   reproduce: LEAF_TMPDIR=<private dir> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x80217234
//   found by the scaffold-ablation sweep (AGENTS-recipes §6bg conjunction trap): the
//   header's own park note had ruled out ONE piece at a time, but the barrier's
//   removal alone had never been measured against the current body.
// PARKED 91.3%: hand-rebuilt from disasm; switch tree steered with empty case
// 0/4 phantoms + case-arm source reorder; fn_8021B55C needs per-caller s32
// return type (M8.31). What resisted (13 insns in case 5):
// (1) want's &sp pointer is TWO webs: scratch addi r30 birth feeding entry
//     stores + first call, then `mr r29,r30` home copy AFTER the call used for
//     the tail store. Every C shape coalesces q=qh into one register (barrier,
//     fresh-expression, post-call-copy all merge).
// (2) want keeps the walker in r3 across cmpwi+flags-load (it never lives past
//     its own iteration); ngccc homes the loop-carried var into saved r30 on
//     every shape tried (while/goto-web/for/two-var crossjump/r3-pin — the pin
//     collapsed allocation to 53%).
// family=m2c range=0x80217234-0x80217488 size=596B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_802201A4(CScript *);
void Script_RunScript(s32, s32, s32, s32, s32);
s32 fn_8021B55C(void *, s32);
s32 fn_8013E2BC(void);
void fn_8022019C(CScript *, s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void AddChecksum(CStruct *, s32, s32);
void fn_80009C00(CStruct *);
void CStruct_delete(CStruct *, s32);
void *fn_8021D578(void *, CStruct *);
void *fn_8021D5AC(void *, CStruct *);
s32 fn_801745B4(s32);
void fn_80173910(void *, Unk_9D99273B *);
void fn_8021CB74(CScript *, CScript *);
extern char lbl_802A8030[];
extern s32 lbl_80305EAC;

void fn_80217234(Unk_C7387A53 *arg0) {
    struct {
        s32 f0;
        s32 f4;
        s32 f8;
        s32 fC;
    } sp;
    Unk_3BD30EA5 *o;
    s32 v;
    Unk_C7387A53 *var;
    s32 flags;
    s32 *q;
    s32 *qh;
    s32 cat;

    o = *((void * *)&arg0->unk0x20);
    v = fn_802201A4(o);
    switch (v) {
    case 0:
    case 4:
        break;
    case 1:
        Script_RunScript(QB_CREATECONNECTINGDIALOG, 0, 0, 0, 0);
        fn_8022019C(o, 0);
        break;
    case 2:
        fn_8021B55C(o, 0);
        if (fn_8013E2BC() == 0) {
            Script_RunScript(QB_CREATEJOININGDIALOG, 0, 0, 0, 0);
        }
        fn_8022019C(o, 0);
        break;
    case 3:
        Script_RunScript(QB_CREATETRYINGPASSWORDDIALOG, 0, 0, 0, 0);
        fn_8022019C(o, 4);
        break;
    case 8:
        var = (void *)CStruct_ctor(CStruct_new(8));
        AddChecksum((s32)var, QB_REASON, o->unk0x1AC);
        fn_80009C00(o->unk0xF0);
        Script_RunScript(QB_CREATEJOINREFUSEDDIALOG, var, 0, 0, 0);
        if (var != NULL) {
            CStruct_delete((s32)var, 3);
        }
        break;
    case 5:
        qh = (s32 *)&sp;
        qh[2] = (s32)lbl_802A8030;
        qh[1] = 0;
        var = fn_8021D578(o, qh);
        q = qh;
        goto test;
    advance:
        var = fn_8021D5AC(o, &sp);
    test:
        if (var != NULL) {
            flags = var->unk0x20;
            if ((flags & 1) == 0) {
                goto advance;
            }
            if ((flags & 4) != 0) {
                cat = lbl_80305EAC;
                fn_80173910(cat, fn_801745B4(cat));
                fn_8021CB74(o, 0);
            }
        }
        Script_RunScript(QB_ENTERED_NETWORK_GAME, 0, 0, 0, 0);
        fn_8022019C(o, 6);
        q[2] = (s32)lbl_802A8030;
        break;
    case 7:
        Script_RunScript(QB_DIALOG_BOX_EXIT, 0, 0, 0, 0);
        fn_80009C00(o->unk0xE8);
        /* FALLTHRU */
    case 9:
        fn_80009C00(o->unk0xF0);
        break;
    }
}