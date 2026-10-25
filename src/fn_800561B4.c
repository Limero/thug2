// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800561B4-0x8005626C (184B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8000913C(CStruct *, s32 *);
s32 fn_80055E74(Unk_FFAD6788 *, void *);
s32 fn_800561B4(Unk_CFB386B2 *, CScript *);
s32 fn_80057C90(CStruct *);
s32 fn_800582C0(CStruct *);
s32 fn_800583FC(CStruct *, void *);
bool fn_800561B4(Unk_CFB386B2 *arg0, CScript *arg1) {
    s32 sp8;
    s32 temp_r30;
    Unk_F5317C5D *temp_r9;

    if (fn_800582C0(arg1) & 0x40) {
        fn_800583FC(arg1, 8);
        arg0->unk0x274 = 1;
        return false;
    }
    if (fn_80055E74(arg0, fn_80057C90(arg1)) == arg1) {
        temp_r30 = arg0->unk0xD0;
        sp8 = fn_80057C90(arg1);
        fn_8000913C(temp_r30, &sp8);
    }
    if (arg1 != NULL) {
        temp_r9 = arg1->unk0x18;
        ((s32 (*)(void *, s32))temp_r9->unk0xC)((char *)arg1 + temp_r9->unk0x8, 3);
    }
    return true;
}
