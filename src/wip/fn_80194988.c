// WIP DRAFT (non-matching) — hand-rebuilt from disasm (batch session)
// family=hand range=0x80194988-0x80194DD4 size=1100B
// BEST: 94.2% NEAR (reloc-masked standalone sweep).
// PARKED 94.2%: exactly 16 diffs remain = one 6-cycle callee-saved register-home
// rotation {p10:r18<-21, orig:r19<-18, walk2:r20<-22, t21:r21<-23, p3C:r22<-19,
// p38:r23<-20}. Everything else byte-exact incl. the mfcr/mtcrf cr4-across-calls
// machinery, the synthesized int->double dances (mr r8,r10 / mr r9,r11 dead-copy
// quirks reproduced via plain casts!), frame layout (frame_t template @0x10,
// cvt temp @0x50, CR@5C, stmw r18,0x60), chained CStruct_ctor(CStruct_new(8)),
// hidden arg0 on AddChecksum (3-arg), 10-arg Script_SpawnScript (stack args 9/10),
// counted latch (--cnt), orig-copy forced pre-getter#2 via "+r" asm wedge.
// Rotation resists: decl-order permutations, full/partial hard-reg pins (they
// collapse the frame calc), "+r"/"=r" wedges, all schedule flags, stmt reorder.
// Doc-15 family member at scale.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 lbl_80300434;
extern f64 lbl_802A9D40;
extern f64 lbl_802A9D48;
extern f32 lbl_802A9D50;
extern f32 lbl_802A9D54;

s32 GetInteger(CStruct *, s32, s32 *, s32);
void GetElement_2(void *, s32, s32, s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void AddChecksum(CStruct *, s32, s32);
s32 Script_RunScript(s32, s32, s32, s32, s32);
void CStruct_delete(CStruct *, s32);
void AddInteger(CStruct *, s32, s32);
s32 Script_SpawnScript(Unk_15EF4A35 *, s32, s32, Unk_80577C09 *, s32, s32, s32, s32, s32, s32);
void fn_801309EC(Unk_DB0E2BAB *);
void CObject_RemoveRefLink(CStruct *, CStruct *);
void CObject_AddRefLink(CStruct *, Unk_9994C3F5 *);
s32 fn_80195214(Unk_C7387A53 *);
s32 GetFloat(CStruct *, s32, f32 *, s32);

typedef union { u32 w[2]; f64 d; } cvtu;

typedef struct {
    s32 sp10;
    char _p1[0xC];
    s32 sp20;
    char _p2[0xC];
    s32 sp30;
    s32 sp34;
    s32 sp38;
    s32 sp3C;
    f32 sp40;
    s32 sp44;
} frame_t;

#define T52 (lbl_802A9D40)

void fn_80194988(Unk_72E9CBBF *arg0, s32 arg1) {
    frame_t fr;
    s32 off;
    char *base;
    s32 e;
    s32 t30;
    s32 t31;
    s32 *w1;
    s32 idx;
    s32 cnt;
    s32 h;
    s32 obj;
    char *p;
    s32 t27;
    s32 z;
    s32 h2;
    s32 obj2;
    char *p2;
    s32 *p10;
    s32 orig;
    char *walk2;
    s32 t21;
    s32 *p3C;
    s32 *p38;
    f64 da;
    f64 db;

    off = arg1 * 0x24;
    base = (char *)arg0 + 0x80;
    GetInteger(arg0->unk0x20, QB_MAX_TRICKS, &fr.sp30, 1);
    t30 = *(s32 *)(base + off);
    t21 = lbl_80300434;
    GetElement_2(&fr.sp10, t21, t30, 1);
    t31 = CStruct_ctor(CStruct_new(8));
    AddChecksum(t31, QB_ID, t30);
    Script_RunScript(QB_GOAL_TETRIS_RESET_TRICK_CONTAINER, t31, 0, 0, 0);
    if (t31 != 0) {
        CStruct_delete(t31, 3);
    }
    orig = off;
    __asm__("" : "+r"(orig));
    fr.sp34 = 0;
    GetInteger(arg0->unk0x20, QB_LIST_IS_RED, &fr.sp34, 0);
    walk2 = (char *)arg0 + 0x84;
    p38 = &fr.sp38;
    p3C = &fr.sp3C;
    p10 = &fr.sp10;
    __asm__("" : "=r"(p10) : "r"(&fr.sp10));
    if (fr.sp34 == 1) {
        da = (double)(arg0->unk0x4AC - 1);
        db = (f64)(f32)((double)fr.sp30) * lbl_802A9D48;
        if (da < db) {
            AddInteger(arg0->unk0x20, QB_LIST_IS_RED, 0);
            w1 = (s32 *)base;
            idx = 0;
            cnt = 0x1E;
            do {
                e = *(s32 *)((char *)(idx + (s32)walk2));
                if (e == 0) {
                    GetElement_2(&fr.sp20, t21, *w1, 1);
                    h = fr.sp20;
                    if (h != 0) {
                        CObject_RemoveRefLink((void *)h, &fr.sp20);
                        fr.sp20 = e;
                    }
                    obj = Script_SpawnScript(QB_GOAL_TETRIS_TURN_TRICK_WHITE, 0, 0, 0, 0, 0, 0, 0, e, e);
                    p = (char *)obj + 0xBC;
                    if (*(s32 *)p != 0) {
                        CObject_RemoveRefLink((void *)*(s32 *)p, p);
                        *(s32 *)p = e;
                    }
                    *(s32 *)p = h;
                    if (h != 0) {
                        CObject_AddRefLink((void *)h, p);
                    }
                    fn_801309EC(obj);
                }
                w1 = (s32 *)((char *)w1 + 0x24);
                idx += 0x24;
            } while (--cnt != 0);
        }
    }
    t27 = CStruct_ctor(CStruct_new(8));
    if (fn_80195214(arg0) != 0) {
        AddChecksum(t27, 0, QB_TRICKTRIS);
    }
    z = 0;
    obj2 = Script_SpawnScript(QB_GOAL_TETRIS_REMOVE_TRICK, t27, 0, 0, 0, 0, 0, 0, z, z);
    h2 = fr.sp10;
    p2 = (char *)obj2 + 0xBC;
    if (*(s32 *)p2 != 0) {
        CObject_RemoveRefLink((void *)*(s32 *)p2, p2);
        *(s32 *)p2 = z;
    }
    *(s32 *)p2 = h2;
    if (h2 != 0) {
        CObject_AddRefLink((void *)h2, p2);
    }
    fn_801309EC(obj2);
    if (t27 != 0) {
        CStruct_delete(t27, 3);
    }
    fr.sp38 = 0;
    GetInteger(arg0->unk0x20, QB_TRICKS_COMPLETED, p38, 0);
    fr.sp38 += 1;
    fr.sp3C = 0;
    GetInteger(arg0->unk0x20, QB_ACCELERATION_INTERVAL, p3C, 0);
    if ((fr.sp3C != 0) && (fr.sp38 == (fr.sp38 / fr.sp3C) * fr.sp3C)) {
        fr.sp40 = lbl_802A9D50;
        GetFloat(arg0->unk0x20, QB_ACCELERATION_PERCENT, &fr.sp40, 0);
        GetInteger(arg0->unk0x20, QB_ADJUSTED_TRICK_TIME, &fr.sp44, 1);
        fr.sp44 = (s32)((lbl_802A9D54 - fr.sp40) *
                        (f32)((double)fr.sp44));
        AddInteger(arg0->unk0x20, QB_ADJUSTED_TRICK_TIME, fr.sp44);
    }
    AddInteger(arg0->unk0x20, QB_TRICKS_COMPLETED, fr.sp38);
    arg0->unk0x4AC -= 1;
    *(s32 *)((char *)walk2 + orig) = 1;
    if (fr.sp10 != 0) {
        CObject_RemoveRefLink((void *)fr.sp10, p10);
        fr.sp10 = 0;
    }
}
