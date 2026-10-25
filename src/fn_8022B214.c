// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022B214-0x8022B2A8 (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_8000F320(void *);
void fn_8021B4C0(void *);
void fn_8000A578(void *, void *);
void fn_8000F2F8(void *, void *);
extern char lbl_802FFE98[];
#include "structs.h"
s32 fn_8021A850(s32);
s32 fn_80009C84(s32);
s32 fn_80219668(void *);
extern s32 lbl_80303148;
bool fn_8022B214(Unk_31DE137E *arg0) {
    s32 temp_r28;
    s32 temp_r29;
    Unk_FFAD6788 *temp_r3;

    temp_r28 = lbl_80303148;
    if (fn_80219668(arg0) != 0) {
        fn_8021B4C0(arg0);
        temp_r3 = *(void **)lbl_802FFE98;
        fn_8000F2F8(temp_r3, temp_r3->unk0x134);
        temp_r29 = fn_8021A850(arg0);
        fn_8000F320(*(void **)lbl_802FFE98);
        if (temp_r29 == 0) {
            return false;
        }
        if (fn_80009C84(arg0->unk0xFC) == 0) {
            fn_8000A578((void *)(temp_r28 + 8), (void *)arg0->unk0xFC);
        }
    }
    return true;
}
