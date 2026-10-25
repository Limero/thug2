// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802195C4-0x80219638 (116B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void fn_8021CD38(Unk_C7387A53 * arg0);
extern void fn_8021A8C8(void *arg0);
extern void fn_8021CDA0(Unk_9994C3F5 * arg0);
void fn_802195C4(Unk_C7387A53 *arg0, s32 arg1) {
    if (arg1 != arg0->unk0x40) {
        arg0->unk0x40 = arg1;
        switch (arg1) {
        case 0:
            break;
        case 1:
            fn_8021CD38(arg0);
            fn_8021A8C8(arg0);
            break;
        case 2:
            fn_8021CD38(arg0);
            fn_8021CDA0(arg0);
            break;
        }
    }
}
