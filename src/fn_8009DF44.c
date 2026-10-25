// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009DF44-0x8009DFA0 (92B). Byte-identical.
#include "types.h"
#include "structs.h"
void CObject_RemoveRefLink(CStruct *, CStruct *);
// CObject_ClearRefLinks @ 0x8009DF44
void CObject_ClearRefLinks(CStruct *arg0) {
    void *temp_r30;
    CStruct *var_r31;

    var_r31 = arg0->unk0x4;
    if (var_r31 != NULL) {
        do {
            temp_r30 = var_r31->unk0x8;
            if ((s32) var_r31->unk0x0 != 0) {
                CObject_RemoveRefLink(*(s32 *)((char *)var_r31), var_r31);
                var_r31->unk0x0 = 0;
            }
            var_r31->unk0x0 = 0;
            var_r31 = temp_r30;
        } while (var_r31 != NULL);
    }
}
