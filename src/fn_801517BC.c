// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801517BC-0x80151A28 (620B). Byte-identical.
#include "types.h"
extern s32 lbl_802FFE98;
extern s32 lbl_80300448;
extern s32 lbl_80301B48;
extern s32 lbl_80302C34;
extern s32 lbl_80305EA4;
extern s32 lbl_80305EAC;
extern s32 lbl_80305FF8;
extern char lbl_802A7D58[];
extern s32 lbl_80383100[];
#include "qb_constants.h"
#include "structs.h"
extern void fn_8005572C(void);
extern s32 Game_GetGoalManager(void);
extern void fn_801843AC(s32 arg0, s32 arg1);
extern void fn_801842C0(Unk_C7387A53 * arg0);
extern void fn_80171844(CStruct * arg0);
extern void fn_80230FA8(Unk_C7387A53 * arg0);
extern void fn_8003EF48(void);
extern s32 fn_80128A90(CStruct * arg0, void * arg1);
extern void Script_RunScript(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void fn_80174814(Unk_40426380 * arg0);
extern void fn_8006FCC8(s32 * arg0);
extern void fn_8006C584(void);
extern s32 fn_8002D2A0(void);
extern void fn_8002D2B0(s32 arg0, s32 arg1);
extern void fn_8006EB68(s32 arg0);
extern void fn_80131C94(void);
extern void fn_8010BDD8(void);
extern void fn_80059218(void);
extern void fn_8011984C(s32 arg0);
extern void fn_800F2DAC(Unk_C7387A53 * arg0, s32 arg1, s32 arg2);
extern void fn_800F2CF0(Unk_C7387A53 * arg0, s32 arg1);
extern s32 fn_8012543C(s32 arg0);
extern void fn_8016A6E4(s32 arg0);
extern void ScriptUnloadAllLevelGeometry(s32 arg0, s32 arg1);
extern void fn_80010258(s32 arg0);
extern s32 fn_80012AD8(s32 arg0);
extern s32 fn_80012B78(s32 arg0);
extern void fn_800126DC(s32 arg0);
extern void fn_8005E040(void);
extern void fn_800599B0(void);
extern void fn_8005D7D4(s32 arg0);
extern s32 fn_800A7F38(void);
extern void fn_800A8288(CStruct * arg0);
extern s32 fn_801770FC(Unk_71062261 * arg0);
extern void fn_8000FEAC(Unk_C7387A53 * arg0);
extern void fn_800A2B0C(void);
extern void fn_8000FE2C(Unk_C7387A53 * arg0);
extern void fn_80177158(Unk_7258DEBD * arg0);
struct unkflags { u32 bit:1; u32 val:31; };
bool ScriptCleanup(CStruct *arg0, void *arg1) {
    Unk_9994C3F5 *temp_r3;
    s32 temp_r27;
    s32 temp_r30;
    s32 temp_r30b;
    s32 temp_r31;
    s32 var_r28;
    s32 var_zero;
    s32 var_r29;
    s32 var_r30;
    s32 var_r31;

    fn_8005572C();
    var_r28 = 0;
    temp_r30 = Game_GetGoalManager();
    fn_801843AC(temp_r30, 0);
    fn_801842C0(temp_r30);
    fn_80171844(lbl_80305EA4);
    fn_80230FA8(lbl_80305FF8);
    temp_r27 = lbl_80305EAC;
    fn_8003EF48();
    if (arg0 != 0) {
        var_r28 = fn_80128A90(arg0, (s32)lbl_802A7D58);
    }
    var_r29 = 0;
    if (arg1 != 0) {
        var_r29 = ((struct unkflags *)((char *)arg1 + 0xCC))->bit;
        ((struct unkflags *)((char *)arg1 + 0xCC))->bit = 0;
    }
    temp_r30b = lbl_80301B48;
    Script_RunScript(QB_EXIT_PAUSE_MENU, 0, 0, 0, 0);
    Script_RunScript(QB_LEVEL_CLEANUP_ASSETS, 0, 0, 0, 0);
    fn_80174814(temp_r27);
    if (arg1 != 0) {
        ((struct unkflags *)((char *)arg1 + 0xCC))->bit = var_r29;
    }
    fn_8006FCC8(lbl_80300448);
    fn_8006C584();
    fn_8002D2B0(fn_8002D2A0(), 0);
    fn_8006EB68(0);
    fn_80131C94();
    fn_8010BDD8();
    fn_80059218();
    fn_8011984C(lbl_80302C34);
    fn_800F2DAC(temp_r30b, 0, 9);
    fn_800F2CF0(temp_r30b, 0);
    temp_r3 = fn_8012543C(QB_NODEARRAY);
    if (temp_r3 != 0) {
        fn_8016A6E4(temp_r3->unk0x8);
    }
    var_zero = 0;
    var_r30 = 0;
    var_r31 = 0xF;
    do {
        fn_8016A6E4(*(s32 *)((char *)lbl_80383100 + var_r30));
        *(s32 *)((char *)lbl_80383100 + var_r30) = var_zero;
        var_r30 += 4;
    } while (--var_r31 != 0);
    ScriptUnloadAllLevelGeometry(0, 0);
    if (var_r28 == 0) {
        fn_80010258(lbl_802FFE98);
    }
    var_r30 = fn_80012AD8(0);
    while (var_r30 != 0) {
        var_r31 = fn_80012AD8(var_r30);
        if (fn_80012B78(var_r30) == 0) {
            fn_800126DC(var_r30);
        }
        var_r30 = var_r31;
    }
    fn_8005E040();
    fn_800599B0();
    fn_8005D7D4(0);
    fn_800A8288(fn_800A7F38());
    if (fn_801770FC(temp_r27) == 0) {
        fn_8000FEAC(lbl_802FFE98);
    }
    fn_800A2B0C();
    if (fn_801770FC(temp_r27) != 0) {
        fn_8000FE2C(lbl_802FFE98);
    }
    fn_80177158(temp_r27);
    return true;
}
