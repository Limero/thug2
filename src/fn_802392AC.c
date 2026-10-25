// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802392AC-0x802392F0 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_802435EC(s32, s32);
void fn_802392AC(Unk_673C6403 *arg0) {
    s32 temp;

    temp = arg0->unk0x177CC;
    if (temp != 0) {
        fn_802435EC(temp, 3);
        arg0->unk0x177CC = 0;
    }
}
