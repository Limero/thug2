// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005F688-0x8005F70C (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_8005F5B8(void *, void *);
#include "structs.h"
s32 fn_8000F2F8(s32, s32);
s32 Mem_Alloc_3(s32);
void fn_8000F320(s32);
extern char lbl_802FFE98[];
void fn_8005F688(Unk_C7387A53 *arg0, s32 arg1) {
    s32 temp_r29;
    Unk_89783F6B *temp_r3;

    temp_r29 = fn_8005F550();
    if ((s32) arg0->unk0xC == 0) {
        temp_r3 = *(void **)&lbl_802FFE98;
        fn_8000F2F8(temp_r3, temp_r3->unk0x124);
        arg0->unk0xC = Mem_Alloc_3(temp_r29 * 4);
        fn_8000F320(*(void **)&lbl_802FFE98);
        fn_8005F5B8(arg0, arg0->unk0xC);
    }
    memcpy(arg1, arg0->unk0xC, temp_r29 * 4);
}
