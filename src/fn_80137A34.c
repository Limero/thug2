// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80137A34-0x80137A84 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8029F188[];
s32 fn_80137AD4(void);
void *fn_80137A34(void *arg0) {
    if (fn_80137AD4() == 3)
        return lbl_8029F188;
    return arg0 + ((((Unk_F386DC9F *)arg0)->unk0x21A4 << 5) + 0x21A8);
}
