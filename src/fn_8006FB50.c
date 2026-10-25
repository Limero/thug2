// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006FB50-0x8006FB8C (60B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8005F984(s32, s32);
s32 fn_8006FB50(Unk_5E1C040A *arg0, s32 arg1) {
    arg0->unk0x208 = arg1;
    if (arg1 == 0) {
        return fn_8005F984(arg0->unk0x4, 1);
    }
    return 0;
}
