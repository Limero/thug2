// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B4488-0x800B458C (260B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_802FFE98[];
#include "qb_constants.h"
#include "structs.h"
#include "mem.h"
s32 fn_8000F2F8(Unk_9F352E7C *, void *);
s32 fn_800C9780(Unk_31DE137E *);
s32 fn_8005069C(CStruct *, void *);
s32 fn_80010400(void *, void *, void *);
s32 fn_80060934(Unk_C8FEE62D *);
s32 GetChecksum_3(Unk_6A70655D *, s32);
s32 fn_80036968(void *);
s32 fn_800531F4(void);
s32 fn_80050638(s32, s32);
s32 fn_80050720(s32, s32);
s32 fn_800608E8(s32, s32);
s32 fn_8000F320(s32);
void fn_800B4488(Unk_A9B14BE5 *arg0) {
    s32 temp_r27;
    s32 temp_r30;
    s32 temp_r30_2;
    s32 temp_r3;
    Unk_9994C3F5 *temp_r31;
    Unk_9994C3F5 *temp_r3_2;

    if ((arg0->unk0x214 != 0) || (temp_r3 = GetChecksum_3(arg0->unk0xC, QB_SKELETON), arg0->unk0x214 = temp_r3, temp_r3 != 0)) {
        if (fn_80060934(arg0->unk0x210) == 0) {
            temp_r30 = *(s32 *)&lbl_802FFE98;
            fn_8000F2F8(temp_r30, fn_80010400(temp_r30, QB_COLLISION, 1));
            temp_r31 = (Unk_9994C3F5 *)fn_800C9780(arg0->unk0x214);
            temp_r27 = temp_r31->unk0x8;
            fn_80036968(temp_r31);
            temp_r3_2 = (Unk_9994C3F5 *)fn_800531F4();
            if (temp_r3_2 != 0) {
                temp_r3_2->unk0x8 = temp_r3_2->unk0x8 + 1;
            } else {
                temp_r30_2 = fn_80050638(Mem_Alloc2(0xC), 0);
                fn_8005069C((CStruct *)temp_r30_2, (void *)fn_80036968(temp_r31));
                fn_80050720(temp_r30_2, temp_r27);
            }
            fn_800608E8(arg0->unk0x210, (s32)temp_r3_2);
            fn_8000F320(*(s32 *)&lbl_802FFE98);
        }
    }
}
