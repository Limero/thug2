// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802590F8-0x80259194 (156B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_803CA340;

void fn_80257CC4(void *dst, s32 n);   /* zero-fill(dst,n), 2-arg */
void fn_8024EBD8(void *heap, s32 * ptr);

void Vtable0x8030804C_m21(Unk_C8FEE62D *arg0) {
    s32 lblv;
    void *sub;

    if (arg0 != NULL) {
        sub = *((void * *)&arg0->unk0x8);
        if (sub != NULL) {
            void *data;
            data = *(void **)sub;
            if (data != NULL) {
                lblv = lbl_803CA340;
                fn_8024EBD8(lblv, data);
            }
            if (*(void **)((char *)*((void * *)&arg0->unk0x8) + (s32)0x4) != NULL) {
                lblv = lbl_803CA340;
                fn_8024EBD8(lblv, *(void **)((char *)*((void * *)&arg0->unk0x8) + (s32)0x4));
            }
            lblv = lbl_803CA340;
            fn_8024EBD8(lblv, *((void * *)&arg0->unk0x8));
        }
        if (*((void * *)&arg0->unk0x18) != NULL) {
            lblv = lbl_803CA340;
            fn_8024EBD8(lblv, *((void * *)&arg0->unk0x18));
        }
        fn_80257CC4(arg0, 0x24);
        lblv = lbl_803CA340;
        fn_8024EBD8(lblv, arg0);
    }
}
