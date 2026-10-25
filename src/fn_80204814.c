// Promoted from src/wip — byte-identical match
// family=proto range=0x80204814-0x80204878 size=100B
#include "types.h"
#include "structs.h"
extern void fn_80204928(Unk_DB0E2BAB *);
extern void fn_80204E30(Unk_23A2CE55 *);
extern void fn_80204DF4(void *);
void fn_80204814(Unk_FFAD6788 *arg0) {
    if (((s32) *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x1C) + 0x340) != 0) && ((s32) arg0->unk0xC8 == 0) && ((s32) *((s32 *)&arg0->unk0x28) != 0)) {
        fn_80204928(arg0);
        fn_80204E30(arg0);
        fn_80204DF4(arg0);
    }
}