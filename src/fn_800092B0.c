// Promoted from src/wip — byte-identical match - destructor variant: field at +8, decrement global
// family=dtor range=0x800092B0-0x80009314 size=100B
#include "types.h"
#include "structs.h"
#include "mem.h"
extern s32 lbl_802FFA34;
void fn_800092B0(Unk_9994C3F5 *arg0, s32 arg1) {
    if (*((void * *)&arg0->unk0x8) != NULL) {
        Mem_Free2(*((void * *)&arg0->unk0x8));
        *((void * *)&arg0->unk0x8) = NULL;
    }
    lbl_802FFA34--;
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}