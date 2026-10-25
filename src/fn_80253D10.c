// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80253D10-0x80253DBC (172B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_803CA340;
void fn_80257CC4(void *dst, s32 size);
void fn_8024EBD8(void *heap, s32 * ptr);
void *fn_8024ECD0(CStruct * heap, void *ptr, s32 size);

void fn_80253D10(Unk_C7387A53 *arg0) {
    CStruct *node;
    void *next;
    s32 overflow;

    node = *((void * *)&arg0->unk0x40);
    while (node != NULL) {
        void *data = *((void * *)&node->unk0x0);
        s32 lblv;
        lblv = lbl_803CA340;
        next = *((void * *)&node->unk0x4);
        fn_8024EBD8(lblv, data);
        fn_80257CC4(node, 8);
        {
            register s32 t __asm__("r3");
            register s32 n __asm__("r4");
            t = lbl_803CA340;
            __asm__("mr %0, %1" : "=r"(n) : "r"((s32)node), "r"(t));
            fn_8024EBD8(t, (void *)n);
        }
        node = next;
    }
    overflow = arg0->unk0x3C;
    if (overflow != 0) {
        s32 lblv;
        lblv = lbl_803CA340;
        arg0->unk0x30 = (s32)fn_8024ECD0(lblv, *((void * *)&arg0->unk0x30), overflow + arg0->unk0x38);
        arg0->unk0x38 = arg0->unk0x38 + arg0->unk0x3C;
        arg0->unk0x3C = 0;
    }
    arg0->unk0x34 = 0;
    *((void * *)&arg0->unk0x40) = NULL;
}
