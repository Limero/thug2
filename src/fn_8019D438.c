// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019D438-0x8019D62C (500B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 lbl_802FFE7C;
extern s32 lbl_80300434;
extern s32 lbl_80300460;
extern s32 lbl_80301A38;
extern s32 lbl_80303148;
extern s32 lbl_80305EAC;

void fn_80174A20(void *arg0, s32 arg1);
void fn_8000BC4C(s32 arg0);
void fn_8000BD04(s32 arg0);
void fn_801312C4(s32 arg0);
void *fn_801746A4(Unk_C7387A53 *arg0, s32 arg1);
void fn_800A1DF8(void *arg0, s32 arg1);
void fn_80124E70(s32 arg0);
void fn_8004B1C0(void *arg0, s32 arg1);
void fn_800142F4(void);
void fn_800142F8(void);
s32 fn_801745B4(s32 arg0);
s32 Script_GetInteger(s32 arg0, s32 arg1);
void AddInteger(CStruct *arg0, s32 arg1, s32 arg2);
void ScriptSetViewMode(CStruct *arg0, void *arg1);
s32 CStruct_new(s32 arg0);
s32 CStruct_ctor(s32 arg0);
void CStruct_delete(CStruct *arg0, s32 arg1);

typedef struct W746A4_Node {
    u8 _p0[4];
    s32 id;
    u8 _p8[4];
    struct W746A4_Node *next;
} W746A4_Node;

typedef struct W746A4_Root {
    u8 _p[0x38];
    W746A4_Node *head;
} W746A4_Root;

void fn_8019D438(Unk_C7387A53 *arg0, s32 arg1) {
    W746A4_Root *mgr;
    W746A4_Node *var_r9;
    u32 var_r29;
    u32 var_r31;
    void *temp_r3;
    s32 temp_r31;

    if (arg1 == arg0->unk0x48) {
        return;
    }
    mgr = (W746A4_Root *)lbl_80305EAC;
    if (arg1 != 0) {
        fn_80174A20(mgr, 1);
        fn_8000BC4C(lbl_802FFE7C);
    } else {
        fn_8000BD04(lbl_802FFE7C);
    }
    fn_801312C4(arg1);
    var_r29 = 0;
    var_r9 = mgr->head;
    goto test;
body:
    var_r9 = var_r9->next;
    var_r29 += 1;
test:
    if (var_r9->id == -1) {
        var_r9 = NULL;
    }
    if (var_r9 != NULL) {
        goto body;
    }
    var_r31 = 0U;
    if (var_r31 < var_r29) {
        do {
            temp_r3 = fn_801746A4(mgr, var_r31);
            if (temp_r3 != NULL) {
            if (arg1 != 0) {
                void *vt = *(void **)((char *)temp_r3 + 8);
                ((s32 (*)(void *))(*(s32 *)((char *)vt + 0x64)))((char *)temp_r3 + *(s16 *)((char *)vt + 0x60));
            } else {
                void *vt = *(void **)((char *)temp_r3 + 8);
                ((s32 (*)(void *))(*(s32 *)((char *)vt + 0x6C)))((char *)temp_r3 + *(s16 *)((char *)vt + 0x68));
            }
            }
            var_r31 += 1;
        } while (var_r31 < var_r29);
    }
    fn_800A1DF8(lbl_80301A38, arg1);
    fn_80124E70(arg1);
    fn_8004B1C0(lbl_80300434, arg1);
    lbl_80300460 = arg1;
    arg0->unk0x48 = arg1;
    if (arg1 != 0) {
        *(s32 *)((char *)lbl_80303148 + 0x10) = 0xC;
        fn_800142F4();
    } else {
        s32 *sp10 = (s32 *)((char *)lbl_80303148 + 0x10);
        fn_80174A20(lbl_80305EAC, (*sp10 = arg1, 0));
        fn_800142F8();
    }
    if ((s32) arg0->unk0x48 == 0 && fn_801745B4(mgr) != 0) {
        temp_r31 = CStruct_ctor(CStruct_new(8));
        AddInteger(temp_r31, 0, Script_GetInteger(QB_VIEW_MODE, 0));
        ScriptSetViewMode(temp_r31, 0);
        if (temp_r31 != 0) {
            CStruct_delete(temp_r31, 3);
        }
    }
}
