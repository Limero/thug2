// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016C9B8-0x8016CA58 (160B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 lbl_802FFE54;
extern char lbl_802FFE98[];
extern void fn_8000F2F8(Unk_9F352E7C *arg0, s32 arg1);
extern void fn_8016CA58(Unk_C7387A53 *arg0);
extern void *Mem_NewZero(s32 size);
extern void *fn_8019E770(Unk_361D6392 *arg0, s32 arg1);
extern void fn_8019EB40(Unk_1ECA8143 *arg0, CStruct *arg1);
extern void fn_8000F320(Unk_F12C5E01 *self);
void fn_8016C9B8(Unk_C7387A53 *arg0, Unk_1ECA8143 *arg1) {
    Unk_C7387A53 *temp_r3;
    Unk_9994C3F5 *temp_r3_2;
    void *temp_r0;

    if (lbl_802FFE54 != 0) {
        temp_r3 = *(void **)&lbl_802FFE98;
        fn_8000F2F8(temp_r3, temp_r3->unk0x178);
    } else {
        temp_r3_2 = *(void **)&lbl_802FFE98;
        fn_8000F2F8(temp_r3_2, temp_r3_2->unk0x11C);
    }
    if (arg0->unk0x58 != 0) {
        fn_8016CA58(arg0);
    }
    temp_r0 = fn_8019E770(Mem_NewZero(0x140), arg0->unk0x54);
    arg0->unk0x58 = (s32) temp_r0;
    fn_8019EB40(temp_r0, arg1);
    fn_8000F320(*(void **)&lbl_802FFE98);
}
