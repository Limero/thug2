// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8017FB44-0x8017FC8C (328B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_80305EAC;
void *fn_80182F98(CStruct *, s32);
void *fn_8017471C(void *, s32);
void *GetChecksum_3(Unk_6A70655D *, s32);
void fn_801805DC(Unk_911C30D6 *);
void fn_801808C8(void *, s32);
void fn_80181014(Unk_667BA59C *, s32, f32);

void fn_8017FB44(Unk_F515CE8D *arg0, s32 arg1) {
    void *base;
    void *entry;
    Unk_C7387A53 *found;
    s32 i;
    s32 n;

    if ((s32)arg0->unk0x68 > 0) {
        if (*(u8 *)((char *)fn_80182F98((char *)arg0 + 0x54, arg0->unk0x68 - 1) + 0x1C) != 0) {
            n = 0;
            i = arg0->unk0x68 - 1;
            while (i > 0) {
                if (*(s32 *)((char *)fn_80182F98((char *)arg0 + 0x54, i) + 0x18) & 2) {
                    break;
                }
                n += 1;
                i -= 1;
            }
            if ((n <= 0xA)
                && (((*(s32 *)((char *)fn_80182F98((char *)arg0 + 0x54, arg0->unk0x68 - 1) + 0x18) & 2))
                    || (*(s32 *)((char *)fn_80182F98((char *)arg0 + 0x54, arg0->unk0x68 - 1)) <= 0x4E20))
                && (((found = GetChecksum_3(fn_8017471C(lbl_80305EAC, (s32)arg0->unk0xC),
                                         QB_SKATERADJUSTPHYSICS))
                     == NULL)
                    || (found->unk0x20 == 0))) {
                entry = fn_80182F98((char *)arg0 + 0x54, arg0->unk0x68 - 1);
                *(s32 *)entry += arg1;
                fn_801805DC(arg0);
                fn_801808C8(arg0, 0);
                arg0->unk0x14 = 0;
                fn_80181014(arg0, arg0->unk0x18, arg0->unk0x6C);
            }
        }
    }
}
