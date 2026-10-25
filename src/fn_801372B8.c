// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801372B8-0x8013733C (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8013741C(s32);
s32 fn_80137414(CStruct *o);
void fn_801372B8(Unk_1624B368 *arg0, s32 arg1) {
    s32 sum;
    s32 i;
    s32 lim = 0x3E8;
    void *p;
    sum = 0;
    i = 0;
    if (i < (s32) arg0->unk0xC04) {
        p = (char *)arg0 + 4;
        do {
            if ((s32)(arg1 - fn_8013741C((s32)p)) < lim) {
                sum += fn_80137414((CStruct *)p);
            }
            i += 1;
            p += 0xC;
        } while ((i <= 0xFF) && (i < (s32) arg0->unk0xC04));
    }
    arg0->unk0x140C = sum;
}
