// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8014030C-0x8014036C (96B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_80140164(Unk_FFAD6788 *);
extern s32 GetFloat(CStruct *, s32, f32 *, s32);
extern f32 fn_8012570C(s32, s32);
f32 fn_8014030C(s32 arg0, s32 arg1, Unk_FFAD6788 *arg2) {
    f32 sp8;

    if (GetFloat(fn_80140164(arg2), arg0, &sp8, 0) != 0) {
        return sp8;
    }
    return fn_8012570C(arg0, arg1);
}
