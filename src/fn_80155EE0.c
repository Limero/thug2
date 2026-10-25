// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80155EE0-0x80155F68 (136B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80303148[];
extern void * lbl_80305DE4;
extern char lbl_802A7FF0[];
extern s32 Mem_NewZero(s32);
extern s32 fn_80009B04(Unk_5EF41E38 *, void *);
extern void fn_8014DA98();
extern s32 fn_8000A578(s32, s32);

bool ScriptSpawnSecondControllerCheck(CStruct *pParams, CScript *pScript) {
    void *sp8;
    s32 temp_r31;
    void *temp_r0;
    CScript *temp_r29;

    temp_r0 = lbl_80305DE4;
    temp_r31 = *(s32 *)&lbl_80303148;
    if (temp_r0 == NULL) {
        void *temp_r28;
        s32 temp_r30;

        sp8 = temp_r0;
        temp_r29 = (void *)Mem_NewZero(0x24);
        temp_r30 = (s32)fn_8014DA98;
        temp_r28 = &sp8;
        fn_80009B04(temp_r29, 0);
        temp_r29->unk0x1C = temp_r30;
        temp_r29->unk0x20 = (s32)temp_r28;
        temp_r29->unk0x18 = (s32)lbl_802A7FF0;
        lbl_80305DE4 = temp_r29;
        fn_8000A578((void *)(temp_r31 + 8), temp_r29);
    }
    return true;
}
