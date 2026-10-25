// range 0x80070D40-0x80070DB0 (0x70). Byte-identical.
// Identification: linked-list unlink keyed off the self->4 flag. Sibling of
// fn_80070D20 (the head-swap): picks one of two list heads
// (lbl_803015EC vs lbl_803015E8) from the 0x100 flag bit; if self is the
// head, replaces it with self->0; otherwise walks the list
// (node = node->0) until node->0 is null or equals self, then unlinks
// node->next (node->0 = node->0->0).
//
// Matching key: the initial `node == self` test must be written as
// `if (*head == self)` FIRST and `node = *head` assigned after — ngccc then
// CSEs the head load into r0 for the compare and copies r0->r11 at the
// while-loop entry (`or. r11,r0,r0; b check`), and the unlink reads
// self->0 from r3. Reading node once and reusing it (or using a ternary
// head select) makes ngccc keep node in r11 throughout (11/26); the
// if/else head select + CSE compare form is what hits 28/28.
#include "types.h"
#include "structs.h"
extern char lbl_803015EC[];
extern char lbl_803015E8[];
void fn_80070D40(CStruct *self) {
    void **head;
    void *node;
    s32 flag = self->unk0x4;
    if (flag & 0x100)
        head = (void **)lbl_803015EC;
    else
        head = (void **)lbl_803015E8;
    if (*head == self) {
        *head = *(void **)self;
        return;
    }
    node = *head;
    while (node != 0 && *(void **)node != 0 && *(void **)node != self)
        node = *(void **)node;
    {
        void *next = *(void **)node;
        *(void **)node = *(void **)next;
    }
}
