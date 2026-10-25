// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80153678-0x801537F4 (380B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_801258E8(void *, void *);
void AddComponent(CStruct *, void *, void *, void *);
s32 fn_80128E64(CStruct *, void *, void *, void *);
s32 Script_RunScript(void *, void *, void *, void *, void *);
s32 fn_80137724(void *);
s32 fn_80137ADC(Unk_F386DC9F *);
extern char lbl_80303448[];
extern char lbl_802A7E08[];
extern char lbl_802A7E20[];
extern char lbl_802A7E38[];
extern char lbl_802A7E50[];
extern char lbl_802A7E68[];
extern char lbl_802A7E84[];
extern char lbl_802A7E9C[];
extern char lbl_802A7EB4[];
s32 ScriptTestNetSetup(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r31;
    s32 temp_r3;

    temp_r31 = *(s32 *)&lbl_80303448;
    temp_r3 = fn_80137724(temp_r31);
    if (temp_r3 == 0) {
if (fn_80137ADC(temp_r31) == 5) {
            AddComponent(pParams, (void *)QB_TEXT, (void *)3, (void *)fn_801258E8((void *)lbl_802A7E08, 0));
            Script_RunScript(QB_CREATE_NET_STARTUP_ERROR_DIALOG, pParams, 0, 0, 0);
} else if (fn_80137ADC(temp_r31) == 4) {
            AddComponent(pParams, (void *)QB_TEXT, (void *)3, (void *)fn_801258E8((void *)lbl_802A7E20, 0));
            Script_RunScript(QB_CREATE_NET_STARTUP_ERROR_DIALOG, pParams, 0, 0, 0);
} else if (fn_80137ADC(temp_r31) == 2) {
            AddComponent(pParams, (void *)QB_TEXT, (void *)3, (void *)fn_801258E8((void *)lbl_802A7E38, 0));
            Script_RunScript(QB_CREATE_NET_STARTUP_ERROR_DIALOG, pParams, 0, 0, 0);
} else if (fn_80137ADC(temp_r31) == 6) {
            AddComponent(pParams, (void *)QB_TEXT, (void *)3, (void *)fn_801258E8((void *)lbl_802A7E50, 0));
            Script_RunScript(QB_CREATE_NET_STARTUP_ERROR_DIALOG, pParams, 0, 0, 0);
} else if (fn_80137ADC(temp_r31) == 7) {
            AddComponent(pParams, (void *)QB_TEXT, (void *)3, (void *)fn_801258E8((void *)lbl_802A7E68, 0));
            Script_RunScript(QB_CREATE_NET_STARTUP_ERROR_DIALOG, pParams, 0, 0, 0);
} else if (fn_80137ADC(temp_r31) == 3) {
            AddComponent(pParams, (void *)QB_TEXT, (void *)3, (void *)fn_801258E8((void *)lbl_802A7E84, 0));
            Script_RunScript(QB_CREATE_NET_STARTUP_ERROR_DIALOG, pParams, 0, 0, 0);
        } else {
            AddComponent(pParams, (void *)QB_TEXT, (void *)3, (void *)fn_801258E8((void *)lbl_802A7E9C, 0));
            Script_RunScript(QB_CREATE_NET_STARTUP_ERROR_DIALOG, pParams, 0, 0, 0);
        }
    } else {
        fn_80128E64(pParams, (void *)lbl_802A7EB4, &sp8, (void *)1);
        Script_RunScript(sp8, pParams, 0, 0, 0);
    }
    return temp_r3;
}
