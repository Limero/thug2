// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021F500-0x8021F5C8 (200B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802A83F8[];
extern void *fn_8021D454(s32 arg0, CStruct * arg1, s32 arg2);
extern void *fn_8021D4E8(s32 arg0, CStruct * arg1, s32 arg2);
extern s32 GetChecksum_3(Unk_6A70655D * arg0, s32 arg1);
extern void fn_80180390(Unk_F515CE8D * arg0);

void fn_8021F500(s32 arg0) {
    s32 sp8[3];
    register s32 *itv __asm__("r4");
    register s32 *it __asm__("r28");
    s32 temp_r9;
    s32 temp_r3;
    s32 t;
    CScript *var_r3;

    itv = &sp8[0];
    it = itv;
    itv[2] = (s32)lbl_802A83F8;
    itv[1] = 0;
    var_r3 = fn_8021D454(arg0, itv, 1);
    if (var_r3 != NULL) {
        do {
            temp_r3 = var_r3->unk0x1D8;
            temp_r9 = var_r3->unk0x18;
            var_r3->unk0x20 = 0;
            var_r3->unk0x38 = 0;
            var_r3->unk0x1D8 = temp_r3 & QB_UNKNOWN_0xFFFDFEFF;
            var_r3->unk0x24 = 0;
            if ((temp_r9 != 0) &&
                ((t = *(s32 *)((char *)GetChecksum_3(temp_r9, QB_SKATERSCORE) + (s32)0x1C)) != 0)) {
                fn_80180390(t);
            }
            var_r3 = fn_8021D4E8(arg0, (void *)&sp8[0], 1);
        } while (var_r3 != NULL);
    }
    it[2] = (s32)lbl_802A83F8;
}
