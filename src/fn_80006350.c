// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80006350-0x800063B4 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void *fn_80006350(void *arg0, f32 angle) {
    volatile double _dummy;
    volatile double _dummy2;
    f32 s = sinf(angle);
    f32 c = cosf(angle);
    arg0 = arg0;
    *((f32 *)&((CStruct *)arg0)->unk0x0) = c;
    *((f32 *)&((CStruct *)arg0)->unk0x4) = s;
    *((f32 *)&((CStruct *)arg0)->unk0x8) = -s;
    *((f32 *)&((CStruct *)arg0)->unk0xC) = c;
    return arg0;
}
