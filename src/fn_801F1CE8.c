// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F1CE8-0x801F1FCC (740B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"

typedef struct { char _p00[4]; s32 unk0x4; } Mgr_t;

extern s32 lbl_802FFE98;
extern s32 lbl_80301B40;

extern void *fn_800F105C(void);
extern s32 fn_800F1084(void);
extern void fn_8000F2F8(void *, void *);
extern void fn_8000F320(void *);
extern void fn_80129068(void *, s32, s32);
extern void fn_8012911C(void *, s32);
extern void fn_80129314(void *, s32, s32);
extern s32 fn_80129528(void *, s32);
extern s32 CStruct_new(s32);
extern s32 CStruct_ctor(s32);
extern void fn_80126FF4(void *, s32);
extern s32 GetStructure(s32, s32);
extern void AddChecksum(void *, s32, s32);
extern void AddInteger(void *, s32, s32);
extern s32 fn_801F1940(s32, s32);
extern s32 fn_801F1FCC(void);
extern s32 fn_800F1DB0(s32, s32, s32, s32);

void fn_801F1CE8(void *arg0, s32 *arg1, s32 arg2) {
    s32 sp8;
    s32 v25;
    s32 *cursor;
    s32 v28a;
    s32 flag;
    s32 v24;
    Mgr_t *mgr;
    s32 v26;
    s32 v27;
    s32 v28;
    s32 node;
    s32 tmp;

    v25 = 0;
    cursor = arg1;
    __asm__("" : "+r"(cursor));
    v28a = arg2;
    flag = 1;
    sp8 = 0;
    v24 = 0;
    mgr = arg0;

    if (mgr == NULL) {
        mgr = fn_800F105C();
        cursor = &sp8;
        flag = 0;
        v24 = lbl_80301B40;
        v25 = fn_800F1084();
        tmp = mgr->unk0x4;
        sp8 = tmp;
        if (tmp == 0) {
            fn_80129068(mgr, fn_801F1FCC(), 0xA);
        } else {
            fn_8012911C(mgr, tmp + fn_801F1FCC());
        }
    }

    fn_8000F2F8((void *)lbl_802FFE98, (void *)v28a);
    v26 = 0;
    do {
        if (flag != 0) {
            node = fn_80129528(mgr, *cursor);
        } else {
            node = CStruct_ctor(CStruct_new(8));
        }
        fn_80126FF4(node, GetStructure(QB_EDITEDGOAL_PRO_NODE, 1));
        AddChecksum(node, QB_NAME, fn_801F1940(v26, 0));
        AddInteger(node, QB_NODEINDEX, *cursor);
        if (flag == 0) {
            fn_80129314(mgr, *cursor, node);
            fn_800F1DB0(v24, v25, *cursor, node);
        }
        *cursor = *cursor + 1;
        if (flag != 0) {
            node = fn_80129528(mgr, *cursor);
        } else {
            node = CStruct_ctor(CStruct_new(8));
        }
        fn_80126FF4(node, GetStructure(QB_EDITEDGOAL_RESTART_NODE, 1));
        AddChecksum(node, QB_NAME, fn_801F1940(v26, 1));
        AddInteger(node, QB_NODEINDEX, *cursor);
        if (flag == 0) {
            fn_80129314(mgr, *cursor, node);
            fn_800F1DB0(v24, v25, *cursor, node);
        }
        v28 = 0;
        v27 = v26 + 1;
        *cursor = *cursor + 1;
        do {
            if (flag != 0) {
                node = fn_80129528(mgr, *cursor);
            } else {
                node = CStruct_ctor(CStruct_new(8));
            }
            fn_80126FF4(node, GetStructure(0x000B52B3, 1));
            AddChecksum(node, QB_NAME, fn_801F1940(v26, v28 + 2));
            AddInteger(node, QB_NODEINDEX, *cursor);
            if (flag == 0) {
                fn_80129314(mgr, *cursor, node);
                fn_800F1DB0(v24, v25, *cursor, node);
            }
            v28 = v28 + 1;
            *cursor = *cursor + 1;
        } while (v28 <= 0xA);
        v26 = v27;
    } while (v26 <= 9);

    fn_8000F320((void *)lbl_802FFE98);
}
