// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80172C44-0x80172E40 (508B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80303148;
extern f32 lbl_802A8D7C;
extern s32 lbl_80305EC0;
extern s32 lbl_802FFE98;
extern char lbl_802A8D68[];
extern s32 lbl_80305EFC;
extern bool lbl_802FFE58;
extern bool lbl_80303460;
extern void fn_8010BC58(void);
extern void Script_RunScript(s32, s32, s32, s32, s32);
extern void fn_800B0EA4(void);
extern void fn_800B0590(void);
extern void fn_8000A578(s32, s32);
extern void fn_80199120(s32);
extern s32 fn_8011BC38(void);
extern s32 fn_8011BC60(void);
extern void Pcm_Init(void);
extern void fn_8000F2F8(Unk_9F352E7C *, s32);
extern s32 fn_8001075C(s32);
extern void fn_80010760(void);
extern void fn_8000F320(Unk_F12C5E01 *);
extern void fn_801A59B4(Unk_C8FEE62D *);
extern void fn_801A7EE8(Unk_C08FFCDD *);
void fn_80172C44(Unk_DDF317E1 *arg0) {
    s32 temp_r30;

    fn_8010BC58();
    Script_RunScript(QB_INIT_LIGHT_MANAGER, 0, 0, 0, 0);
    Script_RunScript(QB_LOAD_PERMANENT_PREFILES, 0, 0, 0, 0);
    temp_r30 = lbl_80303148;
    arg0->unk0x420 = lbl_802A8D7C;
    fn_800B0EA4();
    fn_800B0590();
    *(s32 *)(arg0->unk0x18 + 0x14) = 2;
    fn_8000A578(temp_r30 + 8, arg0->unk0x18);
    fn_80199120(lbl_80305EC0);
    Script_RunScript(QB_NETWORK_DRIVER_STARTUP, 0, 0, 0, 0);
    Script_RunScript(QB_INIT_LOADING_BAR, 0, 0, 0, 0);
    Script_RunScript(QB_STARTUP_LOADING_SCREEN, 0, 0, 0, 0);
    if ((fn_8011BC38() == 0) || (fn_8011BC60() == 0)) {
        Pcm_Init();
    }
    Script_RunScript(QB_LOADPERMSOUNDS, 0, 0, 0, 0);
    fn_8000F2F8(lbl_802FFE98, ((Unk_8500B740 *)lbl_802FFE98)->unk0x11C);
    fn_8001075C(lbl_802A8D68);
    Script_RunScript(QB_LOAD_PERMANENT_ASSETS, 0, 0, 0, 0);
    fn_80010760();
    fn_8000F320(lbl_802FFE98);
    fn_801A59B4(lbl_80305EFC);
    fn_801A7EE8(arg0->unk0x64);
    Script_RunScript(QB_INIT_ENVIRONMENT, 0, 0, 0, 0);
    Script_RunScript(QB_DEFAULT_SYSTEM_STARTUP, 0, 0, 0, 0);
    if ((lbl_802FFE58 == 0) && (lbl_80303460 == 0)) {
        Script_RunScript(QB_CALL_PERSONAL_STARTUP_SCRIPT, 0, 0, 0, 0);
    }
}
