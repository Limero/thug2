// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80109F18-0x8010A00C (244B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-gcse
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_8029CD4C;
extern f32 lbl_8029CD50;
extern char lbl_80300434[];
extern bool lbl_80302C0C;
void GetElement_2(void *, s32, s32, s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void AddChecksum(CStruct *, s32, s32);
void fn_8012772C(CStruct *, s32, f32);
bool ScriptDoScreenElementMorph(s32, s32);
void CStruct_delete(CStruct *, s32);
void CObject_RemoveRefLink(CStruct *, CStruct *);
void fn_80109F18(s32 arg0, s32 arg1) {
    struct { s32 unk00, unk04, unk08, unk0C, unk10, unk14; } sp8;
    f32 temp_f31;
    s32 temp_r31;

    GetElement_2(&sp8, *(s32 *)&lbl_80300434, QB_LENS_FLARE_CONTAINER, 0);
    if (sp8.unk00 == 0) {
        return;
    }
    temp_f31 = lbl_8029CD4C;
    temp_r31 = CStruct_ctor(CStruct_new(8));
    AddChecksum(temp_r31, QB_ID, QB_LENS_FLARE_CONTAINER);
    fn_8012772C(temp_r31, QB_ALPHA, lbl_8029CD50);
    fn_8012772C(temp_r31, QB_TIME, temp_f31);
    ScriptDoScreenElementMorph(temp_r31, arg1);
    if (temp_r31 != 0) {
        CStruct_delete(temp_r31, 3);
    }
    lbl_80302C0C = 0;
    if (sp8.unk00 != 0) {
        CObject_RemoveRefLink(sp8.unk00, &sp8);
        sp8.unk00 = 0;
    }
}
