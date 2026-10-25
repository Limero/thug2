// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80015B94-0x80015BDC (72B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80015B94(Unk_C8FEE62D *);
s32 CARDGetEncoding(s32, u16 *);
s32 fn_80015B94(Unk_C8FEE62D *arg0) {
    u16 sp8;
    s32 var_r3;

    if (((s32) arg0->unk0xC == 0) || (CARDGetEncoding(arg0->unk0x18, &sp8), var_r3 = 1, (((s32) sp8 == 1) == 0))) {
        var_r3 = 0;
    }
    return var_r3;
}
