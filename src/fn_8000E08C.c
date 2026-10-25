// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000E08C-0x8000E104 (120B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802FFE84[];
extern s32 lbl_802FFE88;
s32 fn_8000D028(Unk_42076946 *, s32, s32);
s32 fn_8000D3DC(Unk_C8FEE62D *, s32);
s32 fn_8000E08C(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_r3;
    void *temp_r9;
    s32 temp_r5;

    temp_r3 = fn_8000D3DC(*(void * *)&lbl_802FFE84, arg0);
    if (temp_r3 != 0) {
        temp_r9 = *(void * *)&lbl_802FFE84;
        temp_r5 = *(s32 *)((s32 *)temp_r9 + 0x1);
        lbl_802FFE88 = 1;
        return fn_8000D028(temp_r5, arg1, arg2);
    }
    lbl_802FFE88 = temp_r3;
    return 0;
}
