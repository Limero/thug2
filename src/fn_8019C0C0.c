// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019C0C0-0x8019C10C (76B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_8019B768(void);
void fn_8019C0C0(Unk_27F05558 *arg0) {
    arg0->unk0x434 += 1;
    if ((u32)arg0->unk0x434 >= (u32)fn_8019B768()) {
        arg0->unk0x434 = 0;
    }
}
