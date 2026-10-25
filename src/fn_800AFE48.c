// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AFE48-0x800B0070 (552B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_802FFE98;
extern bool lbl_8030016C;
extern s32 lbl_8030044C;
extern bool lbl_803017F8;
extern s32 lbl_80301B48;
extern s32 lbl_80305EAC;
void Script_RunScript(s32, s32, s32, s32, s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void AddChecksum(CStruct *, s32, s32);
void fn_800685A4(s32);
s32 fn_800F2A48(s32, s32, s32);
void fn_800F28E4(s32, s32);
void fn_800599B0(void);
s32 fn_801745B4(s32);
void fn_800AB3A8(s32);
void fn_800AB80C(s32);
void fn_8001E17C(s32);
void fn_800B03B0(s32);
void CStruct_delete(CStruct *, s32);
void fn_800100A4(void *);
void fn_800AFE48(Unk_C8FEE62D *arg0) {
    s32 temp_r30;
    s32 temp_r30_2;
    s32 temp_r3;

    if ((s32) arg0->unk0x6C != 0) {
        Script_RunScript(QB_KILL_CUTSCENE_PANEL, 0, 0, 0, 0);
        Script_RunScript(QB_FLUSHCUTSCENEDESTROYLIST, 0, 0, 0, 0);
        fn_800685A4(lbl_8030044C);
        if ((s32) arg0->unk0x3C != 0) {
            temp_r30 = lbl_80301B48;
            fn_800F28E4(temp_r30, fn_800F2A48(temp_r30, arg0->unk0x40, 1));
            arg0->unk0x3C = 0;
        }
        fn_800599B0();
        if ((s32) arg0->unk0x4C != 0) {
            Script_RunScript(arg0->unk0x4C, 0, 0, 0, 0);
        }
        Script_RunScript(QB_KILL_CUTSCENE_CAMERA_HUD, 0, 0, 0, 0);
        Script_RunScript(QB_FLUSHDEADOBJECTS, 0, 0, 0, 0);
        fn_800100A4((void *)lbl_802FFE98);
        temp_r3 = fn_801745B4(lbl_80305EAC);
        if (temp_r3 != 0) {
            temp_r30_2 = CStruct_ctor(CStruct_new(8));
            AddChecksum((CStruct *)temp_r30_2, 0, QB_ISBLOCKING);
            Script_RunScript(QB_CUTSCENE_RESTORE_SKATER_MODEL_LIGHTS, temp_r30_2, temp_r3, 0, 0);
            if (temp_r30_2 != 0) {
                CStruct_delete((CStruct *)temp_r30_2, 3);
            }
        }
        Script_RunScript(QB_POSTCUTSCENE, arg0->unk0x50, 0, 0, 0);
        fn_800B03B0(arg0);
        fn_800AB3A8(arg0);
        Script_RunScript(QB_RESTORE_SKATER_CAMERA, 0, 0, 0, 0);
        lbl_803017F8 = 0;
        if (lbl_8030016C != 0) {
            lbl_8030016C = 0;
            fn_8001E17C(0);
        }
    } else {
        if ((s32) arg0->unk0x3C != 0) {
            fn_800AB80C(arg0->unk0x3C);
        }
        if ((s32) arg0->unk0x4C != 0) {
            Script_RunScript(arg0->unk0x4C, 0, 0, 0, 0);
        }
        fn_800AB3A8(arg0);
    }
}
