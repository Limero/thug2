// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80116840-0x801168CC (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum(CStruct *, s32);
s32 GetArray(CStruct *, s32, s32 *, s32);
void fn_8012F260(Unk_15EF4A35 *, s32, Unk_C8FEE62D *, CStruct *);
s32 Mth_Rnd(s32);
bool ScriptGotoRandomScript(CStruct *arg0, Unk_FFAD6788 *arg1) {
    s32 sp8;
    s32 n;

    sp8 = 0;
    GetArray(arg0, 0, &sp8, 0);
    if ((sp8 != 0) && (((Unk_5AA7B5D7 *)sp8)->unk0x4 != 0) && (*(u8 *)((char *)sp8 + 2) == 0xD)) {
        n = Mth_Rnd(((Unk_5AA7B5D7 *)sp8)->unk0x4);
        fn_8012F260(arg1, GetChecksum((CStruct *)sp8, n), 0, arg1->unk0xBC);
    }
    return true;
}
