// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80068528-0x800685A4 (124B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800685A4(void);
s32 Mem_NewZero(s32);
s32 fn_8001094C(Unk_C8FEE62D *, s32);
s32 fn_8000F95C(Unk_FFAD6788 *, void *, void *, void *);
extern char lbl_802FFE98[];
extern char lbl_802948A8[];
bool fn_80068528(CStruct *arg0, s32 arg1) {
    s32 t1;
    s32 t2;

    fn_800685A4();
    t1 = fn_8001094C(Mem_NewZero(0x1C), arg1);
    arg0->unk0x8 = t1;
    if (t1 != 0) {
        t2 = fn_8000F95C(*(s32 *)lbl_802FFE98, t1, 1, (s32)lbl_802948A8);
        arg0->unk0xC = t2;
        if (t2 != 0)
            return true;
    }
    return false;
}
