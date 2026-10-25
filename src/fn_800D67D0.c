// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D67D0-0x800D6848 (120B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800A7E30(CStruct *, CStruct *);
s32 fn_800A7F38(void);
s32 fn_800A7F9C(s32 *, Unk_9994C3F5 *, s32);
void fn_800A93E8(void *, s32, s32);
void fn_800D6490(CScript *, s32);
s32 fn_800D64DC(CScript *);
void fn_800D67D0(Unk_6A70655D *arg0, s32 arg1) {
    if (arg0->unk0x110 != 0) {
        fn_800A7E30(*((void * *)&arg0->unk0x110), arg0->unk0xC);
    }
    arg0->unk0x110 = fn_800A7F9C((s32 *)fn_800A7F38(), arg0->unk0xC, arg1);
    fn_800D6490(arg0, arg0->unk0xC);
    fn_800A93E8((void *)fn_800D64DC(arg0), arg1, arg0->unk0xC + 0x58);
}
