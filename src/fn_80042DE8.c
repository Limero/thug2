// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80042DE8-0x80042E68 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_802FFE98[];
void fn_8000F2F8(void *arg0, s32 arg1);
Unk_D4A84CA9 *Mem_Alloc2(s32 arg0);
Unk_D4A84CA9 *fn_80050178(Unk_D4A84CA9 *arg0);
void fn_8000F320(void *arg0);
void fn_800438E8(void *arg0, s32 arg1);
void fn_80043800(void *arg0, s32 arg1, s32 arg2);
void CTextElement_AttachBlurEffect(Unk_D469C2FD *arg0) {
    Unk_D4A84CA9 *obj;
    register s32 g __asm__("r3");

    if (arg0->unk0x1A8 == NULL) {
        fn_800438E8(arg0, 0);
        fn_8000F2F8(*(Unk_89783F6B **)lbl_802FFE98, (*(Unk_89783F6B **)lbl_802FFE98)->unk0x124);
        obj = fn_80050178(Mem_Alloc2(0x4C0));
        g = *(s32 *)lbl_802FFE98;
        arg0->unk0x1A8 = (s32)obj;
        obj->unk0x4B8 = arg0->unk0xC8;
        fn_8000F320((void *)g);
        fn_80043800(arg0, 0x11, 0);
    }
}
