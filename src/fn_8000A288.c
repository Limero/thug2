// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000A288-0x8000A37C (244B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_8028FFB8[];
void Mem_Free(void *);
void fn_8000A3DC(Unk_C8FEE62D *);
void fn_8000A0A8(Unk_C8FEE62D *);
void fn_8000A288(Unk_C8FEE62D *self, s32 flag) {
    s32 count;
    Unk_C8FEE62D *base0;
    Unk_C8FEE62D *base1;
    register s32 headv __asm__("r28");
    Unk_DB0E2BAB *node;

    base0 = (Unk_C8FEE62D *)((char *)self + 0xC);
    headv = (s32)base0;
loop_1:
    node = (Unk_DB0E2BAB *)((Unk_DB0E2BAB *)headv)->unk0xC;
    count = 0;
    if (node->unk0x4 == -1) {
        node = NULL;
    }
    if (node == NULL) {
        base1 = (Unk_C8FEE62D *)((char *)self + 0x24);
    } else {
        base1 = (Unk_C8FEE62D *)((char *)self + 0x24);
        do {
            node = (Unk_DB0E2BAB *)node->unk0xC;
            count += 1;
            if (node->unk0x4 == -1) {
                node = NULL;
            }
        } while (node != NULL);
    }
    if (count != 0) {
        fn_8000A3DC(self);
        goto loop_1;
    }
    fn_8000A0A8(self);
    base1->unk0x14 = lbl_8028FFB8;
    *(s32 *)(*(s32 *)((char *)base1 + 0x10) + 0xC) = base1->unk0xC;
    *(s32 *)(*(s32 *)((char *)base1 + 0xC) + 0x10) = base1->unk0x10;
    base1->unk0xC = base1;
    base1->unk0x10 = base1;
    base0->unk0x14 = lbl_8028FFB8;
    *(s32 *)(*(s32 *)((char *)base0 + 0x10) + 0xC) = base0->unk0xC;
    *(s32 *)(*(s32 *)((char *)base0 + 0xC) + 0x10) = base0->unk0x10;
    base0->unk0xC = base0;
    base0->unk0x10 = base0;
    if (flag & 1) {
        Mem_Free(self);
    }
}
