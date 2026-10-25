// WIP DRAFT (non-matching) — hand rebuild from disasm
// family=m2c range=0x801808C8-0x801809F0 size=296B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// PARKED: 41.4% (29/70 masked). Blocker = doc-28 CR-liveness: want tests
// (cached != 0) with mid-function `mfcr r31` + `beq END`, then after
// bl CObject_RemoveRefLink does `mtcrf 0x80, r31` + `beq END` — one comparison's CC
// reused across the call via hardware-CR save/restore. Every plain-C shape
// threads the second test away (provably equal) or materializes the boolean
// into a GPR (li r0,1/cmpwi): tried named flag var, &&-comma chain
// (`(call, sp8=0, cached != 0)`), bare double-if, r27 dead-slot guard,
// register pins a0->r30/a1->r29, -O1/-O3/-Os, all five ProDG versions show
// the same behavior on minimal repros. Wild DOL sites with the identical
// idiom (e.g. 0x80139804: andi. on a call result, mfcr, body-with-bl,
// mtcrf, beq) confirm it is a real compiler behavior no C source shape
// found reproduces. Cracked parts: frame-template struct
// {s32 sp8; char h0[12]; s32 buf[250]} pins exact 0x410 layout incl. holes;
// regmap r28=cached/r29=arg1/r30=arg0; loop is for (i = 0;
// i < fn_80182FA8(obj); i++) buf[i] = fn_80182F98(obj, i) + 0x5C with the
// count call re-evaluated per iteration + once more after the loop.
// NOTE: m2c draft constant 0xF4D3A70E was wrong for this fn — want's
// addis 0x4472 / addi 0x7dae = +0x44727DAE.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
extern s32 lbl_80300434;
s32 fn_8017471C(void *, s32);
s32 fn_80141FA4(Unk_5FCDF30E *);
void GetElement_2(s32 *, s32, s32, s32);
void CObject_RemoveRefLink(CStruct *, CStruct *);
s32 fn_80182F98(CStruct *, s32);
s32 fn_80182FA8(Unk_C7387A53 *);
void fn_80044110(Unk_CACD1EF6 *, s32 *, s32);
void Script_RunScript(s32, s32, s32, s32, s32);
void fn_801808C8(void *arg0, s32 arg1) {
    register void *a0 __asm__("r30");
    register s32 a1 __asm__("r29");
    struct { s32 sp8; char h0[12]; s32 buf[250]; } L;
    s32 temp_r31;
    s32 temp_r3;
    s32 var_r5;
    s32 cached;
    void *obj;
    s32 i;

    a0 = arg0;
    a1 = arg1;
    temp_r31 = lbl_80300434;
    temp_r3 = fn_8017471C(lbl_80305EAC, ((Unk_667BA59C *)a0)->unk0xC);
    var_r5 = 0;
    if (temp_r3 != 0) {
        var_r5 = fn_80141FA4(temp_r3);
    }
    GetElement_2(&L.sp8, temp_r31, var_r5 + (s32)QB_THE_TRICK_TEXT, 0);
    cached = L.sp8;
    if ((cached != 0) && (CObject_RemoveRefLink(cached, &L.sp8), (L.sp8 = 0), (cached != 0))) {
        if (a1 == 0) {
            obj = (char *)a0 + 0x54;
            for (i = 0; i < fn_80182FA8((s32)obj); i++) {
                L.buf[i] = fn_80182F98((s32)obj, i) + 0x5C;
            }
            fn_80044110(cached, L.buf, fn_80182FA8((s32)obj));
        } else {
            fn_80044110(cached, L.buf, 0);
        }
        Script_RunScript(QB_UNKNOWN_0xA4491BE1, 0, 0, 0, 0);
    }
}
