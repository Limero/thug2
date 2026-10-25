// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007257C-0x800725B8 (60B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern volatile s32 lbl_80301600;
extern volatile s32 lbl_80301610;
void *fn_80073A5C(CStruct *, Unk_DB0E2BAB *);
void *fn_8007257C(void) {
    if (lbl_80301600 != 0) {
        return fn_80073A5C((void *)&lbl_80301600, (void *)&lbl_80301610);
    }
    return (void *)&lbl_80301600;
}
