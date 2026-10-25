// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80202298-0x80202380 (232B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 CStruct_new(s32);
extern void CStruct_delete(CStruct *, s32);
extern s32 Script_RunScript(s32, s32, s32, s32, s32);
extern void AddInteger(CStruct *, s32, s32);
extern void AddString(CStruct *, s32, void *);
extern s32 CStruct_ctor(s32);
extern s32 fn_802010FC(Unk_BC7B49A5 *);

void fn_80202298(Unk_BC7B49A5 *arg0, s32 arg1) {
    char *b1;
    char *b2;
    char *b3;
    char *b4;
    s32 t38;
    s32 temp_r29;
    s32 temp_r31;

    if (fn_802010FC((s32)arg0) != 0) {
        temp_r29 = arg1 * 0x24;
        temp_r31 = CStruct_ctor(CStruct_new(8));
        b1 = (char *)arg0 + 0x34;
        AddString(temp_r31, QB_STRING, *(s32 *)(b1 + temp_r29));
        b2 = (char *)arg0 + 0x28;
        AddInteger(temp_r31, QB_VALUE, *(s32 *)(b2 + temp_r29));
        b3 = (char *)arg0 + 0x38;
        t38 = *(s32 *)(b3 + temp_r29);
        if (t38 != 0) {
            AddString(temp_r31, QB_VSTRING, t38);
        }
        AddInteger(temp_r31, QB_INDEX, arg1);
        Script_RunScript(QB_SHOW_STATS_MESSAGE, temp_r31, 0, 0, 0);
        b4 = (char *)arg0 + 0x2C;
        *(s32 *)(b4 + temp_r29) = 1;
        if (temp_r31 != 0) {
            CStruct_delete(temp_r31, 3);
        }
    }
}
