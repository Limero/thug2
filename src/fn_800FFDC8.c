// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800FFDC8-0x800FFE40 (120B). Byte-identical.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_8029C2E0[];
extern void fn_80102350(Unk_6AC87105 *, Unk_6AC87105 *);
void fn_800FFE40(Unk_377B7C81 * arg0, void *arg1);

void *fn_800FFDC8(Unk_9E1F72FD *arg0) {
    Unk_9988AEC4 *obj;
    void *argNext;
    obj = Mem_Alloc2(0xC0);
    fn_80102350(obj, arg0);
    argNext = arg0->unk0x8;
    obj->unk0xC = (s32)lbl_8029C2E0;
    obj->unk0xA0 = arg0->unk0xA0;
    obj->unk0xA8 = arg0->unk0xA8;
    obj->unk0xB0 = arg0->unk0xB0;
    obj->unk0xB8 = arg0->unk0xB8;
    fn_800FFE40(obj, argNext);
    return obj;
}