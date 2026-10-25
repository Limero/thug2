// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000DFA0-0x8000E014 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_802FFE84[];
extern s32 lbl_802FFE88;
void fn_8000CFC8(Unk_C8FEE62D *, s32);
s32 fn_8000D3DC(Unk_C8FEE62D *, s32);
bool fn_8000DFA0(s32 arg0, s32 arg1) {
    s32 temp_r3;
    temp_r3 = fn_8000D3DC(*(Unk_C8FEE62D **)&lbl_802FFE84, arg0);
    if (temp_r3 != 0) {
        fn_8000CFC8(*(Unk_C8FEE62D **)((char *)(*(void * *)&lbl_802FFE84) + 0x4), arg1);
        lbl_802FFE88 = 1;
        return false;
    }
    lbl_802FFE88 = temp_r3;
    return false;
}
