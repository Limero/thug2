// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021B4C0-0x8021B508 (72B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80303448[];
void fn_801371D4(Unk_F386DC9F * arg0, Unk_82779A3F * arg1);

void fn_8021B4C0(Unk_C7387A53 *arg0) {
    if ((s32)arg0->unk0x24 != 0) {
        fn_801371D4(*(void **)&lbl_80303448, arg0->unk0x24);
        arg0->unk0x24 = 0;
    }
}
