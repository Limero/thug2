// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F6C8C-0x801F6CCC (64B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801F5898(void);
s32 fn_801F5C18(Unk_F0C166E4 *, Unk_127FDB99 *);
bool fn_801F6C8C(Unk_F0C166E4 *arg0) {
    s32 ret;
    ret = fn_801F5898();
    if (ret != 0) {
        fn_801F5C18(arg0, ret);
    }
    return true;
}
