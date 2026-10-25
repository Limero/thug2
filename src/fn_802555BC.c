// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802555BC-0x802556C4 (264B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_803CA340;
void fn_8024EBD8(void *heap, s32 * ptr);
void fn_80257CC4(void *dst, s32 size);

void fn_802555BC(Unk_DB0E2BAB *arg0) {
    s32 t;
    s32 lblv;

    if (arg0->unk0x30 != 0) {
        t = arg0->unk0x20;
        if (t != 0) {
            lblv = lbl_803CA340;
            fn_8024EBD8((void *)lblv, (void *)t);
        }
        t = arg0->unk0x8;
        if (t != 0) {
            lblv = lbl_803CA340;
            fn_8024EBD8((void *)lblv, (void *)t);
        }
        if (arg0->unk0x24 != NULL) {
            lblv = lbl_803CA340;
            fn_8024EBD8((void *)lblv, *(void **)arg0->unk0x24);
            lblv = lbl_803CA340;
            fn_8024EBD8((void *)lblv, *(void **)((char *)arg0->unk0x24 + (s32)4));
            lblv = lbl_803CA340;
            fn_8024EBD8((void *)lblv, *(void **)((char *)arg0->unk0x24 + (s32)8));
            lblv = lbl_803CA340;
            fn_8024EBD8((void *)lblv, *(void **)((char *)arg0->unk0x24 + (s32)0xC));
            fn_80257CC4(*((void * *)&arg0->unk0x24), 0x18);
            lblv = lbl_803CA340;
            fn_8024EBD8((void *)lblv, (void *)arg0->unk0x24);
        }
        if (arg0->unk0x28 != NULL) {
            lblv = lbl_803CA340;
            fn_8024EBD8((void *)lblv, *(void **)arg0->unk0x28);
            lblv = lbl_803CA340;
            fn_8024EBD8((void *)lblv, *(void **)((char *)arg0->unk0x28 + (s32)4));
            fn_80257CC4(*((void * *)&arg0->unk0x28), 0x10);
            lblv = lbl_803CA340;
            fn_8024EBD8((void *)lblv, (void *)arg0->unk0x28);
        }
        fn_80257CC4(arg0, 0x34);
    }
}
