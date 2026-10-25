// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80131DC0-0x80131E50 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
s32 fn_8000F2F8(s32, s32);
s32 fn_800A3D68(s32);
void fn_800A3E28(s32, s32, s32, s32, s32, s32, s32);
void fn_8000F320(s32);
extern void *lbl_802FFE98;
void fn_80131DC0(Unk_FFAD6788 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, CStruct *arg5) {
    Unk_89783F6B *temp_r3;

    temp_r3 = lbl_802FFE98;
    fn_8000F2F8(temp_r3, temp_r3->unk0x124);
    if (arg0->unk0xE0 == 0) {
        arg0->unk0xE0 = fn_800A3D68(Mem_Alloc2(0x14));
    }
    fn_800A3E28(arg0->unk0xE0, arg0, arg1, arg2, arg3, arg4, arg5);
    fn_8000F320(lbl_802FFE98);
}
