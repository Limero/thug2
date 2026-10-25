// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801205D0-0x8012063C (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "mem.h"

typedef struct Obj {
    char pad[0x11C];
    s32 unk0x11C;
    char pad2[0x3C];
    s32 unk0x15C;
} Obj;

extern char lbl_802FFE98[];
void fn_8000F2F8(void *, s32);
void fn_80010D94(s32, s32);
void fn_80010E78(s32);
void fn_8000F320(void *);

s32 fn_801205D0(s32 arg0) {
    Obj *o = *(Obj **)&lbl_802FFE98;
    s32 r;

    fn_8000F2F8(o, o->unk0x15C);
    fn_80010D94((*(Obj **)&lbl_802FFE98)->unk0x11C, 0x20);
    r = Mem_Alloc(arg0);
    fn_80010E78((*(Obj **)&lbl_802FFE98)->unk0x11C);
    fn_8000F320(*(void **)&lbl_802FFE98);
    return r;
}
