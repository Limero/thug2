// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022CBBC-0x8022CBE4 (40B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8022CBBC(CStruct *arg0) {
    s32 sum;
    Unk_4E705049 *p;

    sum = 0;
    p = *((s32 * *)&arg0->unk0x4);
    if (p != NULL) {
        do {
            sum += *((u16 *)&p->unk0x18);
            p = *((s32 * *)&p->unk0x1C);
        } while (p != NULL);
    }
    return sum;
}
