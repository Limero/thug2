// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012E018-0x8012E0AC (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void * Mem_Alloc_3(u32 size);
extern char lbl_802FFE98[];
extern char lbl_803032B8[];
#include "structs.h"
s32 fn_8000F2F8(s32, s32);
void fn_8000F320(Unk_F12C5E01 *self);
void fn_8012E018(s32 arg0) {
    s32 var_ctr;
    Unk_C7387A53 *temp_r3;
    Unk_C7387A53 *temp_r3_2;
    void *var_r9;

    if (arg0 != 0) {
        temp_r3 = *(void **)lbl_802FFE98;
        fn_8000F2F8(temp_r3, temp_r3->unk0x178);
    } else {
        temp_r3_2 = *(s32 *)lbl_802FFE98;
        fn_8000F2F8(temp_r3_2, temp_r3_2->unk0x12C);
    }
    *(void **)lbl_803032B8 = Mem_Alloc_3(0xC000);
    fn_8000F320(*(s32 *)(s32)lbl_802FFE98);
    var_r9 = *(void **)lbl_803032B8;
    var_ctr = 0x1000;
    do {
        ((CStruct *)var_r9)->unk0x0 = 0;
        ((CStruct *)var_r9)->unk0x4 = 0;
        ((CStruct *)var_r9)->unk0x8 = 0;
        var_r9 += 0xC;
        var_ctr -= 1;
    } while (var_ctr != 0);
}