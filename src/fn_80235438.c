// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80235438-0x802357B0 (888B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

/* --- fn_80236F80 result --- */
typedef struct {
    char pad0x0[0x34];
    s32 unk0x34;
} QBNode;

/* --- pair inside a record --- */
typedef struct {
    s32 unk0x0;
    char *unk0x4;
} QBPair;

/* --- record at arg0+0x10770, stride 0x154, 40 entries (cf. fn_8023897C) --- */
typedef struct {
    s32 unk0x0;
    char *unk0x4;
    QBPair unk0x8[40];
    s32 unk0x148;
    s32 unk0x14C;
    u8 unk0x150;
    u8 unk0x151;
    char pad0x152[2];
} QBRec;

/* --- 16-byte cleared element at arg0+0x3538 --- */
typedef struct {
    s32 unk0x0;
    s32 unk0x4;
    char pad0x8[8];
} QBZ;

typedef union {
    QBZ unk0x0[60][58];
    struct {
        char pad0x0[0xD238];
        QBRec recs[40];
    } recs;
} QBBlk;

typedef struct {
    void *unk0x0;
    s32 unk0x4;
    char pad0x8[0x3530];
    QBBlk blk;
    s32 unk0x13C90;
    char pad1[0x177C8 - 0x13C94];
    s32 unk0x177C8;
} QBLvl;

/* --- the global object pointer at 0x802FFE98 --- */
typedef struct {
    char pad0x0[0x118];
    s32 unk0x118;
} QBGObj;

typedef struct {
    QBGObj *unk0x0;
    s32 unk0x4;
} QBGlob;

extern QBGlob lbl_802FFE98;
extern char lbl_802B0BB8[];
extern char lbl_802B0BC8[];
extern char lbl_802B0BE0[];
extern char lbl_802B0BE8[];
extern char lbl_802B0BF0[];
extern char lbl_802B0BFC[];
extern char lbl_802B0C08[];
extern char lbl_802B0C10[];

s32 sprintf(char *, ...);
void *Mem_Alloc2(s32);
void fn_8023F980(s32);
void fn_8000F2F8(QBGObj *, s32);
void fn_8000F320(QBGObj *);
s32 fn_802435B8(void *, QBLvl *);
s32 fn_80235CB4(QBLvl *);
void fn_8022D334(void *, s32, s32);
void fn_8023A8A0(QBLvl *);
void fn_8023BFB8(QBLvl *);
s32 fn_8023BF1C(QBLvl *);
void fn_80235FA8(QBLvl *, s32);
void fn_8022F0D8(void *);
CStruct *fn_80125A08(char *, s32);
CStruct *fn_80129528(CStruct *, s32);
void fn_80128C20(CStruct *, void *, void *, s32);
s32 Script_GenerateCRC(char *);
s32 GetChecksum_4(CStruct *, void *, void *, s32);
void *fn_80236EF4(QBLvl *, s32, s32 *);
QBNode *fn_80236F80(QBLvl *, s32);
s32 fn_801281DC(CStruct *, void *, void *, s32);
s32 ContainsFlag(CStruct *, s32);
s32 fn_801258B0(s32, s32);
s32 fn_80128A90(CStruct *, void *);

void fn_80235438(QBLvl *arg0, s32 arg1) {
    char sp8[0x68];
    s32 sp70;
    s32 sp74;
    volatile CStruct *sp78;
    CStruct *temp_r3_2;
    CStruct *temp_r24;
    s32 i;
    s32 j;
    s32 k;
    s32 t;
    s32 var_r17;
    s32 temp_r26;
    char *temp_r29;

    if (arg0->unk0x4 == 0) {
        arg0->unk0x4 = 1;
        fn_8023F980(arg1);
        {
            s32 zi;
            s32 zj;
            for (zi = 0; zi <= 0x39; zi++) {
                for (zj = 0; zj < 0x3A; zj++) {
                    arg0->blk.unk0x0[zi][zj].unk0x0 = 0;
                    arg0->blk.unk0x0[zi][zj].unk0x4 = 0;
                }
            }
        }
        if (arg1 == QB_REGULAR_PLAY) {
            fn_8000F2F8(lbl_802FFE98.unk0x0, lbl_802FFE98.unk0x0->unk0x118);
            arg0->unk0x177C8 = fn_802435B8(Mem_Alloc2(0x108), arg0);
            fn_8000F320(lbl_802FFE98.unk0x0);
        } else {
            arg0->unk0x177C8 = fn_802435B8(Mem_Alloc2(0x108), arg0);
        }
        fn_8022D334(arg0->unk0x0, arg1, fn_80235CB4(arg0));
        fn_8023A8A0(arg0);
        fn_8023BFB8(arg0);
        fn_8023BF1C(arg0);
        fn_80235FA8(arg0, 0);
        if (arg1 == QB_EDIT) {
            fn_8022F0D8(arg0->unk0x0);
        }
        sp78 = fn_80125A08(lbl_802B0BB8, 1);
        arg0->unk0x13C90 = sp78->unk0x4;
        temp_r3_2 = fn_80125A08(lbl_802B0BC8, 1);
        var_r17 = temp_r3_2->unk0x4;
        for (i = arg0->unk0x13C90 - 1; i >= 0; i--) {
            temp_r24 = fn_80129528(sp78, i);
            arg0->blk.recs.recs[i].unk0x4 = 0;
            fn_80128C20(temp_r24, lbl_802B0BE0,
                        &arg0->blk.recs.recs[i].unk0x4, 1);
            arg0->blk.recs.recs[i].unk0x0 =
                Script_GenerateCRC(arg0->blk.recs.recs[i].unk0x4);
            arg0->blk.recs.recs[i].unk0x14C = 0;
            arg0->blk.recs.recs[i].unk0x148 = 0;
            if (GetChecksum_4(temp_r24, lbl_802B0BE8, &sp70, 0) != 0) {
                sp74 = 0;
                fn_80236EF4(arg0, sp70, &sp74);
                j = 0;
                temp_r26 = var_r17 - sp74;
                arg0->blk.recs.recs[i].unk0x148 = temp_r26;
                var_r17 = sp74;
                k = sp74;
                while (j < arg0->blk.recs.recs[i].unk0x148) {
                    arg0->blk.recs.recs[i].unk0x8[j].unk0x0 =
                        fn_80236F80(arg0, k)->unk0x34;
                    if (fn_801281DC(fn_80129528(temp_r3_2, k), lbl_802B0BF0,
                                    &arg0->blk.recs.recs[i].unk0x8[j].unk0x4,
                                    0) == 0) {
                        arg0->blk.recs.recs[i].unk0x8[j].unk0x4 = 0;
                    }
                    k++;
                    j++;
                }
            }
            arg0->blk.recs.recs[i].unk0x151 = 0;
            if (ContainsFlag(temp_r24, QB_CLIPBOARD_SET) != 0) {
                arg0->blk.recs.recs[i].unk0x151 = 1;
                arg0->blk.recs.recs[i].unk0x148 = 6;
                temp_r29 = fn_801258B0(QB_CLIPBOARDTITLE, 0);
                for (t = 0; t <= 5; t++) {
                    sprintf(sp8, lbl_802B0BFC, t);
                    arg0->blk.recs.recs[i].unk0x8[t].unk0x4 = temp_r29;
                    arg0->blk.recs.recs[i].unk0x8[t].unk0x0 =
                        Script_GenerateCRC(sp8);
                }
            }
            arg0->blk.recs.recs[i].unk0x150 =
                fn_80128A90(temp_r24, lbl_802B0C08) ^ 1;
            if (fn_80128A90(temp_r24, lbl_802B0C10) != 0) {
                arg0->blk.recs.recs[i].unk0x150 = 0;
            }
        }
    }
}
