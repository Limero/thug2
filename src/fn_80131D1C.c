// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80131D1C-0x80131DC0 (164B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_802FFE98[];
extern void fn_8000F2F8(void *, s32);
extern void fn_8000F320(void *);
extern s32 Mem_Alloc2(s32);
extern s32 fn_800A3D68(void);
extern void fn_800A4B40(s32, void *);
extern void fn_800A4078(s32, void *, s32);
extern void fn_800A456C(s32);
extern s32 fn_800A4AB4(s32, void *);
void fn_80131D1C(Unk_FFAD6788 *arg0, CStruct *arg1, s32 arg2) {
    s32 v;

    fn_8000F2F8(*(void **)&lbl_802FFE98, *(s32 *)((char *)*(void **)&lbl_802FFE98 + 0x124));
    v = arg0->unk0xE0;
    if (v == 0) {
        Mem_Alloc2(0x14);
        arg0->unk0xE0 = fn_800A3D68();
    } else {
        fn_800A4B40(v, arg0);
    }
    fn_800A4078(arg0->unk0xE0, arg1, (arg2 != 0) ? 1 : 0);
    fn_800A456C(arg0->unk0xE0);
    fn_800A4AB4(arg0->unk0xE0, arg0);
    fn_8000F320(*(void **)&lbl_802FFE98);
}
