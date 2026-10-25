// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80093F48-0x80094010 (200B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_80301820[];
void fn_80099460(void *, s32);
void Mem_Free(void *);
void fn_80093F48(CStruct *arg0, s32 arg1) {
    s32 head;
    s32 *slot;
    CStruct *node;
    s32 next;

    if (arg0->unk0x0 & 1) {
        if (arg0->unk0x54 != 0) {
            fn_80099460((void *)arg0->unk0x54, 3);
            arg0->unk0x54 = 0;
        }
        if (arg0->unk0x48 != 0) {
            Mem_Free((void *)arg0->unk0x48);
            arg0->unk0x48 = 0;
        }
    }
    head = *(s32 *)lbl_80301820;
    slot = (s32 *)lbl_80301820;
    if (head != 0) {
        if (head == (s32)arg0) {
            *(s32 *)lbl_80301820 = arg0->unk0x6C;
        } else {
            do {
                node = (CStruct *)*slot;
                next = node->unk0x6C;
                slot = (s32 *)&node->unk0x6C;
                if (next == 0) break;
                if (next == (s32)arg0) {
                    node->unk0x6C = arg0->unk0x6C;
                    break;
                }
            } while (1);
        }
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
