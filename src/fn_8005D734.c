// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005D734-0x8005D7A0 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_8036645C[];
typedef struct Obj {
    s32 unk0x0;
    s16 unk0x4;
    s16 unk0x6;
} Obj;
s32 fn_8007B450(Obj *);
void fn_8005D8E4(void *, s32 *);
bool fn_8005D734(Obj *arg0) {
    s32 sp8;

    if (--arg0->unk0x4 == 0) {
        sp8 = arg0->unk0x0;
        fn_8005D8E4(lbl_8036645C, &sp8);
        fn_8007B450(arg0);
        return true;
    }
    return false;
}
