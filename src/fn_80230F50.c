// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80230F50-0x80230FA8 (88B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
s32 fn_802401C8(s32);
s32 fn_80238970(void);
void fn_80235438(void *, s32);
void fn_8023EFD4(void);
void fn_8023C5A4(void);
void fn_80230F50(s32 arg0, s32 arg1) {
    fn_802401C8(QB_STARTEDITOR);
    fn_80235438(fn_80238970(), arg1);
    if (arg1 == QB_EDIT) {
        fn_8023EFD4();
        fn_8023C5A4();
    }
}
