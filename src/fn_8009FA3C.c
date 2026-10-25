// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009FA3C-0x8009FACC (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

void fn_8009FA3C(Unk_6A70655D *arg0, s32 arg1) {
    s32 flags;
    s32 var_r9;
    Unk_DB0E2BAB *temp_r9;
    void *var_r31;

    flags = arg0->unk0x114;
    var_r9 = 1;
    if (!(flags & 2)) {
        var_r9 = 0;
    }
    if (arg1 != var_r9) {
        if (arg1 != 0) {
            arg0->unk0x114 = flags | 2;
        } else {
            arg0->unk0x114 = flags & QB_UNKNOWN_0xFFFFFFFD;
        }
        var_r31 = arg0->unk0x110;
        if (var_r31 != NULL) {
            do {
                temp_r9 = ((Unk_C8FEE62D *)var_r31)->unk0x18;
                ((s32 (*)(void *, s32))temp_r9->unk0x44)(var_r31 + temp_r9->unk0x40, arg1);
                var_r31 = ((Unk_C8FEE62D *)var_r31)->unk0x10;
            } while (var_r31 != NULL);
        }
    }
}
