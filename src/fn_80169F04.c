// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80169F04-0x8016A048 (324B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "qb_constants.h"
#include "structs.h"
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 CStruct_new(s32);
extern s32 CStruct_ctor(s32);
extern s32 s_insert_game_save_info(s32, CStruct *);
extern s32 fn_80129E28(void *, void *);
extern s32 s_generate_summary_info(s32, s32, CStruct *);
extern void AddInteger(CStruct *, s32, s32);
extern void fn_80127CD4(CStruct *, s32, s32);
extern s32 fn_80168890(s32);
bool ScriptGetSaveInfo(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 t1;
    s32 t2;
    s32 t30;
    s32 t26;

    sp8 = 0;
    GetChecksum_2(pParams, QB_TYPE, &sp8, 0);
    t1 = CStruct_ctor(CStruct_new(8));
    s_insert_game_save_info(sp8, t1);
    t30 = fn_80129E28(t1, 0x186A0);
    t2 = CStruct_ctor(CStruct_new(8));
    s_generate_summary_info(t2, sp8, t1);
    t26 = fn_80129E28(t2, 0x186A0);
    AddInteger(pScript->unk0x18, QB_MAINSTRUCTURESIZE, t30);
    AddInteger(pScript->unk0x18, QB_SUMMARYINFOSIZE, t26);
    // scheduling barrier: ends the region so `ori r4,lo` lands before `mr r5,r26`
    __asm__ volatile("");
    AddInteger(pScript->unk0x18, QB_MAXSUMMARYINFOSIZE, 0x64);
    __asm__ volatile("" : : : "memory");
    t30 += 0x2C54;
    __asm__ volatile("" : : : "memory");
    AddInteger(pScript->unk0x18, QB_TOTALSIZE, t26 + t30);
    AddInteger(pScript->unk0x18, QB_MAXTOTALSIZE, fn_80168890(sp8));
    fn_80127CD4(pScript->unk0x18, QB_SUMMARYINFO, t2);
    fn_80127CD4(pScript->unk0x18, QB_MAINSTRUCTURE, t1);
    return true;
}
