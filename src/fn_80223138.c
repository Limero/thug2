// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80223138-0x80223168 (48B). Byte-identical.
#include "types.h"
#include "structs.h"

extern char lbl_8029A578[];
s32 fn_80009B80(Unk_C8FEE62D *, s32);

s32 fn_80223138(Unk_C8FEE62D *arg0, s32 arg1) {
    register void *obj __asm__("r11");
    obj = arg0;
    ((CScript *)obj)->unk0x18 = (s32)lbl_8029A578;
    return fn_80009B80(arg0, arg1);
}
