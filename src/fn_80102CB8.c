// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80102CB8-0x80102D18 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern s32 fn_80105B44(CStruct * arg0);
extern s32 fn_80105B90(CStruct * arg0);

s32 fn_80102CB8(Unk_1D62F22E *arg0) {
    s32 sum;
    void *kids;

    if ((arg0->unk0x3 & 3) == 3) {
        return *(u16 *)arg0;
    }
    kids = (char *)arg0 + 4;
    sum = fn_80102CB8((void *)fn_80105B44(kids));
    sum = sum + fn_80102CB8((void *)fn_80105B90(kids));
    return sum;
}
