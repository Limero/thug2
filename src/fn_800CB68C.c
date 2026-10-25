// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CB68C-0x800CB748 (188B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

/* want: lha r3, 8(r9) then add r3,r31,r3 -- the +0x8 member of the vtable-ish
   node is a SIGNED HALFWORD, not s32.  File-local view (Unk_C8FEE62D is shared
   and its 0x8 is s32, same story as fn_800DBAE4's bag). */
typedef struct CbVt {
    char pad0x0[0x4];
    s32 unk0x4;
    s16 unk0x8;
    char pad0xA[0x2];
    s32 unk0xC;
} CbVt;

s32 fn_80128E34(CStruct *, void *, void *, void *);
bool fn_800CB68C(Unk_C7387A53 *arg0, s32 arg1, CStruct *arg2) {
    s32 sp8;
    CStruct *temp_r9;
    void *var_r31;
    register CStruct *var_r9 __asm__("r9");
    register s32 t4 __asm__("r11");

    var_r9 = arg0->unk0x38;
    sp8 = 0;
    t4 = var_r9->unk0x4;
    if (t4 == -1) {
        var_r9 = NULL;
    }
    var_r31 = var_r9;
    fn_80128E34(arg2, QB_SUBSETID, &sp8, 0);
    if (var_r31 != NULL) {
loop_3:
        if ((s32) ((Unk_C8FEE62D *)var_r31)->unk0x30 == sp8) {
            if (var_r31 != NULL) {
                temp_r9 = ((Unk_C8FEE62D *)var_r31)->unk0x14;
                ((s32 (*)(void *, s32))temp_r9->unk0xC)(var_r31 + ((CbVt *)temp_r9)->unk0x8, 3);
            }
        } else {
            var_r9 = ((Unk_C8FEE62D *)var_r31)->unk0xC;
            if ((s32) var_r9->unk0x4 == -1) {
                var_r9 = NULL;
            }
            var_r31 = var_r9;
            if (var_r31 != NULL) {
                goto loop_3;
            }
        }
    }
    return true;
}
