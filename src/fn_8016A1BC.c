// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016A1BC-0x8016A258 (156B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern void *lbl_80300368;
extern bool lbl_80305E78;
extern char lbl_80305E7C[];
extern s32 lbl_803A0178;
void fn_8016A30C(void);
void fn_801262A0(void);
void fn_8016A374(void);
void fn_8016A34C(void);
void fn_801261C0(void);
void fn_8016A388(void);
void fn_8016A360(void);
void fn_80126230(void);
void fn_8016A39C(void);
void fn_8025EDA0(s32);
void fn_80024000(s32);

bool ScriptRemoveTemporaryMemCardPools(CStruct *pParams, CScript *pScript) {
    fn_8016A30C();
    fn_801262A0();
    fn_8016A374();
    fn_8016A34C();
    fn_801261C0();
    fn_8016A388();
    fn_8016A360();
    fn_80126230();
    fn_8016A39C();
    if (*(s32 *)&lbl_80305E7C != 0) {
        memcpy(lbl_80300368, *(s32 *)&lbl_80305E7C, 0x59D80);
    }
    fn_8025EDA0(lbl_803A0178);
    Mem_Free(*(s32 *)&lbl_80305E7C);
    lbl_80305E78 = 0;
    fn_80024000(1);
    return true;
}
