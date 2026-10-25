// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800ACBB8-0x800ACC2C (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_80037F88(s32, void *, s32);
#include "qb_constants.h"
#include "structs.h"
void *GetChecksum_3(Unk_6A70655D *, s32);
s32 fn_800C9780(void *);
void fn_800ACBB8(Unk_6A70655D *unused_arg1, Unk_C8FEE62D *arg2, s32 arg0) {
    void *skel;

    skel = GetChecksum_3(arg2, QB_SKELETON);
    if ((skel != NULL) && (*(s32 *) ((char *) GetChecksum_3(arg2, QB_MODEL) + 0x23C) != 0)) {
        fn_80037F88(fn_800C9780(skel), (void *) arg0, 0);
    }
}
