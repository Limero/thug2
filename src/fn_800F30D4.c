// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F30D4-0x800F3160 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
bool fn_800F30D4(Unk_C7387A53 **arg0, Unk_C7387A53 *arg1) {
    Unk_C7387A53 *head;
    Unk_C7387A53 *node;
    head = (Unk_C7387A53 *)arg1->unk0x30;
    if (head == arg1) {
        *arg0 = NULL;
        arg1->unk0x2C = 0;
        arg1->unk0x30 = NULL;
        return true;
    }
    if (*arg0 == arg1) {
        *arg0 = head;
    }
    node = *arg0;
    while (node != NULL) {
        if (node == arg1) {
            ((Unk_C7387A53 *)node->unk0x30)->unk0x2C = node->unk0x2C;
            ((Unk_C7387A53 *)node->unk0x2C)->unk0x30 = node->unk0x30;
            node->unk0x2C = 0;
            node->unk0x30 = 0;
            return true;
        }
        node = (Unk_C7387A53 *)node->unk0x30;
    }
    return false;
}
