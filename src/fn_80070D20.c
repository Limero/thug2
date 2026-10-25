// range 0x80070D20-0x80070D40 (0x20). Byte-identical.
// Identification: list-head swap + flag set — stores the current head
// (lbl_803015EC) into self+0, makes self the new head, and sets the
// 0x100 flag bit in self+4. Sibling fn_80070D40 (the linked-list unlink)
// reads the same flag/heads.
//
// Matching key: the `|= 0x100` read of self->4 must be materialized as a
// load at the TOP of the function (before the stores) with the store last;
// writing the |= statement inline lets ngccc emit the self->4 load after
// the other stores. Splitting into `s32 v = self->4; ...; self->4 = v|0x100;`
// with the load first is what gives want's hoisted-load/sunk-store (8/8).
#include "types.h"
#include "structs.h"
extern char lbl_803015EC[];
void fn_80070D20(CStruct *self) {
    s32 v = self->unk0x4;
    *((void * *)&self->unk0x0) = *(void **)lbl_803015EC;
    *(void **)lbl_803015EC = self;
    self->unk0x4 = v | 0x100;
}
