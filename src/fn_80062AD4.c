// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80062AD4-0x80062B18 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80012A10(s32);
void fn_80062AD4(Unk_6A78CE27 *arg0) {
    if ((s32) arg0->unk0x8 != 0) {
        fn_80012A10((char *)arg0 + 8);
        arg0->unk0x8 = 0U;
    }
}
