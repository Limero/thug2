// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80254C8C-0x80254CEC (96B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_803CA340;
void fn_8024EBD8(void *heap, s32 * ptr);
void fn_80257CC4(void *dst, s32 size);

void fn_80254C8C(CStruct *arg0) {
    s32 t;

    if (arg0 != NULL) {
        t = arg0->unk0x8;
        if (t != 0) {
            s32 lblv;
            lblv = lbl_803CA340;
            fn_8024EBD8((void *)lblv, (void *)t);
        }
        t = arg0->unk0xC;
        if (t != 0) {
            s32 lblv;
            lblv = lbl_803CA340;
            fn_8024EBD8((void *)lblv, (void *)t);
        }
        fn_80257CC4(arg0, 0x14);
    }
}
